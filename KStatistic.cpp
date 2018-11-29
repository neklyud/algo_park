//Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..109] размера n.
//Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k ∈[0..n-1] в отсортированном массиве.
//Напишите нерекурсивный алгоритм.
//Требования к дополнительной памяти: O(n).
//Требуемое среднее время работы: O(n).
//Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
//Описание для случая прохода от начала массива к концу:
//Выбирается опорный элемент.
//Опорный элемент меняется с последним элементом массива.
//Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
//Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
//Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
//Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j. Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
//В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
#include <iostream>
#include <cassert>

class getPivot{
    public:
        int operator()(int* arr,int left,int right){
            int mediana = (left+right)/2;
            if(arr[left]<arr[mediana]){
                if(arr[mediana]<arr[right]){
                    return mediana;
                } else {
                if(arr[left]<arr[right]){
                    return right;
                } else {
                    return left;   
                }
            }   
        } else {
        if(arr[mediana]<arr[right]){
            if(arr[left]<arr[right]){
                return left;
            } else {
                return right;
            }
        } else {
            return mediana;
        }
    }
        }
};

int Partition(int* arr,int left,int right,getPivot GetPivot){
    int pivot=getPivot()(arr,left,right);
    int i=left,j=left;
    std::swap(arr[pivot],arr[right]);
    while(j<right){
        if(arr[j]<arr[right]){
            std::swap(arr[i],arr[j]);
            i++;
        }
        j++;
    }
    std::swap(arr[i],arr[right]);
    return i;
}

int KstatSearch(int* array,int k, int n){
    getPivot getpivot;
    int Partit = Partition(array,0,n-1,getpivot);
    int left=0,right=n-1;
    int i=0;
    while(Partit!=k && left<n && right<n && left<right){
        if(Partit>k){
            right=Partit-1;
        } else {
                left=Partit+1;
        }
        Partit = Partition(array,left,right,getpivot);
    }
    return array[Partit];
}

int main(){
    int n=0,k=0;
    std::cin>>n>>k;
    assert(n>0);
    assert(k>=0);
    int *arr = new int[n];
    for(int i=0;i<n;i++){
        std::cin>>arr[i];
    }
    std::cout<<KstatSearch(arr,k,n)<<std::endl;
    return 0;
}
