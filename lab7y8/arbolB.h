#ifndef stdio_h
#include <stdio.h>
#define stdio_h
#endif

#ifndef stdlib_h
#include <stdlib.h>
#define stdlib_h
#endif

#ifndef string_h
#include <string.h>
#define string_h
#endif

#define TAMANO 2
//////////////////////////////////////////////////////////////////////////////
typedef struct nodo_int
{
	int tipo,cantidad,nombre_propio;
	int claves[(TAMANO*2)+1],hijos[(TAMANO*2)+2];
}Nodo;
typedef struct cabeza
{
	int digito;
	int nombre_R;
}Cab;
//////////////////////////////////////////////////////////////////////////////
void Crear_Cabeza()
{
	Cab *aux;
	aux=malloc(sizeof(Cab));
	aux->nombre_R=0;
	aux->digito=1;
	FILE *Archivo;
	Archivo=fopen("info","wb");
	fwrite(aux,sizeof(Cab),1,Archivo);///--->
	fclose(Archivo);
}
//////////////////////////////////////////////////////////////////////////////
void Guardar_Nodo(Nodo *aux)
{
    FILE *Arc;
    char nombre[10];
    sprintf(nombre,"%i",aux->nombre_propio);
	Arc=fopen(nombre,"wb");
	fwrite(aux,sizeof(Nodo),1,Arc);
	fclose(Arc);
}
//////////////////////////////////////////////////////////////////////////////
void Crear_Arbol_B()
{
	Crear_Cabeza();
    Nodo *aux;
    aux=malloc(sizeof(Nodo));
    aux->tipo=1;
    aux->cantidad=-1;
	aux->nombre_propio=0;
    int i=0;
    for(i;i<=TAMANO*2;i++)
    {
        aux->claves[i]=0;
        aux->hijos[i]=-1;
    }
    aux->hijos[i]=-1;
    Guardar_Nodo(aux);
    free(aux);
}
//////////////////////////////////////////////////////////////////////////////
int Raiz()//busca arhivo que contiene info cobre la raiz, sino la encuentra retornara -1 si lo encuentra retorna el nombre de la raiz
{
	FILE *Archivo; Cab *aux;
	Archivo=fopen("info","rb");
	if(Archivo==NULL)
	{
		fclose(Archivo);
		return(-1);
	}
	else
	{
		aux=malloc(sizeof(Cab));
		fread(aux,sizeof(Cab),1,Archivo);/// <----
		int N=aux->nombre_R;
		free(aux);
		fclose(Archivo);
		return(N);
	}
}
//////////////////////////////////////////////////////////////////////////////
int Crear_Nombre()
{
	FILE *Archivo; Cab *aux;
	Archivo=fopen("info","rb");
	if(Archivo==NULL)
	{
		printf("ERROR, RAIZ NO ENCONTRADA...\n");
		fclose(Archivo);
	}
	else
	{
		aux=malloc(sizeof(Cab));
		fread(aux,sizeof(Cab),1,Archivo);
		int digito = aux->digito;
		aux->digito=aux->digito+1;
		fclose(Archivo);
		Archivo=fopen("info","wb");
		fwrite(aux,sizeof(Cab),1,Archivo);//--->
		fclose(Archivo);
		free(aux);
		return(digito);
	}
}
//////////////////////////////////////////////////////////////////////////////
Nodo* Leer_Nodo(int digito)
{
	Nodo *aux;
	char Nombre[10];
	sprintf(Nombre,"%i",digito);
	FILE *Archivo;
	Archivo=fopen(Nombre,"rb");
	aux=malloc(sizeof(Nodo));
	fread(aux,sizeof(Nodo),1,Archivo);
	fclose(Archivo);
	return(aux);
}
//////////////////////////////////////////////////////////////////////////////
int Buscar_Dato(int arbol,int dato)
{
    if(arbol==-1)
    {
        printf("arbol no existe\n");
		return(-1);
    }
    Nodo *aux;
    aux=Leer_Nodo(arbol);
    int i=0;
    while((i<=aux->cantidad)&&(dato>aux->claves[i]))
    {
        i++;
    }
    if((i<=aux->cantidad)&&(dato==aux->claves[i]))
    {
		printf("Dato existe\n");
        return(aux->nombre_propio);
    }
    if(aux->tipo==1)
    {
        free(aux);
        printf("Dato no existe\n");
        return(-1);
    }
    else
    {
        int hijo;
		hijo=aux->hijos[i];
        free(aux);
        return(Buscar_Dato(hijo,dato));
    }
}
//////////////////////////////////////////////////////////////////////////////
void imprimir(int Nombre)
{
	if(Nombre!=-1)
	{ int contador=0;
		Nodo *aux;char N[10];
		FILE *Ar;int i;
		sprintf(N,"%i",Nombre);
		Ar=fopen(N,"rb");
		aux=malloc(sizeof(Nodo));
		fread(aux,sizeof(Nodo),1,Ar);
		fclose(Ar);
		//if(aux->tipo==0)
		//{
			printf("///////////////////////////////////////////////\n");
			printf("Nombre Archivo: %i \n",aux->nombre_propio);
			printf("Tipo: %i    Cantidad de elementos: %i\n",aux->tipo,aux->cantidad+1);
			printf("Datos:");
			for(i=0;i<(TAMANO*2)+1;i++)
			{
				if(aux->claves[i]!=0)
				{
					printf("|%i",aux->claves[i]);
				}
			}
			printf("\n--------------------------------");
			printf("\nNombre Hijos:");
			for(i=0;i<(TAMANO*2)+2;i++)
			{
				if(aux->hijos[i]!=-1)
				{
					contador++;
					printf("|%i",aux->hijos[i]);
				}
			}
			printf("\ncantidad de hijos: %i\n///////////////////////////////////////////////\n",contador);
		//}
		for(i=0;i<=(TAMANO*2)+1;i++)
		{
			if(aux->hijos[i]!=-1)
			{
				imprimir(aux->hijos[i]);
			}
		}
		free(aux);
	}
}
//////////////////////////////////////////////////////////////////////////////
void Dividir_hijo(Nodo *Padre ,int i ,Nodo *Hermano_IZQ ){
	Nodo *Hermano_DER;   
	Hermano_DER=malloc(sizeof(Nodo));
	Hermano_DER->tipo=Hermano_IZQ->tipo;
	Hermano_DER->cantidad=TAMANO-1;
	int k=0;
	for(k;k<=TAMANO*2;k++)
	{
	    Hermano_DER->claves[k]=0;
	    Hermano_DER->hijos[k]=-1;
	}
	Hermano_DER->hijos[k]=-1;
	Hermano_DER->nombre_propio = Crear_Nombre();
	int j;
	
	//traslado claves
	for(j=0;j<=(TAMANO-1);j++)
	{
		Hermano_DER->claves[j]=Hermano_IZQ->claves[j+TAMANO+1];
		Hermano_IZQ->claves[j+TAMANO+1]=0;
	}
	
	//traslado hijos
	if(Hermano_DER->tipo==0)//si no es hoja
	{
		for(j=0;j<TAMANO+1;j++)
		{
			Hermano_DER->hijos[j]=Hermano_IZQ->hijos[j+TAMANO+1];
			Hermano_IZQ->hijos[j+TAMANO+1]=-1;
		}
	}
	
	Hermano_IZQ->cantidad=TAMANO-1;
	
	
	for(j=Padre->cantidad+1;j>=i + 1;j--)//rehubica los hijos del padre en las posiciones correctas
	{
		Padre->hijos[j+1]=Padre->hijos[j];
	}
	
	
	Padre->hijos[i+1] = Hermano_DER -> nombre_propio;
	
	for(j=Padre->cantidad;j>=i;j--){
		Padre->claves[j+1]=Padre->claves[j];
	}
	
	Padre->claves[i]=Hermano_IZQ->claves[TAMANO];
	
	Hermano_IZQ->claves[TAMANO]=0;
	
	Padre->cantidad=Padre->cantidad+1;
	
	Guardar_Nodo(Padre);
	Guardar_Nodo(Hermano_DER);
	Guardar_Nodo(Hermano_IZQ);
	free(Hermano_DER);
}
//////////////////////////////////////////////////////////////////////////////
void Insertar_Dato(Nodo *aux,int dato){
	int i = aux->cantidad;
	
	//si es hoja solo encuentro clave e ingreso
	
	if(aux->tipo == 1){//si es hoja 
		//busco desde clave[i] posicion de la clave mayor hacia atras
		while((i >= 0) && (dato < aux->claves[i])){
			aux->claves[i+1] = aux->claves[i];
			i--;
		}
		i++;
		aux->claves[i] = dato;
		
		aux->cantidad = aux->cantidad+1;
		
		Guardar_Nodo(aux);
		
	}	else{ 
	
		while((i>=0)&&(dato<aux->claves[i]))
		{
			i=i-1;
		}
		i++;
		
		Nodo *auxB;
		
		auxB = Leer_Nodo(aux->hijos[i]);
		
		if(auxB -> cantidad == 2*TAMANO)
		{
			Dividir_hijo(aux,i,auxB);
			
			if(dato>aux->claves[i])
			{
				i++;
				free(auxB);
				auxB = Leer_Nodo(aux->hijos[i]);
			}
			
		}
		Insertar_Dato(auxB,dato);
		free(auxB);
		

	
	
	}
}
//////////////////////////////////////////////////////////////////////////////
void Agregar_Dato(int Nombre_Nodo,int dato)
{
	Nodo *aux;
	if(Nombre_Nodo==-1)
	{
		Crear_Arbol_B();
		aux=Leer_Nodo(0);// extrae contenido 
	}
	else
	{
		aux=Leer_Nodo(Nombre_Nodo);
	}
	
	
	
	if(aux->cantidad==(2*TAMANO))// si esta lleno se hace esto, si no se inserta  libremente
	{
		
		
		Nodo *New_aux;int nombreAUX;
		New_aux=malloc(sizeof(Nodo));
		int i=0;
		for(i;i<=TAMANO*2;i++)
		{
		    New_aux->claves[i]=0;
		    New_aux->hijos[i]=-1;
		}
		New_aux->hijos[i]=-1;
		
		
		New_aux->nombre_propio=Crear_Nombre();
		
		
		nombreAUX=New_aux->nombre_propio;
		
		New_aux->nombre_propio=aux->nombre_propio;
		
		aux->nombre_propio=nombreAUX;
		
		New_aux->tipo = 0;
		New_aux->cantidad=-1;
		New_aux->hijos[0]=aux->nombre_propio;
		
		Dividir_hijo(New_aux,0,aux);
		Insertar_Dato(New_aux,dato);
		free(New_aux);
		free(aux);
	}
	else
		{
		Insertar_Dato(aux,dato);
		free(aux);
	}
}
