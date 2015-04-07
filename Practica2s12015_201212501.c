
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//VARIABLES
long duracionInserta = 0, duracionRecorrido = 0, duracionBurbuja = 0, duracionQuicksort = 0;
clock_t t1, t2;
char cGrafica[200],cInserta[80],cNo[80], cGrafica2[200], cRecorrido[80], cGrafica3[200], cBurbuja[80], cGrafica4[200], cQuick[80], cTemp[80], cGrafica5[200];

//ESTRUCTURAS
enum {left, rig};
typedef struct estructuraArbol{
	int dato;
	int fe;
	struct estructuraArbol *up;
	struct estructuraArbol *left;
	struct estructuraArbol *rig;
	
}
Nodo;
typedef Nodo *Arbol,*nodo_up;
struct nlis{
	int dato;
	struct nlis* sig;
};

typedef struct nlis *Tlista;
Tlista pri, ult;

//METODOS
long tiemp(clock_t t1, clock_t t2);
void recorrido(Arbol arbol);
void add(int n);
void burbuja(Tlista lista);
void qs(int lista[],int fTempite_left,int fTempite_rig);
void Inserta(Arbol *arbol, int nodo);
void balance(Arbol *raiz, nodo_up nodo, int, int);
void rotacionleft(Arbol *raiz, nodo_up nodo);
void rotacionrig(Arbol *raiz, nodo_up nodo);
void rotacionrigleft(Arbol *raiz, nodo_up nodo);
void rotacionrigrig(Arbol *raiz, nodo_up nodo);
void graficar(int cont);

FILE * archivo;
Arbol arbol = NULL; 
char cad[100],* dirArchivo;  //array linea: guarda la linea mas larga del fichero
int numero = 0, cont = 0, i ,j, y, w, k;
int arreglo[1000000];

int main(){	
	//LEE LINEA X LINEA EL ARCHIVO E INSERTA
	dirArchivo = "C:/Users/Natthaliee/Desktop/texto.txt";
	archivo=fopen(dirArchivo, "r");
			
	if (archivo==NULL){
   		perror ("Error al abrir fichero.txt");
   		return -1;
	}else{
		printf("Insertando datos al árbol: \n");
		t1 = clock();
		while(fgets(cad,1000000,archivo)!=NULL){
			printf("%s",cad);
			Inserta(&arbol,atoi(cad));
			add(atoi(cad));
			cont=cont+1;
			arreglo[k]	= atoi(cad);
			k++;
		}
		fclose(archivo);
		t2 = clock();
		duracionInserta = tiemp(t1, t2);
		printf("\nTiempo Insercion: %ld milisegundos\n",duracionInserta);
	}
	//RECORRIDO	
	printf("\n\nRecorrido enOrden:\n");
	t1 = clock();
	//recorrido(arbol);
	if(arbol!=NULL){
		recorrido(arbol->left);
		recorrido(arbol->rig);
	}
	t2 = clock();
	duracionRecorrido = tiemp(t1, t2);
	printf("\nTiempo Recorrido: %ld milisegundos\n",duracionRecorrido);
	
	//ORDENAMIENTO
	ordenamiento(arbol,k);
	
	//GRAFICA
	printf("Presione cualquier tecla para continuar..");
	getchar();
	graficar(cont);
	
	//SALIR
	system("PAUSE");
	return 0;
}

long tiemp(clock_t t1, clock_t t2) {
    long duracion = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return duracion;
}

void recorrido(Arbol arbol){
	if(arbol!=NULL){
		recorrido(arbol->left);
		recorrido(arbol->rig);
	}
}

void ordenamiento(Arbol arbol,int k){
	
	//ORDENAMIENTO BURBUJA EN LISTA
	Tlista pri2;
	pri2= pri;
	
	printf("\n\nLOrdenamiento Burbuja:\n");
	t1 = clock();
	burbuja(pri);
	t2 = clock();
	duracionBurbuja = tiemp(t1, t2);
	printf("\nTiempo Ordenamiento Burbuja: %ld milisegundos\n",duracionBurbuja);
	
	//ORDENAMIENTO BURBUJA ARRAY
	printf("\n\nOrdenamiento Burbuja:\n");
	t1 = clock();
		for (y=1; y<k;y++) 
         {
            for(w=0;w<k-1;w++)
            {
               if (arreglo[w]>arreglo[w+1])
               {
                  int temp=arreglo[w];
                  arreglo[w]=arreglo[w+1];
                  arreglo[w+1]=temp;
               }
            }
         } 
         
         for ( j=0; j<k; j++) {
	        printf("%d",arreglo[j]);
	        if(j<k-1)
	            printf(" ");
	    }
	t2 = clock();
	
	duracionBurbuja = tiemp(t1, t2);
	printf("\nTiempo Ordenamiento Burbuja: %ld milisegundos\n",duracionBurbuja);
	
	//ORDENAMIENTO QUICKSORT
	printf("\n\nOrdenamiento QuickSort:\n");
	t1 = clock();
	qs(arreglo,0,k-1);
	
	for ( j=0; j<k; j++) {
	        printf("%d",arreglo[j]);
	        if(j<k-1)
	            printf(" ");
	    }
	t2 = clock();
	
	duracionQuicksort = tiemp(t1, t2);
	printf("\nTiempo Ordenamiento QuickSort: %ld milisegundos\n",duracionQuicksort);
}

