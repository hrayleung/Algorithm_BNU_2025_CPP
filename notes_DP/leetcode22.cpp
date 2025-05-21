#include <iostream>
#include <vector>
using namespace std;

vector<string> generateParenthesis(int n);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<string> res = generateParenthesis(n);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i];
    }
}
vector<string> generateParenthesis(int n)
{
    vector<vector<string>> dp(n + 1);
    dp[0] = {""};
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            for (const string &left : dp[j])
            {
                for (const string &right : dp[i - j - 1])
                {
                    dp[i].push_back("(" + left + ")" + right);
                }
            }
        }
    }
    return dp[n];
}