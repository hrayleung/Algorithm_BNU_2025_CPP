#include <iostream>
#include <vector>
using namespace std;

class HanoiTower {
public:
    int step = 0;

    // Move top disk from src to tar
    void move(vector<int>& src, vector<int>& tar) {
        int pan = src.back();
        src.pop_back();
        tar.push_back(pan);
    }

    // Recursive DFS to solve Tower of Hanoi
    void dfs(int i, vector<int>& src, vector<int>& buf, vector<int>& tar) {
        if (i == 1) {
            move(src, tar);
            step++;
            return;
        }
        dfs(i - 1, src, tar, buf);
        step++;
        dfs(i - 1, buf, src, tar);
    }

    // Solve function to start DFS
    void solve(vector<int>& A, vector<int>& B, vector<int>& C) {
        int n = A.size();
        dfs(n, A, B, C);
    }
};

int main() {
    vector<int> A, B, C;
    int n;

    cout << "Please input the number of pans:" << endl;
    cin >> n;

    // Initialize source peg A
    for (int i = n; i > 0; i--) {
        A.push_back(i);
    }

    HanoiTower hanoiTower;
    hanoiTower.solve(A, B, C);

    cout << "Total Step:" << hanoiTower.step << endl;
    return 0;
}