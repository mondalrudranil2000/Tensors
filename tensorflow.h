#ifndef Tenflow_H
#define Tenflow_H
#include "tensor.h"
#include <string>
#include <tuple>
enum ACTIVATIONS{ LINEAR,RELU,SIGMOID};
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
		Array<float> bias;
		bool b_t;
		ACTIVATIONS activation;
	public :
		const Array<int>& dims();
		std::string activation_func();
		Multitron()=default;
		Multitron(const Multitron&);
		void operator=(const Multitron&);
		Multitron(int,int,std::string,bool);
		void init(int,int,std::string,bool);
		Array2d<float> operator()(Array2d<float>&);
		Array2d<float> update(Array2d<float>& error,float lr);
		void print();
};
typedef Multitron Dense;
class Sequential{
	private :
		Array<Dense> layers;
		Array<float> losses;
		int in_shape;
		float lr;
		Array2d<float> forward(Array2d<float> input);
		void backward(Array2d<float> error,float threshold);
	public :
		Sequential()=default;
		Sequential(float lr,int input_shape);
		void add(int,std::string,bool);
		std::tuple<Array<float>,Array<float>> train(int,int,Array2d<float>,Array2d<float>,float,bool,float);
		float test(Array2d<float>,Array2d<float>,int,bool);
		void dims();
};
void z_normalize(Array2d<float>& arr);
void min_max_normalize(Array2d<float>& arr);
std::tuple<Array2d<float>,Array2d<float>> split_data(float fraction,Array2d<float> arr);
std::tuple<Array<float>,Array<float>> split_data(float fraction,Array<float> arr);
#include "tensorflow.cpp"
#endif