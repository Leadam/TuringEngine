#ifndef TRAINER_H
#define TRAINER_H
#include <vector>
#include "layer.h"
#include "network.h"

template<typename T>
class trainer{
public:
	typedef layer<T> layer_t;
	typedef typename layer_t::input_t input_t;
	typedef typename layer_t::output_t output_t;
	typedef typename layer_t::error_t error_t;
	typedef std::vector<std::pair<input_t,output_t> > dataset_t;
	
	template<typename>
	friend class network;
	
private:
	std::vector<layer_t*> _layers;
	std::vector<output_t> _outputs;
	std::vector<error_t> _errors;
	
	double _learning_rate;
	
	
	
	output_t _compute_forward(const input_t& in){
		auto l = _layers.begin();
		auto o = _outputs.begin();
		*o = in;
		++o;
		for(;l != _layers.end(); ++l, ++o){
			*o = (*l)->compute_forward(*(o-1));
		}
		return *(o-1);
	}
	
	error_t _error(const output_t& expected, const output_t& result){
		return -(expected - result);
	}
	
	void _learn(const error_t& e){
		
		auto l = _layers.rbegin();
		auto o = _outputs.rbegin();
		error_t error = e;
		for(;l != _layers.rend(); ++l, ++o){
			error_t d_in = (*l)->derivate_activate(*(o+1));
			error_t last = error;
			error = (*l)->compute_backward(error);
			(*l)->_weight += ((d_in.t() * last) * _learning_rate);
		}
	}
public:
	trainer(const network<T>& network, double learning_rate) : 
		_layers(network._layers),
		_outputs(_layers.size()+1),
		_errors(_layers.size()+1),
		_learning_rate(learning_rate){}
		
	trainer(trainer&& other) :
		_layers(other._layer),
		_outputs(other._outputs),
		_errors(other._errors),
		_learning_rate(other._learning_rate){}
		
	double train_once(input_t in, output_t out){
		output_t result = _compute_forward(in);
		error_t e = _error(out, result);
		_learn(e);
		return arma::sum(e);
	}
	
	double train(const dataset_t& data, double error = 0.001){
		error_t e;
		for(auto& it : data){
			e = train_once(it.first, it.second);
			if( e < error) return e;
		}
		return e;
	}
};

#endif // TRAINER_H
