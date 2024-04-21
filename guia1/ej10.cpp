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

int N;
vector<int> w, s;
vector<vector<int>> PD;

int cajas(int i, int suma){
    if(PD[i][suma] == -1){
        if(i == 0){
            if(suma <= s[i]){
                PD[i][suma] = 1;
            } else {
                PD[i][suma] = 0;
            }
        } else if(suma <= s[i]){
            PD[i][suma] = (max(1 + cajas(i-1, suma + w[i]), cajas(i-1, suma)));
        } else {
            PD[i][suma] =(cajas(i-1, suma));
        }  
    }
    return PD[i][suma];

}

int cajasBottomUp(){
    for(int i = 0; i < PD[0].size(); i++){
        if(i <= s[0]){
            PD[0][i] = 1;
        } else {
            PD[0][i] = 0;
        }
    }
    for(int i = 1; i < N; i++){
        for( int j = 0; j < PD[0].size(); j++){
            if(j <= s[i]){
                PD[i][j] = (max(1 + PD[i-1][j + w[i]], PD[i-1][j]));
            } else {
                PD[i][j] = PD[i-1][j];
            }
        }
    }
    return PD[N-1][0];
}


int main(){
    w = {19,7,5,6,1};
    s = {15,13,7,8,2};
    N = w.size();
    int sumaMaxima = 0;
    for(int i = 0; i < N; i++){
        sumaMaxima += w[i];
    }
    for(int i = 0; i < N; i++){
        vector<int> vectorLocal(sumaMaxima + 1, -1);
        PD.push_back(vectorLocal);
    }
    cout << cajasBottomUp();

}