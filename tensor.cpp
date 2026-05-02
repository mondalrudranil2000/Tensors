#include <iostream>
#include <string>
#include <initializer_list>
template <typename F>
Array<F>::Array():data(nullptr),length(0){}
template <typename F>
Array<F>::~Array(){ if(data){delete[] data;} data=nullptr;}
template <typename F>
void Array<F>::init(int size,F value){
			data = new F[size];
			for(int i=0;i<size;i++){
				data[i] = value;
			}
			length = size;
		}
template <typename F>
void Array<F>::init(std::initializer_list<F> list){
			int size = list.size();
			data = new F[size];
			int i=0;
			for(F value : list){
				data[i] = value;++i;
			}
			length = size;
		}
template <typename F>
Array<F>::Array(std::initializer_list<F> list){
			init(list);	
		}
template <typename F>
Array<F>::Array(int size){
			data = new F[size];
			length = size;
		}
template <typename F>
Array<F>::Array(int size,F value){
			init(size,value);
		}
template <typename F>
Array<F>::Array(const Array<F>& v){
			*this = v;
		}
template <typename F>
F& Array<F>::operator[](int index){ return data[index];}
template <typename F>
const F& Array<F>::operator[](int index) const{ return data[index];}
template <typename F>
void Array<F>::operator=(const Array<F>& v){
			if(this == &v) return;
			F* newData = new F[v.len()];
			for(int i=0;i<v.len();i++){
				newData[i] = v[i];
			}
			delete[] data;
			data = newData;
			length = v.len();
		}
template <typename F>
Array<F> Array<F>::operator+(F& value){
			Array<F> a(length);
			int i=0;
			for(F& val : *this){
				a[i] = val + value;++i;}
			return a;
		}
template <typename F>
Array<F> Array<F>::operator+(const Array<F>& v){
			Array<F> a(length);
			for(int i=0;i<length;i++){
				a[i] = data[i] + v[i];
			}
			return a;
		}
template <typename F>
Array<F> Array<F>::operator*(F& value){
			Array<F> a(length);
			int i=0;
			for(F& val : *this){
				a[i] = val * value;++i;}
			return a;
		}
template <typename F>
Array<F> Array<F>::operator*(const Array<F>& v){
			Array<F> a(length);
			for(int i=0;i<length;i++){
				a[i] = data[i] * v[i];
			}
			return a;
		}

template <typename F>
const F* Array<F>::begin() const {return data;}
template <typename F>
F* Array<F>::begin() {return data;}
template <typename F>
const F* Array<F>::end() const {return data+length;}
template <typename F>
F* Array<F>::end() {return data+length;}
template <typename F>
const int Array<F>::len() const{return length;}
template <typename F>
const void Array<F>::print() const{
			std::cout<<"{ ";
			for(const F& val : *this){
				std::cout<<val<<" , ";
			}
			std::cout<<" }"<<std::endl;
		}
		
//array helper
template <typename F>
F sum(const Array<F>& arr){
		F sum = (F)0;
		for( F val : arr){ sum += val;}
		return sum;
}	
template <typename F>
F avg(const Array<F>& arr){
	return (F)(sum(arr)/arr.len());
}

//2d	
template <typename F>
Array2d<F>::Array2d(int m,int n){ 
data.init(m,Array<F>(n)); this->dimensions = Array<int>({m,n});}
template <typename F>
Array2d<F>::Array2d(int m,int n, F value){ 
data.init(m,Array<F>(n,value)); this->dimensions = Array<int>({m,n});}
template <typename F>
Array2d<F>::Array2d(const Array2d& arr){ 
this->data = arr.data;
this->dimensions = arr.dims();
 }
template <typename F>
Array2d<F>::Array2d(std::initializer_list<std::initializer_list<F>> list){ 
			data.init(list.size(),Array<F>());
			int i=0;
			for(std::initializer_list<F> val : list){
				data[i].init(val);++i;
			}
			this->dimensions = Array({i, data[0].len()});
		}
template <typename F>
Array<F>& Array2d<F>::operator[](int index){
			return data[index];
		}
template <typename F>
const Array<F>& Array2d<F>::operator[](int index) const{
			return data[index];
		}
template <typename F>
void Array2d<F>::operator=(const Array2d& v){
			if(this == &v) return;
			this->data = v.data;
			this->dimensions = v.dims();
		}
template <typename F>
Array2d<F> Array2d<F>::operator+(F value){
			Array2d<F> a = *this;
			for(int i=0;i<data.len();i++){
				a[i] = data[i] + value;
			}
			return a;
		}
template <typename F>
Array2d<F> Array2d<F>::operator+(const Array<F>& value){
			Array2d<F> a = *this;
			for(int i=0;i<data.len();i++){
				a[i] = data[i] + value;
			}
			return a;
		}
template <typename F>
Array2d<F> Array2d<F>::operator+(const Array2d<F>& arr){
			Array2d<F> a = *this;
			for(int i=0;i<data.len();i++){
				a[i] = data[i] + arr[i];
			}
			return a;
		}
template <typename F>
Array2d<F> Array2d<F>::operator*(F value){
			Array2d<F> a = *this;
			for(int i=0;i<data.len();i++){
				a[i] = data[i] * value;
			}
			return a;
		}
template <typename F>
Array2d<F> Array2d<F>::operator*(const Array<F>& value){
			Array2d<F> a = *this;
			for(int i=0;i<data.len();i++){
				a[i] = data[i] * value;
			}
			return a;
		}
template <typename F>
Array2d<F> Array2d<F>::operator*(const Array2d<F>& arr){
			Array2d<F> a = *this;
			for(int i=0;i<data.len();i++){
				a[i] = data[i] * arr[i];
			}
			return a;
		}
template <typename F>
const int Array2d<F>::len() const{ return data.len();}
template <typename F>
const void Array2d<F>::print() const{
			std::cout<<"{"<<std::endl;
			for(const auto& val : data){
				std::cout<<"    ";val.print();
			}
			std::cout<<"}"<<std::endl;
		}
template <typename F>
const Array<int>& Array2d<F>::dims() const{ return dimensions;}


template <typename F>
Array2d<F> Array2d<F>::dot(const Array2d& v){
		if(!MadeT){
			T.init(dimensions[1],Array<F>(dimensions[0]));
			for(int i=0;i<dimensions[0];i++){
				for(int j=0;j<dimensions[1];j++){
					T[j][i] = data[i][j];
				}}
			MadeT = true;}
		Array<int> dim = v.dimensions;
		if (dimensions[1] != dim[0]) {std::cout<<"Error dimensions Not Same !!"; exit(1);}
		Array2d<F> a = Array2d(dimensions[0],dim[1]);
		for(int i=0;i<dimensions[0];i++){
			for(int j=0;j<dim[1];j++){
					a[i][j] = sum(data[i] * v.T[j]);
			}
		}
		return a;
}
template <typename F>
Array2d<F> Array2d<F>::operator&(const Array2d& v) { return this->dot(v); }

/*
 	----------- DO AFTER THE INTERPRETER PROJECT IS COMPLETE -------
class FuncArray<F>{
	private:
		Array<F><string> data;
	public:
		FuncArray<F>(int size){data.init(size,"1");}
		FuncArray<F>(int size, string func){data.init(size,func);}
		FuncArray<F>(std::initializer_list<string> functions){data.init(functions);}
		Array<F><float> operator[](float )
*/