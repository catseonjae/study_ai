#include <bits/stdc++.h>
using namespace std;
class matrix{
  vector<vector<double>> v;
  public:
    matrix(){
        
    }
    matrix(int n, int m){
      v=vector<vector<double>>(n,vector<double>(m));
    }
    matrix(int n, int m, int x){
      v=vector<vector<double>>(n,vector<double>(m,x));
    }
    vector<double> operator [] (int idx){
      return v[idx];
    }
    matrix operator () (matrix m){
      
    }
}


int main() {

      return 0;
}
