#include "tensorflow.h"
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