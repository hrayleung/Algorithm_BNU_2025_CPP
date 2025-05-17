#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;

int maxArea(vector<int> &height);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> height(n);
    for (int i = 0; i < n; i++) {
        cin >> height[i];
    }
    cout << maxArea(height) << endl;
    return 0;
}

int maxArea(vector<int> &height) {
    int left = 0;
    int right = height.size() - 1;
    int maxArea = 0;
    while (left < right) {
        int w = right - left;
        int h = min(height[right], height[left]);
        maxArea = max(maxArea, w * h);
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    return maxArea;
}