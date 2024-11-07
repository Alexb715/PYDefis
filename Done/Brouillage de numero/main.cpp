#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <set>
using namespace std;


map<char, char> NumeroTelephone ={
    {{'A', '2'}, {'B', '2'}, {'C', '2'},
{'D', '3'}, {'E', '3'}, {'F', '3'},
{'G', '4'}, {'H', '4'}, {'I', '4'},
{'J', '5'}, {'K', '5'}, {'L', '5'},
{'M', '6'}, {'N', '6'}, {'O', '6'},
{'P', '7'}, {'Q', '7'}, {'R', '7'}, {'S', '7'},
{'T', '8'}, {'U', '8'}, {'V', '8'},
{'W', '9'}, {'X', '9'}, {'Y', '9'}, {'Z', '9'}}
};


int main(){
   multimap<string,string> numero;
   string mot;
   while(cin >> mot){
        string num;
        for(auto chars : mot){
            num += NumeroTelephone[chars];
        }
        numero.insert({num, mot});
   }
   size_t maxi;
   for(auto it : numero){
        maxi = max(maxi,numero.count(it.first));
   }
   cout << maxi << endl;
    set<string> ans;
   for(auto &elt : numero){

        if(numero.count(elt.first) == maxi){
            ans.insert(elt.first);
        }
   }
   for(auto i : ans){
    cout << i << ","<< " ";
   }
}