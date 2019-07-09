typedef struct nodo
{
	char dato;
  	struct nodo *izquierda,*derecha;
}AB;
///////////////////////
AB *iniciar_arbol()
{
	return NULL;
}
////////////////////////////
AB *crear_nodo(int dato)
{
	AB *aux;
	aux=malloc(sizeof(AB));
	aux->derecha=aux->izquierda=NULL;
	aux->dato=dato;
	return aux;
}
///////////////////////////////
int agregar(AB **arbol,char num)
{
	int exito=0;
	if(*arbol==NULL)
	{
		*arbol=crear_nodo(num);//printf("%c\n",*arbol->dato);
		return 1;
	}
	else
	{
		if((*arbol)->dato!='N')//si  nodo es distinto de n
		{
			exito=agregar(&(*arbol)->izquierda,num);
			if(exito==1){ return 1;	}else
			exito=agregar(&(*arbol)->derecha,num);//printf("%d",arbol->derecha);
			if(exito==1){ return 1; }
		}
	}
	return 0;
}
///////////////////////////////
AB *crear_arbol(char *nombrearchivoarbol)
{
	FILE *op;
	AB *arbol=iniciar_arbol();
	int letra;
	op=fopen(nombrearchivoarbol,"r");
	if(op==NULL)
	{
		printf("no existe archivo");
	}
	else
	{
		while((letra=fgetc(op))!=EOF)//lee letra x letra
		{
		//	printf("mmm %c",letra);system ("pause");
			agregar(&arbol,letra);
		}
	}
	imprimir(arbol,0);
}
/////////////////////////////////////////////
int imprimir(AB *arbol)
{ 
	if(arbol==NULL)
	{
		return;
	}
	else 
	{	printf("%c" ,arbol->dato);
		imprimir(arbol->izquierda);
		imprimir(arbol->derecha);
	}
}
