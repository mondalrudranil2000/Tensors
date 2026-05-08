#include "tensorflow.h"
int main(int argc, char *argv[])
{
	float t_val = 3;
	Array<float> a(3,{-1,1});
	Perceptron p(3);
	for(int i=0;i<20;i++){
		float pred=p(a);
		float loss = pred-t_val;
		std::cout<<"Pred : "<<pred<<" , "<<"Loss : "<<loss<<std::endl;
		p.update(loss, 0.3);
	}
	return 0;
}