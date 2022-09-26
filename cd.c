
____________________________________________________________________________
BINARY SEARCH 

#include <stdio.h>
int binary(int a[], int n, int data){
    int l=0,r=n-1;
    while (l<r){
        int mid = (l+r)/2;
        if (data == a[mid]){
            return mid;
        }
        else if (data < a[mid]){
            r = mid - 1;
        }
        else{
            l = mid + 1;

        }
        
        
    }
}
int main() {
    int b[10] = {1,2,3,4,5};
    int data = 4;
    int n = 10;
    int x = binary(b,n,data);
    printf("%d",x);
}

____________________________________________________________________________



____________________________________________________________________________
INSERTION SORT

#include <stdio.h>
void insertion(int a[],int n){
    for(int i=0;i<n;i++){
        int temp = a[i];
        int j = i-1;
        while((j>=0)&&(a[j]>temp)){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = temp;
    }
        
    }
int main() {
    int b[5] = {4,5,3,1,2};
    int n = 5;
    insertion(b,n);
    for(int i=0;i<n;i++){
        printf("%d ",b[i]);
    }
}

____________________________________________________________________________

SELECTION SORT

#include <stdio.h>
void selection(int a[],int n){
    for(int i=0;i<n-1;i++){
        int min = i;
        for (int j =i+1;j<n;j++){
            if(a[j]<a[min]){
                min = j;
            }
        }
        
        if(min != 0){
            int x = a[i];
            a[i] = a[min];
            a[min] = x;
        }
        
    }
int main() {
    int b[5] = {4,5,3,1,2};
    int n = 5;
    insertion(b,n);
    for(int i=0;i<n;i++){
        printf("%d ",b[i]);
    }
}

____________________________________________________________________________

BUBBLE SORT 

#include <stdio.h>
void bubblesort(int a[],int n){
    for(int i=0;i<n-1;i++){
        int flag = 0;
        for (int j =0;j<n-1-i;j++){
            if(a[j]>a[j+1]){
                int x = a[j];
                a[j] = a[j+1];
                a[j+1] = x;
                flag = 1;
            }
        }
        
        if(flag == 0){
            break;

        }
        
    }
}
int main() {
    int b[5] = {4,5,3,1,2};
    int n = 5;
    selection(b,n);
    for(int i=0;i<n;i++){
        printf("%d ",b[i]);
        
        
    }
}

______________________________________________________________________________

QUICK SORT 



#include <stdio.h>
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}


int partition(int array[], int low, int high) {

  int pivot = array[high];
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {

      i++;
      swap(&array[i], &array[j]);
    }
  }

  swap(&array[i + 1], &array[high]);
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    quickSort(array, low, pi - 1);
    quickSort(array, pi + 1, high);
  }
}

void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", array[i]);
  }
  printf("\n");
}

int main() {
  int data[] = {8, 7, 2, 1, 0, 9, 6};
  int n = sizeof(data) / sizeof(data[0]);
  
  printf("Unsorted Array\n");
  printArray(data, n);
  quickSort(data, 0, n - 1);
  
  printf("Sorted array in ascending order: \n");
  printArray(data, n);
}



__________________________________________________________________________________________________________________________-

MERGE SORT 



#include <stdio.h>

void merge(int arr[], int p, int q, int r) {

  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];

  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
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
    arr[k] = M[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int l, int r) {
  if (l < r) {

    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
}

void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

int main() {
  int arr[] = {6, 5, 12, 10, 9, 1};
  int size = sizeof(arr) / sizeof(arr[0]);

  mergeSort(arr, 0, size - 1);

  printf("Sorted array: \n");
  printArray(arr, size);
}

__________________________________________________________________________________________________________________________

RADIX SORT 

#include <stdio.h>

int getMax(int array[], int n) {
  int max = array[0];
  for (int i = 1; i < n; i++)
    if (array[i] > max)
      max = array[i];
  return max;
}

void countingSort(int array[], int size, int place) {
  int output[size + 1];
  int max = (array[0] / place) % 10;

  for (int i = 1; i < size; i++) {
    if (((array[i] / place) % 10) > max)
      max = array[i];
  }
  int count[max + 1];

  for (int i = 0; i < max; ++i)
    count[i] = 0;


  for (int i = 0; i < size; i++)
    count[(array[i] / place) % 10]++;

  for (int i = 1; i < 10; i++)
    count[i] += count[i - 1];

  for (int i = size - 1; i >= 0; i--) {
    output[count[(array[i] / place) % 10] - 1] = array[i];
    count[(array[i] / place) % 10]--;
  }

  for (int i = 0; i < size; i++)
    array[i] = output[i];
}

void radixsort(int array[], int size) {

  int max = getMax(array, size);

  for (int place = 1; max / place > 0; place *= 10)
    countingSort(array, size, place);
}


void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", array[i]);
  }
  printf("\n");
}

