#ifndef NETWORKH
#define NETWORKH

#include "stdcpp.h"

#include "matrix.h"
const double EPSILON=1E-5;
namespace activation{
	double sigmoid(double x);
	double relu(double x);
}
namespace lose{
	double sse(matrix<double> a, matrix<double> t);
	double cee(matrix<double> a, matrix<double> t);
	matrix<double> softmax(matrix<double> output);
}
class network {
	std::vector<matrix<double>> w;
	std::vector<matrix<double>> layers;
	std::vector<std::vector<double>> gradients;
	matrix<double> input, output;
	double train_rate;
	std::function<double(matrix<double>,matrix<double>)> lose_function;
	std::function<double(double)> activation_function;

	int cur_layer;
	void back_propagation(matrix<double> &output);

	public:
	int depth;
	network();
	network(std::vector<int> dim=std::vector<int>(), std::function<double(double)> activation_function = activation::relu, std::function<double(matrix<double>,matrix<double>)> lose_function = lose::cee);
	void train(matrix<double> input,matrix<double> output);
	matrix<double> predict(matrix<double> input);
	std::string info();
};
#endif
