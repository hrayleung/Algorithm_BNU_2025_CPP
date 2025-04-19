#include "iostream"
#include "algorithm"
#include "vector"

using namespace std;

int LIS(vector<int>);

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    cout << "Please input the array:";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << "LIS of the array is: " << LIS(arr) << endl;
}

int LIS(vector<int> array) {
    int n = array.size();
    vector<int> dp(n, 1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (array[j] < array[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    return *max_element(dp.begin(), dp.end());
}