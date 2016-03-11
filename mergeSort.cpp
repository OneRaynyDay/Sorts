#include <iostream>
using namespace std;

void merge(int arr[], int lstart, int lend, int rstart, int rend){
    /* Implementation of the merging process of mergeSort. This takes O(N) where 
     * N = lend-lstart + rend-rstart
     * If lend = rstart , then we have 
     * N = rstart-1-lstart + rend-rstart = rend-lstart
     */
    int lctr = lstart, rctr = rstart, actr = 0;
    int a[lend-lstart + rend-rstart];
    while(lctr < lend || rctr < rend){
        if(lctr == lend)
            a[actr++] = arr[rctr++];
        else if(rctr == rend)
            a[actr++] = arr[lctr++];
        else if(arr[lctr] > arr[rctr]){
            a[actr++] = arr[rctr++];
        }
        else{
            a[actr++] = arr[lctr++];
        }
    }
    /* We copy over the contents of the temp array into the real one */
    int i;
    for(i = 0; i < lend - lstart; i++)
        arr[lstart+i] = a[i];
    for(int j = 0; j < rend - rstart; j++)
        arr[rstart+j] = a[i++];
}

void mergeSort(int arr[], int start, int end){
    if(end-start < 2)
       return;
    int mid = (end+start)/2;
    mergeSort(arr, start, mid); 
    mergeSort(arr, mid, end);
    merge(arr, start, mid, mid, end); 
}

int main(){
    /**
     * Testing
     */
    int NUM_TEST = 160000;
    int NUM_RANGE = 100000;

    cout << "Timing now:" << endl;
    int t[NUM_TEST];
    for(int i = 0; i < NUM_TEST; i++){
        t[i] = rand()%NUM_RANGE;
    }
    for(int i = 0; i < NUM_TEST; i++){
        cout << t[i] << endl;
    }
    int starttime = clock();
    mergeSort(t, 0, NUM_TEST);
    int endtime = clock();
    cout << "done." << endl;
    for(int i = 0; i < NUM_TEST; i++){
        cout << t[i] << endl;
    }
    std::cout << "it took " << endtime - starttime << "ticks, or " << ((float)endtime - starttime)/CLOCKS_PER_SEC << "seconds." << std::endl;
}
