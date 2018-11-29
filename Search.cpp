//Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1].
//Необходимо найти первую пару индексов i0 и j0,
//такую что A[i0] + B[j0] = max {A[i] + B[j],
//где 0 <= i < n, 0 <= j < n, i <= j}.
//Время работы - O(n). n ≤ 100000.

#include <iostream>
#include <cassert>

class Array {
    private:
        int N;  //количество элементов массива
        int currentSize;  //размер массива 
        int *mas;  //массив
    public:
        Array() : N(0),currentSize(0), mas(nullptr){};
        Array( int n );
        Array(const Array& other) = delete;
        Array(Array&& other){*this = std::move(other);};
        ~Array();

        Array& operator=(const Array& other) = delete;
        Array& operator=(Array&& other) ;
        
        int getCurrentSize() const;
        void print() const;
        int getElement( int i ) const;
        void putValue( int value, int place);
};

Array::Array( int n ) {
    N=n;
    currentSize=0;
    mas = new int[N];
    for(int i = 0 ; i < N ; i++ )
        mas[i]=0;
}

Array::~Array() {
    delete[] mas;
}

void Array::print() const{
    for(int i = 0 ; i < N ; i++) {
        std::cout<<mas[i]<<" ";
    }
    std::cout<<std::endl;
}

int Array::getElement(int element) const {
    assert(element<N);
    return mas[element];
}

int Array::getCurrentSize() const {
    return currentSize;
}

void Array::putValue(int value,int place) {
    mas[place]=0;
    mas[place]=value;
    currentSize++;
}

void getSum(Array& mas1, Array& mas2,int n){
    int index1=0,index2=0;
    int mas[n];
    int max=INT32_MIN;
    int ii=0;
    for(int i=0;i<n;i++){
        if(mas1.getElement(i)>max){
            max=mas1.getElement(i);
            ii=i;
        }
        mas[i]=ii;
    }
    max=INT32_MIN;
    for(int i=0;i<n;i++){
        if(mas1.getElement(mas[i])+mas2.getElement(i)>max){
            max=mas1.getElement(mas[i])+mas2.getElement(i);
            index1=mas[i];
            index2=i;
        }
    }
    std::cout<<index1<<" "<<index2<<std::endl;
}

Array& Array::operator=(Array&& arr){
    *this = std::move(arr);
    return *this;
}

int main(){
    int n=0;
    int temp=0;
    std::cin>>n;
    assert(n>0);
    assert(n<=100000);
    Array mas1(n),mas2(n);
    while(mas1.getCurrentSize()<n && std::cin>>temp){
        mas1.putValue(temp,mas1.getCurrentSize());
    }
    if(mas1.getCurrentSize()<n) 
        return 0;    
    while(mas2.getCurrentSize()<n && std::cin>>temp){
        mas2.putValue(temp,mas2.getCurrentSize());
    }
    if(mas2.getCurrentSize()<n)
        return 0;
    getSum(mas1,mas2,n);
    return 0;
}
