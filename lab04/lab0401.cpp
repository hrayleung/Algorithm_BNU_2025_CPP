#include "iostream"
#include "vector"
#include "queue"

using namespace std;

const int maxn = 10005;
const int inf = 2147483647;

struct Edge {
    int to, w;

    Edge(int t, int w) : to(t), w(w) {}
};

vector<Edge> g[maxn];
int dist[maxn];
bool vis[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, s;
    cin >> n >> m >> s;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back(Edge(v, w));
    }

    for (int i = 1; i <= n; i++) {
        dist[i] = inf;
    }
    dist[s] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        auto now = pq.top();
        pq.pop();
        int d = now.first, u = now.second;
        if (vis[u]) continue;
        vis[u] = true;
        for (auto &e: g[u]) {
            int v = e.to, w = e.w;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }


    }
    for (int i = 1; i <= n; i++) {
        cout << dist[i] << (i == n ? '\n' : ' ');
    }
    return 0;

}