#ifndef Tensor_H
#define Tensor_H
#include <initializer_list>
#include <string>
template <typename F>
class Array{
	private:
		F* data;
		int length;
	public:
		Array();
		~Array();
		void init(std::initializer_list<F>);
		void init(int,F);
		Array(std::initializer_list<F>);
		Array(int);
		Array(int,F);
		Array(const Array&);
		F& operator[](int);
		const F& operator[](int) const;
		void operator=(const Array&);
		Array<F> operator+(F&);
		Array<F> operator+(const Array&);
		F* begin();
		const F* begin() const;
		F* end();
		const F* end() const;
		const int len() const;
		const void print() const;
};
#include "tensor.cpp"
#endif