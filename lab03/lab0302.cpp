#include "iostream"
#include "vector"
#include "algorithm"
#include "string"

using namespace std;

int minDistance(string word1, string word2) {
    int m = word1.length();
    int n = word2.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    for (int i = 0; i <= n; i++) {
        dp[0][i] = i;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int cost = word1[i - 1] == word2[j - 1] ? 0 : 1;

            int replace_cost = dp[i - 1][j - 1] + cost;
            int delete_cost = dp[i - 1][j] + 1;
            int insert_cost = dp[i][j - 1] + 1;

            dp[i][j] = min({replace_cost, delete_cost, insert_cost});
        }
    }

    return dp[m][n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string word1;
    string word2;
    cin >> word1 >> word2;

    cout << minDistance(word1, word2) << endl;
}