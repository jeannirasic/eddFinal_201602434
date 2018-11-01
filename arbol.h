#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

FILE *archivoSpl;

typedef struct nodoSpl{
    int id;
    struct nodoSpl *derecho;
    struct nodoSpl *izquierdo;
}nodoSpl;

typedef struct arbolSpl{
    nodoSpl *raiz;
}arbolSpl;

void inicializarSpl(arbolSpl **arbol){
    (*arbol)->raiz = NULL;
}

nodoSpl *crearNodo(int id){
    nodoSpl *nuevo = (nodoSpl*) malloc(sizeof(nodoSpl));
    nuevo->id = id;
    nuevo->derecho = NULL;
    nuevo->izquierdo = NULL;
    return nuevo;
}

nodoSpl *zig(nodoSpl *padre, nodoSpl *hijo){
    nodoSpl *derHijo = hijo->derecho;
    padre->izquierdo = derHijo;
    hijo->derecho = padre;
    return hijo;
}

nodoSpl *zag(nodoSpl *padre, nodoSpl *hijo){
    nodoSpl * izqHijo = hijo->izquierdo;
    padre->derecho = izqHijo;
    hijo->izquierdo = padre;
    return hijo;
}

nodoSpl* insertarSpl(nodoSpl **nodo, int id){
    if((*nodo) == NULL){
        (*nodo) = crearNodo(id);
        return (*nodo);
    }else{
        if((*nodo)->id > id){ //ZIG
            nodoSpl *hijo = insertarSpl(&(*nodo)->izquierdo, id);
            (*nodo) = zig((*nodo), hijo);
            return (*nodo);
        }else if((*nodo)->id < id){ //ZAG
            nodoSpl *hijo = insertarSpl(&(*nodo)->derecho, id);
            (*nodo) = zag((*nodo), hijo);
            return (*nodo);
        }
    }
}

nodoSpl *modificarSpl(nodoSpl *nodo, int id, int nuevoId){
    if(nodo == NULL){
        return NULL;
    }else{
        if(nodo->id > id){ //ZIG
            nodoSpl *hijo = modificarSpl(nodo->izquierdo, id, nuevoId);
            nodo = zig(nodo, hijo);
            return nodo;
        }else if(nodo->id < id){ //ZAG
            nodoSpl *hijo = modificarSpl(nodo->derecho, id, nuevoId);
            nodo = zag(nodo, hijo);
            return nodo;
        }else if(nodo->id == id){
            printf("Se modifico el dato: %i\n", id);
            nodo->id = nuevoId;
            return nodo;
        }
    }
}

nodoSpl *buscarSpl(nodoSpl *nodo, int id){
    if(nodo == NULL){
        return NULL;
    }else{
        if(nodo->id > id){ //ZIG
            nodoSpl *hijo = buscarSpl(nodo->izquierdo, id);
            nodo = zig(nodo, hijo);
            return nodo;
        }else if(nodo->id < id){ //ZAG
            nodoSpl *hijo = buscarSpl(nodo->derecho, id);
            nodo = zag(nodo, hijo);
            return nodo;
        }else if(nodo->id == id){
            printf("Se encontro el dato: %i\n", id);
            return nodo;
        }
    }
}

void auxGraficarSpl(nodoSpl *nodo){
    if(nodo == NULL){
        return;
    }else{
        fprintf(archivoSpl, "%i", nodo->id);
        fprintf(archivoSpl, "%s", "[label=\"");
        fprintf(archivoSpl, "%i", nodo->id);
        fprintf(archivoSpl, "%s", "\"];\n");

        if(nodo->izquierdo != NULL){
            fprintf(archivoSpl, "%i", nodo->id);
            fprintf(archivoSpl, "%s", "->");
            fprintf(archivoSpl, "%i", nodo->izquierdo->id);
            fprintf(archivoSpl, "%s", ";\n");
            auxGraficarSpl(nodo->izquierdo);
        }
        if(nodo->derecho != NULL){
            fprintf(archivoSpl, "%i", nodo->id);
            fprintf(archivoSpl, "%s", "->");
            fprintf(archivoSpl, "%i", nodo->derecho->id);
            fprintf(archivoSpl, "%s", ";\n");
            auxGraficarSpl(nodo->derecho);
        }
    }
}

