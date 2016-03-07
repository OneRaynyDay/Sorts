#include <iostream>
#include <time.h>
using namespace std;

/* GENERAL IDEA OF QUICKSORT:
 * Quicksort is an O(NlogN) AVERAGE algorithm with O(N^2) WORST case. Therefore, we call it a O(N^2) algorithm!
 * Quicksort uses space complexity of O(logN), because it does in-place sorting but requiring logN number of stack frames for recursion.
 * It replaces items on the left of the pivot with the items on the right of the pivot.
 * It recursively does the above until there is only 1 element left.
 *
 * This algorithm is NOT stable, meaning the elements won't be in their natural order from before the sort.
 * Same values after sorts will not be in their pre-planned state
 *
 * A way to optimize this algorithm is to do insertion sort at around 15-30 elements.
 */

int medianOfThree(int arr[], int start, int end){
    /**
     * We implement a median of 3 check to see which number is the middle value.
     * This way we can somewhat prevent the O(N^2) condition, which is when
     * quicksort sorts a partially sorted array. This causes the right partitioning to be
     * the entire right side of the array.
     */
    int one = arr[start], two = arr[(start+end)/2], three = arr[end];
    if(one > two){
        if(two > three)
            return (start+end)/2;
        else if(one > three)
            return end;
        else
            return start;
    }
    else{
        if(two < three)
            return (start+end)/2;
        else if(one < three)
            return end;
        else
            return start;
    }
}

void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

int sortAroundPivot(int arr[], int pivot, int start, int end){
    int pivotVal = arr[pivot];
    while(start < end){
        // We want to find the first element on the left and first element on the right that is greater/less 
        // than the pivot value.
        // Then, when start and end are the same(at pivot) are we done.
        while(arr[start] < pivotVal) start++;
        while(arr[end] > pivotVal) end--;
        if(start != end && arr[start] == arr[end]){ // If they are the same, then we'll go into an infinite loop unless we state this explicitly!
            start++;
            end--;
            continue;
        }
        swap(arr[start], arr[end]); 
    }
    return start; // doesn't matter whether we return start or end here.
}

void quickSort(int arr[], int start, int end){
    /**
     * Parameters:
     * arr[] = int array to be sorted
     * start = start index
     * end = end index (NOTE: this is the end INDEX, not the size of the array. Careful!
     *
     * Sorts the array using the standard quicksort.
     */
    if(end-start < 1)
        return;
    /**
     * Now we need to just call the sortAroundPivot for median of 3 here.
     */
    int pivot = medianOfThree(arr, start, end);
    pivot = sortAroundPivot(arr, pivot, start, end);
    quickSort(arr, start, pivot-1);
    quickSort(arr, pivot+1, end);
}

void quickSort(int arr[], int size){
    /**
     * Overloading the quickSort function if someone wants to sort the entire array.
     */
    quickSort(arr, 0, size-1);
}

int main(){
    /**
     * Testing
     */
    int NUM_TEST = 1000;
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
    quickSort(t, NUM_TEST);
    int endtime = clock();
    cout << "done." << endl;
    for(int i = 0; i < NUM_TEST; i++){
        cout << t[i] << endl;
    }
    std::cout << "it took " << endtime - starttime << "ticks, or " << ((float)endtime - starttime)/CLOCKS_PER_SEC << "seconds." << std::endl;
}
