#include "iostream"
#include "vector"

using namespace std;
#define mod 100007

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    vector<bool> vis(n, false);

    const long long inf = (long long) 1e18;
    vector<long long> dist(n, inf);

    dist[0] = 0;
    long long res = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        if (dist[u] == inf) {
            break;
        }
        vis[u] = true;
        if (u != -1) {
            res = (res + dist[u]) % mod;
        }

        for (int k = 0; k < n; k++) {
            if (!vis[k] && a[u][k] >= 0) {
                dist[k] = min(dist[k], (long long) a[u][k]);
            }
        }
    }
    cout << res % mod << "\n";
    return 0;


}