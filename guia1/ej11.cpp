#include <iostream>
#include <ostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <limits>
#include <bits/stdc++.h> 
/* pow example */
#include <stdio.h>      /* printf */
#include <math.h>       /* pow */

using namespace std;
vector<vector<tuple<int,string>>> PD;
int N;
vector<int> v;
vector<string> simbolos;
int w;




    /* for(int j = 0; j < 3; j++){
        PD[0][j] = v[0];
    }

    for(int i = 1; i < N; i++){
        for(int j = 0; j < 3; j++){
            bool encontre = false;
            for(int k = 0; k < 3 && !encontre; j++){
                if(j == 0 && PD[i-1][k] + v[i] == PD[i+1][0]){
                    encontre= true;
                } else if(j == 1 && PD[i-1][k]* v[i] == PD[i+1][1]){
                    encontre= true;
                } else if(j == 2 && pow(PD[i][j], v[i+1]) == PD[i+1][2]){
                    encontre= true;
                }
            }
            if(j==0){
                PD[i][j] = make_tuple(PD[i-1][j]+ v[i], );
            } else if(j == 1){
                PD[i][j] = PD[i-1][j]* v[i];
            } else if(j == 2){
                PD[i][j] = pow(PD[i-1][j], v[i]);
            }
        }
    }

    vector<string> res = {};
    int ultima;
    for(int j = 0; j < 3; j++){
        if(j == 0 && PD[N-1][j] == w){
            res.insert(res.begin(), "+");
            ultima = j;
        } else if (j == 1 && PD[N-1][j] == w){
            res.insert(res.begin(), "x");
            ultima = j;
        } else if (j == 2 && PD[N-1][j] == w){
            res.insert(res.begin(), "");
            ultima = j;
        }
    }

    for(int i = N-2; i>= 0; i--){
        bool encontre = false;
        for(int j = 0; j < 3 && !encontre; j++){
            if(ultima == 0 && PD[i][j] + v[i+1] == PD[i+1][0]){
                res.push_back(simbolos[j]);
                encontre= true;
            } else if(ultima == 1 && PD[i][j]* v[i+1] == PD[i+1][1]){
                res.push_back(simbolos[j]);
                encontre= true;
            } else if(ultima == 2 && pow(PD[i][j], v[i+1]) == PD[i+1][2]){
                res.push_back(simbolos[j]);
                encontre= true;
            }
        }
    }
    return res; */


tuple<int,string> operacionesTopDown(int i, int acum){
    if(acum > w){
        return make_tuple(-1,"");
    }
    if(get<0>(PD[i][acum]) == -1){
        if(i == N){
            PD[i][acum] = make_tuple(acum, 0);
        } else {
            tuple<int,string> candidato;
            candidato = operacionesTopDown(i+1, acum + v[i]);
            if(get<0>(candidato) == w){
                PD[i][acum] = make_tuple(w, "+");
            } else {
                candidato = operacionesTopDown(i+1, acum * v[i]);
                if(get<0>(candidato) == w){
                    PD[i][acum] = make_tuple(w, "*");
                } else {
                    candidato = operacionesTopDown(i+1, pow(acum, v[i]));
                    if(get<0>(candidato) == w){
                        PD[i][acum] = make_tuple(w, "↑");
                    }
                }
            }
        }
    }
    return PD[i][acum];
}

vector<string> reconstruir(){
    vector<string> res = {};
    int siguienteAcum = v[0];
    for(int i = 1; i < N; i++){
            if(get<0>(PD[i][siguienteAcum]) == w){
                if(get<1>(PD[i][siguienteAcum]) == "+"){
                    siguienteAcum = siguienteAcum + v[i];
                    res.push_back("+");
                } else if(get<1>(PD[i][siguienteAcum]) == "*"){
                    siguienteAcum = siguienteAcum * v[i];
                    res.push_back("*");
                } else if(get<1>(PD[i][siguienteAcum]) == "↑"){
                    siguienteAcum = pow(siguienteAcum, v[i]);
                    res.push_back("↑");
                }
            }
    }
    return res;
}




int main(){
    v = {3,1,5,2,1};
    w = 400;
    N = v.size();
    for(int i = 0; i <= v.size(); i++){
        vector<tuple<int,string>> vectorLocal(w+1, make_tuple(-1,""));
        PD.push_back(vectorLocal);
    }
    simbolos.push_back("+");
    simbolos.push_back("x");
    simbolos.push_back("↑");
    tuple<int,string> coso = operacionesTopDown(1, v[0]);
    vector<string> res = reconstruir();
    for(int i = 0; i < res.size(); i++){
        cout << res[i] << ", ";
    } 

}
