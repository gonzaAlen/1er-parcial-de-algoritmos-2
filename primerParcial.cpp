//se tiene una cola cargada con datos de una encuesta hecah a los diferentes municipios de posadas, la cola cuenta con los campos: municipio, barrio,edad, respuesta y el puntero sgt.
//realizar un algoritmo que permita ordenar en una lista todos los datos de la cola , tambien se nesecita un modulo para ver le resultad9o de los votos: por barrio, por municipioy en general.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>



//declaracfion de los campos del struct
struct nodo{
	char barrio[30],minicipio[30];
	int edad,respuesta;
	nodo *sgt;	
};





//declaracion de los punteros de entrada y salida de la cola
struct nodo *primero = NULL;
struct nodo *ultimo = NULL;

//declaracion del puntero de lista
struct nodo *cab = NULL;



//prototipado
void cargaCola(char muni[30], char bar[30], int e, int resp);
int colaVacia();
void leeCola();
void borrarTopeCola();
void ordenaEnLista();
void leeLista();
void resultadosDeEncuesta();
int menu();







int main(){
	char barrio[30],minicipio[30];
	int edad,respuesta , b = 1, op;
	
	op = menu();
	while(op != 0){
		if(op == 1){
			while(b != 0){
				fflush(stdin);
				printf("\nMunicipio: ");
				gets(minicipio);
				printf("Barrio: ");
				gets(barrio);
				printf("edad: ");
				scanf("%i",&edad);
				printf("Respuesta: ");
				scanf("%i",&respuesta);
				cargaCola(minicipio, barrio, edad, respuesta);
				printf("\nIngrese:\n1-Cargar otra.\n0-Salir\nop: ");
				scanf("%i",&b);
			}
			printf("\nse cargaron todos los datos correctamente\n");
			system("pause");
		}else if(op == 2){
			while(!colaVacia()){
				ordenaEnLista();
				borrarTopeCola();
			}
			printf("\nse oredenaron los datos correctamente\n");
			system("pause");
		}else if(op == 3){
			leeLista();
			system("pause");
		}else if(op == 4){
			resultadosDeEncuesta();
			system("pause");
		}else{
			printf("\nOpcion incorrecta\n");
		}
		
		op = menu();
	}
	
	
	
	return 0;
}




//carga los datos enviado por parametro a la cola
void cargaCola(char muni[30], char bar[30], int e, int resp){
	struct nodo *nv = (struct nodo*)malloc(sizeof(struct nodo));
	
	strcpy(nv->minicipio, muni);
	strcpy(nv->barrio, bar);
	nv->edad = e;
	nv->respuesta = resp;
	nv->sgt = NULL;
	
	if(colaVacia()){
		primero = nv;
		ultimo = nv;
	}else{
		ultimo->sgt = nv;
		ultimo = nv;
	}
	
}
//---------------------------------------------------------



//veriica si la cola esta vacia
int colaVacia(){
	if(primero == NULL) return 1;
	else return 0;
}
//------------------------------




//lee el contenido de la cola de una manera incorrecta
void leeCola(){
	struct nodo *reco = primero;
	
	while(reco != NULL){
		puts(reco->minicipio);
		puts(reco->barrio);
		printf("Edad: %i",reco->edad);
		printf("\nRespuesta: %i",reco->respuesta);
		printf("\n---------------------------\n");
		reco = reco->sgt;
	}
	
}
//-------------------------------------------------




//borra enl nodo que esta primero en la cola
void borrarTopeCola(){
	struct nodo *borra;
	struct nodo *reco = primero;
	
	borra = reco;
	reco = reco->sgt;
	primero = reco;
	free(borra);
}
//-----------------------------------------





//carga una lista al mismo tiempo que las va ornedando por barrio y municipio
void ordenaEnLista(){
	struct nodo *nv = (struct nodo*)malloc(sizeof(struct nodo));
	struct nodo *aux = cab;
	struct nodo *cola = primero;
	
	if(!colaVacia()){
		strcpy(nv->minicipio, cola->minicipio);
		strcpy(nv->barrio, cola->barrio);
		nv->edad = cola->edad;
		nv->respuesta = cola->respuesta;
		nv->sgt = NULL;
	}
	
	if(aux == NULL){
//		entra por aca si no existe elementos en la lista
		cab = nv;
		aux = NULL;
	}else{
		if(aux->sgt == NULL){
//			entra por aca si la lista tiene un solo nodo
			aux->sgt = nv;
			aux = NULL;
		}else{
//			entra por aca cuando hay dos o mas nodos cargados
			while(aux != NULL){
				if(aux->sgt == NULL){
					aux->sgt = nv;
					aux = NULL;
				}else if(strcmp(nv->minicipio,aux->minicipio) == 0){
					if(strcmp(nv->barrio,aux->barrio) == 0){
//						entra si es igual al barrio y al municipio
						nv->sgt = aux->sgt;
						aux->sgt = nv;
						aux = NULL;
					}else if(strcmp(nv->minicipio,aux->sgt->minicipio) != 0){
//						entra si el municipio que viene es distinto y lo carga
						nv->sgt = aux->sgt;
						aux->sgt = nv;
						aux = NULL;
					}else{
						aux = aux->sgt;
					}
				}else{
//					si no encutra ningun parecido cambia al siguiente nodo de la lista
					aux = aux->sgt;
				}
				
			}
				
		}
		
	}
	
}
//---------------------------------------------------------------------------------





