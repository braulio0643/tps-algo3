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

int potenciaLogaritmica(int a,int b){
    if(b== 0){
        return 1;
    } else if (b == 1){
        return a;
    } else {
        if(b % 2 == 0){
            return pow(potenciaLogaritmica(a,b/2),2);
        } else {
            return a*pow(potenciaLogaritmica(a,(b-1)/2),2);
        }
    }
}

int main(){
    cout << potenciaLogaritmica(2,3) << endl;
}