int main() {
  int array[] = {121, 432, 564, 23, 1, 45, 788};
  int n = sizeof(array) / sizeof(array[0]);
  radixsort(array, n);
  printArray(array, n);
}


__________________________________________________________________________________________________________________________


COUNTING SORT 


#include <stdio.h>

void countingSort(int array[], int size) {
  int output[10];

  int max = array[0];
  for (int i = 1; i < size; i++) {
    if (array[i] > max)
      max = array[i];
  }

  int count[10];

  for (int i = 0; i <= max; ++i) {
    count[i] = 0;
  }

  for (int i = 0; i < size; i++) {
    count[array[i]]++;
  }

  for (int i = 1; i <= max; i++) {
    count[i] += count[i - 1];
  }

  for (int i = size - 1; i >= 0; i--) {
    output[count[array[i]] - 1] = array[i];
    count[array[i]]--;
  }

  for (int i = 0; i < size; i++) {
    array[i] = output[i];
  }
}

void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", array[i]);
  }
  printf("\n");
}


int main() {
  int array[] = {4, 2, 2, 8, 3, 3, 1};
  int n = sizeof(array) / sizeof(array[0]);
  countingSort(array, n);
  printArray(array, n);
}

_____________________________________________________________________________________________________________________________________________-


STACK 
// Implementing Static Stack using an Array in C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// N will be the capacity of the Static Stack
#define N 1000

// Initializing the top of the stack to be -1
int top = -1;

// Initializing the stack using an array
int stack[N];

// Function prototypes
void push();       // Push element to the top of the stack
int pop();         // Remove and return the top most element of the stack
int peek();        // Return the top most element of the stack
bool isEmpty();    // Check if the stack is in Underflow state or not
bool isFull();     // Check if the stack is in Overflow state or not

int main(){
    printf("STATIC ARRAY (Total Capacity: %d)\n", N);
    int choice;

    while(1){
        printf("\nChoose any of the following options:\n");
        printf(" 0: Exit            1: Push            2: Pop            3: Peek\n");
        printf(" 4: Check if the stack is empty     5: Check if the stack is full\n\n");
        scanf("%d", &choice);

        switch(choice){
            case 0: exit(0);
            case 1: push(); break;
            case 2: pop(); break;
            case 3: peek(); break;
            case 4: isEmpty(); break;
            case 5: isFull(); break;
            default: printf("Please choose a correct option!");
        }
    }
    return 0;
}

void push(){
    // Checking overflow state
    if(top == N-1)
        printf("Overflow State: can't add more elements into the stack\n");
    else{
        int x;
        printf("Enter element to be pushed into the stack: ");
        scanf("%d", &x);
        top+=1;
        stack[top] = x;
    }
}

int pop(){
    // Checking underflow state
    if(top == -1)
        printf("Underflow State: Stack already empty, can't remove any element\n");
    else{
        int x = stack[top];
        printf("Popping %d out of the stack\n", x);
        top-=1;
        return x;
    }
    return -1;
}

int peek(){
    int x = stack[top];
    printf("%d is the top most element of the stack\n", x);
    return x;
}

bool isEmpty(){
    if(top == -1){
        printf("Stack is empty: Underflow State\n");
;        return true;
    }
    printf("Stack is not empty\n");
    return false;
}

bool isFull(){
    if(top == N-1){
        printf("Stack is full: Overflow State\n");
        return true;
    }
    printf("Stack is not full\n");
    return false;
}

