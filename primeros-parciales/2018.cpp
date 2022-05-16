/* Problema 1 (15 puntos)
(a) Complete la siguiente definición general de orden de tiempo de ejecución: "T(n) es O(f(n)) si ..." 
T (n) es O(f (n)) si existen c y n0 constantes positivas para los cuales se cumple que T (n) ≤ c ∗ f (n)∀n > n0

(b) Considere la siguiente representación para una lista encadenada de enteros:*/
struct nodo {
    int elem ;
    nodo * sig ;
};

typedef nodo * lista;

/* Sea P un procedimiento que recibe como parámetro una lista de enteros de largo n, definido de la siguiente forma:*/
void P (lista l , unsigned int n) {
    for (int i = n; i > 0; i--) {
        lista itera = l ;
        for (int j = 1; j < i; j++)
            itera = itera->sig ;
        printf ("% d " , itera->elem);
        }
};

/*¿Qué imprime el procedimiento P, dada un lista de enteros de largo n?
Imprime los elementos de la lista l desde el último al primero. 

(c) Asuma que el tiempo de ejecución en peor caso de P, T(n), está determinado por la cantidad de veces
que se ejecuta la sentencia itera=itera->sig. Calcule T(n) y el orden de T(n), en el peor caso. 
T(n) = (n^2)/2 - n/2 en el peor caso => el orden es O(n^2)

(d) ¿Podría implementarse otro procedimiento que imprima lo mismo que P pero que tenga un menor
orden de tiempo de ejecución en el peor caso? Justifique en caso negativo y en caso afirmativo escriba
el procedimiento, indicando el orden (O). */
void P(lista l, unsigned int n) {
    int aux = new int[n];
    for (int i = 0; i < n; i++) {
        aux[i] = l->elem;
        l = l->sig;
    };
    for (int i = n; i >= 0; i++) {
        printf("%d ", aux[i]);
    }
    delete[] aux;
}
 
/* El orden es O(n).

Problema 2 (13 puntos)
Considere la siguiente definición del tipo ABB de árboles binarios de búsqueda de enteros: */
struct nodoABB {
    int dato;
    nodoABB * izq;
    nodoABB * der;
};
typedef nodoABB * ABB;

/*(a) Implemente un procedimiento iterativo concat que, dadas dos listas l y p, agregue al final de la lista l
los elementos de p, en el mismo orden. La lista l resultante comparte memoria con p.*/
void concat(lista &l , lista p) {
    if (p != NULL) {
        if (l == NULL) l = p;
        else {
            lista aux = l;
            while (aux->sig != NULL) aux = aux->sig;
            aux->sig = p; 
        };  
    };
};

/* (b) Implemente una función recursiva menores que dado un árbol binario de búsqueda t de tipo ABB y dado
un entero k, retorne una lista (del tipo definido en el Problema 1) que contenga a todos los elementos de
t menores (estrictos) a k y que esté ordenada de mayor a menor. Si no hay elementos en t menores a
k (en particular si t es vacío), la lista que se obtiene es vacía. La función menores debe evitar recorrer
nodos del árbol que no sean estrictamente necesarios. No se permite definir operaciones auxiliares,
aunque puede usarse el procedimiento concat implementado en la parte anterior. */
lista menores (ABB t , int k) {
    lista result = NULL;
    if (t != NULL) {
        lista menoresIzq = menores(t->izq, k);
        if (t->dato < k) {
            lista raiz = new nodo;
            raiz->elem = t->dato;
            raiz->sig = menoresIzq;
            result = menores(t->der, k);
            concat(result, raiz);
        } else result = menoresIzq;
    }
    return result;
};

/* Problema 3 (12 puntos)
Considere la siguiente definición del tipo ArbGen de árboles generales o finitarios de enteros representados
con árboles binarios con la semántica: primer hijo (pH) – siguiente hermano (sH):*/
struct nodoArbGen {
int dato ;
    nodoArbGen * pH ;
    nodoArbGen * sH ;
} ;
typedef nodoArbGen * ArbGen;

/* (a) Implemente una función recursiva buscar que dado un árbol general t sin elementos repetidos y dado
un entero x, retorne un puntero al nodo del árbol que tenga a x como dato, si x pertenece a t, o NULL
en caso contrario. No se permite definir operaciones auxiliares.*/
ArbGen buscar (ArbGen t, int x) {
    ArbGen puntero;
    if (t == NULL) puntero = NULL;
    else {
        if (t->dato == x) puntero = t;
        else {
            puntero = buscar(t->pH, x);
            if (puntero == NULL) puntero = buscar(t->sH, x);
        };
    return puntero;
    };
};

/* (b) Implemente, utilizando la función buscar, un procedimiento insertar que dado un árbol general t
sin elementos repetidos y dados enteros v y w, inserte a v como primer hijo de w en t (hijo más a la
izquierda), siempre que w pertenezca al árbol y v no pertenezca al árbol. En caso contrario, la operación
no tendrá efecto. */
void insertar (ArbGen & t , int v , int w ) {
    if (t != NULL) {
        ArbGen prueba = buscar(t, v);
        if (prueba == NULL) {
            ArbGen clave = buscar(t, w);
            if (clave != NULL) {
                ArbGen nuevo = new nodoArbGen;
                nuevo->dato = v;
                nuevo->sH = clave->pH;
                nuevo->pH = NULL;
                clave->pH = nuevo;
            };
        };
    };
    
};