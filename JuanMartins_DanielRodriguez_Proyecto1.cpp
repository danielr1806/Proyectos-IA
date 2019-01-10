#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>
#include <string.h>
using namespace std;

typedef struct{
	int x;
	int y;
}punto;

vector<punto> obstaculos,tributos;

void matar(vector<vector<char> > &matriz, vector<punto> &aux, punto p, int j){
	for(int i=0; i<tributos.size(); i++){	
		if(p.x==tributos[i].x && p.y==tributos[i].y){	//busco el tributo en el vector tributos
			 tributos.erase(tributos.begin()+i);	//borro de vector tributos
			 aux.erase(aux.begin()+j);	//borro de vector aux
			 i=tributos.size();
			 matriz[p.x][p.y]='.';	//borro de matriz
		}
	}
}

void verificar_fila(vector<vector<char> > &matriz, punto katniss){
	punto p;
	int i,j;
	vector<punto> aux1,aux2;
	//Verifico si puedo matar algun tributo
	for(i=0; i<tributos.size(); i++){
		if(katniss.x==tributos[i].x){ //Fila
			p.x=tributos[i].x;
			p.y=tributos[i].y;
			if(katniss.y<p.y){
				aux1.push_back(p);	//aux1 tiene los tributos que estan a la derecha
			}else{
				aux2.push_back(p);	//aux2 tiene los tributos que estan a la izquierda
			}
		}
	}
	while(!aux1.empty()){	
		j=0;
		p=aux1[j];
		for(i=1; i<aux1.size(); i++){	//busco el tributo mas cercano
			if(aux1[i-1].y>aux1[i].y){
				j=i;
				p=aux1[j];
			}
		}
		for(i=0; i<obstaculos.size(); i++){	//busco si hay un obstaculo
			if(p.x==obstaculos[i].x){	//si hay un obstaculo en la misma fila veo si esta antes que el tributo
				if(obstaculos[i].y>katniss.y && p.y>obstaculos[i].y){	//si esta antes no puedo matar
					while(!aux1.empty()){
						aux1.pop_back();
					}
					i=obstaculos.size();
				}
			}	
		}
		if(!aux1.empty()){	//si aux1 no esta vacio, puedo matar
			matar(matriz,aux1,p,j);
		}		
	}
	while(!aux2.empty()){
		j=0;
		p=aux2[j];
		for(i=1; i<aux2.size(); i++){	//busco el tributo mas cercano
			if(aux2[i-1].y<aux2[i].y){
				j=i;
				p=aux2[j];
			}
		}
		for(i=0; i<obstaculos.size(); i++){	//busco si hay un obstaculo
			if(p.x==obstaculos[i].x){	//si hay un obstaculo en la misma fila veo si esta antes que el tributo
				if(obstaculos[i].y<katniss.y && p.y<obstaculos[i].y){	//si esta antes no puedo matar
					while(!aux2.empty()){
						aux2.pop_back();
					}
					i=obstaculos.size();
				}
			}	
		}
		if(!aux2.empty()){	//si aux2 no esta vacio, puedo matar
			matar(matriz,aux2,p,j);
		}		
	}
}

void verificar_columna(vector<vector<char> > &matriz, punto katniss){
	punto p;
	int i,j;
	vector<punto> aux1,aux2;
	//Verifico si puedo matar algun tributo
	for(i=0; i<tributos.size(); i++){
		if(katniss.y==tributos[i].y){ //Fila
			p.x=tributos[i].x;
			p.y=tributos[i].y;
			if(katniss.x<p.x){
				aux1.push_back(p);	//aux1 tiene los tributos que estan abajo
			}else{
				aux2.push_back(p);	//aux2 tiene los tributos que estan arriba
			}
		}
	}
	while(!aux1.empty()){	
		j=0;
		p=aux1[j];
		for(i=1; i<aux1.size(); i++){	//busco el tributo mas cercano
			if(aux1[i-1].x>aux1[i].x){
				j=i;
				p=aux1[j];
			}
		}
		for(i=0; i<obstaculos.size(); i++){	//busco si hay un obstaculo
			if(p.y==obstaculos[i].y){	//si hay un obstaculo en la misma columna veo si esta antes que el tributo
				if(obstaculos[i].x>katniss.x && p.x>obstaculos[i].x){	//si esta antes no puedo matar
					while(!aux1.empty()){
						aux1.pop_back();
					}
					i=obstaculos.size();
				}
			}	
		}
		if(!aux1.empty()){	//si aux1 no esta vacio, puedo matar
			matar(matriz,aux1,p,j);
		}		
	}
	while(!aux2.empty()){
		j=0;
		p=aux2[j];
		for(i=1; i<aux2.size(); i++){	//busco el tributo mas cercano
			if(aux2[i-1].x<aux2[i].x){
				j=i;
				p=aux2[j];
			}
		}
		for(i=0; i<obstaculos.size(); i++){	//busco si hay un obstaculo
			if(p.y==obstaculos[i].y){	//si hay un obstaculo en la misma columna veo si esta antes que el tributo
				if(obstaculos[i].x<katniss.x && p.x<obstaculos[i].x){	//si esta antes no puedo matar
					while(!aux2.empty()){
						aux2.pop_back();
					}
					i=obstaculos.size();
				}
			}	
		}
		if(!aux2.empty()){	//si aux2 no esta vacio, puedo matar
			matar(matriz,aux2,p,j);
		}		
	}
}

