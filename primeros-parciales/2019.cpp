/*Problema 1 (8 puntos)
Dada la especificación de la Figura 1a del TAD Pila de Enteros, escriba un procedimiento iterativo imprimirKAntiguos
que reciba una pila p y un entero positivo k, e imprima los k números más antiguos de la pila en el orden
en que fueron ingresados. Si la pila tiene menos de k elementos, se deberán imprimir todos. Al finalizar el
procedimiento la pila p debe quedar en la misma condición en que estaba originalmente.*/

Pila crearPila ( ) ;
/* Devuelve l a p i l a vac í a . */
Pila apilar ( i n t s , Pila p ) ;
/* I n s e r t a s en l a cima de p . */
int cima ( Pila p ) ;
/* Devuelve la cima de p.
P r e c o n d i c i o n : ! e s V a c i a P i l a ( p ) . */
Pila desapilar ( Pila p ) ;
/* Remueve l a cima de p .
P r e c o n d i c i o n : ! e s V a c i a P i l a ( p ) . */
bool esVaciaPila ( Pila p ) ;
/* Devuelve ' t r u e ' s i p es vacia ,
' f a l s e ' en o t r o caso . */
void destruirPila ( Pila &p ) ;
/* L i b e r a l a memoria asociada a p . */

void imprimirKAntiguos(Pila p, int k) {
    if (!esVaciaPila(p)) {
        Pila aux = crearPila();
        while (!esVaciaPila(p)) {
            aux = apilar(cima(p), aux);
            p = desapilar(p);
        };

        while (!esVaciaPila(aux) && k>0) {
            printf("%d ", cima(aux));
            p = apilar(cima(aux), p);
            aux = desapilar(aux);
            k--;
        }

        while (!esVaciaPila(aux)) {
            p = apilar(cima(aux), p);
            aux = desapilar(aux);
        };
        destruirPila(aux);
    }
}


/* Problema 2 (14 puntos)
Considere la siguiente definición de nodos de listas dinámicas de enteros: */

struct nodoLista {
    int dato ;
    nodoLista * sig ;
};
typedef nodoLista * Lista ;

/* (a) Defina un procedimiento recursivo insertarOrdenado que dada una lista de enteros L ordenada de
menor a mayor, sin elementos repetidos, y dado un entero x, inserte a x en L manteniendo el orden. Si
x estaba en L, el procedimiento no tendrá efecto. */

void insertarOrdenado ( Lista & L , int x ) {
    if (L == NULL || L->dato > x) {
        Lista aux = L;
        L = new nodoLista;
        L->dato = x;
        L->sig = aux;
    } else if (L->sig->dato < x) insertarOrdenado(L, x);
};

void insertarOrdenadoIT ( Lista & L , int x ) {
    if (L == NULL || L->dato > x) {
        Lista nuevo = new nodoLista;
        nuevo->dato = x;
        nuevo->sig = L->sig;
        L = nuevo;
    } else if (L != NULL) {
        Lista aux = L;
        while (aux->sig != NULL && aux->sig->dato < x) aux = aux->sig;
        if(aux->dato != x) {
            Lista nuevo = new nodoLista;
            nuevo->dato = x;
            nuevo->sig = aux->sig;
            aux->sig = nuevo;
        };
    };
};

/* (b) Defina una función iterativa ordenar que dada una lista de enteros L, que puede contener elementos
repetidos, retorne una nueva lista, que no comparta memoria con L, que esté ordenada de menor a
mayor y contenga a los elementos de L. Cada elemento de L debe aparecer una sola vez en la lista re-
sultado; esto es, la lista ordenada resultante no debe tener elementos repetidos. Utilice el procedimiento
insertarOrdenado para definir la función ordenar */

Lista ordenar(Lista L) {
    Lista res = NULL;
    while (L != NULL) {
        insertarOrdenado(res, L->dato);
        L = L->sig;
    };
    return res;
}

/*Problema 3 (14 puntos)
Considere la siguiente definición del tipo AB de árboles binarios de enteros:*/

struct nodoAB {
    int dato ;
    nodoAB * izq ;
    nodoAB * der ;
} ;
typedef nodoAB * AB ;

/*(a) Un árbol perfecto es un árbol en el cual todos los nodos interiores tienen dos hijos y todos las hojas
están en el mismo nivel, ver Figura 2. Un árbol vacío y un árbol con un sólo nodo son árboles perfectos*/
/* Implemente una función recursiva maxAlturalPerfecto que, dado un árbol t devuelve la altura del
subárbol máximo perfecto con la misma raíz que t. Notar que la altura del subárbol máximo perfecto
está determinada por el nodo más cercano a la raíz que no tenga alguno de los hijos, ver nodo 6 de la
Figura 2b. Recordar que la altura del árbol vacío es 0 y la de un árbol con un sólo nodo es 1. */
int min(a, b) {
    if (a <= b) return a;
    else return b;
};

int maxAlturaPerfecto ( AB t ) {
    int res;
    if (t == NULL) res = 0;
    else {
        res = 1 + min(maxAlturaPerfecto(AB->der), maxAlturaPerfecto(AB->izq));
    }
    return res;
}

int maxAlturaPerfecto2 ( AB t ) { //solucion de los profes
    int res = 0;
    if (t !=NULL ) {
        int hizq = maxAlturaPerfecto2(t->izq);
        int hder = maxAlturaPerfecto2(t->der);
        res = 1 + min(hizq,hder);
    };
    return res ;
}

/* (b) Implemente un procedimiento recursivo borrarRecursivo que, dado un árbol t lo elimina completa-
mente, liberando la memoria ocupada. */
void borrarRecursivo (AB & t) {
    if (t != NULL) {
        borrarRecursivo(t->izq);
        borrarRecursivo(t->der);
        delete t;
        t = NULL;
    }
}

/* (c) Implemente un procedimiento que, dado un árbol t borra todos los nodos necesarios para obtener el
subárbol máximo perfecto con la misma raíz que t, ver Figura 3.*/
void podar(AB t, int h) {
    if (h == 0) {
        borrarRecursivo(t);
    } else {
        podar(t->der, h-1);
        podar(t->izq, h-1);
    };
}

void obtenerPerfecto ( AB & t ) {
    int h = maxAlturaPerfecto(t);
    podar(t, h);
}  