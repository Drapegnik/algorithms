#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

class Result {
 public:
  int first, second, third;

  Result() : first(0), second(0), third(0) {}

  Result(int first, int second, int third) : first(first),
                                             second(second),
                                             third(third) {}

  bool operator<(const Result& obj) const {
    return first < obj.first;
  }
};

vector<int> tree;
int sz;

int min_el(int r) {
  int res = INT_MAX;
  int l = sz;
  r += sz - 1;

  while (l <= r) {
    if (l % 2 != 0) {
      res = min(res, tree[l]);
      l++;
    }
    if (r % 2 == 0) {
      res = min(res, tree[r]);
      r--;
    }
    r /= 2;
    l /= 2;
  }
  return res;
}

void upd(int key, int val) {
  key += sz - 1;
  tree[key] = val;
  key /= 2;
  while (key > 0) {
    if (tree[key] <= val) {
      break;
    }

    tree[key] = val;
    key /= 2;
  }
}


int main() {
  int n;
  fin >> n;
  set<Result> s;
  for (int i = 0; i < n; i++) {
    int x, y, z;
    fin >> x >> y >> z;
    s.insert(Result(x, y, z));
  }

  sz = n;
  while (sz & (sz - 1)) { sz++; }
  tree = vector<int>(2 * sz, INT_MAX);

  int ans = 0;
  for (set<Result>::iterator i = s.begin(); i != s.end(); i++) {
    upd(i->second, i->third);
    if (i->third < min_el(i->second - 1)) { ans++; }
  }

  fout << ans;
  return 0;
}