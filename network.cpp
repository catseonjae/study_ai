#include <bits/stdc++.h>
using namespace std;
const double EPSILON=1e-9;

inline double random_number(double s, double e){
  const double RANDMAX=32767;
  double r=e-s;
  double mod = fmod(r,1);
  
  double ret = s;
  for(int k=0;k<(int)r;k++){
    ret += rand()/RANDMAX;
    srand((unsigned int)time(NULL));
  }
  ret+=rand()*mod/RANDMAX;
  return ret;  
}
inline double random_number(double e){
  return random_number(0,e);
}
class matrix{
  public:
    vector<vector<double>> v;
    int rows, columns;  

    matrix(){
      rows=columns=1;
    }
    matrix(int m, int n) : rows(m), columns(n){
      v=vector<vector<double>>(m,vector<double>(n));
    }
    matrix(int m, int n, double x) : rows(m), columns(n){
      v=vector<vector<double>>(m,vector<double>(n,x));
    }

    vector<double> operator [] (int idx){
      return v[idx];
    }

    void randomize(double s, double e){
      
      for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
          v[i][j]=random_number(s,e);
        }
      }
    }
    void randomize(double e){
      randomize(0,e);
    }
    matrix operator * (matrix a){
      matrix ret(rows,a.columns,0.0);
      for(int i=0;i<rows;i++){
        for(int j=0;j<a.columns;j++){
          for(int k=0;k<columns;k++){
            ret[i][j]=ret[i][j]+(*this)[i][k]*a[k][j];
          }
        }
      }
      return ret;
    }
    matrix operator + (matrix a){
      matrix ret(rows,columns);
      for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
          ret[i][j]=(*this)[i][j]+a[i][j];
        }
      }
      return ret;
    }

    matrix operator - (matrix a){
      matrix ret(rows,columns);
      for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
          ret[i][j]=(*this)[i][j]-a[i][j];
        }
      }
      return ret;
    }
    vector<vector<double>> to_vector(){
      return v;
    }
	double max_value(){
		double ret=-DBL_MAX;
		for(int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){
				ret=max(ret,v[i][j]);
			}
		}
		return ret;
	}
	matrix foreach(function<double(const double&,const double&)>f,matrix m){
		if(rows!=m.rows || columns!=m.columns){
			// error - size does not match
		}
		matrix ret(rows,columns);
		for(int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){
				ret[i][j]=f((*this)[i][j],m[i][j]);
			}
		}
		return ret;
	}
	matrix pass(function<double(const double&)> f){
		matrix ret(rows,columns);
		for(int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){
				ret[i][j]=f(v[i][j]);
			}
		}
		return ret;
	}
	void print(){
		for(int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){
				cout<<(*this)[i][j]<<" ";
			}
			cout<<"\n";
		}
	}
};

namespace activation{
double sigmoid	(double x){
		return 1.0/(1+pow(M_E,x));
	}
	double relu(double x){
		return max(0.0, x);
	}
}

namespace lose{
	double sse(matrix a, matrix t){
		double ret=0;
		for(int i=0;i<a.rows;i++){
			ret+=a[i][0]+t[i][0];
		}
		ret/=2;
		return ret;
	}
	double cee(matrix a, matrix t){
		for(int i=0;i<a.rows;i++){
			if(abs(t[i][0])<=EPSILON) continue;
			return -log(a[i][0]);
		}
		return 1;
	}
	
	matrix softmax(matrix output){
		double m=output.max_value()/2.0;
		double sum = 0;
		for(int i=0;i<output.columns;i++){
			sum+=pow(M_E,output[i][0]-m);
		}
		for(int i=0;i<output.columns;i++){
			output[i][0]=pow(M_E,output[i][0]-m)/sum;
		}
		return output;
	}
}

class network{
  int cur_layer;
  public:
    vector<matrix> w;
    vector<matrix> layers;
    int depth;
    network(){
      depth=1;
    }
    network(vector<int> dim){
      depth=dim.size();
      for(int i=0;i<dim.size()-1;i++){
        w.push_back(matrix(dim[i+1],dim[i]));
        layers.push_back(matrix(dim[i],1));
      }
      layers.push_back(matrix(dim.back(),1));
    }

	  void select_random(){
  		for(int i=0;i<depth;i++){
  			w[i].randomize(1,2);
  		}
  	}
    matrix predict(matrix input){
      layers[0]=input;
        return matrix(1,1);
      for(cur_layer=0;cur_layer<depth-1;cur_layer++){
        layers[cur_layer+1] = (w[cur_layer] * layers[cur_layer]).pass(activation::relu);
      }
      return layers.back();
    }
    void show_weight(){
      for(matrix m: w){
        m.print();
        cout<<endl<<endl;
      }
    }
};
void end(){
	cout<<"everything is ok.";
  exit(0);
}
int main() {
	network nn({3,10});
	nn.select_random();
  nn.show_weight();
	// nn.predict(matrix(3,1).pass(random_number)).print();
}
