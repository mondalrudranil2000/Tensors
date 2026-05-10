#ifndef Tenflow_H
#define Tenflow_H
#include "tensor.h"
#include <string>
enum ACTIVATIONS{ RELU,SIGMOID};
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
		Array2d<float> input;
		Array2d<float> output;
		Array2d<float> weights;
		ACTIVATIONS activation;
	public :
		Multitron()=default;
		Multitron(int,int,std::string);
		void init(int,int,std::string);
		Array2d<float> operator()(Array2d<float>&);
		Array2d<float> update(Array2d<float>& error,float lr);
};
typedef Multitron Dense;
class Sequential{
	private :
		Array<Dense> layers;
		Array<float> loss;
		Array2d<float> input;
		Array2d<float> true_val;
		float lr;
	public :
		Sequential()=default;
		Sequential(float,int);
		void add(int,std::string);
		void compile();
		Array<float> run(int);
};
#include "tensorflow.cpp"
#endif