void rotacionrigleft(Arbol *a, nodo_up nodo){
	nodo_up up = nodo->up;
	nodo_up nodo2 = nodo;
	nodo_up nodo3 = nodo2->rig;
	nodo_up nodo5 = nodo3->left;
	nodo_up nodo4 = nodo5->left;
	nodo_up nodo6 = nodo5->rig;
	if(up)
	if(up->rig == nodo) up->rig = nodo5;
	else up->left = nodo5;
	else *a = nodo5;
	nodo2->rig = nodo4;
	nodo3->left = nodo6;
	nodo5->left = nodo2;
	nodo5->rig = nodo3;
	nodo5->up = up;
	nodo2->up = nodo3->up = nodo5;
	if(nodo4) nodo4->up = nodo2;
	if(nodo6) nodo6->up = nodo3;
	switch(nodo5->fe) {
		case -1: 
			nodo2->fe = 0; 
			nodo3->fe = 1; 
		break;
		case 0: 
			nodo2->fe = 0; 
			nodo3->fe = 0; 
		break;
		case 1: 
			nodo2->fe = -1; 
			nodo3->fe = 0; 
		break;
	}
	nodo5->fe = 0;
}

void rotacionrigrig(Arbol *raiz, Arbol nodo){
	nodo_up up = nodo->up;
	nodo_up nodo2 = nodo;
	nodo_up nodo3 = nodo2->left;
	nodo_up nodo5 = nodo3->rig;
	nodo_up nodo4 = nodo5->left;
	nodo_up nodo6 = nodo5->rig;
	if(up)
		if(up->rig == nodo) up->rig = nodo5;
		else up->left = nodo5;
	else *raiz = nodo5;
		nodo3->rig = nodo4;
		nodo2->left = nodo6;
		nodo5->left = nodo3;
		nodo5->rig = nodo2;
		nodo5->up = up;
		nodo2->up = nodo3->up = nodo5;
	if(nodo4) nodo4->up = nodo3;
	if(nodo6) nodo6->up = nodo2;
	switch(nodo5->fe) {
	case -1: 
		nodo3->fe = 0; 
		nodo2->fe = 1; 
	break;
	case 0: 
		nodo3->fe = 0; 
		nodo2->fe = 0; 
	break;
	case 1: 
		nodo3->fe = -1; 
		nodo2->fe = 0; 
		break;
	}
	nodo5->fe = 0;
}
//MÉTODO TIEMPO MILISEGUNDOS
void qs(int lista[],int fTempite_left,int fTempite_rig)
	{
	    int left,rig,temporal,pivote;
	    left=fTempite_left;
	    rig = fTempite_rig;
	    pivote = lista[(left+rig)/2];
	 
	    do{
	        while(lista[left]<pivote && left<fTempite_rig)left++;
	        while(pivote<lista[rig] && rig > fTempite_left)rig--;
	        if(left <=rig){
	            temporal= lista[left];
	            lista[left]=lista[rig];
	            lista[rig]=temporal;
	            left++;
	            rig--;
	        }
	    }
		while(left<=rig);
    	if(fTempite_left<rig){
			qs(lista,fTempite_left,rig);
		}
	    if(fTempite_rig>left){
			qs(lista,left,fTempite_rig);
		}
	}
	
void add(int n){
	Tlista nuevo= malloc(sizeof(Tlista));
	nuevo->sig=NULL;
	nuevo->dato=n;
	if(pri==NULL){
		pri=nuevo;
		ult=nuevo;
	}else{
		ult->sig=nuevo;
		ult=nuevo;
	}	
}