void graficarSpl(nodoSpl *raiz){
    archivoSpl = fopen("/home/jeannira/Escritorio/spl.dot", "w+");

    fprintf(archivoSpl, "%s", "digraph spl { \n");
    fprintf(archivoSpl, "%s", "node[fillcolor=\"thistle2\", style =\"filled\", shape=\"oval\"];\n");

    if(raiz == NULL){
        fprintf(archivoSpl, "%s", "VACIO");
    }else{
        auxGraficarSpl(raiz);
    }


    fprintf(archivoSpl, "%s", "\n\n\n overlap=false \n fontsize=15; \n}");
    fclose (archivoSpl);

    char comando1[] = "dot -Tpng /home/jeannira/Escritorio/spl.dot -o /home/jeannira/Escritorio/spl.png";
    system(comando1);

    char comando2[] = "eog /home/jeannira/Escritorio/spl.png";
    system(comando2);
}

nodoSpl *reemplazar(nodoSpl **raiz){
    nodoSpl *mayorMenores = (*raiz)->izquierdo;
    if(mayorMenores->derecho != NULL){
        nodoSpl *anteriorMayorMenores;
        while(mayorMenores->derecho != NULL){
            anteriorMayorMenores = mayorMenores;
            mayorMenores = mayorMenores->derecho;
        }
        nodoSpl *hijoMayorMenores = mayorMenores->izquierdo;
        nodoSpl *hijoRaizI = (*raiz)->izquierdo;
        nodoSpl *hijoRaizD = (*raiz)->derecho;
        anteriorMayorMenores->derecho = hijoMayorMenores;
        (*raiz) = mayorMenores;
        mayorMenores->izquierdo = hijoRaizI;
        mayorMenores->derecho = hijoRaizD;
    }else{
        nodoSpl *der = (*raiz)->derecho;
        (*raiz) = mayorMenores;
        (*raiz)->derecho = der;
    }
    return (*raiz);
}

nodoSpl *auxEliminarSpl(nodoSpl **raiz, int id){
    if((*raiz) == NULL){
        //printf("No existe el nodo\n");
        return NULL;
    }else if((*raiz)->id > id){// se va a la izquierda
        return auxEliminarSpl(&(*raiz)->izquierdo, id);
    }else if((*raiz)->id < id){ //se va a la derecha
        return auxEliminarSpl(&(*raiz)->derecho, id);
    }else if((*raiz)->id == id){//se encontro el id
        nodoSpl *temporal = (*raiz);
        //printf("Se elimina el nodo\n");
        if((*raiz)->izquierdo == NULL && (*raiz)->derecho == NULL){
            //printf("Es hoja\n");
            (*raiz) = NULL;
            return (*raiz);
        }else if(((*raiz)->izquierdo == NULL && (*raiz)->derecho != NULL) || ((*raiz)->derecho == NULL && (*raiz)->izquierdo != NULL)){
            //printf("Solo tiene un hijo\n");
            if((*raiz)->izquierdo != NULL){//Se sube la izquierda
                (*raiz) = temporal->izquierdo;
                return (*raiz);
            }else{//se sube la derecha
                (*raiz) = temporal->derecho;
                return (*raiz);
            }
        }else if((*raiz)->izquierdo != NULL && (*raiz)->derecho != NULL){
            //printf("Ya valiste, tiene dos hijos XD\n");
            (*raiz) = reemplazar(&(*raiz));
            return (*raiz);
        }
    }
}

nodoSpl *auxEliminarSpl1(nodoSpl *nodo, int id){
    if(nodo == NULL){
        return NULL;
    }else{
        if(nodo->id > id){ //ZIG
            nodoSpl *hijo = auxEliminarSpl1(nodo->izquierdo, id);
            nodo = zig(nodo, hijo);
            return nodo;
        }else if(nodo->id < id){ //ZAG
            nodoSpl *hijo = auxEliminarSpl1(nodo->derecho, id);
            nodo = zag(nodo, hijo);
            return nodo;
        }else if(nodo->id == id){
            return nodo;
        }
    }
}

nodoSpl *eliminarSpl(nodoSpl **raiz, int id){
    (*raiz) = auxEliminarSpl1((*raiz), id);
    (*raiz) = auxEliminarSpl(&(*raiz), id);
    return (*raiz);
}

#endif // ARBOL_H_INCLUDED
