#include <iostream>
#include <vector>
using namespace std;

// Read array elements from input
vector<int> readArray(int size) {
    vector<int> array(size);
    for (int i = 0; i < size; i++) {
        cin >> array[i];
    }
    return array;
}

// Recursive binary search
int binarySearchRecursive(const vector<int>& array, int target, int left, int right) {
    if (left > right) return -1;

    int mid = left + (right - left) / 2;

    if (array[mid] == target) return mid;

    if (array[mid] < target)
        return binarySearchRecursive(array, target, mid + 1, right);

    return binarySearchRecursive(array, target, left, mid - 1);
}

// Binary search wrapper
int binarySearch(const vector<int>& array, int target) {
    return binarySearchRecursive(array, target, 0, array.size() - 1);
}

int main() {
    int size;
    cin >> size;

    vector<int> array = readArray(size);

    int target;
    cin >> target;

    cout << binarySearch(array, target) << endl;

    return 0;
}
