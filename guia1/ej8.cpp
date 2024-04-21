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

vector<int> C;
int inf = numeric_limits<int>::max();
vector<vector<int>> PD;

int minCosto(int i, int j){
    if(PD[i][j] == -1){
        int minLocal = inf;
        for(int k = 0; k < C.size(); k++){
            if(C[k]> i && C[k] < j){
                minLocal = min(minCosto(i, C[k]) + minCosto(C[k], j), minLocal);
            }
        }
        if(minLocal == inf){ //esto significa que no hay ningún corte posible entre i y j, por lo tanto devuelve 0
            PD[i][j] = 0;
        } else {
            PD[i][j] = j-i + minLocal;
        }
    }
    return PD[i][j];
    
}

int minCostoBottomUp(){
    for(int k = 0; k <  C.size(); k++){
        for(int i = 0; i < )
    }
}

int main() {
    C = {2,4,7};
    int l = 10;
    for(int i = 0; i <= l; i++){
        vector<int> vectorLocal(l+1,-1);
        PD.push_back(vectorLocal);
    }
    int res = minCosto(0,l);
    cout << res << endl;
}

//complejidad temporal: o(l²) o o(n²)