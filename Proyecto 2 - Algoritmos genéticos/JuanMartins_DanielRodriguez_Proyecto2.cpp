#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <time.h>
#include <math.h>
using namespace std;

bool auxA[3][2]={false,false,false,false,false,false};
bool auxB[3][2]={false,false,false,false,false,false};
bool moviA1=false, moviB1=false, moviA2=false, moviB2=false, aux_A=false, aux_B=false;

typedef struct{
	int efectividad;
	int stamina;
}maestro;

typedef struct{	//Cromosoma
	maestro agua;
	maestro fuego;
	maestro tierra;
}equipo;

vector<maestro>agua,fuego,tierra;
vector<equipo> equipos;
vector<equipo> generacion;                              

int random(int n){	//Random de 0 a n
	return rand()%n;
}

float aptitud(equipo x){	//Funcion de aptitud
	float apt=0.0;
	float agua = (x.agua.stamina/x.agua.efectividad)/3;
	float fuego = (x.fuego.stamina/x.fuego.efectividad)/3;
	float tierra = (x.tierra.stamina/x.tierra.efectividad)/3;
	if(agua<1) agua=-333;
	if(fuego<1) fuego=-333;
	if(tierra<1) tierra=-333;
	if((agua+fuego+tierra)/3 > apt) apt=(agua+fuego+tierra)/3;
	return apt;
}

float RandomFloat(float min, float max) {	//Random entre 0.0 y 1.0
    return  (max - min) * ((((float) rand()) / (float) RAND_MAX)) + min ;
}

void Mutacion_multibit(equipo &cromosoma, int n1, int n2, int n3){
	float const mutar = 0.3;	//constante a mutar
	float prob;					
	int size=3;
	equipo aux=cromosoma;		//guardo el cromosoma antes de modificarlo
	for(int i=0;i<size;i++){
		prob=RandomFloat(0,1);	//obtengo la probabilidad para verificar si muto o no el bit
		if(prob <= mutar){		//verifico si la probabilidad es menor o igual
			if(i==0){					
				cromosoma.agua=agua[random(n1)];	//muto el bit del maestro agua
			}
			if(i==1){
				cromosoma.fuego=fuego[random(n2)];	//muto el bit del maestro fuego
			}
			if(i==2){
				cromosoma.tierra=tierra[random(n3)];	//muto el bit del maestro tierra
			}
		}
	}
	
	if(aptitud(cromosoma)<aptitud(aux)) cromosoma=aux;	//si la aptitud del nuevo individuo es menor que la anterior, retorno el original
}

void Cruce_Mascara(equipo &padre1, equipo &padre2){
	srand (time(NULL));
	int mascara,cont=0;
	equipo hijo1,hijo2;

	for(int i=0;i<3;i++){
		mascara=random(1);		//Le asigno a mascara 0 o 1 de manera aleatoria
		if(i==0){
			if(mascara==0){				
				hijo1.agua=padre1.agua;		//Si la mascara es 0, asigno al hijo1 el gen de padre1
				hijo2.agua=padre2.agua;		//Y a hijo2 el gen de padre2
			}else{
				cont++;						//Por cada vez que salga mascara=1, sumo el contador
				hijo2.agua=padre1.agua;		//Si la mascara es 1 hijo2 hereda el gen de padre1
				hijo1.agua=padre2.agua;		//Y hijo1 hereda de padre2
			}
		}
		if(i==1){							//Lo mismo para los demas genes
			if(mascara==0){
				hijo1.fuego=padre1.fuego;
				hijo2.fuego=padre2.fuego;
			}else{
				cont++;
				hijo2.fuego=padre1.fuego;
				hijo1.fuego=padre2.fuego;
			}
		}
		if(i==2){
			if(cont==2 || mascara==0 && cont!=0){		//si cont=2, salio 1 dos veces, por ende ahora le toca al 0
				hijo1.agua=padre1.agua;					//de lo contrario verifico que la mascara sea 0 y que el 0 no haya salido dos veces
				hijo2.agua=padre2.agua;
			}else{
				hijo2.tierra=padre1.tierra;
				hijo1.tierra=padre2.tierra;
			}
		}
	}
	
	//Si los hijos tienen mejor aptitud que los padres, se usan los hijos
	if(aptitud(padre1)<aptitud(hijo1)) padre1=hijo1;
	if(aptitud(padre2)<aptitud(hijo2)) padre2=hijo2;
}

