#include <iostream>
#include <ostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
#include <cmath>
using namespace std;
int N;

vector<vector<int>> potenciaSum(vector<vector<int>> a, int b){
    if(b == 2){
        return a + potencia(a,2);
    }
    vector<vector<int>> mitadIzq = potencia(a,b/2);
    return mitadIzq + mitadIzq*(potenciaSum(a,b/2));
    
}