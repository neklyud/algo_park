//2_2. Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] 
//значения массива строго возрастают, а на интервале [m, n-1] строго убывают. 
//Найти m за O(log m).
//2 ≤ n ≤ 10000.
#include <iostream>
#include <cassert>
#include <cmath>

void print(int mas[],int n) {
    for(int i=0;i<n;i++){
        std::cout<<mas[i]<<" ";
    }
    std::cout<<std::endl;
}

int Search(int mas[],int n){
    int left=0,right=1;
    int middle=0;
    int pos=0;
    while(mas[left]<mas[right]){
        if(mas[middle]>mas[middle+1]){
            break;
        } else {
            left=middle;
        }
        left=right;
        right=pow(2,left)>n?n:pow(2,left);
        std::cout<<left<<" "<<right<<"\n";
        middle=(left+right)/2;
    }
    if(left==n){
        left--;
        right--;
        left=right-1;
    }
    while(left<(right)){
        middle=(left+right)/2;
        if(mas[middle]>=mas[middle+1]){
            right=middle;
        } else {
            left=middle+1;
        }

    }

    return left;
}

int main(){
    int i=0,temp=0, n=0;
    std::cin>>n;
    assert(n>0);
    int *mas = new int[n];
    for(i=0;i<n;i++){
        std::cin>>temp;
        mas[i]=temp;
    }
    std::cout<<Search(mas,n)<<std::endl;
    return 0;
}