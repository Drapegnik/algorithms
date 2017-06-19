#include <iostream>
#include <fstream>
#include <set>
#include <iomanip>
#include <vector>
#include <queue>

using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

int c = 1;

class Compare {
 public:
  bool operator()(pair<int, int> a, pair<int, int> b) {
    if ((c + a.second) / a.first == (c + b.second) / b.first) {
      return a.first > b.first;
    }

    return (c + a.second) / a.first > (c + b.second) / b.first;
  }
};

int main() {
  int n, m, x;
  double ans = 0.0;
  fin >> n;
  multiset<int, greater<int> > job;

  for (int i = 0; i < n; i++) {
    fin >> x;
    job.insert(x);
  }

  fin >> m;
  priority_queue<pair<int, int>, vector<pair<int, int> >, Compare> workers;

  for (int i = 0; i < m; i++) {
    fin >> x;
    workers.push(make_pair(x, 0));
  }

  for (set<int>::iterator it = job.begin(); it != job.end(); it++) {
    c = *it;
    priority_queue<pair<int, int>, vector<pair<int, int> >, Compare> sorted_workers;

    for (int i = 0; i < m; i++) {
      sorted_workers.push(workers.top());
      workers.pop();
    }

    pair<int, int> w = sorted_workers.top();
    sorted_workers.pop();
    w.second += *it;
    ans = max(ans, ((double) w.second / w.first));

    sorted_workers.push(w);
    workers = sorted_workers;
  }

  fout << fixed << setprecision(5) << ans;
  return 0;
}
