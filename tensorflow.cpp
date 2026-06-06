#include "tensorflow.h"
#define eps 1e-5
void Relu(Array2d<float>& pred){
	for(int i=0;i<pred.dims()[0];i++){
		for(int j=0;j<pred.dims()[1];j++){
				pred[i][j] = fmax(0.0f,pred[i][j]);
		}
	}		
}
void ReluGrad(Array2d<float>& error,Array2d<float>& pred){
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

void z_normalize(Array2d<float>& arr){
	float mean = avg(arr);
	float var = 0.0f;
	int m=arr.dims()[0];
	int n=arr.dims()[1];
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			float diff = arr[i][j] - mean;
			var += diff * diff;
		}
	}
	float std_dev = std::sqrt(var/(m*n));
	arr = (arr - mean) * (1.0f/(std_dev + 1e-7));
}
void min_max_normalize(Array2d<float>& arr){
	float max = arr.max();
	arr = arr / (max+1e-7);
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
Multitron::Multitron(const Multitron& m){
	weights = m.weights;
	activation = m.activation;
	bias = m.bias;
	b_t  = m.b_t;
}
void Multitron::operator=(const Multitron& m){
	weights = m.weights;
	activation = m.activation;
	bias = m.bias;
	b_t = m.b_t;
}
Multitron::Multitron(int m,int n,std::string Activation="relu",bool b_true=false){
	weights.init(m,n,{-1,1});
	bias.init(n,0);
	b_t = b_true;
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
void Multitron::init(int m,int n,std::string Activation="",bool b_true=false){
	weights.init(m,n,{-1,1});
	weights = weights / std::sqrt(m);
	b_t = b_true;
	bias.init(n,0);
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
		activation = LINEAR;
	}
}
const Array<int>& Multitron::dims(){
	return weights.dims();
}
Array2d<float> Multitron::operator()(Array2d<float>& arr){
	input = arr;
	Array2d<float> pred = arr.dot(weights);
	if(b_t) pred = pred + bias;			
	if(activation==RELU){
		Relu(pred);
	}
	else if(activation==SIGMOID){
		Sigmoid(pred);
	}
	output = pred;
	return pred;	
}
Array2d<float> Multitron::update(Array2d<float>& error, float lr){
	if(activation==RELU){
		ReluGrad(error,output);
	}
	else if(activation==SIGMOID){
		error = error * (1.0f-output) * output;
	}
	Array2d<float> step = input.T().dot(error);
	Array2d<float> grad = error.dot(weights.T());
	step = step * lr;
	weights -= step;
	if(b_t){
		Array<float> b_step = sum(error,0);
		b_step = b_step * lr;
		bias -= b_step;
	}
	return grad;
}
std::string Multitron::activation_func(){
	std::string name = "linear";
	if(activation==RELU) name = "relu";
	else if(activation==SIGMOID) name = "sigmoid";
	return name;
}
void Multitron::print(){
	weights.print();
}
Sequential::Sequential(float lr,int input_shape){
		this->lr = lr;
		in_shape = input_shape;
}
void Sequential::add(int n,std::string activation,bool bias=false){
		if(layers.len()==0){
			layers.append(Dense(in_shape,n,activation,bias));
		}
		else{
			int m = layers[-1].dims()[1];
			layers.append(Dense(m,n,activation,bias));
		}
}
Array<float> Sequential::train(int epochs,int batch_size,Array2d<float> input,Array2d<float> true_vals,float threshold = 5.0f, bool normalize = true){
		int nums = input.dims()[0];
		std::cout<<" Prepairing "<<std::endl;
		if(normalize){
			z_normalize(input);
			if(layers[-1].activation_func()=="relu"){
				min_max_normalize(true_vals);
			}
		}
		Array<Array2d<float>> batches;
		Array<Array2d<float>> batch_trues;
		for(int i=0;i<nums;i+=batch_size){
			Array<Array<float>> batch;
			Array<Array<float>> batch_true;
			for(int j=0;j<batch_size;j++){
				if((i+j)>=nums) break;
				Array<float> temp(input[i+j]);
				batch.append(temp);
				temp = true_vals[i+j];
				batch_true.append(temp);
			}
			Array2d<float> bth;
			bth = batch;
			batches.append(bth);
			bth = batch_true;
			batch_trues.append(bth);
		}
		std::cout<<"Starting"<<std::endl;
		for(int i=0;i<epochs;i++){
			std::cout<<"Epoch : "<<i<<std::endl;
			float Epoch_loss=0.0f;
			for(int k=0; k< batches.len();k++){
			Array2d<float> pred(batches[k]);
			for(int j=0;j<layers.len();j++){
				Array2d<float> p = layers[j](pred);
				pred = p;
			}
			Array2d<float> error = pred - batch_trues[k];
			float loss = 0.0f;
			for(int j=0;j<error.dims()[0];j++){
				loss += sum(error[j]*error[j]);
			}
			Epoch_loss += loss;
			Array2d<float> grad = error;
			for(int j=layers.len()-1;j>=0;--j){
				for(int r=0;r<grad.dims()[0];r++){
					for(int c=0;c<grad.dims()[1];c++){
						if(grad[r][c]>threshold) grad[r][c] = threshold;
						if(grad[r][c]<-threshold) grad[r][c] = -threshold;
					}
				}
				grad = layers[j].update(grad,lr);
			}
		}
		losses.append(Epoch_loss/(float)nums);
	}
	return losses;
}
float Sequential::test(Array2d<float> input, Array2d<float> true_vals, int batch_size=32,bool normalize=true){
		int nums = input.dims()[0];
		std::cout<<" Prepairing "<<std::endl;
		if(normalize){
			z_normalize(input);
			if(layers[-1].activation_func()=="relu"){
				min_max_normalize(true_vals);
			}
		}
		Array<Array2d<float>> batches;
		Array<Array2d<float>> batch_trues;
		for(int i=0;i<nums;i+=batch_size){
			Array<Array<float>> batch;
			Array<Array<float>> batch_true;
			for(int j=0;j<batch_size;j++){
				if((i+j)>=nums) break;
				Array<float> temp(input[i+j]);
				batch.append(temp);
				temp = true_vals[i+j];
				batch_true.append(temp);
			}
			Array2d<float> bth;
			bth = batch;
			batches.append(bth);
			bth = batch_true;
			batch_trues.append(bth);
		}
		Array<float> sum;
		std::cout<<"Starting tests"<<std::endl;
		for(int k=0; k< batches.len();k++){
			Array2d<float> pred(batches[k]);
			for(int j=0;j<layers.len();j++){
				Array2d<float> p = layers[j](pred);
				pred = p;
			}
			int correct_elements = 0;
			int total_elements = 0;

			for(int i = 0; i < batch_trues[k].dims()[0]; i++) {
			    for(int j = 0; j < batch_trues[k].dims()[1]; j++) {
			        float absolute_diff = std::abs(pred[i][j] - batch_trues[k][i][j]);
			        
			        if(!std::isfinite(absolute_diff)) continue;
			        
		 	       if (absolute_diff <= 0.5f) {
		  	          correct_elements++;
		   	     }
  		  	    total_elements++;
		    	}	
			}
			sum.append((float)correct_elements / total_elements);
		}
	return avg(sum);
}
void Sequential::dims(){
	for(auto weight : layers){
		weight.dims().print();
		weight.print();
	}
}