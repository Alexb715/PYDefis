// known_phrase_attack_mt.cpp
// g++ -O3 -std=c++17 -march=native -pthread -o known_phrase_attack_mt known_phrase_attack_mt.cpp
//
// Usage:
//  ./known_phrase_attack_mt [--threads N] [--start S] [--end E] <base64_ciphertext> "known phrase"
//
// Notes:
// - start and end are unsigned 64-bit decimal; end is exclusive.
// - default: threads = hardware_concurrency(), start = 0, end = 2^32
// - This program will attempt to brute force; running the full 2^32 on one machine will take a long time.
// - Progress is printed periodically.

#include <bits/stdc++.h>
using namespace std;
using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;
using i64 = int64_t;
static constexpr u64 U32MAX_PLUS1 = (1ULL<<32);

// --- Base64 decode ---
vector<u8> base64_decode(const string &in) {
    static const string b64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    vector<int> T(256, -1);
    for (int i = 0; i < (int)b64_chars.size(); ++i) T[(unsigned char)b64_chars[i]] = i;

    vector<u8> out;
    out.reserve((in.size()*3)/4);
    int val=0, valb=-8;
    for (char c : in) {
        if (isspace((unsigned char)c)) continue;
        if (c == '=') break;
        int d = (c>=0 && c<256) ? T[(unsigned char)c] : -1;
        if (d == -1) continue;
        val = (val<<6) + d;
        valb += 6;
        if (valb >= 0) {
            out.push_back((u8)((val>>valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

// generate keystream bytes into an existing buffer (must be sized >= needed)
// keystream derived as in problem statement (big-endian byte order for each 32-bit x)
inline void gen_keystream_into(u32 seed, u8 *out, size_t needed) {
    u32 x = seed;
    size_t pos = 0;
    while (pos < needed) {
        // 4 bytes big-endian
        if (pos < needed) out[pos++] = (u8)((x >> 24) & 0xFF);
        if (pos < needed) out[pos++] = (u8)((x >> 16) & 0xFF);
        if (pos < needed) out[pos++] = (u8)((x >> 8) & 0xFF);
        if (pos < needed) out[pos++] = (u8)(x & 0xFF);
        x = (u32)(((uint64_t)65537 * x + 3) & 0xFFFFFFFFu);
    }
}

// Thread worker
struct Worker {
    const vector<u8> *cbytes;      // ciphertext bytes
    const string *phrase;          // known phrase (latin1 bytes ideally)
    u64 start_seed;
    u64 end_seed;                  // exclusive
    atomic<u64> *global_count;     // optional for progress
    mutex *out_mtx;
    vector<pair<u32,string>> *found; // shared vector for discovered seeds (protected by out_mtx)
    bool verbose;
    Worker(const vector<u8>* c, const string* p, u64 s, u64 e, atomic<u64>* gc,
           mutex* m, vector<pair<u32,string>>* f, bool v)
        : cbytes(c), phrase(p), start_seed(s), end_seed(e), global_count(gc), out_mtx(m), found(f), verbose(v) {}
    void operator()() {
        const size_t clen = cbytes->size();
        if (clen == 0) return;
        vector<u8> ks(clen);
        string plaintext;
        plaintext.resize(clen);
        const size_t phrase_len = phrase->size();
        // We'll do a simple search using std::string::find on the constructed plaintext.
        // For better performance one can implement KMP on bytes; std::string::find is OK and highly optimized.
        const u64 progress_interval = 1'000'000; // update after this many seeds
        u64 local_seen = 0;
        for (u64 s = start_seed; s < end_seed; ++s) {
            gen_keystream_into((u32)s, ks.data(), clen);
            // decrypt in-place into plaintext string (avoid allocating)
            for (size_t i = 0; i < clen; ++i) plaintext[i] = static_cast<char>((*cbytes)[i] ^ ks[i]);
            // search
            if (plaintext.find(*phrase) != string::npos) {
                // lock and record
                lock_guard<mutex> lg(*out_mtx);
                found->emplace_back((u32)s, plaintext.substr(0, min<size_t>(1024, plaintext.size()))); // store a snippet (first 1k) to avoid enormous memory
                // also print immediate notification
                cerr << "FOUND seed = " << s << " (0x" << hex << setw(8) << setfill('0') << (u32)s << dec << ")\n";
                cerr << " -> plaintext snippet (first 1k bytes):\n";
                // print snippet as-is (may contain non-printable)
                string snippet = plaintext.substr(0, min<size_t>(1024, plaintext.size()));
                // replace non-printable with dot for cleaner display
                for (char &ch : snippet) if ((unsigned char)ch < 32 || (unsigned char)ch > 126) ch = '.';
                cerr << snippet << "\n";
            }
            ++local_seen;
            if (global_count && (local_seen % progress_interval == 0)) {
                global_count->fetch_add(progress_interval, memory_order_relaxed);
                if (verbose) {
                    u64 total_done = global_count->load();
                    cerr << "Thread " << this_thread::get_id() << " progressed, total seeds tested: " << total_done << "\n";
                }
            }
        }
        // add remainder progress
        if (global_count && (local_seen % progress_interval != 0)) {
            global_count->fetch_add(local_seen % progress_interval, memory_order_relaxed);
        }
    }
};

void print_usage(const char* prog) {
    cerr << "Usage:\n"
         << prog << " [--threads N] [--start S] [--end E] <base64_ciphertext> \"known phrase\"\n\n"
         << "Defaults:\n"
         << "  threads = hardware_concurrency()\n"
         << "  start = 0\n"
         << "  end = 2^32 (exclusive)\n\n"
         << "Examples:\n"
         << "  " << prog << " <base64> \"Le Prostetnic Vogon\"\n"
         << "  " << prog << " --threads 8 --start 0 --end 100000000 <base64> \"phrase\"\n";
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc < 3) {
        print_usage(argv[0]);
        return 1;
    }

    // parse options
    int argi = 1;
    unsigned threads = 0;
    u64 start = 0;
    u64 end = U32MAX_PLUS1;
    bool verbose = true;

    while (argi < argc && strncmp(argv[argi], "--", 2) == 0) {
        string opt = argv[argi];
        if (opt == "--threads") {
            if (argi+1 >= argc) { cerr << "Missing value for --threads\n"; return 1; }
            threads = (unsigned)stoul(argv[++argi]);
        } else if (opt == "--start") {
            if (argi+1 >= argc) { cerr << "Missing value for --start\n"; return 1; }
            start = stoull(argv[++argi]);
        } else if (opt == "--end") {
            if (argi+1 >= argc) { cerr << "Missing value for --end\n"; return 1; }
            end = stoull(argv[++argi]);
        } else if (opt == "--quiet") {
            verbose = false;
        } else {
            cerr << "Unknown option: " << opt << "\n";
            print_usage(argv[0]);
            return 1;
        }
        ++argi;
    }

    if (argi + 2 != argc) {
        print_usage(argv[0]);
        return 1;
    }

    string b64 = argv[argi++];
    string phrase = argv[argi++];

    // decode ciphertext
    vector<u8> cbytes = base64_decode(b64);
    if (cbytes.empty()) {
        cerr << "Error: invalid or empty base64 ciphertext\n";
        return 1;
    }
    if (phrase.empty()) {
        cerr << "Error: empty phrase\n";
        return 1;
    }

    // Convert phrase string to bytes as-is (user should provide latin1 encoding if necessary).
    // If phrase contains UTF-8 multi-byte sequences but the original plaintext was latin1,
    // the match will fail. If you need latin1, pass a file with raw latin1 bytes instead.
    // For now we treat the provided phrase as the byte sequence to search for.
    // (std::string is fine for this.)
    size_t clen = cbytes.size();
    cerr << "Ciphertext length = " << clen << " bytes\n";
    cerr << "Searching for phrase of length " << phrase.size() << " bytes\n";
    cerr << "Seed range: [" << start << ", " << end << ")  (end exclusive)\n";

    if (start >= end) {
        cerr << "Error: start >= end\n";
        return 1;
    }
    if (end > U32MAX_PLUS1) {
        cerr << "Warning: end truncated to 2^32\n";
        end = U32MAX_PLUS1;
    }

    if (threads == 0) {
        threads = thread::hardware_concurrency();
        if (threads == 0) threads = 4;
    }

    // split range among threads
    u64 total = end - start;
    u64 base_chunk = total / threads;
    u64 remainder = total % threads;

    vector<thread> tlist;
    mutex out_mtx;
    vector<pair<u32,string>> found;
    atomic<u64> global_count(0);

    u64 cur = start;
    for (unsigned i = 0; i < threads; ++i) {
        u64 chunk = base_chunk + (i < remainder ? 1 : 0);
        u64 s = cur;
        u64 e = s + chunk;
        cur = e;
        if (s >= e) {
            // no work for this thread
            continue;
        }
        Worker w(&cbytes, &phrase, s, e, &global_count, &out_mtx, &found, verbose);
        tlist.emplace_back(w);
    }

    // join
    for (auto &th : tlist) th.join();

    // report results
    if (found.empty()) {
        cerr << "No seeds found in the given range.\n";
    } else {
        cerr << "Found " << found.size() << " seed(s):\n";
        for (auto &pr : found) {
            u32 s = pr.first;
            cerr << s << " (0x" << hex << setw(8) << setfill('0') << s << dec << ")\n";
        }
    }
    cerr << "Total seeds tested (approx): " << global_count.load() << "\n";
    return 0;
}
