#include <bits/stdc++.h>

using namespace std;

using Type = long long;
using Matrix = vector<vector<Type>>;
using Clique = vector<Matrix>;

long long Gcd(long long a, long long b) {
    if (b == 0) return a;
    return Gcd(b, a % b);
}

void Print(const Matrix & a) {
    for (auto el : a) {
        for (auto e : el) {
            cout << e << " ";
        }
        cout << endl;
    }
    return;
}


bool IndependentVectors(Matrix a) {
    int n = a.size();
    int m = a[0].size();
    int curr_line = 0;
    for (int i = 0; i < m && curr_line < n; i++) {
        int ind = -1;
        for (int j = curr_line; j < n; j++) {
            if (a[j][i]) {
                ind = j;
                break;
            }
        }
        if (ind == -1) continue;

        if (ind != curr_line) {
            for (int j = 0; j < m; j++) {
                swap(a[curr_line][j], a[ind][j]);
            }
        }

        for (int j = 0; j < n; j++) {
            if (j == curr_line) continue;
            long long x = a[curr_line][i] / Gcd(a[j][i], a[curr_line][i]);
            long long y = a[j][i] / Gcd(a[j][i], a[curr_line][i]);
            for (int k = 0; k < m; k++) {
                a[j][k] = x * a[j][k] - y * a[curr_line][k];
            }
        }
        curr_line++;
    }
    return curr_line == n;
}

Type Det(const Matrix& a) {
    if (a.size() == 2) {
        return a[0][0] * a[1][1] - a[1][0] * a[0][1];
    }
    if (a.size() == 3) {
        Type d1 = a[1][1] * a[2][2] - a[1][2] * a[2][1];
        Type d2 = a[1][0] * a[2][2] - a[1][2] * a[2][0];
        Type d3 = a[1][0] * a[2][1] - a[1][1] * a[2][0];
        return (a[0][0] * d1 - a[0][1] * d2 + a[0][2] * d3);
    }
    Type det = 0;
    size_t n = a.size();
    vector<int> p(n);
    for (int i = 0; i < n; i++) p[i] = i;
    do {
        int cnt = 0;
        Type ans = 1;
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

Matrix InCoordinate(const vector<Matrix> & ans) {
    Matrix A(ans.size(), vector<Type>(20));
    for (int i = 0; i < ans.size(); i++) {
        A[i][0] = 1;
        A[i][1] = ans[i][1][1] * ans[i][2][2] - ans[i][1][2] * ans[i][2][1];
        A[i][2] = ans[i][1][2] * ans[i][2][0] - ans[i][1][0] * ans[i][2][2];
        A[i][3] = ans[i][1][0] * ans[i][2][1] - ans[i][1][1] * ans[i][2][0];
        A[i][4] = ans[i][2][1] * ans[i][0][2] - ans[i][0][1] * ans[i][2][2];
        A[i][5] = ans[i][0][0] * ans[i][2][2] - ans[i][0][2] * ans[i][2][0];
        A[i][6] = ans[i][0][1] * ans[i][2][0] - ans[i][0][0] * ans[i][2][1];
        A[i][7] = ans[i][0][1] * ans[i][1][2] - ans[i][1][1] * ans[i][0][2];
        A[i][8] = ans[i][1][0] * ans[i][0][2] - ans[i][0][0] * ans[i][1][2];
        A[i][9] = ans[i][0][0] * ans[i][1][1] - ans[i][0][1] * ans[i][1][0];
        A[i][10] = ans[i][0][0];
        A[i][11] = ans[i][0][1];
        A[i][12] = ans[i][0][2];
        A[i][13] = ans[i][1][0];
        A[i][14] = ans[i][1][1];
        A[i][15] = ans[i][1][2];
        A[i][16] = ans[i][2][0];
        A[i][17] = ans[i][2][1];
        A[i][18] = ans[i][2][2];
        A[i][19] = Det(ans[i]);
    }
    return A;
}

bool IndependentPolynomials(const vector<Matrix> & ans) {
    Matrix A = InCoordinate(ans);
    return IndependentVectors(A);
}

int main() {
    vector<Matrix> ans;
    Matrix coefs = {
            {1, 1, 1},
            {1, 2, 2},
            {1, 2, 3},
            {2, 2, 2},
            {2, 3, 1},
            {1, 1, 2}
    };
    for (int i = 0; i < coefs.size(); i++) {
        Matrix M = {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}
        };
        M[0][0] = coefs[i][0];
        M[1][1] = coefs[i][1];
        M[2][2] = coefs[i][2];
        ans.push_back(M);
    }
    for (int i = 0; i < 6; i++) {
        Matrix M = {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}
        };
        M[0][1] = coefs[i][0];
        M[1][2] = coefs[i][1];
        M[2][0] = coefs[i][2];
        ans.push_back(M);
    }
    for (int i = 0; i < 6; i++) {
        Matrix M = {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}
        };
        M[0][2] = coefs[i][0];
        M[1][0] = coefs[i][1];
        M[2][1] = coefs[i][2];
        ans.push_back(M);
    }
    Matrix X(3, vector<Type>(3));
    Matrix Y(3, vector<Type>(3));
    int cnt = 10;
    while (cnt--) {
        while (true) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    X[i][j] = rand() % 5 - 2;
                }
            }
            if (Det(X)) {
                break;
            }
        }

        ans.push_back(X);
        if (IndependentPolynomials(ans)) {
            int cnt2 = 10;
            while (cnt2--) {
                while (true) {
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            Y[i][j] = rand() % 5 - 2;
                        }
                    }
                    if (Det(Y)) {
                        break;
                    }
                }
                ans.push_back(Y);
                if (IndependentPolynomials(ans)) {
                    for (auto el : ans) {
                        Print(el);
                        cout << endl;
                    }
                    Matrix A = InCoordinate(ans);
                    Print(A);
                    return 0;
                }
                ans.pop_back();
            }
        }
        ans.pop_back();
    }
    return 0;
}