void Inserta(Arbol *arbol, int nodo){
	nodo_up up = NULL;
	nodo_up primero = *arbol;
	while(primero!=NULL && nodo != primero->dato) {
		up = primero;
		if(nodo < primero->dato){
			primero = primero->left;
		} else if(nodo > primero->dato){
			primero = primero->rig;
		} 
	}
	if(primero!=NULL) return;
	if(up==NULL) {
		*arbol = (Arbol)malloc(sizeof(Nodo));
		(*arbol)->dato = nodo;
		(*arbol)->left = (*arbol)->rig = NULL;
		(*arbol)->up = NULL;
		(*arbol)->fe = 0;
	}
	else if(nodo < up->dato) {
		primero = (Arbol)malloc(sizeof(Nodo));
		up->left = primero;
		primero->dato = nodo;
		primero->left = primero->rig = NULL; 
		primero->up = up;
		primero->fe = 0;
		balance(arbol, up, left, 1);
	}
	else if(nodo > up->dato) {
		primero = (Arbol)malloc(sizeof(Nodo));
		up->rig = primero;
		primero->dato = nodo;
		primero->left = primero->rig = NULL;
		primero->up = up;
		primero->fe = 0;
		balance(arbol, up, rig, 1);
	}
}


void rotacionleft(Arbol *a, nodo_up nodo){
	nodo_up up = nodo->up;
	nodo_up nodo2 = nodo;
	nodo_up nodo3 = nodo2->rig;
	nodo_up nodo4 = nodo3->left;
	if(up)
		if(up->rig == nodo2) up->rig = nodo3;
		else up->left = nodo3;
	else *a = nodo3;
		nodo2->rig = nodo4;
		nodo3->left = nodo2;
		nodo2->up = nodo3;
		if(nodo4) nodo4->up = nodo2;
		nodo3->up = up;
		nodo2->fe = 0;
		nodo3->fe = 0;
}

void rotacionrig(Arbol *a, nodo_up nodo){
	nodo_up up = nodo->up;
	nodo_up nodo2 = nodo;
	nodo_up nodo3 = nodo2->left;
	nodo_up nodo4 = nodo3->rig;
	if(up)
		if(up->rig == nodo2) up->rig = nodo3;
		else up->left = nodo3;
	else *a = nodo3;
		nodo2->left = nodo4;
		nodo3->rig = nodo2;
		nodo2->up = nodo3;
		if(nodo4) nodo4->up = nodo2;
		nodo3->up = up;
		nodo2->fe = 0;
		nodo3->fe = 0;
}

