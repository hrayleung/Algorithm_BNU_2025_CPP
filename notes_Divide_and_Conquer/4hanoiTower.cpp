#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class FourTowerHanoi
{
public:
    int step = 0;

    // Move top disk from src to tar
    void move(vector<int> &src, vector<int> &tar)
    {
        int pan = src.back();
        src.pop_back();
        tar.push_back(pan);
    }

    // Solve Hanoi with 3 towers recursively
    void dfs(int i, vector<int> &src, vector<int> &buf, vector<int> &tar)
    {
        if (i == 1)
        {
            move(src, tar);
            step++;
            return;
        }
        dfs(i - 1, src, tar, buf);
        move(src, tar);
        step++;
        dfs(i - 1, buf, src, tar);
    }

    // Solve Hanoi with 3 towers
    void hanoi3(int n, vector<int> &A, vector<int> &B, vector<int> &C)
    {
        if (n <= 0)
            return;
        dfs(n, A, B, C);
    }

    // Solve Hanoi with 4 towers
    void hanoi4(int n, vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D)
    {
        if (n == 0)
            return;
        if (n == 1)
        {
            move(A, D);
            step++;
            return;
        }

        // Optimal number of disks to move to buffer
        int k = static_cast<int>(sqrt(2 * n));
        if (k >= n)
            k = n - 1;

        // Move k disks to first buffer
        hanoi4(k, A, C, D, B);
        // Move remaining disks to target using 3 pegs
        hanoi3(n - k, A, C, D);
        // Move k disks from buffer to target
        hanoi4(k, B, A, C, D);
    }
};

int main()
{
    vector<int> A, B, C, D;
    int n;

    cout << "Please input the number of disks:" << endl;
    cin >> n;

    // Fill source tower with n disks
    for (int i = n; i > 0; i--)
    {
        A.push_back(i);
    }

    FourTowerHanoi hanoi;
    hanoi.hanoi4(n, A, B, C, D);

    cout << "Total Step:" << hanoi.step << endl;
    return 0;
}