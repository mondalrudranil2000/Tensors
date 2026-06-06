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
		void init(int,std::initializer_list<F>);
		Array(std::initializer_list<F>);
		Array(int);
		Array(int,F);
		Array(int,std::initializer_list<F>);
		Array(const Array&);
		F& operator[](int);
		const F& operator[](int) const;
		void operator=(const Array&);
		 const Array<int> operator==(const Array<F>&) const ;
		 const Array<int> operator<=(const Array<F>&) const;
		 const Array<int> operator>=(const Array<F>&) const;
		 const Array<int> operator==(F) const;
		const Array<int> operator<=(F) const;
		const Array<int> operator>=(F) const;
		Array<F> operator+(F&) const ;
		Array<F> operator+(const Array&) const;
		Array<F> operator*(F&) const;
		Array<F> operator*(const Array&) const;
		Array<F> operator-(F&) const;
		Array<F> operator-(const Array&) const;
		void operator-=(const Array&);
		Array<F> operator/(F&) const;
		Array<F> operator/(const Array&) const;
		F* begin();
		const F* begin() const;
		F* end();
		const F* end() const;
		F max() const;
		F min() const;
		void append(F value);
		const int len() const;
		const void print() const;
};

template <typename F> class Array2d;
template <typename F>
class TensorProxy{
	public :
		Array2d<F>& source;
		TensorProxy(Array2d<F>& src):source(src){}
		struct Column{
			Array2d<F>& parent;
			int col_idx;
			F& operator[](int i);
			const	F& operator[](int i)const;
		};
		Column operator[](int i);
		const Column operator[](int i) const ;
		Array2d<F> dot(const Array2d<F>&);
		Array2d<F> operator&(const Array2d<F>&);
};
template <typename F>
class Array2d{
	private : 
		Array<Array<F>> data;
		Array<int> dimensions;
	public:
		Array2d() = default;
		Array2d(int,int);
		Array2d(int,int,F);
		Array2d(int,int,std::initializer_list<F>);
		void init(int,int,std::initializer_list<F>);
		void init(int,int,F);
		Array2d(const Array2d&);
		Array2d(std::initializer_list<std::initializer_list<F>>);
		Array<F>& operator[](int);
		const Array<F>& operator[](int)const;
		void operator=(const Array2d&);
		void operator=(const Array<Array<F>>&);
		const Array2d<int> operator==(const Array2d<F>&) const;
		const Array2d<int> operator<=(const Array2d<F>&) const;
		const Array2d<int> operator>=(const Array2d<F>&) const;
		const Array2d<int> operator==(const Array<F>&) const;
		const Array2d<int> operator<=(const Array<F>&) const;
		const Array2d<int> operator>=(const Array<F>&) const;
		const Array2d<int> operator==(F) const;
		const Array2d<int> operator<=(F) const;
		const Array2d<int> operator>=(F) const;
		Array2d operator+(F) const;
		Array2d operator+(const Array<F>&) const;
		Array2d operator+(const Array2d&) const;
		Array2d operator*(F) const;
		Array2d operator*(const Array<F>&) const;
		Array2d operator*(const Array2d&) const;
		Array2d operator-(F) const;
		Array2d operator-(const Array<F>&) const;
		Array2d operator-(const Array2d&) const;
		void operator-=(const Array2d&);
		Array2d operator/(F) const;
		Array2d operator/(const Array<F>&) const;
		Array2d operator/(const Array2d&) const;
		F max() const;
		F min() const;
		const int len() const;
		const void print() const;
		const Array<int>& dims() const;
		TensorProxy<F> T();
		Array2d dot(const Array2d<F>&);
		Array2d operator&(const Array2d<F>&);
		Array2d dot(const TensorProxy<F>&);
		Array2d operator&(const TensorProxy<F>&);
};
#include "tensor.cpp"
#endif