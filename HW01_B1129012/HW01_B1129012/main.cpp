//
//  main.cpp
//  HW01_B1129012
//
//  Created by macbook pro on 2024/3/23.
//  reference:https://youtu.be/j-DqQcNPGbE?si=NSkyNE8goWyP_HEX
//            https://alrightchiu.github.io/SecondRound/comparison-sort-merge-sorthe-bing-pai-xu-fa.html
//            https://alrightchiu.github.io/SecondRound/comparison-sort-quick-sortkuai-su-pai-xu-fa.html

#include <iostream>
#include <time.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
//QuickSort---
int partition(int *arr, int front, int end){
    int pivot = arr[end];
    int i = front -1;
    for (int j = front; j < end; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    i++;
    swap(&arr[i], &arr[end]);
    return i;
}
void quickSort(int *arr, int front, int end){
    if (front < end) {
        int pivot = partition(arr, front, end);
        quickSort(arr, front, pivot - 1);
        quickSort(arr, pivot + 1, end);
    }
}
//MergeSort---
void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[low + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}
//HeapSort---
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
int main(){
    int max = 1000;
    double START,END;
    srand(static_cast<unsigned int>(time(nullptr)));
    int arr[max];
    int n = sizeof(arr)/sizeof(arr[0]);
    for (int i=0; i<max; i++) {
        arr[i]=rand()%max+1;
    }
    //printArray(arr, n);
    START = clock();
    std::cout << "Result of multiplication: "<<std::endl;
    //quickSort(arr, 0, n-1);
    //mergeSort(arr,0,n-1);
    heapSort(arr, n);
    END = clock();
    printArray(arr, n);
    std::cout<<std::endl<<"執行時間："<<(END-START)/CLOCKS_PER_SEC<<"s";
    return 0;
}
