#include <stdio.h>
/* Problema 1
Considere la siguiente definición del tipo ABB de árboles binarios de búsqueda de enteros (sin elementos repetidos) 
y la definición del tipo Lista para listas de enteros: */

struct nodoABB{
    int dato;
    nodoABB *izq, *der;
};
typedef nodoABB * ABB;

struct nodoLista{
    int dato;
    nodoLista *sig;
};
typedef nodoLista * Lista;

/* Implemente un procedimiento recursivo rangoEnLista que dados un árbol binario de búsqueda t de tipo ABB,
dos enteros inf y sup, y una lista l de tipo Lista, agregue en l (que asumimos inicialmente vacía: NULL) los elementos 
de t que sean menores estrictos que sup y mayores estrictos que inf (asumimos inf < sup). Los elementos
incorporados en l deben estar ordenados de menor a mayor. El procedimiento debe tener O(n) peor caso, siendo
n la cantidad de nodos de t, aunque deben evitarse recorrer nodos de t que resulten innecesarios. Si no hay elementos 
de t en el rango entre inf y sup (en particular si t es vacío: NULL), el procedimiento no tendrá efecto. No
defina operaciones auxiliares para implementar rangoEnLista.*/

void rangoEnLista (ABB t, int inf, int sup, Lista &l) {
    if (t != NULL) {
        if (t->dato < sup-1)  rangoEnLista(t->der, inf, sup, l);
        if (t->dato > inf && t->dato < sup) {

            Lista nuevoElem = new nodoLista;
            nuevoElem->dato = t->dato;
            nuevoElem->sig = l;
            l = nuevoElem;

        }
        if (t->dato > inf+1) rangoEnLista(t->izq, inf, sup, l);
    }
};

/* Problema 2
Considere un árbol general de enteros representado mediante un árbol binario de enteros con la semántica: pun -
tero al primer hijo (pH), puntero al siguiente hermano (sH). */

struct nodoAG{
    int dato;
    nodoAG *pH, *sH;
};
typedef struct nodoAG * AG;

/* Un árbol general t es n ario (con n>0) si y solo si t es vacío (NULL) ó cada elemento (nodo) de t tiene a lo sumo
n hijos (entre 0 y n nodos).
Implemente la función bool nArio (AG t, int n) que retorne true si y solo si el árbol t es n ario, asumiendo que 
n > 0 
y t->sH == NULL (si el árbol t no es vacío, el nodo raíz no tiene hermanos). Si utiliza operaciones auxiliares, 
deberá implementarlas. */

bool nArio (AG t, int n){
    if (t == NULL)
    return true;
    else
    return (hijos(t) <= n) && nArio(t->pH, n) && nArio(t->sH, n);
}
// Retorna la cantidad de hijos de t en un árbol pH-sH. Precondición: t != NULL.
int hijos (AG t){
    int cantHijos = 0;
    t = t->pH;
    while (t != NULL){
        cantHijos++;
        t = t->sH;
}
    return cantHijos;
}

// Procedimiento que rellena un arbol
void CrearArbol2(ABB tree){
    tree->dato = 1;
    tree->izq = new nodoABB;
    tree->izq->dato = 2;
    tree->izq->izq = new nodoABB;
    tree->izq->izq->dato = 4;
    tree->izq->izq->izq = NULL;
    tree->izq->izq->der = NULL;
    tree->izq->der = new nodoABB;
    tree->izq->der->dato = 5;
    tree->izq->der->der = NULL;
    tree->izq->der->izq = new nodoABB;
    tree->izq->der->izq->dato = 7;
    tree->izq->der->izq->izq = NULL;
    tree->izq->der->izq->der = new nodoABB;
    tree->izq->der->izq->der->dato = 10;
    tree->izq->der->izq->der->izq = NULL;
    tree->izq->der->izq->der->der = NULL;


    tree->der = new nodoABB;
    tree->der->dato = 3;
    tree->der->izq = NULL;
    tree->der->der = new nodoABB;
    tree->der->der->dato = 6;
    tree->der->der->izq = new nodoABB;
    tree->der->der->izq->dato = 8;
    tree->der->der->izq->izq = NULL;
    tree->der->der->izq->der = NULL;

    tree->der->der->der = new nodoABB;
    tree->der->der->der->dato = 9;
    tree->der->der->der->izq = NULL;
    tree->der->der->der->der = NULL;

};

// Procedimiento que imprime una lista
void printLista(Lista list) {
    while (list != NULL) {
        printf("%d", list->dato);
        list = list->sig;
    }
    printf("\n");
};


int main() {
    ABB t = new nodoABB;
    CrearArbol2(t);
    Lista nuevo = new nodoLista;
    nuevo = NULL;
    rangoEnLista(t, 1, 3, nuevo);
    printLista(nuevo);
};
