#include <fstream>
#include <vector>

using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
  int n, m, d;
  fin >> n >> m >> d;
  vector<int> len(n);
  for (int i = 0; i < n; i++) {
    fin >> len[i];
  }

  vector<vector<vector<int> > >
      a(n + 1, vector<vector<int> >(m + 1, vector<int>(d + 1, 0)));

  for (int s = 1; s <= n; s++) {
    for (int l = 1; l <= m; l++) {
      for (int k = 0; k <= d; k++) {
        int v1 = (k + len[s - 1] <= d) ? (a[s - 1][l][k + len[s - 1]] + 1) : 0;
        int v2 = a[s - 1][l][k];
        int v3 = (k + len[s - 1] <= d) ? (a[s - 1][l - 1][0] + 1) : 0;

        a[s][l][k] = max(max(v1, v2), v3);
      }
    }
  }
  fout << a[n][m][0] << endl;

  fin.close();
  fout.close();
  return 0;
}
