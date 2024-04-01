#include <iostream>
#include <ostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

int C, N;
vector<int> anchos,alturas;
int maxCreciente, maxDecreciente;

//agregar podas con maxPosible

int skylineCreciente(int i, int ultimo){
    if(i == N){
        return 0;
    } else {
        
        int candidatoSin = skylineCreciente(i+1, ultimo);
        if(ultimo== 0 || alturas[i] > ultimo){
            int candidatoCon = anchos[i] + skylineCreciente(i+1, alturas[i]);
            //cout << "i: " << i << "  candidatoCon :" << candidatoCon << "   candidatoSin:  " << candidatoSin << endl;
            return max(candidatoSin, candidatoCon);
        } else {
            return candidatoSin;
        }
    }  
}

int skylineDecreciente(int i, int ultimo){
    if(i == N){
        return 0;
    } else {
        int candidatoSin = skylineDecreciente(i+1, ultimo);
        if(ultimo== 0 || alturas[i] < ultimo){
            int candidatoCon = anchos[i] + skylineDecreciente(i+1, alturas[i]);
            return max(candidatoSin, candidatoCon);
        } else {
            return candidatoSin;
        }
    }  
}

int main() {
    //ofstream fileOut("output.txt");
    //cout.rdbuf(fileOut.rdbuf());
    cin >> C;
    int caso = 1;
    while(caso <= C){
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
        maxCreciente = 0;
        maxDecreciente = 0;
        int increasing = skylineCreciente(0, 0);
        int decreasing = skylineDecreciente(0, 0);
        if(increasing >= decreasing){
            cout << "Case " << caso << ". Increasing (" <<  increasing << "). Decreasing (" << decreasing << ")." << endl;
        } else {
            cout << "Case " << caso << ". Decreasing (" <<  decreasing << "). Increasing (" << increasing << ")." << endl;
        }
        
        caso++;
    }
}