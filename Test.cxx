#include "tensor.h"
template <typename F>
Array2d<F> dot(const Array2d<F>& b,const Array2d<F>& v){
		std::cout<<"A ";
		if (b.dims()[1] != v.dims()[0]) {std::cout<<"Error dimensions Not Same !!"; return Array2d<F>(1,1,0);}
		Array2d<F> a(b.dims()[0],v.dims()[1],(F)0);
		std::cout<<"C "<<std::endl;
		for(int i=0;i<b.dims()[0];i++){
			for(int j=0;j<v.dims()[1];j++){
					a[i][j] = sum(b[i] * v.T[j]);
					std::cout<<i<<" , "<<j<<" , "<<a[i][j]<<std::endl;
			}
		}
		a.Transpose();
		return a;
}

int main(int argc, char *argv[])
{
	Array2d<int> a(3,2,2);
	a.print();
	Array2d<int> b(3,2,2);
	b.print();
	Array2d<int> d=a.T()&b;
	Array2d<int> e=a&b.T();
	d.print();
	e.print();
	return 0;
}