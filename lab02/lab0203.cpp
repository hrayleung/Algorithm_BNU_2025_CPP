#include <iostream>
#include <vector>
using namespace std;

// Swap two elements in the array
void swap(vector<int>& arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Partition the array and return the pivot index
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Use the last element as pivot
    int i = low;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            swap(arr, i, j); // Move smaller elements to front
            i++;
        }
    }
    swap(arr, i, high); // Place pivot in correct position
    return i;
}

// QuickSelect algorithm to find the k-th smallest element
int quickSelect(vector<int>& arr, int low, int high, int k) {
    while (low < high) {
        int pivotIndex = partition(arr, low, high);
        if (k == pivotIndex)
            return arr[k]; // Found the k-th smallest element
        else if (k < pivotIndex)
            high = pivotIndex - 1;
        else
            low = pivotIndex + 1;
    }
    return arr[low]; // Return the k-th smallest directly
}

int main() {
    int n, k;
    cin >> n >> k; // Read number of elements and k

    vector<int> l(n); // Initialize array
    for (int i = 0; i < n; ++i)
        cin >> l[i]; // Read elements

    cout << quickSelect(l, 0, n - 1, k - 1) << endl; // Output result
    return 0;
}