#include <bits/stdc++.h>

using namespace std;

using Matrix = vector<vector<long long>>;

long long Det(const Matrix& a) {
    if (a.size() == 2) {
        return a[0][0] * a[1][1] - a[1][0] * a[0][1];
    }
    if (a.size() == 3) {
        long long d1 = a[1][1] * a[2][2] - a[1][2] * a[2][1];
        long long d2 = a[1][0] * a[2][2] - a[1][2] * a[2][0];
        long long d3 = a[1][0] * a[2][1] - a[1][1] * a[2][0];
        return (a[0][0] * d1 - a[0][1] * d2 + a[0][2] * d3);
    }
    long long det = 0;
    int n = a.size();
    vector<int> p(n);
    for (int i = 0; i < n; i++) p[i] = i;
    do {
        int cnt = 0;
        long long ans = 1;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (p[i] > p[j]) cnt++;
            }
            ans *= a[i][p[i]];
        }
        if (cnt % 2 == 1) {
            det -= ans;
        } else {
            det += ans;
        }
    } while(next_permutation(p.begin(), p.end()));
    return det;
}

bool Conect(const Matrix& a, const Matrix& b) {
    if (a.size() == 3) {
        long long d1 = ((a[1][1] + b[1][1]) * (a[2][2] + b[2][2]) -
                        (a[1][2] + b[1][2]) * (a[2][1] + b[2][1]));
        long long d2 = ((a[1][0] + b[1][0]) * (a[2][2] + b[2][2]) -
                        (a[1][2] + b[1][2]) * (a[2][0] + b[2][0]));
        long long d3 = ((a[1][0] + b[1][0]) * (a[2][1] + b[2][1]) -
                        (a[1][1] + b[1][1]) * (a[2][0] + b[2][0]));
        return !((a[0][0] + b[0][0]) * d1 - (a[0][1] + b[0][1]) * d2 + (a[0][2] + b[0][2]) * d3);
    }
    int n = a.size();
    Matrix c(n, vector<long long>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    return Det(c) == 0;
}

Matrix MakeRandomMatrix(int n, vector<int> values, int seed = 14373) {
    static std::mt19937 gen(seed);
    Matrix a(n, vector<long long>(n));
    int sz = values.size();
    while (!Det(a)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = values[gen() % sz];
            }
        }
    }
    return a;
}

Matrix MakeRandomMatrix(int n, int maxc, int seed = 14373) {
    static std::mt19937 gen(seed);
    Matrix a(n, vector<long long>(n));
    while (!Det(a)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = (int)(gen() % (2 * maxc + 1)) - maxc;
            }
        }
    }
    return a;
}

void Print(const Matrix& a) {
    for (auto el : a) {
        for (auto e : el) cout << e << " ";
        cout << endl;
    }
}

int best = 8;
vector<Matrix> ans = {
        {{1, 1, -1},
         {1, 0, 0},
         {1, -1, 0}
        },
        {{1, 1, 1},
         {-1, 0, 0},
         {1, -1, 0}
        },
        {{-1, 1, -1},
         {-1, 0, 0},
         {1, -1, 0}
        },
        {{1, 1, 1},
         {1, 0, 0},
         {1, 1, 0}
        },
        {{-1, 1, 1},
         {1, 0, 0},
         {1, -1, 0}
        },
        {{-1, 1, 1},
         {-1, 0, 0},
         {1, 1, 0}
        },
        {{1, 1, -1},
         {-1, 0, 0},
         {1, 1, 0}
        },
        {{-1, 1, -1},
         {1, 0, 0},
         {1, 1, 0}
        }
};


void GenerationAns(vector<Matrix>& curr_ans) {
    if (curr_ans.size() > best) {
        best = curr_ans.size();
        cout << best << " : \n";
        for (auto el : curr_ans) {
            Print(el);
            cout << "\n";
        }
        cout << "-----------\n";
    }
    int cnt_try = 1000;
    int maxc = 1;
    if (curr_ans.size() >= 10) {
        cnt_try = 5000;
    }
    while (cnt_try--) {
        Matrix nw = MakeRandomMatrix(3, maxc);
        bool check = true;
        for (auto& a : curr_ans) {
            if (!Conect(a, nw)) {
                check = false;
                break;
            }
        }
        if (check) {
            curr_ans.push_back(nw);
            GenerationAns(curr_ans);
            curr_ans.pop_back();
        }
    }
}


int main() {
    GenerationAns(ans);
    return 0;
}
