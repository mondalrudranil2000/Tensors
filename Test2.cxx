#include "tensorflow.h"
#include <iomanip>
using namespace std;
int main(int argc, char *argv[])
{
	int size = 32;
	Array2d<float> a(size, size,{-5,5});
	Array2d<float> t = a * a;
	Array2d<float> in = a;
	Sequential sq(0.005, size);
	sq.add(64,"relu",true);
	sq.add(64,"relu",true);
	sq.add(32,"relu",true);
	sq.add(size,"linear",true);
	Array<float> ls = sq.train(50,12,in,t);
	ls.print();
	float acc = sq.test(in,t,12);
	cout<<"Accuracy : "<<acc*100.0f<<" % "<<endl;
	return 0;
}