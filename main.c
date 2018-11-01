#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"

/*
	gcc -o main main.c arbol.h
	./main
	eddFinal_201602434

	git clone "https://github.com/jeannirasic/eddFinal_201602434.git"
	git add.
	git comit -m "carga 1"
	git push
*/

int main()
{
    arbolSpl *arbol = (arbolSpl*) malloc(sizeof(arbolSpl));
    inicializarSpl(&arbol);

    //INSERCIONES
    arbol->raiz = insertarSpl(&arbol->raiz, 15);
    arbol->raiz = insertarSpl(&arbol->raiz, 6);
    arbol->raiz = insertarSpl(&arbol->raiz, 12);
    arbol->raiz = insertarSpl(&arbol->raiz, 7);
    arbol->raiz = insertarSpl(&arbol->raiz, 14);
    arbol->raiz = insertarSpl(&arbol->raiz, 20);
    arbol->raiz = insertarSpl(&arbol->raiz, 13);
    arbol->raiz = insertarSpl(&arbol->raiz, 16);
    arbol->raiz = insertarSpl(&arbol->raiz, 11);
    arbol->raiz = insertarSpl(&arbol->raiz, 17);
    arbol->raiz = insertarSpl(&arbol->raiz, 5);
    arbol->raiz = insertarSpl(&arbol->raiz, 8);
    arbol->raiz = insertarSpl(&arbol->raiz, 3);
    arbol->raiz = insertarSpl(&arbol->raiz, 4);
    arbol->raiz = insertarSpl(&arbol->raiz, 9);

    //MODIFICACIONES
    arbol->raiz = modificarSpl(arbol->raiz, 6, 6);
    arbol->raiz = modificarSpl(arbol->raiz, 16, 16);
    arbol->raiz = modificarSpl(arbol->raiz, 15, 15);

    //BUSQUEDAS
    arbol->raiz = buscarSpl(arbol->raiz, 7);
    arbol->raiz = buscarSpl(arbol->raiz, 13);
    arbol->raiz = buscarSpl(arbol->raiz, 8);
    arbol->raiz = buscarSpl(arbol->raiz, 12);
    arbol->raiz = buscarSpl(arbol->raiz, 5);
    arbol->raiz = buscarSpl(arbol->raiz, 20);
    arbol->raiz = buscarSpl(arbol->raiz, 17);
    arbol->raiz = buscarSpl(arbol->raiz, 8);

    //ELIMINACIONES
    arbol->raiz = eliminarSpl(&arbol->raiz, 16);
    arbol->raiz = eliminarSpl(&arbol->raiz, 11);
    arbol->raiz = eliminarSpl(&arbol->raiz, 14);
    arbol->raiz = eliminarSpl(&arbol->raiz, 12);
    arbol->raiz = eliminarSpl(&arbol->raiz, 9);

    graficarSpl(arbol->raiz);

    return 0;
}
