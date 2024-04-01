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
vector<int> maxPosible(10,0);
int maxDefensa = 0;
int maxAtaque = 0;


void crearMaxPosible(vector<tuple<int,int,string>> &s, int n){
    int i, j;
    vector<tuple<int,int,string>> copia = s;

    tuple<int,int,string> key;
    for(i = 1; i < n; i++){
        key = (copia[i]);
        j = i-1;
        while(j>= 0 && get<0>(copia[j]) < get<0>(key)){
            copia[j+1] = copia[j];
            j= j-1;
        }
        copia[j+1] = key;
    }

    int suma = 0;
    
    for(int i = 0; i < 5; i++){
        suma += get<0>(copia[i]); 
    }
    maxAtaque = suma;
    
    for(i = 0; i < n; i++){
        key = (copia[i]);
        j = i-1;
        while(j>= 0 && get<1>(copia[j]) < get<1>(key)){
            copia[j+1] = copia[j];
            j= j-1;
        }
        copia[j+1] = key;
    }

    suma = 0;
    
    for(int i = 0; i < 5; i++){
        suma += get<1>(copia[i]); 
    }

    maxDefensa = suma;
    
}

void sortNombres(vector<tuple<int,int,string>> &s, int n){

    tuple<int,int,string> key;
    int i, j;
    for(i = 1; i < n; i++){
        key = (s[i]);
        j = i-1;
        while(j>= 0 && get<2>(s[j]) > get<2>(key)){
            s[j+1] = s[j];
            j= j-1;
        }
        s[j+1] = key;
    }
}

tuple<int,int, vector<string>> futbol(vector<string> &PI, int i, vector<int> &disponible, int sumaAtaque, int sumaDefensa){
    
    if(i==10){
        tuple<int,int,vector<string>> res(sumaAtaque, sumaDefensa, PI);
        return(res);
    } else { //
        if((i>=5 && sumaAtaque < get<0>(maxActual))
        || (i < 5 && sumaAtaque + maxAtaque < get<0>(maxActual))
        || (i >= 5 && sumaDefensa + maxDefensa < get<1>(maxActual))
        ){
            return maxActual;
            
        }
        for(int j = 0; j < 10; j++){
            if(disponible[j] == 1){
                tuple<int,int, vector<string>> candidato;
                
                if (i < 5){
                    disponible[j] = 0;
                    PI.push_back(get<2>(jugadores[j]));
                    candidato = futbol(PI, i+1, disponible, sumaAtaque + get<0>(jugadores[j]), sumaDefensa);
                
                    disponible[j] = 1;
                    PI.pop_back();
                    
                } else {
                
                    vector<string> PICandidato = PI;
                    int sumaDefensaCandidata = 0;
                    for(int k = 0; k < 10; k++){
                        if(disponible[k]== 1){
                            PICandidato.push_back(get<2>(jugadores[k]));
                            sumaDefensaCandidata+= get<1>(jugadores[k]);
                        }
                    } 
                    tuple<int,int, vector<string>> resultado(sumaAtaque, sumaDefensaCandidata, PICandidato);
                    candidato = resultado;
                    
                }
                if((get<0>(candidato) > get<0>(maxActual))
                || (get<0>(candidato)==get<0>(maxActual) && get<1>(candidato) > get<1>(maxActual))
                ){ //
                    
                    maxActual = candidato;
                }
            }
        }
        return maxActual;
    } 
}

int main(){
    int n;
    cin >> n;
    int caso = 1;
    while(caso <= n){
        get<0>(maxActual) = 0;
        get<1>(maxActual) = 0;
        get<2>(maxActual) = {};
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
        
        crearMaxPosible(jugadores, 10);
        sortNombres(jugadores, 10);
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


        cout << "Case " << caso << ":" << endl;
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
        caso++;
    }
    return 0;
}
