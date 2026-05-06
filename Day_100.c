/*
Problem: For each element, count how many smaller elements appear on right side.
Use merge sort technique or Fenwick Tree (BIT).
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Pair;

// Merge function
void merge(Pair arr[], int left, int mid, int right, int count[]) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Pair L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    int rightCount = 0;

    while (i < n1 && j < n2) {
        if (L[i].value <= R[j].value) {
            count[L[i].index] += rightCount;
            arr[k++] = L[i++];
        } else {
            rightCount++;  // smaller element on right
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        count[L[i].index] += rightCount;
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}

// Merge sort
void mergeSort(Pair arr[], int left, int right, int count[]) {
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    mergeSort(arr, left, mid, count);
    mergeSort(arr, mid + 1, right, count);
    merge(arr, left, mid, right, count);
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    Pair pairs[n];
    int count[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        pairs[i].value = arr[i];
        pairs[i].index = i;
        count[i] = 0;
    }

    mergeSort(pairs, 0, n - 1, count);

    // Output
    for (int i = 0; i < n; i++) {
        printf("%d ", count[i]);
    }

    return 0;
}