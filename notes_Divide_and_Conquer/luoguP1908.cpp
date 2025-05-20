#include <iostream>
#include <vector>
using namespace std;

// Merge function to merge two sorted halves and count inversions
long long mergeAndCount(vector<int> &arr, vector<int> &temp, int left, int mid, int right)
{
    int i = left;    // Pointer for left half
    int j = mid + 1; // Pointer for right half
    int k = left;    // Pointer for temp merged array
    long long invCount = 0;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
            invCount += (mid - i + 1); // All remaining elements in left half > arr[j]
        }
    }

    // Copy remaining elements
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];

    // Copy merged result back to original array
    for (int idx = left; idx <= right; ++idx)
    {
        arr[idx] = temp[idx];
    }

    return invCount;
}

// Recursive Merge Sort with inversion counting
long long mergeSortAndCount(vector<int> &arr, vector<int> &temp, int left, int right)
{
    if (left >= right)
        return 0;

    int mid = left + (right - left) / 2;
    long long invCount = 0;

    invCount += mergeSortAndCount(arr, temp, left, mid);
    invCount += mergeSortAndCount(arr, temp, mid + 1, right);
    invCount += mergeAndCount(arr, temp, left, mid, right);

    return invCount;
}

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n), temp(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    long long invCount = mergeSortAndCount(arr, temp, 0, n - 1);

    cout << invCount << endl;
    return 0;
}