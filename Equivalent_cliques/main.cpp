#include <bits/stdc++.h>

using namespace std;

using Matrix = vector<vector<int>>;

int p = 3;

int Mul(int a, int b) {
    return (a * b) % p;
}

int Sum(int a, int b) {
    return (a + b) % p;
}

int Dif(int a, int b) {
    return (p + a - b) % p;
}

void Print(const Matrix& a) {
    for (auto el : a) {
        for (auto e : el) cout << e << " ";
        cout << endl;
    }
}

void PrintClique(const vector<Matrix> & a) {
    for (int i = 0; i < a[0].size(); i++) {
        for (auto el : a) {
            for (int j = 0; j < el[i].size(); j++) cout << el[i][j] << " ";
            cout << "   ";
        }
        cout << endl;
    }
    cout << endl;
}

int Det(const Matrix & a) {
    return Dif(Mul(a[0][0], a[1][1]), Mul(a[0][1], a[1][0]));
}

int Det(const Matrix & a, const Matrix & b) {
    return Dif(Mul(Sum(a[0][0], b[0][0]), Sum(a[1][1], b[1][1])), 
               Mul(Sum(a[0][1], b[0][1]), Sum(a[1][0], b[1][0])));
}

vector<Matrix> Gl;
int max_ans = 5;

vector<vector<Matrix>> all_cliques;

void GetCliques(vector<Matrix> & curr, int i) {
    if (curr.size() == max_ans) {
        all_cliques.push_back(curr);
    }
    for (; i < Gl.size(); i++) {
        bool connect = true;
        for (auto el : curr) {
            if (Det(el, Gl[i])) {
                connect = false;
            }
        }
        if (connect) {
            curr.push_back(Gl[i]);
            GetCliques(curr, i + 1);
            curr.pop_back();
        }
    }
}

Matrix MatrixMul(const Matrix & a, const Matrix & b) {
    Matrix c(2, vector<int>(2));
    c[0][0] = Sum(Mul(a[0][0], b[0][0]), Mul(a[0][1], b[1][0]));
    c[0][1] = Sum(Mul(a[0][0], b[0][1]), Mul(a[0][1], b[1][1]));
    c[1][0] = Sum(Mul(a[1][0], b[0][0]), Mul(a[1][1], b[1][0]));
    c[1][1] = Sum(Mul(a[1][0], b[0][1]), Mul(a[1][1], b[1][1]));
    return c;
}

Matrix T(const Matrix & a) {
    Matrix c(2, vector<int>(2));
    c[0][0] = a[0][0];
    c[0][1] = a[1][0];
    c[1][0] = a[0][1];
    c[1][1] = a[1][1];
    return c;
}

bool EquivalentCliques(vector<Matrix> & u, vector<Matrix> & v) {
    for (int i = 0; i < Gl.size(); i++) {
        for (int j = 0; j < Gl.size(); j++) {
            vector<bool> used(v.size()), usedt(v.size());
            for (auto x : u) {
                Matrix y = MatrixMul(MatrixMul(Gl[i], x), Gl[j]);
                Matrix ty = MatrixMul(MatrixMul(Gl[i], T(x)), Gl[j]);
                for (int k = 0; k < v.size(); k++) {
                    if (v[k] == y) {
                        used[k] = true;
                        break;
                    }
                }
                for (int k = 0; k < v.size(); k++) {
                    if (v[k] == ty) {
                        usedt[k] = true;
                        break;
                    }
                }
            }
            bool same = true, samet = true;
            for (int k = 0; k < v.size(); k++) {
                if (!used[k]) same = false;
                if (!usedt[k]) samet = false;
            }
            if (same || samet) return true;
        }
    }
    return false;
}

int main() {
    Matrix a(2, vector<int>(2));
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < p; k++) {
                for (int t = 0; t < p; t++) {
                    a[0][0] = i;
                    a[0][1] = j;
                    a[1][0] = k;
                    a[1][1] = t;
                    if (Det(a)) {
                        Gl.push_back(a);
                    }
                }
            }
        }
    }
    
    cout << "Number of matrix : " <<  Gl.size() << endl;
    
    vector<Matrix> curr;
    GetCliques(curr, 0);
    cout << "Number of cliques : " << all_cliques.size() << endl;
    bool equivalent = true;
    for (int i = 1; i < all_cliques.size(); i++) {
        if (!EquivalentCliques(all_cliques[0], all_cliques[i])) {
            cout << "Not equivalent cliques:" << endl;
            PrintClique(all_cliques[0]);
            PrintClique(all_cliques[i]);
            equivalent = false;
        }
    }
    if (equivalent) {
        cout << "All cliques are equivalent" << endl;
    }
    
    return 0;
}