//GRAFICA CADA UNO DE LOS TIEMPOS
void graficar(int cont){
	FILE *grafica;
	FILE *grafica2;
	FILE *grafica3;
	FILE *grafica4;
	FILE *grafica5;
	
	if(grafica==NULL){
		fprintf(stderr, "Error al graficar %s", "C:/gnuplot/bin/gnuplot.exe -perotacionleftst");
		exit(EXIT_FAILURE);
	}else{
		

		//GRAFICA INSERTA
		float ultserta=duracionInserta;
		sprintf(cInserta, "%f", ultserta);
		sprintf(cNo, "%i", k);
		strcpy(cGrafica, "C:/gnuplot/bin/gnuplot.exe -perotacionleftst -p -e \"plot [0:");
		strcat(cGrafica, cInserta);strcat(cGrafica, "][0:");strcat(cGrafica, cNo);
		strcat(cGrafica, "] ");	strcat(cGrafica, cNo);strcat(cGrafica, "*x/");
		strcat(cGrafica, cInserta);strcat(cGrafica, " title 'Insertar'");strcat(cGrafica, "\"");
		system(cGrafica);
		
		//GRAFICA RECORRIDO
		float fRecorrido=duracionRecorrido;
		sprintf(cRecorrido, "%f", fRecorrido);
		strcpy(cGrafica2, "C:/gnuplot/bin/gnuplot.exe -perotacionleftst -p -e \"plot [0:");
		strcat(cGrafica2, cRecorrido);strcat(cGrafica2, "][0:");strcat(cGrafica2, cNo);
		strcat(cGrafica2, "] ");strcat(cGrafica2, cNo);strcat(cGrafica2, "*x/");
		strcat(cGrafica2, cRecorrido);strcat(cGrafica2, " title 'Recorrido'");strcat(cGrafica2, "\"");
		system(cGrafica2);
		
		//GRAFICA ORDENAMIENTO BURBUJA
		float fBurbuja=duracionBurbuja;
		
		sprintf(cBurbuja, "%f", fBurbuja);
		strcpy(cGrafica3, "C:/gnuplot/bin/gnuplot.exe -perotacionleftst -p -e \"plot [0:");
		strcat(cGrafica3, cBurbuja);strcat(cGrafica3, "][0:");strcat(cGrafica3, cNo);
		strcat(cGrafica3, "] ");strcat(cGrafica3, cNo); strcat(cGrafica3, "*x/");
		strcat(cGrafica3, cBurbuja);strcat(cGrafica3, " title 'Ordenamiento Burbuja'");strcat(cGrafica3, "\"");
		system(cGrafica3);
		
		//GRAFICA QUICKSORT
		float fQuick=duracionQuicksort;
		
		sprintf(cQuick, "%f", fQuick);
		strcpy(cGrafica4, "C:/gnuplot/bin/gnuplot.exe -perotacionleftst -p -e \"plot [0:");
		strcat(cGrafica4, cQuick);strcat(cGrafica4, "][0:");strcat(cGrafica4, cNo);
		strcat(cGrafica4, "] ");strcat(cGrafica4, cNo);strcat(cGrafica4, "*x/");
		strcat(cGrafica4, cQuick);strcat(cGrafica4, " title 'Ordenamiento Quick'");strcat(cGrafica4, "\"");
		system(cGrafica4);
		
		//GRAFICA COMPLETA
		float fTemp= fQuick;
		if (fBurbuja>fTemp){  fTemp=fBurbuja;  }
		if (ultserta>fTemp){  fTemp=ultserta;  }
		if (fRecorrido>fTemp){fTemp=fRecorrido;}
		
		sprintf(cTemp, "%f", fTemp);
		strcpy(cGrafica5, "plot [0:");
		strcat(cGrafica5, cTemp);strcat(cGrafica5, "][0:");strcat(cGrafica5, cNo);strcat(cGrafica5, "] ");
		strcat(cGrafica5, cNo);strcat(cGrafica5, "*x/");strcat(cGrafica5, cInserta);strcat(cGrafica5, " title 'Insercion',");
		strcat(cGrafica5, cNo);strcat(cGrafica5, "*x/");strcat(cGrafica5, cRecorrido);strcat(cGrafica5, " title 'Recorrido',");
		strcat(cGrafica5, cNo);strcat(cGrafica5, "*x/");strcat(cGrafica5, cBurbuja);strcat(cGrafica5, " title 'Ordenamiento Burbuja',");
		strcat(cGrafica5, cNo);strcat(cGrafica5, "*x/");strcat(cGrafica5, cQuick);strcat(cGrafica5, " title 'Ordenamiento Quick'");

		grafica= popen("C:/gnuplot/bin/gnuplot.exe -perotacionleftst", "w");
		
		fprintf(grafica,"set title \"Grafica Completa Datos vs Tiempo\"\n");
		fprintf(grafica,"set ylabel \"Datos\"\n");
		fprintf(grafica,"set xlabel \"Tiempo\"\n");
		fprintf(grafica,"set terminal png\n");
		fprintf(grafica,"set output 'gCompleta.png'\n");
		fprintf(grafica,cGrafica5);
		fflush(grafica);
		getchar();
		pclose(grafica);
		
		getchar();
			
		return(EXIT_SUCCESS);
	}
}
//METODO BURBUJA 2
void burbuja(Tlista lista){
	Tlista lista2, temp;
	int t;
	
	while(lista->sig != NULL){
		lista2 = lista->sig;
		while(lista2!=NULL){
			if(lista->dato > lista2->dato){
				t = lista2->dato;
				lista2->dato = lista->dato;
				lista->dato = t;
			}
			lista2 = lista2->sig;
		}
		lista = lista->sig;
		lista2 = lista->sig;
	}
	temp=pri;
	while(temp!=NULL){
		printf("%d ",temp->dato);
		temp=temp->sig;
	}
}






//BALANCE DEL ARBOL FE(FACTOR DE EQUILIBRIO)
void balance(Arbol *arbol, nodo_up nodo, int arista, int nuevo){
	int salir = 0;
	while(nodo && !salir) {
		if(nuevo)
			if(arista == left) nodo->fe--;
			else nodo->fe++;
		else
		if(arista == left) nodo->fe++;
		else nodo->fe--;
		
		if(nodo->fe == 0) salir = 1; 
		else if(nodo->fe == -2) {
		
			if(nodo->left->fe == 1){
				rotacionrigrig(arbol, nodo); 
			} else{
				rotacionrig(arbol, nodo); 
			} 
			salir = 1;
		}else if(nodo->fe == 2) { 
			if(nodo->rig->fe == -1){
				rotacionrigleft(arbol, nodo);
			}  else{
				rotacionleft(arbol, nodo); 
			} 
			salir = 1;
		}
		if(nodo->up)
		if(nodo->up->rig == nodo) arista = rig; else arista = left;
	}
}




