#ifndef MATRIXH
#define MATRIXH
#include "stdcpp.h"

typedef long long biginteger;
template <typename element_type> 
class matrix{
	typedef std::function<element_type *(matrix &, biginteger, biginteger)> accessor_type;
private:
	biginteger rows,columns;
	element_type *pos;
	accessor_type accessor;
	void allocate_memory() {
		pos = (element_type *)std::malloc(sizeof(element_type)*rows*columns);
	}
	void set_basic_accessor() {
		accessor = [=](matrix &m, biginteger i,biginteger j) -> element_type* {
			return  m.get_pos()+m.calculate_relpos(i,j);
		};
	}
public:
	// constructors
	matrix() :rows(1), columns(1) {
		allocate_memory();
		set_basic_accessor();
	}
	matrix(biginteger rows) : rows(rows),columns(1){
		allocate_memory();
		set_basic_accessor();
	}
	matrix(biginteger rows,biginteger columns) : rows(rows),columns(columns){
		allocate_memory();
		set_basic_accessor();
	}

	matrix(biginteger rows,biginteger columns, element_type x) : rows(rows),columns(columns){
		allocate_memory();
		set_basic_accessor();
		for(biginteger i=1;i<=rows;i++){
			for(biginteger j=1;j<=rows;j++){
				(*this)(i,j)=x;
			}
		}
	}

	matrix(biginteger rows,biginteger columns, const matrix &m) : rows(rows),columns(columns){
		allocate_memory();
		set_basic_accessor();
		for(biginteger i=1;i<=rows;i++){
			for(biginteger j=1;j<=rows;j++){
				(*this)(i,j)=m(i,j);
			}
		}
	}

	matrix(biginteger rows,biginteger columns, element_type * pos) : rows(rows),columns(columns), pos(pos) {
		set_basic_accessor();}
	matrix(biginteger rows,biginteger columns, accessor_type accessor) : rows(rows),columns(columns), accessor(accessor){
		allocate_memory();
	}
	matrix(biginteger rows,biginteger columns, element_type * pos, accessor_type accessor) : rows(rows),columns(columns), pos(pos), accessor(accessor) {}
	matrix(biginteger rows,biginteger columns, std::function<element_type(biginteger, biginteger)> f){
		allocate_memory();
		set_basic_accessor();
		for (biginteger i = 1; i <= rows; i++) {
			for (biginteger j = 1; j <= columns; j++) {
				(*this)(i,j) = f(i, j);
			}
		}
	}
	
	// getters
	element_type *get_pos() {
		return pos;
	}
	biginteger get_rows() {
		return rows;
	}
	biginteger get_columns() {
		return columns;
	}
	accessor_type get_accessor(){
		return accessor;
	}
	std::pair<biginteger,biginteger> size(){
		return std::pair<biginteger,biginteger>(rows,columns);
	}


	//setters
	void set_pos(element_type *pos){
		pos=pos;
	}
	void set_accessor(accessor_type accessor){
		accessor=accessor;
	}

	element_type &operator ()(biginteger i, biginteger j){
		if(!check_pos(i,j)){
			throw std::runtime_error("invalid idx - in element reference");
		}
		return *accessor((*this),i,j);
	} //^element accessor
	matrix operator ()(biginteger idx){
		if(rows==1){
			return (*this)(1,idx);
		}
		if(columns==1){
			return (*this)(idx,1);
		}
		if(idx<1 or idx>rows){
			throw std::runtime_error("invalid idx - in row vector refference");
		}
		return matrix(1, columns, pos, [=](matrix &m, biginteger i, biginteger j){
			return pos+calculate_relpos(i,idx);
		});
	} //^row accessor
	matrix operator[](biginteger idx) {
		if(rows==1){
			return (*this)(1,idx);
		}
		if(columns==1){
			return (*this)(idx,1);
		}
		if(idx<1 or idx>columns){
			throw std::runtime_error("in column vector reference");
		}
		return matrix(rows, 1, pos, [=](matrix &m, biginteger i,biginteger j){
			return pos+calculate_relpos(i,idx);
		});
	} //^column accessor
	matrix operator * (matrix a) {
		if(!check_multipliable(a)){
			throw std::runtime_error("in multiply operation, matrix sizes do not match\nfirst matrix:\n"+info()+"second matrix:\n"+a.info());
		}
		matrix<element_type> ret(rows, a.get_columns());
		for (biginteger i = 1; i <= rows; i++) {
			for (biginteger j = 1; j <= a.columns; j++) {
				for (biginteger k = 1; k <= columns; k++) {
					ret(i,j) = ret(i,j) + (*this)(i,k) * a(k,j);
				}
			}
		}
		return ret;
	}
	matrix operator + (matrix a) {
		if(!is_same_size(a)){
			throw std::runtime_error("in add operation, matrix sizes do not match\nfirst matrix:\n"+info()+"second matrix:\n"+a.info());
		}
		matrix<element_type> ret(rows, columns);
		for (int i = 1; i <= rows; i++) {
			for (int j = 1; j <= columns; j++) {
				ret(i,j) = (*this)(i,j) + a(i,j);
			}
		}
		return ret;
	}
	matrix operator - (matrix a) {
		if(!is_same_size(a)){
			throw std::runtime_error("in sub operation, matrix sizes does not match\nfirst matrix:\n"+info()+"second matrix:\n"+a.info());
		}
		matrix<element_type> ret(rows, columns);
		for (int i = 1; i <= rows; i++) {
			for (int j = 1; j <= columns; j++) {
				ret(i,j) = (*this)(i,j) - a(i,j);
			}
		}
		return ret;
	}
		
