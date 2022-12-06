#include <bits/stdc++.h>
using namespace std;

double random_number(double s, double e){
  const double RANDMAX=32767;
  double r=e-s;
  double mod = fmod(r,RANDMAX);
  
  int rep=r/RANDMAX;
  double ret = 0;
  for(int k=0;k<rep;k++){
    ret += rand();
    srand((unsigned int)time(NULL));
  }
  ret+=rand()*mod/RANDMAX;
  return ret;  
}

class matrix{
  public:
    vector<vector<double>> v;
    int rows, columns;  

    matrix(){
      rows=columns=1;
    }
    matrix(int n, int m) : rows(n), columns(m){
      v=vector<vector<double>>(n,vector<double>(m));
    }
    matrix(int n, int m, int x) : rows(n), columns(m){
      v=vector<vector<double>>(n,vector<double>(m,x));
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

    matrix operator * (matrix a){
      matrix ret(rows,a.columns,0.0);
      for(int i=0;i<rows;i++){
        for(int j=0;j<a.columns;j++){
          for(int k=0;k<columns;k++){
            ret[i][j]=ret[i][j]+this[i][k]*a[k][j];
          }
        }
      }
      return ret;
    }
    matrix operator + (matrix a){
      matrix ret(rows,columns);
      for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
          ret[i][j]=this[i][j]+a[i][j];
        }
      }
      return ret;
    }

    matrix operator - (matrix a){
      matrix ret(rows,columns);
      for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
          ret[i][j]=this[i][j]-a[i][j];
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
	
};

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
        w.push_back(matrix(dim[i],dim[i+1]));
        layers.push_back(matrix(dim[i],1));
      }
      layers.push_back(matrix(dim.back(),1));
    }
    matrix predict(matrix input){
      layers[0]=input;
      for(cur_layer=0;cur_layer<depth-1;cur_layer++){
        layers[cur_layer+1] = w[cur_layer] * layers[cur_layer];
      }
      return layers.back();
    }
	double sigmoid(double x){
		return 1.0/(1+pow(M_E,x));
	}
	double relu(double x){
		return max(0.0, x);
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
	double sse(matrix a, matrix t){
		double ret=0;
		for(int i=0;i<a.rows;i++){
			ret+=a[i][0]+t[i][0];
		}
		ret/=2;
		return ret;
	}
	double cee(matrix a, matrix t){
		
	}
};

int main() {
    return 0;
}
