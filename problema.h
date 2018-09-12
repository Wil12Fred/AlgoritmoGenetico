template<class Indiv>
struct Problema{
	typedef Indiv indiv;
	int tamano_de_poblacion;
	int numero_de_generaciones;
	int numero_de_cromosomas;
	Problema(){}
	Problema(int n_poblacion, int n_generaciones,int n_cromosomas){
		tamano_de_poblacion=n_poblacion;
		numero_de_generaciones=n_generaciones;
		numero_de_cromosomas=n_cromosomas;
	}
	void generar_nuevo_individuo(Indiv& B){}
	int valor_aleatorio(int max){
		return XorShift(max);
	}
	double valor_aleatorio(double max){
		long long aleatorio = XorShift(100000000);
		return (max*aleatorio)/double(100000000);
	}
	double aptitud(Indiv& individuo){
		return -1;
	}
};

template<class Indiv>
struct Practica2: Problema<Indiv>{
	Practica2(int n_poblacion, int n_generaciones,int n_cromosomas):
		Problema<Indiv>(n_poblacion, n_generaciones, n_cromosomas){
	}
	int NumeroDeCromosomas(){
		return this->numero_de_cromosomas;
	}
	void generar_nuevo_individuo(Indiv& B){
		Represent nuevo(NumeroDeCromosomas());
		for (int i=0;i<NumeroDeCromosomas();i++){
			nuevo.cromosomas[i]=XorShift(2);
		}
		B.representacion=nuevo;
	}
	double func(double x1, double x2){
		double x=max(sqrt(x1*x1+x2*x2),eps);
		double z=sin(pi*x)/(pi*x);
		return z*z;
	}
	double aptitud(Indiv& individuo){
		double x1,x2;
		x1=individuo.representacion.getX().first;
		x2=individuo.representacion.getX().second;
		return (func(x1,x2)+1)*1000;//(func(x1,x2));
	}
};
