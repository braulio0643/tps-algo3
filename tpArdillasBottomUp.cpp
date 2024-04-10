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
vector<int> vectorAltura;
vector<int> maxPorAltura;

#define INF numeric_limits<int>::min();

int acorn(){
    for (int i = 0; i < t; i++) { 
        for (int j = 1; j <= h; j++) { 
            resultados[i][j] += resultados[i][j-1];
            maxPorAltura[j] = max(maxPorAltura[j], resultados[i][j]);
        } 
    } 
   
    for (int j = f+1; j <= h; j++) { 
        int maxLocal = maxPorAltura[j];
        for (int i = 0; i < t; i++) {
            resultados[i][j] = max(maxPorAltura[j-f]+ arboles[i][j], resultados[i][j-1] + arboles[i][j]); 
            maxLocal = max(maxLocal, resultados[i][j]);
            resultados[i][j+1] = resultados[i][j] + arboles[i][j+1];
        }
        maxPorAltura[j] = maxLocal;
    }

    int maxTotal = 0;
    for (int i = 0; i < t; i++) {
        maxTotal = max(maxTotal, resultados[i][h]);
    }
    return maxTotal;

}


int main() {
    ios_base::sync_with_stdio(false);

   /*   ofstream fileOut("output.txt");
    cout.rdbuf(fileOut.rdbuf());
    ifstream fileIn("input.txt");
    cin.rdbuf(fileIn.rdbuf());     */

    cin >> C;
    int caso = 1;
    while(caso <= C){
        cin >> t >> h >> f;
        for(int i = 0; i < t; i++){
            vector<int> arbol(h+2, 0);
            cin >> a;
            int suma = 0;
            for(int j = 0; j < a; j++){
                cin >> bellota;
                arbol[bellota]++;
            }
            arboles.push_back(arbol);  
        }

        for(int i = 0; i <=h ; i++){
            maxPorAltura.push_back(0);
        }
        resultados = arboles;
        cout << acorn() << endl;
        resultados= {};
        arboles = {};
        maxPorAltura = {};
        caso++;
    }
    int cero;
    cin >> cero;
}