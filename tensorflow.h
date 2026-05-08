#ifndef Tenflow_H
#define Tenflow_H
#include "tensor.h"
class Perceptron{
	private:
		Array<float> weight;
		Array<float> grad;
	public:
		Perceptron()=default;
		Perceptron(int);
		void init(int);
		float operator()(const Array<float>&);
		void update(float loss,float lr);
};
class Multitron{
	private : 
		
#include "tensorflow.cpp"
#endif