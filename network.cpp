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
};


int main() {

      return 0;
}
