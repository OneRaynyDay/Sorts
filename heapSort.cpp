#include <math.h>
#include <iostream>
#include <time.h>
using namespace std;

class Heap{ //max heap
public:
    Heap(int cap = 1000){
        heap = new int[cap];
        //we should start the heap at 1
        for(int i = 0; i < capacity; heap[i++] = INT_MIN);
        capacity = cap;
        size = 0;
    }
    ~Heap(){
        delete [] heap;
    }
    void swap(int& a, int& b){
        int temp = a;
        a = b;
        b = temp;
    }
    bool add(int num){
        if(size == capacity) 
            return false;
        heap[size++] = num;
        pushUp(size-1);
        return true;
    }
    void percolateDown(int index){
        while(index*2+1 < size){
            int curSwap = (heap[index*2+1] > heap[index*2+2]) ? index * 2 + 1 : index * 2 + 2;
            if(heap[index] < heap[curSwap]){
                //currently we want to swap with curSwap 
                swap(heap[curSwap], heap[index]);
                index = curSwap;
            }
            else 
                break;
        }
    }
    void pushUp(int index){
        while(index > 0){
            if(heap[index] > heap[index/2]){
                swap(heap[index],heap[index/2]);
            }
            else
                break;
            index /= 2;
        }
    }
    void traverse(){
       for(int i = 0; i < size; i++){
            cout << heap[i] << " ";
       } 
       cout << endl;
    } 

    int remove(){ 
        if(size == 0)
            return INT_MIN;
        int temp = heap[0];
        heap[0] = heap[size-1];
        percolateDown(0);
        size--;
        return temp; 
    }
        
private:
    int* heap;
    int size;
    int capacity;
};

/* Learned from CS 32's class. Donald Knuth's implementation of
 * Heap Sort. It's a little faster but still O(NlogN).
 */
void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}
void percolateOptimized(int arr[], int curIndex, int size){
    //while it still has children

    while(curIndex*2 + 1 < size){
        //if it has a right child as well
        int maxIndex;
        if(curIndex*2 + 2 < size){
            maxIndex = (arr[curIndex*2 + 2] < arr[curIndex*2 + 1]) 
                ? curIndex*2 + 1 : curIndex*2 + 2;
        }
        else{
            maxIndex = curIndex*2 + 1;
        }
        if(arr[maxIndex] > arr[curIndex]){
            swap(arr[curIndex], arr[maxIndex]);
        }
        else
            break;
        curIndex = maxIndex; 
    }
}
void heapSortOptimized(int arr[], int size){
    // We start at N/2 - 1 because the base children are already assumed to be
    // "Sorted". At N/2 - 1 is the index of the elements that are 1 level above the
    // leaves.
    for(int i = size/2-1; i >= 0; i--){
        percolateOptimized(arr, i, size);
    }
}

int main(){
    int NUM_TEST = 10;
    int NUM_RANGE = 100000;
    int NUM_CHECK = 10;
    /*Heap heap(NUM_TEST);
    heap.add(3);
    heap.add(-1);*/
    
    int result[NUM_TEST];

    for(int i = 0; i < NUM_TEST; i++){
        int randNum = rand()%NUM_RANGE;
        //heap.add(randNum);
        result[i] = randNum;
    }
    for(int i = 0; i < NUM_CHECK; i++){
        cout << result[i] << endl;
    }   
    //Timing speed
    int starttime = clock();
    heapSortOptimized(result, NUM_TEST);
    int endtime = clock();
    cout << " ------- " << endl;
    for(int i = 0; i < NUM_CHECK; i++){
        cout << result[i] << endl;
    }

    std::cout << "it took " << endtime - starttime << "ticks, or " << ((float)endtime - starttime)/CLOCKS_PER_SEC << "seconds." << std::endl;

}

/**
 * LOG: 
 * Expected divergence rate: O(n*log(n))
 * Graph used by plotly, ran 6 times for each specific N
 * Behavior as expected. Check out HeapSort.png for more information.
**/




