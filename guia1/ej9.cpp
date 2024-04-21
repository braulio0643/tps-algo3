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

vector<vector<int>> A;
vector<vector<int>> PD;
int N,M;

int minVida(int i, int j){
    if(PD[i][j]== -1){
        if(i == A.size()-1 && j == A[0].size()-1){
            PD[i][j] = max(1 -A[i][j],1);
        } else if (i == A.size()-1 && j < A[0].size()-1){
            PD[i][j] =max(minVida(i,j+1) - A[i][j], 1);
        } else if ( i < A.size()-1 && j == A[0].size()-1){
            PD[i][j] =max(minVida(i+1,j) - A[i][j],1);
        } else {
            PD[i][j] =max(min(minVida(i+1,j), minVida(i,j+1)) - A[i][j], 1);
        }
    }
    return PD[i][j];
    
}

int minVidaBottomUp(){
    PD[M-1][N-1] = max(1, 1-A[M-1][N-1]);
    for(int i = M-2; i >= 0; i--){
        PD[i][N-1] = max(1, PD[i+1][N-1] - A[i][N-1]);
    } 
    for(int i = N-2; i >= 0; i--){
        PD[M-1][i] = max(1, PD[M-1][i+1] - A[M-1][i]);
    } 
    for(int i = M-2; i >= 0; i--){
        for(int j = N-2; j >= 0; j--){
            PD[i][j] = max(min(PD[i+1][j], PD[i][j+1]) - A[i][j], 1);
        }
    }
    return PD[0][0];
}


int main(){
    A = {{-2,-3,3}, {-5,-10,1}, {10,30,-5}};
    N = 3;
    M = 3;
    for(int i = 0; i < M; i++){
        vector<int> vectorLocal(N,-1);
        PD.push_back(vectorLocal);
    }
    cout << minVidaBottomUp();
}

//complejidad temporal = O(M . N . k) siendo k la complejidad temporal 
// de las operaciones. En este caso, al ser solo restas y accesos en o(1),
// nos queda O(M . N)