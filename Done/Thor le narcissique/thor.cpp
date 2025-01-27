#include <string>
#include<unordered_map>
#include<iostream>
using namespace std;
int main(){
    unordered_map<char,int> thor  = {{'t',1},{'h',1},{'o',1},{'r',1}};
    string mot = "";
    uint64_t nombre = 0;
    while(getline(cin,mot)){
        unordered_map<char,int> lettre;
        for(int i = 0; i< mot.size(); i++){
            if(mot[i] == 't' ||mot[i] == 'h' ||mot[i] == 'o' ||mot[i] == 'r'){
                lettre[mot[i]]++;}
        }
        if(lettre == thor){
            nombre++;
        }
    }
    cout << nombre;


}