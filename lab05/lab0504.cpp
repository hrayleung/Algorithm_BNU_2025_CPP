#include <algorithm>
#include <iostream>
#include <vector>

int n_global, m_global;

std::vector<int> current_combination;

void backtrack(int start_num, int count_selected) {
  if (count_selected == m_global) {
    for (int i = 0; i < current_combination.size(); ++i) {
      std::cout << current_combination[i]
                << (i == current_combination.size() - 1 ? "" : " ");
    }
    std::cout << std::endl;
    return;
  }

  if ((n_global - start_num + 1) < (m_global - count_selected)) {
    return;
  }

  for (int i = start_num; i <= n_global; ++i) {
    current_combination.push_back(i);
    backtrack(i + 1, count_selected + 1);
    current_combination.pop_back();
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::cin >> n_global >> m_global;

  backtrack(1, 0);

  return 0;
}
