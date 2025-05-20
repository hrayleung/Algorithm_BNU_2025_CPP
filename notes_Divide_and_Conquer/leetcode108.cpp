#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include "TreeNode.h"
using namespace std;

class Solution
{
public:
    TreeNode *sortedArrayToBST(const vector<int> &nums)
    {
        return buildBST(nums, 0, nums.size() - 1);
    }

private:
    TreeNode *buildBST(const vector<int> &nums, int left, int right)
    {
        if (left > right)
            return nullptr;
        int mid = left + (right - left) / 2;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = buildBST(nums, left, mid - 1);
        root->right = buildBST(nums, mid + 1, right);
        return root;
    }
};

// Print the tree level order like [0, -10, 5, null, -3, null, 9]
void printTree(TreeNode *root)
{
    if (!root)
    {
        cout << "[]" << endl;
        return;
    }

    vector<string> result;
    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *node = q.front();
        q.pop();

        if (node)
        {
            result.push_back(to_string(node->val));
            q.push(node->left);
            q.push(node->right);
        }
        else
        {
            result.push_back("null");
        }

        // Prevent infinite loop in malformed trees
        if (result.size() > 10000)
        {
            cerr << "ERROR: Tree too deep or malformed." << endl;
            break;
        }
    }

    while (!result.empty() && result.back() == "null")
    {
        result.pop_back();
    }

    cout << "[";
    for (size_t i = 0; i < result.size(); ++i)
    {
        cout << result[i];
        if (i + 1 < result.size())
            cout << ",";
    }
    cout << "]" << endl;
}

// Recursively free tree memory
void deleteTree(TreeNode *root)
{
    if (!root)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main()
{
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
        cin >> nums[i];

    Solution solution;
    TreeNode *root = solution.sortedArrayToBST(nums);
    printTree(root);
    deleteTree(root);

    return 0;
}