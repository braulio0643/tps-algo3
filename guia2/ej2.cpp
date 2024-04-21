#include <iostream>
#include <ostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

//vector<int> v = {-5, -4, -1, 2, 4, 7};
vector<int> v = {8, 4, 7, 6, 5, 1, 3, 2};
bool indiceEspejo(int l, int r){
    if(l == r){
        return (v[l] == l);
    }
    int m = (l+r/2);
    if(v[m]< m){
        return indiceEspejo(m, r);
    } else if(v[m]> m){
        return indiceEspejo(l,m);
    } else {
        return true;
    }
}

int main(){
    cout << indiceEspejo(0, v.size()-1) << endl;
}

