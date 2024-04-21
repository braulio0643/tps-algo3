tuple(int,int) distanciaMax(arbol a){
    if(esHoja(a)){
        return (tuple(0,0))
    }else if(hayArbolIzq(a)){
        tuple(int,int) izq = distanciaMax(a.izq)
        return (1 + izq.first; max(izq.second, 1 + izq.first));
    }else if(hayArbolDer(a)){
        tuple(int,int) der = distanciaMax(a.der)
        return (1 + der.first; max(der.second, 1 + der.first));
    }else {
        tuple(int,int) izq = distanciaMax(a.izq)
        tuple(int,int) der = distanciaMax(a.der)
        return (1 + max(izq.first, der.first); 
        max(izq.second, der.second, 1 + izq.first + 1 + der.first))
    }
}

bool esHoja(arbol a){
    return(a.izq == null && a.der == null);
}

bool hayArbolIzq(arbol a){
    return(a.izq!= null && a.der==null);
}

bool hayArbolDer (arbol a){
    return(a.izq== null && a.der!=null);
}

