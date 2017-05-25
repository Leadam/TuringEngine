#ifndef RELU_LAYER_H
#define RELU_LAYER_H
#include "layer.h"
template<typename T>
class relu_layer : public layer<T>{
public:
	relu_layer(uint32_t input,uint32_t output) : layer<T>(input, output){}
	
	virtual typename layer<T>::output_t activate(const typename layer<T>::output_t& out)const{
		typename layer<T>::output_t result = out;
		result.transform([](T x){ 
			return x > 0 ? x : 0;
		});
		return result;
	};
	
	virtual typename layer<T>::output_t derivate_activate(const typename layer<T>::output_t& out)const{
		typename layer<T>::output_t result = out;
		result.transform([](T x){ 
			return x > 0 ? 1 : 0;
		});
		return result;
	}
};

#endif // RELU_LAYER_H
