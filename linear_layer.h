#ifndef LINEAR_LAYER_H
#define LINEAR_LAYER_H
#include "layer.h"
template<typename T>
class linear_layer : public layer<T>{
public:
	linear_layer(uint32_t input,uint32_t output) : layer<T>(input, output){}
	
	virtual typename layer<T>::output_t activate(const typename layer<T>::output_t& out)const{
		return out;
	};
	
	virtual typename layer<T>::output_t derivate_activate(const typename layer<T>::output_t& out)const{
		return typename layer<T>::output_t(out.n_cols, arma::fill::ones);
	}
};


#endif // LINEAR_LAYER_H
