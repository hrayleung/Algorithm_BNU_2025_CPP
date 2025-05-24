#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;
vector<int> generateRandomArray(int size);
void heapSort(vector<int>& array);
void heapify(vector<int>& array, int heapSize, int index);
void insertionSort(vector<int>& array);
int main() {
    vector<int> sizes = {10000, 20000, 40000, 80000, 160000};
    const int times = 10;

    random_device rd;
    mt19937 gen(rd());
    for (int size : sizes) {
        cout << "date size: " << size << endl;
        long long totalTimeHeap = 0;
        long long totalTimeInsertion = 0;

        uniform_int_distribution<> distrib(0, size - 1);
        for (int i = 0; i < times; i++) {
            vector<int> array(size);
            for(int j = 0; j < size; ++j) {
                array[j] = distrib(gen);
            }

            vector<int> arrforheap = array;
            vector<int> arrforinsertion = array;

            auto startHeap = high_resolution_clock::now();
            heapSort(arrforheap);
            auto endHeap = high_resolution_clock::now();
            long long timeHeap = duration_cast<nanoseconds>(endHeap - startHeap).count();
            totalTimeHeap += timeHeap;

            auto startInsertion = high_resolution_clock::now();
            insertionSort(arrforinsertion);
            auto endInsertion = high_resolution_clock::now();
            long long timeInsertion = duration_cast<nanoseconds>(endInsertion - startInsertion).count();
            totalTimeInsertion += timeInsertion;
        }

        cout << "average heap: " << totalTimeHeap / times << " ns" << endl;
        cout << "average insertion: " << totalTimeInsertion / times << " ns" << endl;
        cout << endl;
    }

    return 0;
}

// Heap Sort implementation
void heapSort(vector<int>& array) {
    int n = array.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(array, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

// To heapify a subtree rooted with node index
void heapify(vector<int>& array, int heapSize, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heapSize && array[left] > array[largest]) {
        largest = left;
    }

    if (right < heapSize && array[right] > array[largest]) {
        largest = right;
    }

    if (largest != index) {
        swap(array[index], array[largest]);
        heapify(array, heapSize, largest);
    }
}

// Insertion Sort implementation
void insertionSort(vector<int>& array) {
    int n = array.size();
    for (int i = 1; i < n; i++) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}
