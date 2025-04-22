#include "iostream"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;

    if (n == 1) {
        cout << 1;
        return 0;
    }

    const int mod = 100007;

    int dp_prev2 = 1;
    int dp_prev1 = 1;
    int dp_curr;

    for (int i = 3; i <= n; i++) {
        dp_curr = dp_prev1 + dp_prev2;
        if(dp_curr>=mod) dp_curr -= mod;
        dp_prev2 = dp_prev1;
        dp_prev1 = dp_curr;
    }

    cout<<dp_prev1<<endl;
    return 0;
}