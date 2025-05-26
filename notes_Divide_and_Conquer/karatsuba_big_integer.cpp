#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

string trim(const string &s) {
  int i = 0;
  int n = s.size();
  while (i + 1 < n && s[i] == '0') {
    i++;
  }
  return s.substr(i);
}

string addStrings(const string &a, const string &b) {
  string res;
  int i = a.size() - 1, j = b.size() - 1, carry = 0;
  while (i >= 0 || j >= 0 || carry) {
    int sum = carry;
    if (i >= 0) {
      sum += a[i--] - '0';
    }
    if (j >= 0) {
      sum += b[j--] - '0';
    }
    res.push_back(char('0' + (sum % 10)));
    carry = sum / 10;
  }
  reverse(res.begin(), res.end());
  return res;
}

string subStrings(const string &a, const string &b) {
  string res;
  int i = a.size() - 1, j = b.size() - 1, borrow = 0;
  while (i >= 0) {
    int diff = (a[i] - '0') - borrow - (j >= 0 ? (b[j] - '0') : 0);
    if (diff < 0) {
      diff += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }
    res.push_back(char('0') + diff);
    --i, --j;
  }
  while (res.size() > 1 && res.back() == '0') {
    res.pop_back();
  }
  reverse(res.begin(), res.end());
  return res;
}