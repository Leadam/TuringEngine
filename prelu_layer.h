#ifndef PRELU_LAYER_H
#define PRELU_LAYER_H
#include "layer.h"
template<typename T>
class prelu_layer : public layer<T>{
private:
	T _alpha;
public:
	prelu_layer (uint32_t input,uint32_t output, T alpha) : layer<T>(input, output), _alpha(alpha){}
	
	virtual typename layer<T>::output_t activate(const typename layer<T>::output_t& out)const{
		typename layer<T>::output_t result = out;
		result.transform([](T x){ 
			return x < 0 ? _alpha * x : x;
		});
		return result;
	};
	
	virtual typename layer<T>::output_t derivate_activate(const typename layer<T>::output_t& out)const{
		typename layer<T>::output_t result = out;
		result.transform([](T x){ 
			return x < 0 ? _alpha : 1;
		});
		return result;
	}
};

#endif // PRELU_LAYER_H
