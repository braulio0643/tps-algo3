b)
return 0      si c == 0 && j == N
return -INF   si c < 0 V c > j V (c > 0 && i == 0)
return max(cc(j+1,c-1) + p[j]; cc(j+1,c+1) - p[j]; cc(j+1,c))  en otro caso

c)
Inicializo mi matriz de memorización de resultados. 
Los posibles valores de C varían de 0 a N, ya que como máximo,
a lo largo del plazo de días, se pueden comprar 1 asteroide por día, es decir N asteroides. 
Por otro lado, los posibles valores de j varían de 0 a N también, ya que N es la cantidad de días dada.

vector<int> vectorC(N+1, -1)
vector<vector<int>> resultados(N+1, vectorC)

Aclaro que EMPIEZO en el día 0, y TERMINO en el dia N. Por lo tanto, mi caso base es cuando j==N.
No hace falta agregar una revisión para si hay c>0 en el caso base, ya que esto se contempla en el 
if(c > N - j) { return -INF }. Si llegamos al día N, se verificaría: if(c > N- N) = if(c > 0).

Por otro lado, al comenzar el algoritmo, verifico que si i == 0, c == 0 también. Estaría mal que c >0, ya que 
se debe empezar con 0 asteroides.

int astroVoid(int j, int c){
    if(resultados[j][c]== -1){
        if(c==0 && j == N){
            resultados[j][c] = 0
        } else if (c < 0 || c > N - j || (c > 0 && j == 0)){
            resultados[j][c] = -INF
        } else { //comparo entre las 3 posibilidades para buscar el máximo (compra, venta y hacer nada)
            int candidatoNada = astroVoid(j + 1, c) //inicializo al máximo con el resultado de la m.g.n de hacer nada
            int max = candidatoNada
            
            int candidatoCompra = astroVoid(j+1, c+1) - p[j]
            if(candidatoCompra > max){ //comparo la m.g.n. de comprar el dia j con la mejor de las 2 anteriores
                max = candidatoCompra
            }
            if(c > 0){ //reviso que c no sea 0 ya que sino el llamado va a ser con c negativo, y no puedo usar indices negativos en la matriz
                int candidatoVenta = astroVoid(j+1, c-1) + p[j]
                if(candidatoVenta > max){ //comparo la m.g.n. de vender el dia j con la de hacer nada el dia j
                    max = candidatoVenta
                } 
            }
            

            resultados[j][c] = max  //la mejor de las 3 queda como máximo, y como resultado final en la matriz para j,c

        }
    }
    return resultados[j][c]
}

int astroVoidBottomUp(int j, int c){
    resultados[N][0] = 0
    for(int k = 1; k < resultados[0].size(); k++){
        resultados[0][k] = -INF
    }

    for(int k = resultados.size()-1; k >= 0; k--){
        for(int h = 0; h < resultados[0].size(); h++){
            if(h > N - k){
                resultados[k][h] = -INF
            } else {
                int candidatoNada = resultados[k+1][h] //inicializo al máximo con el resultado de la m.g.n de hacer nada
                int max = candidatoNada

                int candidatoCompra = resultados[k+1][h+1] - p[k]
                if(candidatoCompra > max){ //comparo la m.g.n. de comprar el dia j con la mejor de las 2 anteriores
                    max = candidatoCompra
                }
                if(h > 0){ //reviso que c no sea 0 ya que sino el llamado va a ser con c negativo, y no puedo usar indices negativos en la matriz
                    int candidatoVenta = resultados[k+1][h-1] + p[k]
                    if(candidatoVenta > max){ //comparo la m.g.n. de vender el dia j con la de hacer nada el dia j
                        max = candidatoVenta
                    } 
                }
                resultados[k][h] = max
            }
        }
    }

    return resultados[j][c]

}