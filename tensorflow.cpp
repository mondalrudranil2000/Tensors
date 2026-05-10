#include "tensorflow.h"
#define eps 1e-5
void Relu(Array2d<float>& pred){
	for(int i=0;i<pred.dims()[0];i++){
		for(int j=0;j<pred.dims()[1];j++){
				pred[i][j] = fmax(0.0f,pred[i][j]);
		}
	}		
}
void ReluGrad(Array2d<float> error,Array2d<float> pred){
	for(int i=0;i<pred.dims()[0];i++){
		for(int j=0;j<pred.dims()[1];j++){
				error[i][j] = pred[i][j]> 0? error[i][j] : 0;
		}
	}		
}
void Sigmoid(Array2d<float>& pred){
		float sc = 1.0 + eps;
		for(int i=0;i<pred.dims()[0];i++){
			for(int j=0;j<pred.dims()[1];j++){
					float deno = sc + exp(-pred[i][j]);
					pred[i][j] = 1.0/deno;
			}
		}
}
Perceptron::Perceptron(int m){
	weight.init(m,{-1,1});
}
void Perceptron::init(int m){
	weight.init(m, {-1,1});
}
float Perceptron::operator()(const Array<float>& input){
	grad = input;
	return sum<float>( weight * input);
}
void Perceptron::update(float loss,float lr){
	float scale = loss * lr;
	Array<float> step = grad * scale;
	weight -= step;
}
Multitron::Multitron(int m,int n,std::string Activation="relu"){
	weights.init(m,n,{-1,1});
	for(auto& c : Activation){
		c = tolower(c);
	}
	if(Activation=="relu"){
		activation = RELU;
	}
	else if(Activation=="sigmoid"){
		activation = SIGMOID;
	}
	else{
		activation = RELU;
	}
}
void Multitron::init(int m,int n,std::string Activation="relu"){
	weights.init(m,n,{-1,1});
	for(auto& c : Activation){
		c = tolower(c);
	}
	if(Activation=="relu"){
		activation = RELU;
	}
	else if(Activation=="sigmoid"){
		activation = SIGMOID;
	}
	else{
		activation = RELU;
	}
}
Array2d<float> Multitron::operator()(Array2d<float>& arr){
	input = arr;
	Array2d<float> pred = arr.dot(weights);
	if(activation==RELU){
		Relu(pred);
	}
	else{
		Sigmoid(pred);
	}
	output = pred;
	return pred;	
}
Array2d<float> Multitron::update(Array2d<float>& error, float lr){
	if(activation==RELU){
		ReluGrad(error,output);
	}
	else{
		error = error * (1.0f-output) * output;
	}
	Array2d<float> step = input.T().dot(error);
	Array2d<float> grad = error.dot(weights.T());
	step = step * lr;
	weights -= step;
	return grad;
}