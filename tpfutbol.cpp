#include <iostream>
#include <ostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;


vector<tuple<int,int,string>> jugadores;
tuple<int, int, vector<string>> maxActual(0, 0, {});

bool esMenor(vector<string> a, vector<string> b){
    string stringMinimo = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    for(int j = 0; j < 5; j++){
        if(a[j] < stringMinimo){
            stringMinimo = a[j];
        }
    }
    for(int j = 0; j < 5; j++){
        if(b[j] < stringMinimo ){
            return false;
        }
    }
    return true;
}

tuple<int,int, vector<string>> futbol(vector<string> &PI, int i, vector<int> &disponible, int sumaAtaque, int sumaDefensa){
       //para verificar el orden lexico, que conviene mas? Verificar en la recursion, o ordenar el arreglo de ataque al final del ejercicio? 
    //(antes de devolver el output)
    
    if(i==10){
        tuple<int,int,vector<string>> res(sumaAtaque, sumaDefensa, PI);
        return(res);
    } else {
        if(i>=5 && sumaAtaque < get<0>(maxActual)){
            return maxActual;
        }
        for(int j = 0; j < 10; j++){
            if(disponible[j] == 1){
                disponible[j] = 0;
                PI.push_back(get<2>(jugadores[j]));
                tuple<int,int, vector<string>> candidato;
                if (i < 5){
                    candidato = futbol(PI, i+1, disponible, sumaAtaque + get<0>(jugadores[j]), sumaDefensa);
                } else {
                    candidato = futbol(PI, i+1, disponible, sumaAtaque, sumaDefensa + get<1>(jugadores[j]));
                }
                disponible[j] = 1;
                PI.pop_back();
                if((get<0>(candidato) > get<0>(maxActual))
                || (get<0>(candidato)==get<0>(maxActual) && get<1>(candidato) > get<1>(maxActual))
                ){ //|| (get<0>(candidato)==get<0>(maxActual) && get<1>(candidato) == get<1>(candidato) && esMenor(get<2>(candidato), get<2>(maxActual)))
                    maxActual = candidato;
                }
            }
        }
        return maxActual;
    } 
}

void sort(vector<tuple<int,int,string>> &s, int n){
    int i, j;
    tuple<int,int,string> key;
    for(i = 1; i < n; i++){
        key = (s[i]);
        j = i-1;
        while(j>= 0 && get<0>(s[j]) < get<0>(key)){
            s[j+1] = s[j];
            j= j-1;
        }
        s[j+1] = key;
    }
    for(i = 6; i < n; i++){
        key = (s[i]);
        j = i-1;
        while(j>= 0 && get<1>(s[j]) < get<1>(key)){
            s[j+1] = s[j];
            j= j-1;
        }
        s[j+1] = key;
    }

}

int main(){
    int n;
    cin >> n;
    while(n > 0){
        for(int i = 0; i < 10; i++){
            tuple<int,int,string> jugador;
            string nombre;
            int ataque, defensa;
            cin >> nombre;
            cin >> ataque;
            cin >> defensa;
            get<0>(jugador) = ataque;
            get<1>(jugador) = defensa;
            get<2>(jugador) = nombre;
            jugadores.push_back(jugador);
        }
        
        sort(jugadores, 10);
        vector<int> disponible(10,1);
        vector<string> PI = {};
        tuple<int,int, vector<string>> res = futbol(PI, 0, disponible, 0, 0);
        PI = get<2>(res);

        vector<string> atacantes;
        vector<string> defensores;

        for(int i = 0; i < 10; i++){
            if(i < 5){
                atacantes.push_back(PI[i]);
            } else if(i < 10){
                defensores.push_back(PI[i]);
            }
        }
        
        sort(atacantes.begin(), atacantes.end());
        sort(defensores.begin(), defensores.end());
        jugadores = {};

        cout << "Case " << n << ":" << endl;
        cout << "(";
        for(int i = 0; i < 4; i++){
            cout << atacantes[i] << ", ";
        }
        cout << atacantes[4] << ")" << endl;
        cout << "(";
        for(int i = 0; i < 4; i++){
            cout << defensores[i] << ", ";
        }
        cout << defensores[4] << ")" << endl;
        n--;
    }
}