#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

static const int ARR_SIZE = 160000;
static const int MAX_NUM = 1000000;

int* generateGaps(const int size, int & newSize){
    // we are going to use the simple N/2 + 1 gaps
    int* gaps = new int[size];
    gaps[0] = size;
    int curGap = 0, ctr = 1;
    do{
        curGap = gaps[ctr-1]*5/11;
        gaps[ctr++] = (curGap) ? curGap : 1;
    }while(curGap > 1);
    newSize = ctr;
    return gaps;
}

void insertionSort(int arr[], int start, int end, int stepSize = 1){
    int delta = start+stepSize;
    for(; delta < end-start; delta+=1){
        int i = delta;
        while(arr[i] >= arr[delta] && i >= start){ i-=stepSize; }
        i += stepSize; //we overshot it by one
        int temp = arr[delta];
        for(int j = delta-stepSize; j >= i; j-=stepSize){ //loop through everything to move back 1
            arr[j+stepSize] = arr[j];
        }
        arr[i] = temp;
    }
}

void shellSort(int arr[], int start, int end, int gaps[], int gapSize){
    // perform shellsort
    for(int i = 0; i < gapSize; i++){ //loop through the gaps
        insertionSort(arr, start, end, gaps[i]);
    }
}

int main(){
    int gapSize;
    int* gaps = generateGaps(ARR_SIZE, gapSize);
    int arr[ARR_SIZE];

    //let's try a one million size array
    for(int i = 0; i < ARR_SIZE; i++){
        arr[i] = rand() % MAX_NUM;
    }
    
    /**---- TIMING SHELL SORT ----**/
    
    int starttime = clock();
    shellSort(arr, 0, ARR_SIZE, gaps, gapSize);
    int endtime = clock();//now check what amount of ticks we have now. 
    //to get the time, just subtract start from end, and divide by clocks_per_sec.
    std::cout << "it took " << endtime - starttime << "ticks, or " << ((float)endtime - starttime)/CLOCKS_PER_SEC << "seconds." << std::endl;

    std::cout << "------ The result(only first 10 to check) -------\n";
    for(int i = 0; i < 10; i++){
        std::cout << arr[i] << std::endl;
    }

    /**---- TIMING INSERTION SORT ----**/
    /*
    //let's try a one million size array
    for(int i = 0; i < ARR_SIZE; i++){
        arr[i] = rand() % MAX_NUM;
    }
        
    starttime = clock();
    insertionSort(arr, 0, ARR_SIZE);
    endtime = clock();//now check what amount of ticks we have now. 
    //to get the time, just subtract start from end, and divide by clocks_per_sec.
    for(int i = 0; i < ARR_SIZE; i++){
        std::cout << arr[i] << std::endl;
    }
    std::cout << "it took " << endtime - starttime << "ticks, or " << ((float)endtime - starttime)/CLOCKS_PER_SEC << "seconds." << std::endl;*/
 }       
