#include "stdcpp.h"
#include "matrix.h"
#include "network.h"

void end(){
	std::cout<<"everything is ok";
	std::exit(0);
}

int main() {
	network nn({3, 10, 5});
	std::cout<<(nn.predict(matrix<double>(3, 1)).info());
}
