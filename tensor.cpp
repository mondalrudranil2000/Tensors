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