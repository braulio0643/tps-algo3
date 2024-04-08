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
    if(resultados[altura][arbol] == -1){
        if(altura == 0){
            resultados[altura][arbol] = 0;
        } else {
            int max = INF;
            for(int i = 0; i < arboles.size(); i++){
                int candidato;
                if(i == arbol){
                    candidato = arboles[arbol][altura] +  acorn(altura-1, i);
                } else if (altura-f >= 0){
                    candidato = arboles[arbol][altura] +  acorn(altura-f, i);
                }
                if(candidato > max){
                    max = candidato;
                }
            }
            resultados[altura][arbol] = max;
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

        for(int i = 0; i <= h ; i++){
            vector<int> vectorArbol(t+1, -1);
            resultados.push_back(vectorArbol);
        }

        int max = 0;
        for(int i = 0; i < t; i++){
            int candidato = acorn(h, i);
            if(candidato> max){
                max = candidato;
            }
        }

        cout << max << endl;
        resultados= {};
        arboles = {};
        caso++;
    }
}