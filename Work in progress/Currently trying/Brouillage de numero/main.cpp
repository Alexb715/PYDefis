#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;


map<char, char> NumeroTelephone ={
    {{'2', 'A'}, {'2', 'B'}, {'2', 'C'},
        {'3', 'D'}, {'3', 'E'}, {'3', 'F'},
        {'4', 'G'}, {'4', 'H'}, {'4', 'I'},
        {'5', 'J'}, {'5', 'K'}, {'5', 'L'},
        {'6', 'M'}, {'6', 'N'}, {'6', 'O'},
        {'7', 'P'}, {'7', 'Q'}, {'7', 'R'}, {'7', 'S'},
        {'8', 'T'}, {'8', 'U'}, {'8', 'V'},
        {'9', 'W'}, {'9', 'X'}, {'9', 'Y'}, {'9', 'Z'}}
};


int main(){
    multimap<string,string> num;
    string mot;
    while( cin >> mot ){
        string nums;
        for(auto &c: mot){
            nums+= NumeroTelephone[c];
        }
        num.insert({nums,mot});
    }
   size_t maxn =1; 
    for(auto &c: num){
        maxn = max(maxn,num.count(c.first));
    }
    cout << maxn;
}