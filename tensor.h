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
		Array<F> operator*(F&);
		Array<F> operator*(const Array&);
		F* begin();
		const F* begin() const;
		F* end();
		const F* end() const;
		const int len() const;
		const void print() const;
};
template <typename F>
class Array2d{
	private : 
		bool MadeT = false;
		Array<Array<F>> data;
		Array<Array<F>> T;
		Array<int> dimensions;
	public :
		Array2d() = default;
		Array2d(int,int);
		Array2d(int,int,F);
		Array2d(const Array2d&);
		Array2d(std::initializer_list<std::initializer_list<F>>);
		Array<F>& operator[](int);
		const Array<F>& operator[](int)const;
		void operator=(const Array2d&);
		Array2d operator+(F);
		Array2d operator+(const Array<F>&);
		Array2d operator+(const Array2d&);
		Array2d operator*(F);
		Array2d operator*(const Array<F>&);
		Array2d operator*(const Array2d&);
		const int len() const;
		const void print() const;
		const Array<int>& dims() const;
		
		Array2d dot(const Array2d&);
		Array2d operator&(const Array2d&);
};
#include "tensor.cpp"
#endif