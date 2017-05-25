#include <iostream>
#include "network.h"
#include "relu_layer.h"
#include "sigmoid_layer.h"
#include "linear_layer.h"
#include "trainer.h"


#include "graphics/graphics.h"

int main(int argc, char **argv) {
	init_te_graphics();
	
	network<double> net;
	net.append_layer< linear_layer<double> >(1);
	net.append_layer< relu_layer<double> >(1000);
	net.append_layer< relu_layer<double> >(1000);
	net.append_layer< relu_layer<double> >(1000);
	net.append_layer< relu_layer<double> >(1000);
	net.append_layer< sigmoid_layer<double> >(1000);
	net.append_layer< relu_layer<double> >(80);
	net.append_layer< relu_layer<double> >(50);
	net.append_layer< sigmoid_layer<double> >(30);
	net.append_layer< sigmoid_layer<double> >(1);
	
	trainer<double> train(net,0.001);
	
	std::vector<double> errors;
	
	chart c;
	c.setDataSet(errors);
	
	int i=0;
	while(i++ < 1000000){
		double num1 = (double)rand() / std::numeric_limits< int >::max();
		errors.push_back(train.train_once({num1},{sin(num1)}));
		
		
		c.update();
	}
	
	
	quit_te_graphics();
}
