#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#include "xorshift.h" //semilla y función para puntos aleatorios
#include "matematica.h" //definiciones basicas
#include "genetico.h"

int main(int argc, char **argv){
	SeedXorShift();
	Practica2<Individuo> P2(100,100,18);
	//Genetico<Practica2<Individuo> > G(&P2,0.3,0.2,false); <-- sin elitismo
	Genetico<Practica2<Individuo> > G(&P2,0.3,0.2,true);
	Individuo mejor=G.iniciar(false);
	return 0;
}