//lee la lista ordenada 
void leeLista(){
	struct nodo *reco = cab;
	
	while(reco != NULL){
		puts(reco->minicipio);
		puts(reco->barrio);
		printf("Edad: %i",reco->edad);
		printf("\nRespuesta: %i",reco->respuesta);
		printf("\n---------------------------\n");
		reco = reco->sgt;
	}
	
}
//-------------------------------------------




//muestra los resultados de la encuesta
void resultadosDeEncuesta(){
	int Buno = 0,Bdos = 0, Btres = 0,Muno = 0,Mdos = 0, Mtres = 0,Guno = 0,Gdos = 0, Gtres = 0, b = 0;
//	creo dos punteros para poder compar y recorrer la lista al mismo timpo
	struct nodo *aux = cab;
	struct nodo *reco = cab;
	
	while(aux != NULL){
//		ya empiezo a contar porque ya se verifico que por lo menos tengo un nodo con contenido
		if(reco->respuesta == 1){
			Buno++;
			Muno++;
			Guno++;
		}else if(reco->respuesta == 2){
			Bdos++;
			Mdos++;
			Gdos++;
		}else if(reco->respuesta == 3){
			Btres++;
			Mtres++;
			Gtres++;
		}
		if(reco->sgt != NULL){//compruebo que el siguiente nodo no sea NULL antes de pasarme
			reco = reco->sgt;
			if(strcmp(reco->minicipio,aux->minicipio) != 0){//verifica que el municipio que venga no sea distinto al que estoy, si es asi entonces muestra los resultados obtenidos hasta el momento e inicializa los contadores
				printf("\n\nMunicipio %s:",aux->minicipio);
				printf("\n1er opcion: %i",Muno);
				printf("\n2da opcion: %i",Mdos);
				printf("\n3er opcion: %i",Mtres);
				printf("\n---------------");
				b = 1;
				Muno = 0;
				Mdos = 0; 
				Mtres = 0;
			}
			if((strcmp(reco->barrio,aux->barrio) != 0) || (b == 1) ){ //lo mismo que el if de arriba pero comparando los barrios
				printf("\n\nBarrio %s:",aux->barrio);
				printf("\n1er opcion: %i",Buno);
				printf("\n2da opcion: %i",Bdos);
				printf("\n3er opcion: %i",Btres);
				Buno = 0;
				Bdos = 0; 
				Btres = 0;
				b = 0;
				
			}
			aux = reco;
		}else{
//			muetra el o los ultimos resultados acumulados
			printf("\n\nBarrio %s:",aux->barrio);
			printf("\n1er opcion: %i",Buno);
			printf("\n2da opcion: %i",Bdos);
			printf("\n3er opcion: %i",Btres);
			printf("\n\nMunicipio %s:",aux->minicipio);
			printf("\n1er opcion: %i",Muno);
			printf("\n2da opcion: %i",Mdos);
			printf("\n3er opcion: %i",Mtres);
			
			aux =NULL;
			reco = NULL;
		}
	}
	
	
	printf("\n\nGeneral:");
	printf("\n1er opcion: %i",Guno);
	printf("\n2da opcion: %i",Gdos);
	printf("\n3er opcion: %i\n\n",Gtres);
	
	
	
}
//---------------------------------------------------------------------------------





//retoorna el valor de la funciuon que desea realizar
int menu(){
	int opc;
	system("cls");
	printf("\t\t\t\t\t1er Parcial\n\n");
	printf("Ingrese una opcion:");
	printf("\n1-Cargar una cola con los resultados de la encuesta.");
	printf("\n2-Ordenar por barrios y municipio la cola en una lista.");
	printf("\n3-Leer la lista");
	printf("\n4-Ver resultados de la encuesta");
	printf("\n0-Salir");
	printf("\nopcion: ");
	scanf("%i",&opc);
	
	return opc;
}
//-----------------------------------------------------------------