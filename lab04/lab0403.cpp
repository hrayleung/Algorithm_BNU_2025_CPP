#include "iostream"
#include "vector"
#include "queue"
#include "string"
#include "unordered_map"

using namespace std;

#define mod 100007

struct Node {
    int freq;
    char c;
    int id;
    Node *left;
    Node *right;

    Node(int f, char ch = '\0', int i = 0) : freq(f), c(ch), id(i), left(nullptr), right(nullptr) {}
};

struct CompareNode {
    bool operator()(Node *a, Node *b) {
        if (a->freq != b->freq) {
            return a->freq > b->freq;
        }

        bool a_is_leaf = (a->c != '\0');
        bool b_is_leaf = (b->c != '\0');

        if (a_is_leaf && b_is_leaf) {
            return a->c > b->c;
        } else if (a_is_leaf) {
            return false;
        } else if (b_is_leaf) {
            return true;
        } else {
            return a->id > b->id;
        }
    }
};

void buildHuffmanCodes(Node *root, string code, unordered_map<char, string> &huffmanCode) {
    if (root == nullptr) return;
    if (root->c != '\0') {
        huffmanCode[root->c] = code;
    }

    buildHuffmanCodes(root->left, code + "0", huffmanCode);
    buildHuffmanCodes(root->right, code + "1", huffmanCode);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> frequencies(26);
    for (int i = 0; i < 26; i++) {
        cin >> frequencies[i];
    }

    string text;
    cin >> text;

    priority_queue<Node *, vector<Node *>, CompareNode> pq;

    for (int i = 0; i < 26; i++) {
        if (frequencies[i] > 0) {
            pq.push(new Node(frequencies[i], 'a' + i));
        }
    }

    int id_counter = 0;
    while (pq.size() > 1) {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        Node *newNode = new Node(left->freq + right->freq, '\0', ++id_counter);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    Node *root = pq.top();

    unordered_map<char, string> huffmanCode;
    buildHuffmanCodes(root, "", huffmanCode);

    long long totalBits = 0;
    for (char ch : text) {
        totalBits = (totalBits + huffmanCode[ch].length()) % mod;
    }

    cout << totalBits << "\n";
    return 0;
}