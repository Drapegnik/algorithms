#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
ifstream fin("input.txt");
FILE* out = fopen("output.txt", "w");

struct domino {
  int first, second, index, r_index;

  domino(int first, int second) : first(first), second(second),
                                  index(first * 10 + second),
                                  r_index(first + 10 * second) {}
};

int k, ans = 0, n = 7;
vector<bool> visit = vector<bool>(n * 10, false);
vector<domino> way;

void dfs(domino cur) {
  visit[cur.index] = true;
  visit[cur.r_index] = true;
  way.push_back(cur);

  if (way.size() == k) {
    if (way[0].first == way[k - 1].second && (
        k == 1 || (
            way[0].first != way[0].second ||
            way[1].second < way[k - 1].first))) {
      for (int i = 0; i < k; i++) {
        fprintf(out, "%d.%d ", way[i].first, way[i].second);
      }
      fprintf(out, "\n");
      ans++;
    }
    return;
  }

  for (int j = 0; j < n; j++) {
    domino next = domino(cur.second, j);
    if (visit[next.index]) { continue; }

    dfs(next);
    way.pop_back();
    visit[next.index] = false;
    visit[next.r_index] = false;
  }
}

int main() {
  fin >> k;

  if (k < 1 || k == 2 || k > 28) {
    fprintf(out, "wrong count");
    return 0;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      way.clear();
      dfs(domino(i, j));
    }
  }

  fprintf(out, "%d", ans);
  return 0;
}