void pelea(equipo A, equipo B, int x, int y){

	int A1=2, F1=2, T1=2;
	int A2=3, F2=3, T2=3;
	int disA=1, disF=1, disT=1;
	int winA=0, winB=0;
	bool ganoA=false, ganoF=false, ganoT=false, imprimir=true;
	char campo[3][6]={'.','.','A','A','.','.','.','.','F','F','.','.','.','.','T','T','.','.'};
	
	while((!ganoA || !ganoF || !ganoT) && (A.agua.stamina>0 || A.fuego.stamina>0 || A.tierra.stamina>0 || B.agua.stamina>0 || B.fuego.stamina>0 || B.tierra.stamina>0)){
		
		//Verifica si he rodado a todo el equipo de zona
		if(!moviB1){	//Si no he confirmado que estan fuera de la zona 1
			if(auxB[0][0] && auxB[1][0] && auxB[2][0]){	//Si todos estan fuera de la zona 1
				if(A1<2 && !ganoA){
					A1++;
					campo[0][A1]='A';
					campo[0][A1-1]='.';
				}
				if(F1<2 && !ganoF){
					F1++;
					campo[1][F1]='F';
					campo[1][F1-1]='.';
				}
				if(T1<2 && !ganoT){
					T1++;
					campo[2][T1]='T';
					campo[2][T1-1]='.';
				}
				moviB1=true;	//Con este valor en true, no se verifica otra vez la zona 1
				aux_A=true;	//Significa que el equipo puede avanzar
			}
		}else{
			if(!moviB2){	//Si no he confirmado que estan fuera de la zona 2
				if(auxB[0][1] && auxB[1][1] && auxB[2][1]){	//Si todos estan fuera de la zona 2
					if(A1<2 && !ganoA){
						A1++;
						campo[0][A1]='A';
						campo[0][A1-1]='.';
					}
					if(F1<2 && !ganoF){
						F1++;
						campo[1][F1]='F';
						campo[1][F1-1]='.';
					}
					if(T1<2 && !ganoT){
						T1++;
						campo[2][T1]='T';
						campo[2][T1-1]='.';
					}
					moviB2=true;	//Con este valor en true, no se verifica otra vez la zona 2
					aux_A=true;
				}
			}
		}
		
		//Se realiza lo mismo para el otro equipo
		if(!moviA1){
			if(auxA[0][0] && auxA[1][0] && auxA[2][0]){
				if(A2>3 && !ganoA){
					A2--;
					campo[0][A2]='A';
					campo[0][A2+1]='.';
				}
				if(F2>3 && !ganoF){
					F2--;
					campo[1][F2]='F';
					campo[1][F2+1]='.';
				}
				if(T2>3 && !ganoT){
					T2--;
					campo[2][T2]='T';
					campo[2][T2+1]='.';
				}
				moviA1=true;
				aux_B=true;
			}
		}else{
			if(!moviA2){
				if(auxA[0][1] && auxA[1][1] && auxA[2][1]){
					if(A2>3 && !ganoA){
						A2--;
						campo[0][A2]='A';
						campo[0][A2+1]='.';
					}
					if(F2>3 && !ganoF){
						F2--;
						campo[1][F2]='F';
						campo[1][F2+1]='.';
					}
					if(T2>3 && !ganoT){
						T2--;
						campo[2][T2]='T';
						campo[2][T2+1]='.';
					}
					moviA2=true;
					aux_B=true;
				}
			}
		}
		
		int i,j;
		
		if(aux_A){	//Si puedo avanzar
			j=0;
			for(i=0;i<3;i++){
				if(auxA[i][1]){	//Si estaba en la zona 3, pongo en false que no he sido desplazado de la zona 2
					auxA[i][1]=false;
				}else{	//Sino, pongo en false que no he sido desplazado de la zona 1
					j++;
					auxA[i][0]=false;
				}
			}
			if(j==3){	//Si todos llegaron a la zona 1, pongo en false que hayan sido desplazados de la zona 1
				moviA1=false;
			}
			moviA2=false;	//Pongo en false que hayan sido desplazados de la zona 2
			aux_A=false;
		}
		
		//Se realiza lo mismo para el otro equipo
		if(aux_B){
			j=0;
			for(i=0;i<3;i++){
				if(auxB[i][1]){
					auxB[i][1]=false;
				}else{
					j++;
					auxB[i][0]=false;
				}
			}
			if(j==3){
				moviB1=false;
			}
			moviB2=false;
			aux_B=false;
		}
		
		if(!ganoA){	//Si no ha ganado un maestro
			if(A.agua.stamina>0) A.agua.efectividad--;
			if(B.agua.stamina>0) B.agua.efectividad--;
			
			if(disA<3){	//Calculo la distancia para luego multiplicarla por la efectividad
				disA=A2-A1;
			}
			
			//Si no tiene stamina suficiente para empujar al oponente
			if(A.agua.stamina-disA*equipos[x].agua.efectividad<0) A.agua.stamina=0;
			if(B.agua.stamina-disA*equipos[y].agua.efectividad<0) B.agua.stamina=0;
			
			if(A.agua.efectividad==0 && A.agua.stamina>0){
				A.agua.efectividad = equipos[x].agua.efectividad;	//Reinicio la efectividad
				A.agua.stamina = A.agua.stamina - disA*A.agua.efectividad;	//Resto la efectividad del atacante
				B.agua.efectividad = equipos[y].agua.efectividad;	//Reinicio la efectividad del atacado
				A2++;	//Desplazo al maestro que recibio los ataques
				if(A2<6){
					campo[0][A2]='A';
				}else{	//Si lo tumbo de la arena
					ganoA=true;
				}
				campo[0][A2-1]='.';
				if(!auxB[0][0]){	//Coloco en true que ha sido desplazado de la zona 1
					auxB[0][0]=true;
				}else{	//Coloco en true que ha sido desplazado de la zona 2
					auxB[0][1]=true;
				}
			}
			if(B.agua.efectividad==0 && B.agua.stamina>0){	//Realizo lo mismo para el otro maestro
				B.agua.efectividad = equipos[y].agua.efectividad;
				B.agua.stamina = B.agua.stamina - disA*B.agua.efectividad;
				A.agua.efectividad = equipos[x].agua.efectividad;
				A1--;
				if(A1>=0){
					campo[0][A1]='A';
				}else{
					ganoA=true;
				}
				campo[0][A1+1]='.';
				if(!auxA[0][0]){
					auxA[0][0]=true;
				}else{
					auxA[0][1]=true;
				}
			}
			if(ganoA){
				A.agua.stamina=0;
				B.agua.stamina=0;
			}
		}
		
		//Realizo lo mismo para los otros maestros
		if(!ganoF){	
			if(A.fuego.stamina>0) A.fuego.efectividad--;
			if(B.fuego.stamina>0) B.fuego.efectividad--;
			
			if(disF<3){
				disF=F2-F1;
			}
			
			if(A.fuego.stamina-disF*equipos[x].fuego.efectividad<0) A.fuego.stamina=0;
			if(B.fuego.stamina-disF*equipos[y].fuego.efectividad<0) B.fuego.stamina=0;
			
			if(A.fuego.efectividad==0 && A.fuego.stamina>0){
				A.fuego.efectividad = equipos[x].fuego.efectividad;
				A.fuego.stamina = A.fuego.stamina - disF*A.fuego.efectividad;
				B.fuego.efectividad = equipos[y].fuego.efectividad;
				F2++;
				if(F2<6){
					campo[1][F2]='F';
				}else{
					ganoF=true;
				}
				campo[1][F2-1]='.';
				imprimir = true;
				if(!auxB[1][0]){
					auxB[1][0]=true;
				}else{
					auxB[1][1]=true;
				}
			}
			if(B.fuego.efectividad==0 && B.fuego.stamina>0){
				B.fuego.efectividad = equipos[y].fuego.efectividad;
				B.fuego.stamina = B.fuego.stamina - disF*B.fuego.efectividad;
				A.fuego.efectividad = equipos[x].fuego.efectividad;
				F1--;
				if(F1>=0){
					campo[1][F1]='F';
				}else{
					ganoF=true;
				}
				campo[1][F1+1]='.';
				imprimir = true;
				if(!auxA[1][0]){
					auxA[1][0]=true;
				}else{
					auxA[1][1]=true;
				}
			}
			if(ganoF){
				A.fuego.stamina=0;
				B.fuego.stamina=0;
			}
		}
		
		if(!ganoT){
			if(A.tierra.stamina>0) A.tierra.efectividad--;
			if(B.tierra.stamina>0) B.tierra.efectividad--;
			
			if(disT<3){
				disT=T2-T1;
			}
			
			if(A.tierra.stamina-disT*equipos[x].tierra.efectividad<0) A.tierra.stamina=0;
			if(B.tierra.stamina-disT*equipos[y].tierra.efectividad<0) B.tierra.stamina=0;
			
			if(A.tierra.efectividad==0 && A.tierra.stamina>0){
				A.tierra.efectividad = equipos[x].tierra.efectividad;
				A.tierra.stamina = A.tierra.stamina - disT*A.tierra.efectividad;
				B.tierra.efectividad = equipos[y].tierra.efectividad;
				T2++;
				if(T2<6){
					campo[2][T2]='T';
				}else{
					ganoT=true;
				}
				campo[2][T2-1]='.';
				imprimir = true;
				if(!auxB[2][0]){
					auxB[2][0]=true;
				}else{
					auxB[2][1]=true;
				}
			}
			if(B.tierra.efectividad==0 && B.tierra.stamina>0){
				B.tierra.efectividad = equipos[y].tierra.efectividad;
				B.tierra.stamina = B.tierra.stamina - disT*B.tierra.efectividad;
				A.tierra.efectividad = equipos[x].tierra.efectividad;
				T1--;
				if(T1>=0){
					campo[2][T1]='T';
				}else{
					ganoT=true;
				}
				campo[2][T1+1]='.';
				imprimir = true;
				if(!auxA[2][0]){
					auxA[2][0]=true;
				}else{
					auxA[2][1]=true;
				}
			}
			if(ganoT){
				A.tierra.stamina=0;
				B.tierra.stamina=0;
			}
		}
	}
	
	//Cuento la cantidad de ganadores por equipos
	if(A1>=0) winA++;
	if(F1>=0) winA++;
	if(T1>=0) winA++;
	
	if(A2<6) winB++;
	if(F2<6) winB++;
	if(T2<6) winB++;
	
	if(winA==winB){	//Si hay empate, lanzo la moneda
		srand (time(NULL));
		int r=rand()%2;
		if(r==0){
			winA++;
		}else{
			winB++;
		}
	}
	if(winA>winB){	//Gana equipo A y se guarda en un vector de ganadores
		generacion.push_back(equipos[x]);
	} 
	if(winA<winB){//Gana equipo B y se guarda en un vector de ganadores
		generacion.push_back(equipos[y]);
	}
}

