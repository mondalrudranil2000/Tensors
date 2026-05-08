#include <iostream>
#include <string>
#include <initializer_list>
#include <vector>
#include <random>
#include <type_traits>

template <typename T>
T Rand(T min, T max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // Choose the correct distribution type based on T
    using dist_type = std::conditional_t<
        std::is_floating_point_v<T>,
        std::uniform_real_distribution<T>,
        std::uniform_int_distribution<T>
    >;

    dist_type dist(min, max);
    return dist(gen);
}
template <typename T>
T Rand(std::initializer_list<T> range) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // Choose the correct distribution type based on T
    using dist_type = std::conditional_t<
        std::is_floating_point_v<T>,
        std::uniform_real_distribution<T>,
        std::uniform_int_distribution<T>
    >;
	std::vector<T> v= range;
    dist_type dist(v[0],v[1]);
    return dist(gen);
}

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
			if(size==0){
				std::cout<<"0 size"<<std::endl;
				exit(1);
			}
			data = new F[size];
			int i=0;
			for(F value : list){
				data[i] = value;++i;
			}
			length = size;
		}
template <typename F>
void Array<F>::init(int m,std::initializer_list<F> range){
	std::vector v=range;
	data =new F[m];
	for(int i=0;i<m;i++){
		data[i] = Rand<F>(v[0],v[1]);
	}
	length = m;
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
Array<F>::Array(int size,std::initializer_list<F> arr){
			init(size, arr);
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
void Array<F>::operator=(const Array<F>& v) {
    if (this == &v) return;
    if (length != v.length) {
        delete[] data;
        data = new F[v.length];
        length = v.length;
    }
    for (int i = 0; i < length; i++) {
        data[i] = v[i];
    }
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
Array<F> Array<F>::operator-(F& value){
			Array<F> a(length);
			int i=0;
			for(F& val : *this){
				a[i] = val - value;++i;}
			return a;
		}
template <typename F>
Array<F> Array<F>::operator-(const Array<F>& v){
			Array<F> a(length);
			for(int i=0;i<length;i++){
				a[i] = data[i] - v[i];
			}
			return a;
		}
template <typename F>
void Array<F>::operator-=(const Array<F>& arr){
	for(int i=0;i<length;i++){
		data[i] -= arr[i];
	}
}
template <typename F>
Array<F> Array<F>::operator/(F& value){
			Array<F> a(length);
			int i=0;
			for(F& val : *this){
				a[i] = val / value;++i;}
			return a;
		}
template <typename F>
Array<F> Array<F>::operator/(const Array<F>& v){
			Array<F> a(length);
			for(int i=0;i<length;i++){
				a[i] = data[i] / v[i];
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
data.init(m,Array<F>(n)); 
this->dimensions = Array<int>({m,n});
}

template <typename F>
Array2d<F>::Array2d(int m,int n, F value){ 
data.init(m,Array<F>(n,value)); this->dimensions = Array<int>({m,n});}
template <typename F>
Array2d<F>::Array2d(const Array2d& arr){ 
*this = arr;
}
template <typename F>
Array2d<F>::Array2d(int m,int n,std::initializer_list<F> arr){
	this = new Array2d<F>(m,n);
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			data[i][j]=Rand(arr);
		}
	}
}
template <typename F>
void Array2d<F>::init(int m,int n,std::initializer_list<F> arr){
		this = new Array2d<F>(m,n,arr);
}
template <typename F>
void Array2d<F>::init(int m,int n,F val){
	data.init(m,Array<F>(n,val));
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
void Array2d<F>::operator=(const Array<Array<F>>& v){
		int m=v.len();
		int n=v[0].len();
		data.init(m,Array<F>(n));
		dimensions.init({m,n});
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				data[i][j] = v[i][j];
			}
		}
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
Array2d<F> Array2d<F>::operator-(F value){
			Array2d<F> a = *this;
			for(int i=0;i<data.len();i++){
				a[i] = data[i] - value;
			}
			return a;
		}
template <typename F>
Array2d<F> Array2d<F>::operator-(const Array<F>& value){
			Array2d<F> a = *this;
			for(int i=0;i<data.len();i++){
				a[i] = data[i] - value;
			}
			return a;
		}
template <typename F>
Array2d<F> Array2d<F>::operator-(const Array2d<F>& arr){
			Array2d<F> a = *this;
			for(int i=0;i<data.len();i++){
				a[i] = data[i] - arr[i];
			}
			return a;
		}
template <typename F>
Array2d<F> Array2d<F>::operator/(F value){
			Array2d<F> a = *this;
			for(int i=0;i<data.len();i++){
				a[i] = data[i] / value;
			}
			return a;
		}
template <typename F>
Array2d<F> Array2d<F>::operator/(const Array<F>& value){
			Array2d<F> a = *this;
			for(int i=0;i<data.len();i++){
				a[i] = data[i] / value;
			}
			return a;
		}
template <typename F>
Array2d<F> Array2d<F>::operator/(const Array2d<F>& arr){
			Array2d<F> a = *this;
			for(int i=0;i<data.len();i++){
				a[i] = data[i] / arr[i];
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
		if (dimensions[1] != v.dims()[0]) {std::cout<<"Error dimensions Not Same !!"; return Array2d<F>(1,1,0);}
		Array2d<F> a(dimensions[0],v.dims()[1],(F)0);
		for(int i=0;i<dimensions[0];i++){
			for(int j=0;j<v.dims()[1];j++){
				F sum =0;
				for(int k=0;k<dimensions[1];k++){
					sum += data[i][k] * v[k][i];
				}
				a[i][j] = sum;
			}
		}
		return a;
}
template <typename F>
Array2d<F> Array2d<F>::operator&(const Array2d& v) { return this->dot(v); }

template <typename F>
typename TensorProxy<F>::Column TensorProxy<F>::operator[](int i){
	return typename TensorProxy<F>::Column{source,i};
}
template <typename F>
F& TensorProxy<F>::Column::operator[](int i){
	return parent[i][col_idx];
}
template <typename F>
const typename TensorProxy<F>::Column TensorProxy<F>::operator[](int i) const{
	return typename TensorProxy<F>::Column{source,i};
}
template <typename F>
const F& TensorProxy<F>::Column::operator[](int i) const{
	return parent[i][col_idx];
}
template <typename F>
TensorProxy<F> Array2d<F>::T(){
	return TensorProxy<F>(*this);
}

template <typename F>
Array2d<F> TensorProxy<F>::dot(const Array2d<F>& v){
		if (source.dims()[0] != v.dims()[0]) {std::cout<<"Error dimensions Not Same !!"; return Array2d<F>(1,1,0);}
		Array2d<F> a(source.dims()[1],v.dims()[1],(F)0);
		for(int i=0;i<source.dims()[1];i++){
			for(int j=0;j<v.dims()[1];j++){
				F sum =0;
				for(int k=0;k<source.dims()[0];k++){
					sum += (*this)[i][k] * v[k][i];
				}
				a[i][j] = sum;
			}
		}
		return a;
}
template <typename F>
Array2d<F> TensorProxy<F>::operator&(const Array2d<F>& v) { return this->dot(v); }
template <typename F>
Array2d<F> Array2d<F>::dot(const TensorProxy<F>& v){
		if (dimensions[1] != v.source.dims()[1]) {std::cout<<"Error dimensions Not Same !!"; return Array2d<F>(1,1,0);}
		Array2d<F> a(dimensions[0],v.source.dims()[0],(F)0);
		for(int i=0;i<dimensions[0];i++){
			for(int j=0;j<v.source.dims()[0];j++){
				F sum =0;
				for(int k=0;k<dimensions[1];k++){
					sum += data[i][k] * v[k][i];
				}
				a[i][j] = sum;
			}
		}
		return a;
}
template <typename F>
Array2d<F> Array2d<F>::operator&(const TensorProxy<F>& v) { return this->dot(v); }

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