#include "tensor.h"
int main(int argc, char *argv[])
{
	Array2d<int> a(3,2,2);
	Array2d<int> b(2,3,2);
	Array2d<int> c = a&b;
	c.print();
	c.dims().print();
	return 0;
}