int main(){
	int n,m,i,j,auxi,auxj;
	cin>>n;
	cin>>m;
	vector<vector<char> > matriz(n, std::vector<char>(m));
	vector<vector<bool> > visitado(n, std::vector<bool>(m));
	punto katniss, p;
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			cin>>matriz[i][j];
			if(matriz[i][j]=='K'){
				katniss.x=i;
				katniss.y=j;
			}
			if(matriz[i][j]=='T'){
				p.x=i;
				p.y=j;
				tributos.push_back(p);
			}
			if(matriz[i][j]=='*'){
				p.x=i;
				p.y=j;
				obstaculos.push_back(p);
			}
			visitado[i][j]=false;
		}
	}

	if(tributos.empty()){	//si no quedan tributos
		cout<<"Simulation Failed. Katniss Won"<<endl;
		return 0;
	}

	//BFS//
	queue <punto> Q;
	Q.push(katniss);
	punto ref;
	ref.x = -1;
	ref.y = -1;
	int dx[4] = {0, 0, 1, -1 };
	int dy[4] = {1, -1, 0, 0 };

	while(!Q.empty()){
		if(!tributos.empty()){
			//Verifico si hay algun tributo adyacente

			if((katniss.x+1<n && matriz[katniss.x+1][katniss.y]=='T')||(katniss.x-1>=0 && matriz[katniss.x-1][katniss.y]=='T')||(katniss.y+1<m && matriz[katniss.x][katniss.y+1]=='T')||(katniss.y-1>=0 && matriz[katniss.x][katniss.y-1]=='T')){
				Q.pop();
			}else{
				//Si me movi con respecto a la posicion anterior, verifico fila o columna para ver si puedo matar tributos//
				if(ref.x!=katniss.x){
					verificar_fila(matriz, katniss);
				}
				if(ref.y!=katniss.y){
					verificar_columna(matriz, katniss);
				}
				//Modifico la posicion anterior de referencia para iterar nuevamente//
				ref=katniss;
				//Me muevo, desencolo y marco la nueva posicion como visitado, ademas altero la matriz//
				katniss=Q.front();
				Q.pop();
				visitado[katniss.x][katniss.y]=true;
				matriz[katniss.x][katniss.y]='K';
				
				//Hago un for para encolar cada posible adyacencia de mi posicion actual si dicha adyacencia es valida//
				for(int i=0;i<4;i++){
					int nx = dx[i] + katniss.x;
					int ny = dy[i] + katniss.y;
					
					//Verifico si dicha posicion adyacente es valida, de serlo, la encolo//
					if(nx>=0 && nx<n && ny>=0 && ny<m && matriz[nx][ny]!='*' && !visitado[nx][ny]){
						punto adyacente;
						adyacente.x=nx;
						adyacente.y=ny;
						Q.push(adyacente);
					}
				}
			}
			
		//Si no quedan tributos, Katniss gana//
		}else{
			cout<<"Simulation Failed. Katniss Won"<<endl;
			return 0;
		}
	
		matriz[ref.x][ref.y]='.'; 
	}
	//Si recorri todos los caminos posibles y quedaron tributos, Katniss pierde//
	cout<<"Simulation Success. Katniss is Doomed"<<endl;
	return 0;
}
