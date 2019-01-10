#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
using namespace std;
int main(){	//Random de 0 a n
	srand (time(NULL));
	while(true){
		cout<<rand()%2<<endl;
		Sleep(1000);
	}
}
