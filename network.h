#ifndef NETWORK_H
#define NETWORK_H
#include "layer.h"

template<typename T>
class network{
public:
	typedef layer<T> layer_t;
	typedef typename layer_t::input_t input_t;
	typedef typename layer_t::output_t output_t;
	
private:
	template<typename>
	friend class trainer;
	
	std::vector<layer_t*> _layers;
public:
	network(){}
	
	template<typename LAYER, typename... ARGS>
	void append_layer(int size, ARGS&... args){ 
		if(_layers.size()){
			uint32_t last_layer_output = _layers.back()->output();
			_layers.push_back(new LAYER(last_layer_output, size, args...)); 
		}else{
			_layers.push_back(new LAYER(size, size, args...));
		}
	}
	
	output_t compute_forward(const input_t& input){
		input_t result = input;
		for(auto it : _layers){
			result = it->compute_forward(result);
		}
		return result;
	}
	
	
	uint32_t size()const{
		return _layers.size();
	}
	
	
};

#endif // NETWORK_H
