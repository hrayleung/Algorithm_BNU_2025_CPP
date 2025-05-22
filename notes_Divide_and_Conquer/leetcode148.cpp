#include "ListNode.h"
#include "iostream"
#include "vector"

using namespace std;

// Creates a linked list from a vector of integers
ListNode *creatList(const vector<int> &vals) {
  if (vals.empty())
    return nullptr;
  ListNode *head = new ListNode(vals[0]);
  ListNode *current = head;
  for (size_t i = 1; i < vals.size(); i++) {
    current->next = new ListNode(vals[i]);
    current = current->next;
  }
  return head;
}

// Prints all nodes in the linked list
void printList(ListNode *head) {
  ListNode *current = head;
  while (current) {
    cout << current->val << "->";
    current = current->next;
  }
  cout << "nullptr" << endl;
}

// Frees memory by deleting all nodes in the linked list
void deleteList(ListNode *head) {
  ListNode *current = head;
  while (current) {
    ListNode *next = current->next;
    delete current;
    current = next;
  }
}

class solution {
public:
  // Merges two sorted linked lists into one sorted list
  ListNode *merge(ListNode *list1, ListNode *list2) {
    ListNode dummy(0); // Dummy node to simplify edge cases
    ListNode *tail = &dummy;
    while (list1 && list2) {
      // Choose the smaller value from either list
      if (list1->val <= list2->val) {
        tail->next = list1;
        list1 = list1->next;
      } else {
        tail->next = list2;
        list2 = list2->next;
      }
      tail = tail->next;
    }
    // Attach remaining elements (if any)
    tail->next = list1 ? list1 : list2;
    return dummy.next;
  }

  // Splits a list after k elements and returns the head of the second part
  ListNode *split(ListNode *start, int k) {
    if (!start)
      return nullptr;
    ListNode *current = start;

    // Move current k-1 steps forward
    for (int i = 1; i < k && current && current->next; i++) {
      current = current->next;
    }

    if (!current)
      return nullptr;

    // Detach the second part and return its head
    ListNode *rest = current->next;
    current->next = nullptr;
    return rest;
  }

  // Sorts a linked list using bottom-up merge sort
  ListNode *sortList(ListNode *head) {
    if (!head || !head->next) {
      return head; // Already sorted if empty or single element
    }

    // Calculate the length of the list
    int length = 0;
    ListNode *node = head;
    while (node) {
      length++;
      node = node->next;
    }

    ListNode dummy(0, head); // Dummy node to handle edge cases

    // Merge subarrays in bottom-up fashion
    for (int sublLength = 1; sublLength < length; sublLength *= 2) {
      ListNode *prev = &dummy;     // Points to the node before current segment
      ListNode *curr = dummy.next; // Current processing position
      while (curr) {
        // Get first sublist of length sublLength
        ListNode *head1 = curr;
        // Split and get second sublist of length sublLength
        ListNode *head2_start = split(head1, sublLength);

        ListNode *head2 = head2_start;
        ListNode *next_segment_start = nullptr;

        if (head2) {
          // Find the start of the next pair of sublists
          next_segment_start = split(head2, sublLength);
        }

        curr = next_segment_start; // Move to next pair

        // Merge current pair of sublists
        ListNode *merged_head = merge(head1, head2);

        // Connect merged list to main list
        prev->next = merged_head;

        // Move prev to the end of merged segment
        while (prev->next) {
          prev = prev->next;
        }
      }
    }
    return dummy.next;
  }
};

int main() {
  solution sol;
  ListNode *head = nullptr;
  ListNode *current = nullptr;
  int n = 0;
  int val = 0;

  cout << "Please input the number of nodes in the list:";
  cin >> n;

  if (n == 0) {
    cout << "Empty list created" << endl;
  } else {
    cout << "Please input " << n << " values for the list:" << endl;

    cin >> val;
    while (cin.fail()) {
      cout << "Invalid Input" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cin >> val;
    }

    // Create the head node with the first input value
    head = new ListNode(val);
    current = head;

    // Create remaining nodes with subsequent input values
    for (int i = 1; i < n; i++) {
      cin >> val;
      while (cin.fail()) {
        cout << "Invalid Input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> val;
      }
      current->next = new ListNode(val);
      current = current->next;
    }
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  cout << "Original list:";
  printList(head);

  // Sort the list using the bottom-up merge sort implementation
  ListNode *sortedHead = sol.sortList(head);
  cout << "Sorted list:";
  printList(sortedHead);
  return 0;
}