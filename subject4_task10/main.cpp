#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");

int n, k, x;
vector<vector<int> > v;
vector<vector<bool> > m;
vector<bool> us;

int check(int s) {
    for (int j = 0; j < k; j++)
        if (!us[v[s][j]]) {
            us[v[s][j]] = true;
            return v[s][j];
        }
    return -1;
}

struct root {
    int next;
    int prev;


    root() : next(-1), prev(-1) { }

    root(int prev, int next) : prev(prev), next(next) { }
};

int main() {
    fin >> n >> k >> x;
    x--;
    v = vector<vector<int> >(n, vector<int>(k));
    m = vector<vector<bool> >(n, vector<bool>(n, false));
    us = vector<bool>(n, false);
    vector<root> ans = vector<root>(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < k; j++) {
            fin >> v[i][j];
            v[i][j]--;
            m[i][v[i][j]] = true;
            m[v[i][j]][i] = true;
        }

    us[x] = true;
    int start = x;
    int finish = x;
    ans[x] = root(x, x);

    while (true) {
        bool found = false;

        int next = check(finish);

        if (next != -1) {
            ans[finish].next = next;
            ans[next].prev = finish;
            finish = next;
            found = true;
        }

        if (!found) {
            next = check(start);

            if (next != -1) {
                ans[start].prev = next;
                ans[next].next = start;
                start = next;
                found = true;
            }
        }

        if (!found) {
            if (!m[start][finish]) {
                int it = ans[start].next;
                while (ans[it].next != ans[finish].prev) {
                    if (m[it][finish] && m[ans[it].next][start]) {
                        int s = ans[it].next;
                        int f = it;

                        ans[finish].next = f;

                        int jt = f;
                        while (jt != start) {
                            ans[jt] = root(ans[jt].next, ans[jt].prev);
                            jt = ans[jt].next;
                        }

                        ans[f].prev = finish;
                        ans[start] = root(ans[start].next, s);

                        finish = start;
                        start = s;

                        break;
                    }
                    it = ans[it].next;
                }
            }
            ans[start].prev = finish;
            ans[finish].next = start;


            for (int i = 0; i < n; i++) {
                if (!us[i])
                    for (int j = 0; j < k; j++)
                        if (us[v[i][j]]) {
                            us[i] = true;
                            ans[i].next = v[i][j];
                            start = i;
                            finish = ans[v[i][j]].prev;
                            ans[v[i][j]].prev = i;
                            found = true;
                            i = n;
                            break;
                        }
            }
        }

        if (m[start][finish]) {
            ans[start].prev = finish;
            ans[finish].next = start;
        }

        if (!found)
            break;
    }
    
    fout << x + 1 << " ";
    int it = x;
    while (ans[it].next != x) {
        fout << ans[it].next + 1 << " ";
        it = ans[it].next;
    }
    fout << x + 1 << " ";
    return 0;
}