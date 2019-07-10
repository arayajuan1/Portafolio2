#include "laboratorio5.h"
////////////////////////////////////////
int main()
{
	int *arreglo,h=0,i=0;


Arbol *unArbol=iniciar();	

	
insertar(&unArbol,5);
insertar(&unArbol,2); 
insertar(&unArbol,3);  
insertar(&unArbol,1);
insertar(&unArbol,8); 
insertar(&unArbol,52);
insertar(&unArbol,21); 
insertar(&unArbol,37);

 h=altura(unArbol);
printf("la altura es: %d \n ",h);
arreglo=(int*)malloc(sizeof(int)*h);
while(i<pow(2,h))
{
	arreglo[i]=0;	i++;
}
	MostrarArbol(unArbol);
	insertar_arbol_en_arreglo(&unArbol,0,arreglo);
	imprimir_arreglo(arreglo,h);


}
