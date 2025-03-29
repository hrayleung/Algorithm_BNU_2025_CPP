#include <iostream>
#include <limits>
using namespace std;

const int MAXN = 10;  // Maximum number of cities
int n;  // Number of cities
int dist[MAXN][MAXN];  // Distance matrix between cities
int cities[MAXN];  // Stores the current path of cities
bool used[MAXN];  // Tracks which cities have been visited
int min_dist = numeric_limits<int>::max();  // Stores the minimum distance found so far

/**
 * DFS function to explore all possible paths through cities
 * @param depth Current position in the path
 * @param last_city The most recently visited city
 * @param current_dist Total distance traveled so far
 */
void dfs(int depth, int last_city, int current_dist) {
    // Pruning: if current distance exceeds minimum found, stop exploring this path
    if (current_dist >= min_dist) {
        return;
    }

    // Base case: all cities have been visited
    if (depth == n) {
        if (current_dist < min_dist) {
            min_dist = current_dist;  // Update minimum distance
        }
        return;
    }

    // Try visiting each unvisited city
    for (int next_city = 0; next_city < n; ++next_city) {
        // Check if city is unvisited and reachable from the last city
        if (!used[next_city] && dist[last_city][next_city] != -1) {
            used[next_city] = true;  // Mark city as visited
            cities[depth] = next_city;  // Add to current path

            // Recursively explore from this city
            dfs(depth + 1, next_city, current_dist + dist[last_city][next_city]);

            used[next_city] = false;  // Backtrack: mark as unvisited for other paths
        }
    }
}

int main() {
    cin >> n;  // Read number of cities

    // Read the distance matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> dist[i][j];
        }
    }

    // Start DFS from city 0
    used[0] = true;
    cities[0] = 0;
    dfs(1, 0, 0);

    // Output result
    if (min_dist == numeric_limits<int>::max()) {
        cout << -1 << endl;  // No valid path exists
    } else {
        cout << min_dist << endl;  // Print the minimum distance
    }

    return 0;
}