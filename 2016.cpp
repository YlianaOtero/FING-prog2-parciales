/* Ejercicio 1 (10 puntos)
Considere las siguientes definiciones de listas encadenadas de enteros y de pares de enteros: */
struct nodoLista {
    int dato;
    nodoLista * sig;
};
typedef nodoLista * Lista ;

struct nodoListaPares {
    int primero, segundo;
    nodoListaPares * sig;
};
typedef nodoListaPares * ListaPares;

/* Implemente una función iterativa (no recursiva) combinar que, dadas dos listas de enteros L1 = [a1, a2, . . . , an] 
y L2 = [b1, b2, . . . , bm], retorne la lista de pares [(a1, b1), (a2, b2), . . . , (ak, bk)], donde
k es el mínimo entre n y m. Si una de las listas es vacía (NULL), el resultado debe ser la lista vacía
(NULL). L1 y L2 no deben recorrerse más de una vez. El orden de tiempo de ejecución en el peor caso
de combinar debe ser O(min(n, m)). */
ListaPares combinar0 (Lista L1, Lista L2) {
    ListaPares nueva = NULL;
    if (L1 == NULL || L2 == NULL) return nueva;
    else {
        int cont = 0;
        while (L1 != NULL && L2 != NULL) {
            ListaPares nodoNuevo = new nodoListaPares;
            nodoNuevo->primero = L1->dato;
            nodoNuevo->segundo = L2->dato;
            nodoNuevo->sig = nueva->sig;
            if (cont == 0) nueva = nodoNuevo;
            cont++;
            L1 = L1->sig;
            L2 = L2->sig;
        };
        return nueva;
    }
};

ListaPares combinar(Lista L1, Lista L2) {
    ListaPares nueva = NULL;
    if (L1 == NULL || L2 == NULL) return nueva;
    else {
        nueva = new nodoListaPares;
        nueva->primero = L1->dato;
        nueva->segundo = L2->dato;
        ListaPares iter = nueva;
        while (L1->sig != NULL && L2->sig != NULL) {
            L1 = L1->sig;
            L2 = L2->sig;
            ListaPares iter = new nodoListaPares;
            iter->primero = L1->dato;
            iter->segundo = L2->dato;
            iter = iter->sig;
        };
        iter->sig = NULL;
        return nueva;
    }
}

/* Ejercicio 2 (10 puntos)
Considere la siguiente definición del tipo ABB de los árboles binarios de búsqueda de enteros, en memoria
dinámica: */

struct nodoABB {
    int dato ;
    nodoABB * izq , * der ;
};
typedef nodoABB * ABB ;

/* Defina una función recursiva copiarMayores que dados un árbol binario de búsqueda de enteros A
de tipo ABB (sin elementos repetidos) y un entero x, retorne una copia de A que contenga a todos
los elementos del árbol cuyos datos son mayores estrictos a x. Si A es vacío (NULL) o no hay elementos
estrictamente mayores a x en A, el resultado debe ser el árbol vacío (NULL). La función debe retornar
un árbol binario de búsqueda que no comparta memoria con el árbol parámetro. El procedimiento debe
tener O(n) de tiempo de ejecución en el peor caso (siendo n la cantidad de nodos de A) y debe evitar
recorrer todo el árbol, de ser posible. No defina funciones o procedimientos auxiliares. */
ABB copiarMayores(ABB A, int x) {
    ABB mayores;
    if (A == NULL) mayores = NULL;
    else {
        ABB mayorDer = copiarMayores(A->der, x);
        if (A->dato <= x) mayores = mayorDer;
        else {
            ABB mayorIzq = copiarMayores(A->izq, x);
            mayores = new nodoABB;
            mayores->dato = A->dato;
            mayores->der = mayorDer;
            mayores->izq = mayorIzq;
        }
    }
    return mayores;
}

/* Ejercicio 3 (10 puntos)
Se quiere representar una estructura simpliFIcada de directorios (carpetas) de un sistema operativo, donde
cada directorio tiene un nombre único que lo identifica. Cada directorio puede contener un número finito
de subdirectorios. No se contemplan archivos en esta versión simplificada del sistema.
Considere el tipo Directorios, definido como árboles generales de strings (char *) e implementado como
árboles binarios con la semántica primer hijo (pH) - siguiente hermano (sH): */

struct nodoDir {
    char * nombre ;
    nodoDir *pH , * sH ;
};

typedef nodoDir * Directorios ;

/*Defina un procedimiento borrar que, dados un Directorios D sin elementos repetidos y el nombre
nom_dir de un directorio, elimine a nom_dir de D si nom_dir está en D y no tiene subdirectorios.
En caso contrario, el procedimiento no tendrá efecto. En particular, si D es el directorio vacío (NULL) el
procedimiento no tendrá efecto. Al eliminar un directorio deberá liberarse la memoria asociada a este.
Utilice la función strEq (que se asume implementada) para comparar strings; strEq retorna true si y
sólo si dos strings son iguales. No defina funciones o procedimientos auxiliares.*/
void borrar (Directorios & D, char * nom_dir) {
    if (D != NULL) {
        if (strEq(D->nombre, nom_dir)) {
            if (D->pH == NULL) {
                Directorios aBorrar = D;
                D = D->sH;
                delete[] aBorrar;
                aBorrar = NULL;
            };
        } else {
            borrar(D->pH);
            borrar(D->sH)
        };
    };
};

