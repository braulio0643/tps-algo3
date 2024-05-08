#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>

using namespace std;
#include <queue>
vector<long long int> a;
long long int n;

long long int vinos(){
    long long int trabajo = 0;
    priority_queue<long long int> pendientes;
    for(int i = 0; i < a.size(); i++){
        if(pendientes.size()== 0){
            pendientes.push(i);
        } else {
            if(a[i] < 0 && a[pendientes.top()] > 0){
                while(a[i] < 0 && a[pendientes.top()]> 0){ // estoy en un vendedor y tengo compras pendientes
                    if(a[pendientes.top()] > -a[i]){ // el pendiente pide más
                        trabajo+= -a[i] * (abs(i - pendientes.top()));
                        a[pendientes.top()]+= a[i];
                        a[i] = 0;
                    } else if (a[pendientes.top()] == -a[i]){ // el pendiente pide lo mismo
                        trabajo+= -a[i] * (abs(i - pendientes.top()));
                        a[i] = 0;
                        a[pendientes.top()] = 0;
                        pendientes.pop();
                    } else { // el pendiente pide menos
                        trabajo+= a[pendientes.top()] * (abs(i - pendientes.top()));
                        a[i] += a[pendientes.top()];
                        a[pendientes.top()] = 0;
                        pendientes.pop(); //capaz hay que cambiar de orden esta linea y la de abajo? creo q no
                    }
                } 
                if(a[i] < 0){
                    pendientes.push(i);
                }
            } else if(a[i] < 0 && a[pendientes.top()] < 0){ // estoy en un vendedor y tengo ventas pendientes
                pendientes.push(i);
            } else if (a[i] > 0 && a[pendientes.top()] < 0){
                while(a[i] > 0 && a[pendientes.top()]< 0){ // estoy en un comprador y tengo ventas pendientes
                    if(-a[pendientes.top()] > a[i]){ // el pendiente vende más
                        trabajo+= a[i] * (abs(i - pendientes.top()));
                        a[pendientes.top()]+= a[i];
                        a[i] = 0;
                    } else if (-a[pendientes.top()] == a[i]){ // el pendiente vende lo mismo
                        trabajo+= a[i] * (abs(i - pendientes.top()));
                        a[i] = 0;
                        a[pendientes.top()] = 0;
                        pendientes.pop();
                    } else { // el pendiente vende menos
                        trabajo+= -a[pendientes.top()] * (abs(i - pendientes.top()));
                        a[i] += a[pendientes.top()];
                        a[pendientes.top()] = 0;
                        pendientes.pop(); 
                    }
                } 
                if(a[i] > 0){
                    pendientes.push(i);
                }    
            } else if(a[i] > 0 && a[pendientes.top()] > 0){ // estoy en un comprador y tengo compras pendientes
                pendientes.push(i);
            }
        }
    } // faltan los casos con a[péndientes.top()] == 0 pero en teoria cuando llegan a 0 se van de la queue
    return trabajo;
}

int main(){
    // usar queue?
    ios_base::sync_with_stdio(false);
    cin >> n;
    while(n != 0){
        a = {};
        for(long long int i = 0; i < n; i++){
            long long int a_i;
            cin >> a_i;
            a.push_back(a_i);
        } 
        cout << vinos() << endl;
        cin >> n;
    } 
}