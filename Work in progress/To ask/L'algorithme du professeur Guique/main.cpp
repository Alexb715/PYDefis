
#include <iostream>
using namespace std;
int main(){
    //initialiser a, b, c, k et n respectivement à 1, 4, 3, 1 et 0
    int a = 1,b=4,c=4,k=1,n=0;
/*initialiser a, b, c, k et n respectivement à 1, 4, 3, 1 et 0
répéter tant que k est strictement inférieur à 1000-n
    a ← b
    b ← c + a
    c ← -4*c - 3*a - b
    n ← a + b
    augmenter k de 1
fin répéter*/
    while(k< 1000-n){
        auto tmp = a;
        auto tmp2=b;
        a = b;
        b = c + tmp;
        c = -4*c - 3*a - b;
        n = a + b;
        k++;
    }
    cout << a << "\t" << b << "\t" << c;
}