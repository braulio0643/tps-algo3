#include <iostream>
#include <ostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> anchos,alturas;
int maxCreciente, maxDecreciente;
vector<vector<int>> resultadosCrecientes, resultadosDecrecientes;
vector<int> resY;

//agregar podas con maxPosible

int skylineCreciente(int i, int ultimo){
    if(i == N){
        return 0;
    } else {
        int candidatoSin;
        if(resultadosCrecientes[i][ultimo]!= -1){
            return resultadosCrecientes[i][ultimo];
        }

        if(resultadosCrecientes[i+1][ultimo]!= -1){
            candidatoSin = resultadosCrecientes[i+1][ultimo];
        } else {
            resultadosCrecientes[i+1][ultimo]= skylineCreciente(i+1, ultimo);
            candidatoSin = resultadosCrecientes[i+1][ultimo];
        }
        
        if(alturas[i] > ultimo){
            int candidatoCon;
            if(resultadosCrecientes[i+1][alturas[i]]!=-1){
                candidatoCon = anchos[i] + resultadosCrecientes[i+1][alturas[i]];
            } else {
                resultadosCrecientes[i+1][alturas[i]] = skylineCreciente(i+1, alturas[i]);
                candidatoCon = anchos[i] + resultadosCrecientes[i+1][alturas[i]];
            }
            //cout << "i: " << i << "  candidatoCon :" << candidatoCon << "   candidatoSin:  " << candidatoSin << endl;
            resultadosCrecientes[i][ultimo] = max(candidatoCon, candidatoSin);
            return resultadosCrecientes[i][ultimo];

        } else {
            resultadosCrecientes[i][ultimo] = candidatoSin;
            return resultadosCrecientes[i][ultimo];
        }
    }  
}

int skylineDecreciente(int i, int ultimo){
    if(i == N){
        return 0;
    } else {
        int candidatoSin;
        if(resultadosDecrecientes[i][ultimo+1]!= -1){
            return resultadosDecrecientes[i][ultimo+1];
        }

        if(resultadosDecrecientes[i+1][ultimo+1]!= -1){
            candidatoSin = resultadosDecrecientes[i+1][ultimo+1];
        } else {
            resultadosDecrecientes[i+1][ultimo+1]= skylineDecreciente(i+1, ultimo);
            candidatoSin = resultadosDecrecientes[i+1][ultimo+1];
        }
        
        if((ultimo == -1) || (alturas[i] < ultimo)){
            int candidatoCon;
            if(resultadosDecrecientes[i+1][alturas[i]+1]!=-1){
                candidatoCon = anchos[i] + resultadosDecrecientes[i+1][alturas[i]+1];
            } else {
                resultadosDecrecientes[i+1][alturas[i]+1] = skylineDecreciente(i+1, alturas[i]);
                candidatoCon = anchos[i] + resultadosDecrecientes[i+1][alturas[i]+1];
            }
            //cout << "i: " << i << "  candidatoCon :" << candidatoCon << "   candidatoSin:  " << candidatoSin << endl;
            resultadosDecrecientes[i][ultimo+1] = max(candidatoCon, candidatoSin);
            return resultadosDecrecientes[i][ultimo+1];

        } else {
            resultadosDecrecientes[i][ultimo+1] = candidatoSin;
            return resultadosDecrecientes[i][ultimo+1];
        }
    }  
}


int main() {
    /* ofstream fileOut("output.txt");
    cout.rdbuf(fileOut.rdbuf());
    ifstream fileIn("input.txt");
    cin.rdbuf(fileIn.rdbuf()); */
    int C;
    cin >> C;
    int caso = 1;
    while(caso <= C){
        resultadosCrecientes = {};
        resultadosDecrecientes = {};
        resY = {};
        cin >> N;
        alturas = {};
        anchos = {};
        for(int i = 0; i < N; i++){
            int altura;
            cin >> altura;
            alturas.push_back(altura); 
        }
        for(int i = 0; i < N; i++){
            int ancho;
            cin >> ancho;
            anchos.push_back(ancho); 
        }

        
        int maxAltura = 0;
        for(int i = 0; i < alturas.size(); i++){
            if(alturas[i] > maxAltura){
                maxAltura = alturas[i];
            }
        }
        
       
        for(int i = 0; i <= maxAltura + 1; i++){
            resY.push_back(-1);
        }
        //hago más grande el vector resY (que representa al parámetro "ultimo"). Esto se debe a que
        //cuando uso skylineDecreciente, para saber si ya se tomó en cuenta antes un edificio o no,
        // debo revisar ultimo. Si ultimo == -1, significa que no hubo ningún edificio antes. En caso contrario,
        //si lo hubo. La única forma de hacer funcionar esta comparación es desplazando todos los usos del índice "ultimo"
        // hacia adelante con +1, ya que no puedo acceder a resultadosDecrecientes[i][-1]. Es decir, el 0 representa al -1,
        // el 1 representa al 0, y así sucesivamente.
        
        for(int i = 0; i <= N; i++){
            resultadosCrecientes.push_back(resY);
            resultadosDecrecientes.push_back(resY);
        }

        int increasing = skylineCreciente(0, 0);
        int decreasing = skylineDecreciente(0, -1);

        /*
        for(int i = 0; i <= N; i++){
            for(int j = 0; j <= maxAltura; j++){
                if(resultadosDecrecientes[i][j] != -1){
                    cout << "fila " << i << ", columna " << j << ", resultado: " << resultadosDecrecientes[i][j] << endl;
                }
            }
        }
        */

        if(increasing >= decreasing){
            cout << "Case " << caso << ". Increasing (" <<  increasing << "). Decreasing (" << decreasing << ")." << endl;
        } else {
            cout << "Case " << caso << ". Decreasing (" <<  decreasing << "). Increasing (" << increasing << ")." << endl;
        }
        
        caso++;
    }
}
