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

vector<int> vSub = {8, 6, 7, 4, 5, 1, 3, 2};
vector<int> vDom = {8, 4, 7, 6, 5, 1, 3, 2};

tuple<bool, int> izquierdaDominante(int l, int r){
    int m = (l+r)/2;
    if(l == r-1){
        return(make_tuple((vDom[l]>vDom[r]),(vDom[l]+vDom[r])));
    }
    return(make_tuple((get<1>(izquierdaDominante(l,m))> get<1>(izquierdaDominante(m+1,r)) && get<0>(izquierdaDominante(l,m)) && get<0>(izquierdaDominante(m+1,r))),
    (get<1>(izquierdaDominante(l,m)) + get<1>(izquierdaDominante(m+1,r)))));
}

int main() {
    cout << get<0>(izquierdaDominante(0,vDom.size()-1)) << endl;
}