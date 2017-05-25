#ifndef SIGMOID_LAYER_H
#define SIGMOID_LAYER_H
#include "layer.h"
#include <complex>
template<typename T>
class sigmoid_layer : public layer<T>{
public:
	sigmoid_layer(uint32_t input,uint32_t output) : layer<T>(input, output){}
	
	virtual typename layer<T>::output_t activate(const typename layer<T>::output_t& out)const{
		typename layer<T>::output_t result = out;
		result.transform([](T x){ 
			return x / (1.0 + std::abs(x));
		});
		return result;
	};
	
	virtual typename layer<T>::output_t derivate_activate(const typename layer<T>::output_t& out)const{
		typename layer<T>::output_t result = out;
		result.transform([](T x){ 
			return x / std::pow((1.0 + std::abs(x)),2);
		});
		return result;
	}	
};

#endif // SIGMOID_LAYER_H
