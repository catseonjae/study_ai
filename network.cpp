#include <bits/stdc++.h>
using namespace std;

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
      const double RANDMAX=32767;
      double r=e-s;
      double mod = fmod(r,RANDMAX);
      
      for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
          int rep=r/RANDMAX;
          double value = 0;
          for(int k=0;k<rep;k+++){
            value += rand();
            srand();
          }
          value+=rand()*mod/RANDMAX;
          v[i][j]=value;
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
  matrix now;
  int cur_layer;
  public:
    vector<matrix> w;
    vector<matrix> layers;
    network(){
      
    }
    network(vector<int> dim){
      for(int i=0;i<dim.size()-1;i++){
        w.push_back(matrix(dim[i],dim[i+1]));
        layers.push_back(matrix(dim[i],1));
      }
      layers.push_back(matrix(dim.back(),1));
    }
    matrix predict(matrix input){
      cur_layer=0;
      now=input;
      
    }
    void propagate(){
      now=
    }
}

int main() {
    return 0;
}
