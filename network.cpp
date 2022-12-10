#include "network.h"
namespace activation{
	double sigmoid(double x) {
		return 1.0 / (1 + std::pow(M_E, x));
	}
	double relu(double x) {
		return std::max(0.0, x);
	}
}
namespace lose{
	double sse(double a, double t){
		return pow(a-t,2.0)/2.0;
	}
	double sse(matrix<double> a, matrix<double> t) {
		double ret = 0;
		for (int i = 1; i <= a.get_rows(); i++) {
			ret += pow(a(i,1)-t(i,1),2.0);
		}
		ret /= 2;
		return ret;
	}
	double cee(double a, double t){
		return -log(a)*t;
	}
	double cee(matrix<double> a, matrix<double> t) {
		for (int i = 1; i <= a.get_rows(); i++) {
			if (abs(t(i,1)) <= EPSILON)
				  continue;
			return -log(a(i,1));
		}
		return 1;
	}
	matrix<double> softmax(matrix<double> output) {
		double m = output.max_value() / 2.0;
		double sum = 0;
		for (int i = 1; i <= output.get_columns(); i++) {
			sum += pow(M_E, output(i,1) - m);
		}
		for (int i = 1; i < output.get_columns(); i++) {
			output(i,1) = pow(M_E, output(i,1) - m) / sum;
		}
		return output;
	}
}

network::network(std::vector<int> dim, std::function<double(double)> activation_function, std::function<double(matrix<double>,matrix<double>)> lose_function) :activation_function(activation_function), lose_function(lose_function){
	depth = dim.size();
	w.push_back(matrix<double>(dim[0+1], dim[0]));
	layers.push_back(matrix<double>(dim[0]));
	for (int i = 1; i < dim.size() - 1; i++) {
		w.push_back(matrix<double>(dim[i + 1], dim[i]));
		layers.push_back(matrix<double>(dim[i]));
		gradients.push_back(std::vector<double>(dim[i]));
	}
	layers.push_back(matrix<double>(dim.back()));
	gradients.push_back(std::vector<double>(dim.back()));
}

void network::back_propagation(matrix<double> &output){
	for(int i=1;i<=layers.back().get_rows();i++){
		gradients[layers.size()-1][i-1]=lose_function(output[i],layers.back()[i]+EPSILON)-lose_function(output[i],layers.back()[i]-EPSILON);
	}
	for(int i=depth-2;i>=0;i--){
		for(biginteger r = 1; r<= layers[i].get_rows(); r++){
			if(i>0) gradients[i-1][r]=0;
			for(biginteger c = 1; c<= layers[i].get_columns(); c++){
				double g = layers[i](r,c)*EPSILON*gradients[i][r];
				layers[i](r,c)-=g*train_rate;
				if(i>0) gradients[i-1][r]+=g;
			}	
		}
	}
}
void network::train(matrix<double> input,matrix<double> output){
	predict(input);
	back_propagation(output);
}

matrix<double> network::predict(matrix<double> input) {
	if(!layers[0].is_same_size(input)){
		throw std::runtime_error("in network predict call, matrix sizes are not same\n"+layers[0].info()+input.info());
	}
	layers[0] = input;
	for (cur_layer = 0; cur_layer < depth - 1; cur_layer++) {
		layers[cur_layer + 1] = (w[cur_layer] * layers[cur_layer]).pass(activation_function);
	}
	return layers.back();
}
std::string network::info(){
	std::string ret;
	ret+="w:\n";
	ret+="size: "+std::to_string(w.size());
	ret+="\nsize of matrixs: ";
	for(matrix<double> i: w){
		ret+=i.size_info();
	}
	//layers: size: {layers.size()} sizeof matrixs: (*),(*),(*),(*) ...
	ret+="\n\nlayers:\n";
	ret+="size: "+std::to_string(layers.size());
	ret+="\nsize of matrixs: ";
	for(matrix<double> i: layers){
		ret+=i.size_info();
	}
	ret+="\n\nw matrixs:\n";
	for(matrix<double> i: w){
		ret+=i.info();
	}
	ret+="\nlayers matrixs:\n";
	for(matrix<double> i:layers){
		ret+=i.info();
	}
	return ret;
}