int main(){
	
	int n,n1,n2,n3,i;
	maestro p;
	equipo campeon;
	
	//Lectura
	i=0;
	ifstream archivo1("agua.txt", ios::in);
	archivo1>>n1;
	while(i<n1 && archivo1&&!archivo1.eof()){
		archivo1 >> p.efectividad;
		archivo1 >> p.stamina;
		agua.push_back(p);
		i++;
	}
	archivo1.close();
	
	i=0;
	ifstream archivo2("fuego.txt", ios::in);
	archivo2>>n2;
	while(i<n2 && archivo2&&!archivo2.eof()){
		archivo2 >> p.efectividad;
		archivo2 >> p.stamina;
		fuego.push_back(p);
		i++;
	}
	archivo2.close();
	
	i=0;
	ifstream archivo3("tierra.txt", ios::in);
	archivo3>>n3;
	while(i<n3 && archivo3&&!archivo3.eof()){
		archivo3 >> p.efectividad;
		archivo3 >> p.stamina;
		tierra.push_back(p);
		i++;
	}
	archivo3.close();
	
	//Seleccion de equipos
	
	n=fmin(n1,fmin(n2,n3))/2;
	n=2*n;
	ofstream archivo("Salida_IA_Proyecto2.txt", ios::out);
	archivo<<"Numero de equipos: "<<n<<endl;
	
	for(i=0; i<n; i++){	//En un principio, el emparejamiento de equipos es fifo
		equipo x;
		x.agua=agua[i];
		x.fuego=fuego[i];
		x.tierra=tierra[i];
		equipos.push_back(x);
	}
	
	int cont=0;
	float apt=0;
	int intentos=0;
	
	while(cont<10000 && intentos<10){	//10000 como cota superior o 10 intentos
	
		i=0;	
		while(i<n){	//Selecciono aleatoriamente a los equipos que pelearan
			int aux_x = random(n);
			int aux_y = random(n);
			pelea(equipos[aux_x],equipos[aux_y],aux_x,aux_y);
			i++;
		}
		
		for(i=0; i<n; i++){
			if(RandomFloat(0,1)>0.7){	//Probabilidad de cruce
				int j=i;
				while(j<n && RandomFloat(0,1)>0.7){
					j++;
				}
				if(j<n && j!=i){	//Si una pareja de equipos pasa el cruce, se cruzan
					Cruce_Mascara(generacion[i],generacion[j]);
				}
			}
		}
		
		for(i=0; i<n; i++){	//Se pasan los cromosomas para que tengan la probabilidad de mutar
			Mutacion_multibit(generacion[i],n1,n2,n3);
		}

		float convergencia = 0.0;
		campeon=generacion[0];
		
		while(!equipos.empty()){	//Limpio el vector que tenia la poblacion anterior
			equipos.erase(equipos.begin());
		}

		while(!generacion.empty()){
			if(aptitud(campeon)<aptitud(generacion[0])) campeon=generacion[0]; //Guardo al mas apto de la poblacion
			equipos.push_back(generacion[0]);	//Guardo el individuo en la nueva poblacion
			convergencia += aptitud(generacion[0]);	//Suma de aptitudes para luego promediarla
			generacion.erase(generacion.begin());
		}

		archivo<<endl<<"Generacion: "<<cont+1<<endl;
		archivo<<"Promedio de aptitud: "<<convergencia/n<<endl;

		/*cout<<endl<<"Campeon del torneo"<<endl;
		cout<<"Agua: "<<campeon.agua.efectividad<<" "<<campeon.agua.stamina<<endl;
		cout<<"Fuego: "<<campeon.fuego.efectividad<<" "<<campeon.fuego.stamina<<endl;
		cout<<"Tierra: "<<campeon.tierra.efectividad<<" "<<campeon.tierra.stamina<<endl;*/
		archivo<<"Aptitud del campeon: "<<aptitud(campeon)<<endl;
		
		cont++;
		if(convergencia/n!=apt){	//Si el promedio de aptitud cambia, reinicio los intentos
			apt=convergencia/n;
			intentos=0;
		}else{	//Si el promedio de aptitud se repite, se aumentan los intentos que llevas
			if(aptitud(campeon) > 15)	intentos++; //15 para incrementar los intentos a partir de una aptitud "decente"
		}
	}
	
	//Equipo con mejor aptitud al final del algoritmo
	archivo<<endl<<"CAMPEON FINAL"<<endl<<endl;
	archivo<<"Agua: "<<campeon.agua.efectividad<<" "<<campeon.agua.stamina<<endl;
	archivo<<"Fuego: "<<campeon.fuego.efectividad<<" "<<campeon.fuego.stamina<<endl;
	archivo<<"Tierra: "<<campeon.tierra.efectividad<<" "<<campeon.tierra.stamina<<endl;
	archivo<<"Aptitud: "<<aptitud(campeon)<<endl;
	archivo<<endl<<"FELICIDADES AL EQUIPO CAMPEON";
	
	archivo.close();
	
	cout<<"Simulacion terminada, revisar archivo 'Salida_IA_Proyecto2.txt'"<<endl;
	
	return 0;
}
