//В первой строке количество команд n. n ≤ 1000000.
//
//Каждая команда задаётся как 2 целых числа: a b.
//
//a = 1 - push front
//a = 2 - pop front
//a = 3 - push back
//a = 4 - pop back
//Если дана команда pop *, то число b - ожидаемое значение. Если команда pop * вызвана для пустой структуры данных, то ожидается “-1”.
//
//
#include <iostream>
#include <cassert>
#include <algorithm>
#include <cstring>

template <typename T>
class Dequeue {
    private:
        T *buffer;
        int head;
        int tail;
        size_t size;
        size_t capacity;
        void clean(){
            delete[] buffer;
            size=capacity=0;
        }
    public:
        Dequeue() : head(0),tail(0),size(0),capacity(4){buffer=new T[capacity+1];};
        Dequeue(const Dequeue& other)=delete;
        Dequeue(Dequeue&& other) { *this=std::move(other);}
        ~Dequeue();

        Dequeue& operator=(const Dequeue& other)=delete;
        Dequeue& operator=(Dequeue&& other){
            clean();
            std::swap(head,other.head);
            std::swap(tail,other.tail);
            return *this;
        }

        Dequeue MakeCopy() const;
        T* getBuf() const { return buffer;};
        bool IsEmpty() const {return size;};
        void print() const{
        int i=0,j=0;
            for(int i=0;i<capacity;i++){
                std::cout<<i<<"="<<buffer[i]<<std::endl;

            }
        };
        int sizeDeq() {
            return head-tail;
        };
        int capacityDeq() {
            return capacity;
        }
        void reallocing(){
            T *newDequeue = new T[capacity*2];
                    
        }
        void PushFront(T value);
        void PushBack(T value);
        T PopBack();
        T PopFront();
};


template <typename T>
void Dequeue<T>::PushBack(T element){
    T *newDequeue=nullptr;
    if(head==(tail+1)%capacity){
        newDequeue = new T[capacity*2];
        for(int i=0;i<capacity-1;i++){
            newDequeue[i]=buffer[head];
            head=(head+1)%capacity;
        }
        delete[] buffer;
        buffer=NULL;
        buffer=newDequeue;
        head=0;
        tail=capacity-1;
        capacity*=2;
    }
    buffer[tail]=element;
    tail=(tail+1)%capacity;
    size++;

}


template <typename T>
void Dequeue<T>::PushFront(T element){
    T *newDequeue=nullptr;
    if(head==(tail+1)%capacity){
        newDequeue = new T[capacity*2];
        for(int i=0;i<capacity-1;i++){
            newDequeue[i]=buffer[head];
            head=(head+1)%capacity;
        }
        delete[] buffer;
        buffer=NULL;
        buffer=newDequeue;
        head=0;
        tail=capacity-1;
        capacity*=2;
    }
    head=(head-1+capacity)%capacity;
    buffer[head]=element;
    size++; 
}


template <typename T>
T Dequeue<T>::PopBack(){
    assert(IsEmpty()!=0);
    T *newDequeue=nullptr;
    if(sizeDeq()<capacity/4){
        newDequeue = new T[capacity/2];
        int newSizeDeq = sizeDeq();
        for(int i=0;i<newSizeDeq-1;i++){
            newDequeue[i]=buffer[i];
            head=(head+1)%capacity;
        }
        delete[] buffer;
        buffer=NULL;
        buffer=newDequeue;
        head=0;
        tail=newSizeDeq-1;
        capacity=capacity/2;
    }
    tail=(tail-1+capacity)%capacity;
    T result = buffer[tail];
    size--;
    buffer[tail]=0;
    return result;
}

template <typename T>
T Dequeue<T>::PopFront(){
    assert(IsEmpty()!=0);
    T *newDequeue=nullptr;
    if(sizeDeq()<capacity/4){
        newDequeue = new T[capacity/2];
        int newSizeDeq = sizeDeq();
        for(int i=0;i<newSizeDeq-1;i++){
            newDequeue[i]=buffer[i];
            head=(head+1)%capacity;
        }
        delete[] buffer;
        buffer=NULL;
        buffer=newDequeue;
        head=0;
        tail=newSizeDeq-1;
        capacity=capacity/2;
    }
    T result = buffer[head];
    buffer[head]=0;
    head=(head+1)%capacity;
    size--;
    return result;
}

template <typename T>
Dequeue<T>::~Dequeue(){
    delete[] buffer;
    buffer=nullptr;
}

int doCommand(Dequeue<int>& deq,int command, int num){
   // deq.print();
    switch(command){
        case 1:{
            deq.PushFront(num);
            return 1;
        }
        case 2:{
            int numberFromDeq = deq.IsEmpty() ? deq.PopFront() : -1;
            return (num==numberFromDeq)? 1 : 0;
        }
        case 3:{
            deq.PushBack(num);
            return 1;
        }
        case 4:{
            int numberFromDeq = deq.IsEmpty() ? deq.PopBack() : -1;
            return (num==numberFromDeq)? 1 : 0;
        }

    }
}

int main(){
    Dequeue<int> deq;
    int n=0;
    int command=0, num=0;
    std::cin>>n;
    assert(n>0);
    for(int i=0;i<n;i++){
        std::cin>>command>>num;
        assert(command>0 && command<5);
        if(!doCommand(deq,command,num)){
            std::cout<<"NO"<<std::endl;
            return 0;
        }
    }
    std::cout<<"YES"<<std::endl;
    deq.~Dequeue();
    return 0;
}