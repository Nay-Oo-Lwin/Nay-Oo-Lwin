#include<iostream>
using namespace std;
int binarySearch(int*,int,int,int);
void bubbleSort(int*,int);
int main(){
    int arrsize{};
    cout<<"Please enter the size of the array\n";
    cin>>arrsize;
    int array[arrsize];
    cout<<"Please enter the array's elements and press enter.\n";
    int temp{};
    for(int i=0;i<arrsize;++i){
        cin>>temp;
        array[i]=temp;
    }
    bubbleSort(array,arrsize);
    cout<<"The sorted version of the array you enter is: \n";
    for(int i=0;i<arrsize;++i){
        cout<<array[i]<<' ';
    }
    cout<<"Please enter the number you want to search for: ";
    int key{};
    cin>>key;
    int index{};
    index=binarySearch(array,0,arrsize-1,key);
    if(index==-1){
        cout<<"The number you typed in do not exist.\n";
    }
    else{
    cout<<"The number you were looking for exists at index "<<index<<'\n';
    }
    return 0;
}
void bubbleSort(int* array,int size){
    int temp{};
    for(int j=0;j<size;++j){
    for(int i=0;i<size-1;++i){
        if(array[i]>array[i+1]){
            temp=array[i];
            array[i]=array[i+1];
            array[i+1]=temp;
        }
    }
    }
    return;
}
int binarySearch(int* array,int low,int high,int key)
{
    int mid{};
    mid=(low+high)/2;
    //base case
    if(low>high){
        return -1;
    }
    if(key==array[mid]){
        return mid;
    }
    else if(key<array[mid]){
       return binarySearch(array,low,mid-1,key);
    }
    else if(key>array[mid]){
        return binarySearch(array,mid+1,high,key);
    }
    return -1;
    }