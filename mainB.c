#ifndef stdio_h
#include <stdio.h>
#define stdio_h
#endif

#ifndef stdlib_h
#include <stdlib.h>
#define stdlib_h
#endif

#ifndef abb
#include "arbolB.h"
#define abb
#endif
void main()
{
	int respuesta,continuar=1,dato=0;
	while(continuar==1)
	{
		system("cls");
		imprimir(Raiz());
		printf(" Que accion desea realizar?...\n");
		printf("1: agregar dato al arbol B\n");
		printf("2: Buscar dato\n");
		printf("3: finalizar Programa.\n");
		scanf("%i",&respuesta);system("cls");
		switch(respuesta){
			case 1://printf("ingrese un dato\n");scanf("%i",&dato);
					while(dato<100)
					{
						Agregar_Dato(Raiz(),dato);
						dato++;
					}
						//	system("cls");Agregar_Dato(Raiz(),dato);
						break;
			case 2:printf("ingrese un dato\n");scanf("%i",&dato);system("cls");Buscar_Dato(Raiz(), dato);		break;
			case 3: continuar=0;system("cls");																	break;
			default: printf("respuesta invalida\n");
		}
	}
	/*FILE *UnArchivo;
	int cantElemento,contador,dato;
	UnArchivo=fopen("file10e6","rb");
	fread(&(cantElemento),1,sizeof(int),UnArchivo);
	for(contador=0;contador<cantElemento;contador++)
	{
		fread(&(dato),1,sizeof(int),UnArchivo);
		Agregar_Dato(Raiz(),dato);
	}
	fclose(UnArchivo);*/
}

