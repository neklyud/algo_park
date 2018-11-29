//Для сложения чисел используется старый компьютер.
// Время, затрачиваемое на нахождение суммы двух чисел равно их сумме.
// Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время,
// в зависимости от порядка вычислений.
// ((1+2)+3) -> 1+2 + 3+3 = 9 ((1+3)+2) -> 1+3 + 4+2 = 10 ((2+3)+1) -> 2+3 + 5+1 = 11 Требуется написать
// программу, которая определяет минимальное время, достаточное для вычисления суммы заданного набора чисел.


#include <iostream>
#include <cassert>
#define BUF_SIZE 4

class Array
{
private:
    int* heap;
    //int* newHeap=nullptr;
    size_t size;
    size_t capacity;
    void clean(){
        delete[] heap;
        size=capacity=0;
    }
public:
    Array() : heap{nullptr}, size{0}, capacity{0}{capacity=BUF_SIZE; heap = new int[capacity];};
    Array(const Array& other)=delete;
    Array(const Array&& other) {*this = std::move(other);};
    ~Array() { 
        delete[] heap;
        };
    Array& operator=(const Array& other) = delete;
    Array& operator=(const Array&& other){
        clean();
        size=other.size;
        capacity=other.capacity;
        heap=other.heap;
        delete []other.heap;
        return *this;
    };
    void SiftDown(int index);
    void SiftUp( int index );
    void Add(int element);
    int GetElement(int index);
    int GetSize() const {return size;};
    void Print() const;
    //void Initialization() {capacity=BUF_SIZE; heap = new int[capacity];};
    void reallocing(){ 
        int* newHeap = nullptr;
        newHeap = new int[capacity*2];
        for(int i=0;i<capacity;i++){
            newHeap[i]=heap[i];
        }
        delete[] heap;
        heap = NULL;
        heap=newHeap;
        capacity*=2;
    }
};

void Array::SiftDown(int index){
    int left=2*index+1;
    int right=2*index+2;
    
    int largest=index;
    if(left<GetSize() && heap[left]<heap[index])
        largest=left;
    if(right<GetSize() && heap[right]<heap[largest])
        largest=right;
    
    if(largest!=index){
        std::swap(heap[index],heap[largest]);
        SiftDown(largest);
    }
}

void Array::SiftUp(int index){
    while(index>0) {
        int parent = (index-1)/2;
        if(heap[index] <= heap[parent]){
            std::swap(heap[index],heap[parent]);
        }
        index = parent;
    }
}

void Array::Add(int element){
    if(capacity-1==size){
        reallocing();
    }
    heap[size]=element;
    SiftUp(size);
    size++;
}

void Array::Print() const{
    for(int i=0;i<size;i++){
        std::cout<<heap[i]<<" ";
    }
    std::cout<<std::endl;
}

int Array::GetElement(int index){
    int tmp = heap[0];
    size--;
    std::swap(heap[0],heap[size]);
    SiftDown(0);
    return tmp;
}

int Timer(Array& arr){
    int time=0;
    while(arr.GetSize()>1){
        int valueElement = arr.GetElement(1);
        valueElement += arr.GetElement(1);
        arr.Add(valueElement);
        time+=valueElement;
    }
    return time;
}

void input(Array& arr,int n){
    for(int i=0;i<n;i++){
        int tmp=0;
        std::cin>>tmp;
        arr.Add(tmp);
    }
}

int main(){
    Array arr;
    int n=0;
    std::cin>>n;
    assert(n>0);
    input(arr,n);
    std::cout<<Timer(arr)<<std::endl;
    return 0;
}