struct Individuo{
	Represent representacion;
	double aptitud;
	Individuo(){}
	Individuo(Represent rep){
		representacion=rep;
	}
	Individuo(Represent representacion,double aptitud){
		representacion=representacion;
		aptitud=aptitud;
	}
	Individuo operator=(const Individuo& B){
		representacion=B.representacion;
		aptitud=B.aptitud;
		return *(this);
	}
	bool operator ==(const Individuo B)const{
		return (representacion==B.representacion);
	}
	Individuo cruzamiento(const Individuo* B){
		//printf("cruzando\n");
		Represent nuevo(representacion.tamano());
		bool cromosoma_padre=XorShift(2);
		int tamano_minimo=3;
		int division=XorShift(representacion.tamano()/2-tamano_minimo)+tamano_minimo;
		for (int i=0;i<representacion.tamano()/2;i++){
			if(i==division)
				cromosoma_padre=!cromosoma_padre;
			if(cromosoma_padre)
				nuevo.cromosomas[i]=representacion.cromosomas[i];
			else
				nuevo.cromosomas[i]=B->representacion.cromosomas[i];
		}
		cromosoma_padre=XorShift(2);
		division=representacion.tamano()/2+XorShift(representacion.tamano()/2-tamano_minimo)+tamano_minimo;
		for (int i=representacion.tamano()/2;i<representacion.tamano();i++){
			if(i==division)
				cromosoma_padre=!cromosoma_padre;
			if(cromosoma_padre)
				nuevo.cromosomas[i]=representacion.cromosomas[i];
			else
				nuevo.cromosomas[i]=B->representacion.cromosomas[i];
		}
		return Individuo(nuevo);
	}
	void mutacion_swap(Represent& nuevo){
		int findice_mutacion=XorShift(representacion.tamano());
		int sindice_mutacion=XorShift(representacion.tamano());
		if(findice_mutacion==sindice_mutacion){
			sindice_mutacion=(sindice_mutacion+1)%representacion.tamano();
		}
		int cromosoma_aleatorio=nuevo.cromosomas[sindice_mutacion];
		nuevo.cromosomas[sindice_mutacion]=nuevo.cromosomas[findice_mutacion];
		nuevo.cromosomas[findice_mutacion]=cromosoma_aleatorio;
	}
	void mutacion_alter(Represent& nuevo, int n){
		set<int> S;
		for (int i=0;i<n;i++){
			//nuevo.cromosomas[XorShift(representacion.tamano())]=XorShift(2);
			int pos=XorShift(representacion.tamano());
			while (S.find(pos)!=S.end()){
				pos=XorShift(representacion.tamano()); 
			}
			nuevo.cromosomas[pos]=!(nuevo.cromosomas[pos]);
			S.insert(pos);
		}
	}
	Individuo mutacion(){
		Represent nuevo(representacion.tamano());
		nuevo=representacion;
		//mutacion_swap(nuevo); //swap
		mutacion_alter(nuevo, XorShift(2)+1); //alter
		return Individuo(nuevo);
	}
	bool operator <(const Individuo& B)const{
		return (aptitud==B.aptitud)?representacion<B.representacion:aptitud<B.aptitud;
	}
};
