#include <iostream>
#include <vector>
#include <string>
#define DELETED "DELETED"
#define NIL "NIL"
#define SIZE 8

class Hasher{
public:
    Hasher() = default;
    int operator()(const std::string& str, int mod, int probe){
        return calculateHash(str, mod, probe);
    }
private:
    int calculateHash(const std::string str, int mod, int probe){
        int hash = 0;
        int a = 3;
        for(auto i = str.begin() ; i != str.end() ; ++i){
            hash = (hash*a + (*i))%mod;
        }
        return (hash + probe) % mod;
    }
    int getSimpleNumber(int M){
        for(int i = 2 ; i < M ; i++){
            if(M%i != 0)
                return i;
        }
        return -1;
    }
};

template <class T>
class CHashTable {
public:
    CHashTable(const Hasher hasher);
    ~CHashTable(); 
    bool Insert(const T& k);
    bool DeleteValue(const T& k);
    bool Search(const T& k);
    void resize();
    void print(){
        for(int i = 0 ; i < capacity ; i++){
            std::cout<<"a[]="<<value[i]<<" "<<"nil="<<nil[i]<<" "<<"del="<<deleted[i]<<std::endl;
        }
    }
private:
    std::vector<bool> nil;
    std::vector<bool> deleted;
    T* value;
    Hasher hasher;
    int capacity;
    int tableSize;
};

template <class T>
void CHashTable<T>::resize() {
    int lastCapacity = capacity;
    int lastSize = tableSize;
    std::vector<bool> lastDeleted = deleted;
    std::vector<bool> lastNil = nil;
    auto lastValue = value;
    capacity*=2;
    tableSize = 0;
    value = new T[capacity];
    for(int i = 0 ; i < capacity; i++){
        nil[i] = false;
        deleted[i] = false;
    }
    for (int i = 0; i < lastCapacity ; i++){
        Insert(lastValue[i]);
    }
    delete[] lastValue;
}

template <class T>
bool CHashTable<T>::Insert(const T& k) {
    if(tableSize >= 3./4.*capacity){
        resize();
    }
    int j = 0;
    for(int i = 0 ; i < capacity; i++){
        int j = hasher(k, capacity , i);
        //std::cout << "hash = "<< j<<std::endl;
        if(value[j] == k)
            return false;
        if(!nil[j]){
            value[j] = k;
            tableSize++;
            nil[j] = true;
            return true;
        }
        if(deleted[j]){
            value[j] = k;
            tableSize++;
            deleted[j] = false;
            return true;
        }
    }
    return false;
}

template <class T>
CHashTable<T>::CHashTable(const Hasher _hasher){
    hasher = _hasher;
    capacity = SIZE;
    tableSize = 0;
    value = new T[capacity];
    for (int i = 0 ; i < capacity ; i++ ){
        nil.push_back(false);
        deleted.push_back(false);
    }
}

template <class T>
bool CHashTable<T>::DeleteValue(const T& k){
    int index = 0;
    for(int i = 0 ; i < capacity ; i++){
        int j = hasher(k, capacity , i);
        if(!deleted[j] && value[j] == k){
            deleted[j] = true;
            --tableSize;
            return true;
            //nil[j] = false;
        }
        if(!nil[j]){
            return false;
        }
    }
    return false;
}

template <class T>
bool CHashTable<T>::Search(const T& k){
    int j = 0;
    for(int i = 0 ; i < capacity ; i++){
        int j = hasher(k, capacity , i);
        if(nil[j] && value[j] == k && !deleted[j]){
            return true;
        }
        if(!nil[j]){
            return false;
        }
    }
    return false;
}

template <class T>
CHashTable<T>::~CHashTable(){
    delete[] value;
}

int main() {
    Hasher hash;
    CHashTable<std::string> HashTable(hash);
    std::string symbol;
    std::string word;
    while(std::cin>>symbol>>word){
        if(symbol == "+"){
            bool check = HashTable.Insert(word);
            if(check == true)
                std::cout<<"OK"<<std::endl;
            else 
                std::cout<<"FAIL"<<std::endl;
        }
        if(symbol == "?"){
            bool check = HashTable.Search(word);
            if(check == true)
                std::cout<<"OK"<<std::endl;
            else 
                std::cout<<"FAIL"<<std::endl;
        }
        if(symbol == "-"){
            bool check = HashTable.DeleteValue(word);
            if(check == true)
                std::cout<<"OK"<<std::endl;
            else 
                std::cout<<"FAIL"<<std::endl;
        }
    }
    //HashTable.print();
    return 0;
}