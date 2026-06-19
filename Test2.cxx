#include "tensorflow.h"
#include <iomanip>
using namespace std;
int main(int argc, char *argv[])
{
	int size = 32;
	int samples = 1000;
	float fraction = 0.2;
	Array2d<float> a(samples, size,{-5,5});
	Array2d<float> t = a * a;
	z_normalize(a);
	min_max_normalize(t);
	auto [train_x,test_x] = split_data(fraction,a);
	auto [train_y,test_y] = split_data(fraction,t);
	Sequential sq(0.00001, size);
	sq.add(64,"relu",true);
	sq.add(64,"relu",true);
	sq.add(32,"relu",true);
	sq.add(size,"linear",true);
	auto [tl,vl] = sq.train(100,12,train_x,train_y,5.0f,false,0.1);
	tl.print();
	vl.print();
	float acc = sq.test(test_x,test_y,12,false);
	cout<<"Accuracy : "<<acc*100.0f<<" % "<<endl;
	return 0;
}