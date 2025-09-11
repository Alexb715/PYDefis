#include <bits/stdc++.h>
using namespace std;

// --- Base64 decoding ---
string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

inline bool is_base64(unsigned char c) {
    return (isalnum(c) || c == '+' || c == '/');
}

vector<unsigned char> base64_decode(string const& encoded) {
    int in_len = encoded.size();
    int i = 0, in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    vector<unsigned char> ret;

    while (in_len-- && (encoded[in_] != '=') && is_base64(encoded[in_])) {
        char_array_4[i++] = encoded[in_]; in_++;
        if (i ==4) {
            for (i = 0; i <4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);
            char_array_3[0] = ( char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
            for (i = 0; i < 3; i++) ret.push_back(char_array_3[i]);
            i = 0;
        }
    }

    if (i) {
        for (int j = i; j <4; j++) char_array_4[j] = 0;
        for (int j = 0; j <4; j++) char_array_4[j] = base64_chars.find(char_array_4[j]);
        char_array_3[0] = ( char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
        for (int j = 0; j < i - 1; j++) ret.push_back(char_array_3[j]);
    }

    return ret;
}

// --- Keystream generator ---
vector<unsigned char> gen_key(uint32_t seed, size_t length) {
    vector<unsigned char> key;
    uint32_t x = seed;
    while (key.size() < length) {
        for (int i = 3; i >= 0; i--)
            key.push_back((x >> (8*i)) & 0xFF);
        x = (uint64_t(65537) * x + 3) % (1ULL << 32);
    }
    key.resize(length);
    return key;
}

int main() {
    string input = "xNHPLk973ymQBNJA0a6cDxMO6ANc5tlFypjSTNEc2U8HvZweQWrfGrLMyArsVMgSOtycGncQ0ODu3d2k/VrV4mfZxPp2I8/+pfPU6Q0GzuBJl8j/l+DZt7lp2e9Ps1X8QAHRw51r08vWh8/HDDucSz6b2Ny+28/U6nlclDlsnNP4qFXdrwrV0uUXnKExmtK3JNLZ5vWk06oKIt6+XjmN9sDRktjlz9m5APrZqw4AVbUCMN2r0ADZlUVs040MiFaKu+Cchv6W7J830MiVYf3VkPLQ05HgEpyzKRnIhiVR0pCzA51h6xPPYiUF0maOX9lumubcLhX9zn5Tx9g6++zIcsKlyH8Yzst4W3idUIlezwPFJ9NPElSHI7bS1QyrvNgP/d/cWzhPndUyPNJWu/LQS+C3zx4mdc5haDjOIaXgxWuLj8g4H0rcbagWzyLc49Q/V3iaLxQJ03mQsM89j1HRKh+gyRBGkpPe"; // ciphertext in Base64
    uint32_t seed = 0x80b4bc5a;

    // 1. Decode Base64
    vector<unsigned char> cipher = base64_decode(input);

    // 2. Generate key
    vector<unsigned char> key = gen_key(seed, cipher.size());

    // 3. XOR to get plaintext
    vector<unsigned char> plain(cipher.size());
    for (size_t i = 0; i < cipher.size(); i++)
        plain[i] = cipher[i] ^ key[i];

    // 4. Print as text
    cout << string(plain.begin(), plain.end()) << "\n";
}
