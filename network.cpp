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
    srand();
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
    matrix oeprator + (matrix a){
      matrix ret(rows,columns);
      for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
          ret[i][j]=this[i][j]+a[i][j];
        }
      }
      return ret;
    }

    matrix oeprator - (matrix a){
      matrix ret(rows,columns);
      for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
          ret[i][j]=this[i][j]-a[i][j];
        }
      }
      return ret;
    }
    vector<double> to_vector(){
      return v;
    }
};

class layer{
  public:
    
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
      depth=dim;
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
    
}

int main() {
    return 0;
}
