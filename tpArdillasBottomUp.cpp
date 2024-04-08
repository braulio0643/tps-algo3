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

vector<vector<int>> arboles;
int C, t, h, f, a, bellota;

vector<vector<int>> resultados;
vector<int> vectorArbol;

#define INF numeric_limits<int>::min();
//sacar el if y probar el max entre todos los arboles?

int acorn(int altura, int arbol){

    for(int i = 0; i < resultados[0].size(); i++){
        resultados[0][i] = 0;
    }
    for(int k = 1; k <= altura; k++){
        for(int l = 0; l < resultados[0].size(); l++){
            int max = 0;
            for(int i = 0; i < arboles.size(); i++){
                int candidato;
                if(k == h+1){
                    candidato = resultados[k-1][i];
                } else if(i == l){
                    candidato = arboles[l][k] + resultados[k-1][i];
                } else if (k-f >= 0){
                    candidato = arboles[l][k] + resultados[k-f][i];
                }
                if(candidato > max){
                    max = candidato;
                }
            }
            resultados[k][l] = max;
        }
    }
    
    return resultados[altura][arbol];
}

int main() {
    ios_base::sync_with_stdio(false);

    ofstream fileOut("output.txt");
    cout.rdbuf(fileOut.rdbuf());
    ifstream fileIn("input.txt");
    cin.rdbuf(fileIn.rdbuf());

    cin >> C;
    int caso = 1;
    while(caso <= C){
        cin >> t >> h >> f;
        for(int i = 0; i < t; i++){
            vector<int> arbol(h+1, 0);
            cin >> a;
            for(int j = 0; j < a; j++){
                cin >> bellota;
                arbol[bellota]++;
            }
            arboles.push_back(arbol);
        }

        for(int i = 0; i <= h +1; i++){
            vector<int> vectorArbol(t, 0);
            resultados.push_back(vectorArbol);
        }

        cout << acorn(h+1,0) << endl;
        resultados= {};
        arboles = {};
        caso++;
    }
}