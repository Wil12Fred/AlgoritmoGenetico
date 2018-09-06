struct Represent{
	vector <bool> cromosomas;
	//vector <int> cromosomas;
	Represent (){}
	Represent (int b){
		cromosomas.resize(b);
	}
	double getDouble(int i,int ent, int dec){
		double ans=0;
		for (int j=i+1;j<i+1+ent;j++){
			if(cromosomas[j]){
				ans+=1<<(i+ent-j);
			}
		}
		for (int j=i+1+ent;j<i+1+ent+dec;j++){
			if(cromosomas[j]){
				ans+=double(1)/(1<<(j-i-ent));
			}
		}
		if(!cromosomas[i]){
			ans*=-1;
		}
		return ans;
	}
	pair<double,double> getX(){
		double x1=getDouble(0,2,cromosomas.size()/2-1-2);
		double x2=getDouble(cromosomas.size()/2,2,cromosomas.size()/2-1-2);
		return make_pair(x1,x2);
	}
	Represent operator = (const Represent& B){
		cromosomas.resize((int)B.cromosomas.size());
		for (int i = 0 ; i < cromosomas.size(); i++){
			cromosomas[i]= B.cromosomas[i];
		}
		return (*this);
	}
	int tamano()const{
		return cromosomas.size();
	}
	bool operator == (const Represent B)const{
		int i = 0;
		while (i < cromosomas.size()){
			if (cromosomas[i] != B.cromosomas[i])
				return false;
		}
		return true;
	}
	bool operator < (const Represent B)const{
		int i = 0;
		while (i < cromosomas.size()){
			if (cromosomas[i]< B.cromosomas[i])
				return true;
			else if (cromosomas[i]!=B.cromosomas[i])
				return false;
			i++;
		}
		return false;
	}
};
