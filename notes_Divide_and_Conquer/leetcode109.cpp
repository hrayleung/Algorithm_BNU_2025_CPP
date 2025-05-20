#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include "TreeNode.h"
#include "ListNode.h"
using namespace std;

class Solution
{
public:
    TreeNode *sortedListToBST(ListNode *head)
    {
        if (!head)
            return nullptr;
        if (!head->next)
            return new TreeNode(head->val);

        ListNode *prev = nullptr;
        ListNode *slow = head;
        ListNode *fast = head;

        // Find middle node
        while (fast && fast->next)
        {
            fast = fast->next->next;
            prev = slow;
            slow = slow->next;
        }

        // Disconnect left part
        if (prev)
            prev->next = nullptr;

        TreeNode *root = new TreeNode(slow->val);

        if (prev)
            root->left = sortedListToBST(head);
        else
            root->left = nullptr;

        root->right = sortedListToBST(slow->next);
        return root;
    }
};

// Level-order tree printer like Leetcode
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

        if (result.size() > 10000)
        {
            cerr << "ERROR: Tree too deep or malformed." << endl;
            break;
        }
    }

    while (!result.empty() && result.back() == "null")
        result.pop_back();

    cout << "[";
    for (size_t i = 0; i < result.size(); ++i)
    {
        cout << result[i];
        if (i + 1 < result.size())
            cout << ",";
    }
    cout << "]" << endl;
}

void deleteTree(TreeNode *root)
{
    if (!root)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void deleteList(ListNode *head)
{
    while (head)
    {
        ListNode *temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    int n;
    cin >> n;
    if (n == 0)
    {
        cout << "[]" << endl;
        return 0;
    }

    int val;
    cin >> val;
    ListNode *head = new ListNode(val);
    ListNode *current = head;
    for (int i = 1; i < n; ++i)
    {
        cin >> val;
        current->next = new ListNode(val);
        current = current->next;
    }

    Solution solution;
    TreeNode *root = solution.sortedListToBST(head);
    printTree(root);

    deleteTree(root);
    deleteList(head);
    return 0;
}