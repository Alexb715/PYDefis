#include <iostream>
#include <unordered_map>
using namespace std;
int main(){
 string n;
 getline(cin,n);
 int amount = stoi(n);
 unordered_map<string, char> keyValues;
 for(int i = 0; i< amount; i++){
    string code;
    getline(cin,code);
    
    cout << code.size() << endl;

    //keyValues[code] = value;
 }   
    for(auto i : keyValues){
        cout << i.first << " -> " << i.second << endl;
    }
}