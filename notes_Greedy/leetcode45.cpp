#include "iostream"
#include "algorithm"
#include "vector"

using namespace std;

int jump(vector<int> &nums);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> leap(n);
    for (int i = 0; i < n; i++) {
        cin >> leap[i];
    }
    cout << jump(leap) << endl;
}

int jump(vector<int> &nums) {
    int jumps = 0, end = 0, farthest = 0;
    for (int i = 0; i < nums.size() - 1; i++) {
        farthest = max(farthest, i + nums[i]);
        if (i == end) {
            jumps++;
            end = farthest;
        }
    }
    return jumps;
}