#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#define num 12
//#include "abb.h"

typedef struct Nodo{
	int dato;
	struct Nodo *hijoder,*hijoizq;
}Arbol;
////////////////////////////////////////
Arbol *iniciar()
{
	return NULL;
}
////////////////////////////////////////

Arbol *CrearArbol(int elem){
	Arbol *unArbol;
	unArbol=malloc(sizeof(Arbol));
	unArbol->hijoder=NULL;
	unArbol->hijoizq=NULL;
	unArbol->dato=elem;
	
	return unArbol;
}
/////////////////////////////////
int altura(Arbol *unArbol)
{
    int a,b;
 if(unArbol==NULL)
 {
 	return -1;
 }
 else
  {
        a = altura(unArbol->hijoizq);
        b = altura(unArbol->hijoder);

        if(a > b){
			 return a+1;
		}else{
		
            return b+1;
   		 }
	}
}
//////////////////////////////////////////////
int insertar(Arbol **unArbol,int elem)
{
	int exito=0;
	if(*unArbol==NULL)
	{
		*unArbol=CrearArbol(elem);return 1;
	}
	else
	{
		if((*unArbol)->dato!='N')//si  nodo es distinto de n
		{
			exito=insertar(&(*unArbol)->hijoizq,elem);
			if(exito==1){ return 1;	}else
			exito=insertar(&(*unArbol)->hijoder,elem);//printf("%d",arbol->derecha);
			if(exito==1){ return 1; }
		}
	}
	return 0;
}
//////////////////////////////////////////
int insertar_arbol_en_arreglo(Arbol **unArbol,int i,int *arreglo)
{
	
	if(*unArbol==NULL)
	{
		return 1;
	}
	else
	{
		arreglo[i]=(*unArbol)->dato;
		insertar_arbol_en_arreglo(&(*unArbol)->hijoizq,(2*i)+1,arreglo);
		insertar_arbol_en_arreglo(&(*unArbol)->hijoder,(2*i)+2,arreglo);
		
	}
	return 0;
}
//////////////////////////////////////////
int imprimir_arreglo(int *arreglo,int h)
{
	int i=0;
	while(i<pow(2,h))
	{
		printf("arreglo[%d]=%d  \n",i,arreglo[i]);
		i++;
	}
	return;
}
/////////////////////////////////////////
void MostrarArbol(Arbol *unArbol){
  if (unArbol==NULL){
      return;
    }
  printf ("%i\n", unArbol->dato);
  MostrarArbol(unArbol->hijoder);
  MostrarArbol (unArbol->hijoizq);
}
