#include "represent.h"
#include "individuo.h"
#include "problema.h"

template <class P, class Indiv=typename P::indiv>
struct Genetico{
	set<Indiv>* poblacion;
	P* problema; 
	double probabilidad_de_cruzamiento;
	double probabilidad_de_mutacion;
	double aptitud_total;
	bool elitismo;
	Genetico(P* p,double c, double m,bool e=false){//R
		aptitud_total=0;
		poblacion = new set<Indiv>();
		problema=p;
		probabilidad_de_cruzamiento=c;
		probabilidad_de_mutacion=m;
		elitismo=e;
		crear_poblacion();
	}
	void crear_poblacion(){//R
		while(poblacion->size()<problema->tamano_de_poblacion){
			Indiv nuevo_individuo;
			problema->generar_nuevo_individuo(nuevo_individuo);
			nuevo_individuo.aptitud=problema->aptitud(nuevo_individuo);
			aptitud_total+=nuevo_individuo.aptitud;
			poblacion->insert(nuevo_individuo);
		}
	}
	bool seleccion_rueda_de_ruleta(double aptitud){//R
		double ruleta = problema->valor_aleatorio(aptitud_total);
		return ruleta<aptitud;
	}
	void seleccion_de_individuos(map<int,Indiv*>& individuos_a_cruzar){//R
		int i=0;
		for (auto it=poblacion->begin();it!=poblacion->end();it++){
			if(seleccion_rueda_de_ruleta(it->aptitud)){
				individuos_a_cruzar[i++]=new Indiv(*it);
			}
		}
	}
	Indiv* seleccionar_padre(map<int,Indiv*>& individuos_a_cruzar){//R
		int aleatorio=problema->valor_aleatorio((int)individuos_a_cruzar.size());
		auto it=individuos_a_cruzar.lower_bound(aleatorio);
		if(it==individuos_a_cruzar.end()){
			it=individuos_a_cruzar.lower_bound(0);
		}
		Indiv* padre = it->second;
		individuos_a_cruzar.erase(it);
		return padre;
	}
	void cruzar_individuos(){//R
		map<int,Indiv*> individuos_a_cruzar;
		seleccion_de_individuos(individuos_a_cruzar);
		while (individuos_a_cruzar.size()>1){
			Indiv* padre = seleccionar_padre(individuos_a_cruzar);
			Indiv hijo=padre->cruzamiento(seleccionar_padre(individuos_a_cruzar));
			hijo.aptitud=problema->aptitud(hijo);
			aptitud_total+=hijo.aptitud;
			poblacion->insert(hijo);
		}
	}
	Indiv getIndividuo(int i){
		auto it=poblacion->begin();
		for (int j=0;j<i;j++){
			it++;
		}
		return *it;
	}
	void mutar_individuos(){//R
		vector<Indiv> Eliminar;
		vector<Indiv> Nuevos;
		for(auto it=poblacion->begin();it!=poblacion->end();it++){
			double aleatorio=problema->valor_aleatorio(double(1));
			if(aleatorio<probabilidad_de_mutacion){
				Indiv mutacion=Indiv(*it).mutacion();
				mutacion.aptitud=problema->aptitud(mutacion);
				Nuevos.push_back(mutacion);
				if(!elitismo){
					Eliminar.push_back(*it);
				}
			}
		}
		for (int i=0;i<Nuevos.size();i++){
			if(Eliminar.size())
				poblacion->erase(Eliminar[i]);
			poblacion->insert(Nuevos[i]);
		}
	}
	Indiv seleccion_de_eliminacion(){
		if(elitismo)
			return *(poblacion->begin());
		else
			return getIndividuo(XorShift(poblacion->size()));
	}
	void ajustar_poblacion(){//R
		while(poblacion->size()>problema->tamano_de_poblacion){
			Indiv condenado=seleccion_de_eliminacion();
			aptitud_total-=condenado.aptitud;
			poblacion->erase(condenado);
		}
	}
	void generar_nueva_poblacion(){//R
		cruzar_individuos();
		mutar_individuos();
		ajustar_poblacion();
	}
	Indiv obtenerMejor(){
		Indiv mejor=*(poblacion->rbegin());
		for (auto it=poblacion->begin();it!=poblacion->end();it++){
			if(it->aptitud>mejor.aptitud){
				mejor=*it;
			}
		}
		pair<double,double> X=mejor.representacion.getX();
		cout << "X = (" << X.first << ", " << X.second  << "), f(X) = " << mejor.aptitud << endl;
		return mejor;
	}
	Indiv iniciar(bool limite=true){//R
		Indiv mejor;
		generar_nueva_poblacion();
		mejor=obtenerMejor();
		bool estable=false;
		int past_modification=0;
		double mejor_aptitud=mejor.aptitud;
		int i=1;
		while ((limite && i<problema->numero_de_generaciones) || (!limite && !estable)){
			generar_nueva_poblacion();
			mejor=obtenerMejor();
			if(mejor.aptitud>mejor_aptitud){
				mejor_aptitud=mejor.aptitud;
				past_modification=i;
			} else if(mejor.aptitud==mejor_aptitud){
					if(i-past_modification>15)
						estable=true;
			} else {
				past_modification=i;
			}
			i++;
		}
		cout << i << " iteraciones" << endl;
		return mejor;
	}
};