	//utilities
	void free() {
		free(pos);
		pos = NULL;
	}
	element_type max_value() {
		element_type ret = (*this)(1,1);
		for(biginteger i=1;i<=rows;i++){
			for(biginteger j=1;j<=columns;j++){
				if((*this)(i,j)>ret){
					ret=(*this)(i,j);
				}
			}
		}
		return ret;
	}
	element_type min_value() {
		element_type ret = (*this)(1,1);
		for(biginteger i=1;i<=rows;i++){
			for(biginteger j=1;j<=columns;j++){
				if((*this)(i,j)<ret){
					ret=(*this)(i,j);
				}
			}
		}
		return ret;
	}
	matrix foreach_calculate (std::function<element_type(const element_type &, const element_type &)> f, matrix a) {
		if (!is_same_size(a)) {
			throw std::runtime_error("in foreach calculate call, matrix sizes does not match\nfirst matrix:\n"+info()+"second matrix:\n"+a.info());
		}
		matrix ret(rows, columns);
		for(biginteger i=1;i<=rows;i++){
			for(biginteger j=1;j<=columns;j++){
				ret(i,j)=f((*this)(i,j),a(i,j));
			}
		}
		return ret;
	}
	matrix pass(std::function<element_type(element_type)> f) {
		matrix ret(rows, columns);
		for (int i = 1; i <= rows; i++) {
			for (int j = 1; j <= columns; j++) {
				ret(i,j)=f((*this)(i,j));
			}
		}
		return ret;
	}
	matrix pass(std::function<element_type(biginteger,biginteger,element_type)> f) {
		matrix ret(rows, columns);
		for (int i = 1; i <= rows; i++) {
			for (int j = 1; j <= columns; j++) {
				ret(i,j)=f(i,j,(*this)(i,j));
			}
		}
		return ret;
	}
	std::string size_info(){
		return "("+std::to_string(rows)+"*"+std::to_string(columns)+") ";
	}
	std::string info() {
		std::string ret="matrix("+std::to_string(rows)+"*"+std::to_string(columns)+")\n(";
		try{
			for (biginteger i = 1; i <= rows; i++) {
				for (biginteger j = 1; j <= columns; j++) {
					ret+=std::to_string((*this)(i,j)) + " ";
				}
				if(i==rows) ret+=")";
				ret+= "\n";
			}	
			return ret;
		} 
    	catch(std::exception *e)
	    {
			throw std::runtime_error("cannot covert type "+std::to_string(*(typeid(element_type).name()))+" to string.");
	    }
	}
	biginteger calculate_relpos(biginteger i, biginteger j){
		return sizeof(element_type)*((i-1)*columns+(j-1));
	}
	bool check_pos(biginteger i, biginteger j){
		return (1<=i && i<=rows) &&(1<=j && j<=columns);
	}
	bool check_multipliable(matrix &m){
		return columns==m.rows;
	}
	bool is_same_size(matrix &m){
		return rows==m.get_rows() and columns==m.get_columns();
	}
	matrix t(){
		matrix<element_type> ret(columns,rows);
		for(biginteger i=1;i<=rows;i++){
			for(biginteger j=1;j<=columns;j++){
				ret(i,j)=(*this)(j,i);
			}
		}
		return ret;
	}
};
#endif
