#ifndef LAYER_H
#define LAYER_H
#include <armadillo>

template<typename T>
class layer{
public:
	typedef T value_t;
	typedef arma::Mat<value_t> weight_t;
        typedef arma::Row<value_t> input_t;
	typedef arma::Row<value_t> output_t;
	typedef arma::Row<value_t> bias_t;
        typedef arma::Row<value_t> error_t;	
private:
	weight_t _weight;
	bias_t _bias;
	
	template<typename>
	friend class trainer;
public:
	layer(uint32_t input,uint32_t output) : 
		_weight(input,output,arma::fill::randu),
		_bias(output,arma::fill::randu)
	{}
	
	uint32_t input()const{ return _weight.n_rows; }
	uint32_t output()const{ return _weight.n_cols; }
	
	output_t compute_forward(const input_t& in)const{
		return activate((in * _weight) + _bias);
	}
	
	input_t compute_backward(const output_t& in)const{
		return in * _weight.t();
	}
	
	virtual output_t activate(const output_t& out)const = 0;
	virtual output_t derivate_activate(const output_t& out)const = 0;
	
};

#endif // LAYER_H
