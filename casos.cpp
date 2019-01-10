#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <time.h>
#include <math.h>
using namespace std;

int random(int n){	//Random de 0 a n
	return 1+rand()%n;
}

int main(){
	ofstream archivo1("agua.txt", ios::out);
	ofstream archivo2("fuego.txt", ios::out);
	ofstream archivo3("tierra.txt", ios::out);
	int n=1000;
	int m=1000;
	archivo1<<n<<endl;
	archivo2<<n<<endl;
	archivo3<<n<<endl;

	srand (time(NULL));
	for(int i=0;i<n;i++){
		archivo1<<random(m)<<" "<<random(1000)<<endl;
		archivo2<<random(m)<<" "<<random(1000)<<endl;
		archivo3<<random(m)<<" "<<random(1000)<<endl;
	}


	return 0;
}
