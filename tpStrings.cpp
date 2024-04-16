#include <iostream>
using namespace std;

string x,y;

bool stringsEquiv(string a, string b){
    if(a==b){
        return true;
    } else if(a.size() % 2 == 1){
        return false;
    } else {
        int mitad = a.size()/2;
        string a1= a.substr(0, mitad);
        string a2= a.substr(mitad, mitad);

        string b1= b.substr(0, mitad);
        string b2= b.substr(mitad, mitad);

        return((stringsEquiv(a1,b2) and stringsEquiv(a2,b1)) or (stringsEquiv(a1,b1) and stringsEquiv(a2,b2)));
    }
}


int main(){
    ios_base::sync_with_stdio(false);

    cin >> x >> y;
    if(stringsEquiv(x,y)){
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}