#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef vector<vector<int>> Matrix;

// Reads an n x n matrix
Matrix inputMatrix(int n) {
    Matrix mat(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> mat[i][j];
    return mat;
}

// Traditional O(n^3) matrix multiplication
Matrix traditionalMultiply(const Matrix& a, const Matrix& b) {
    int n = a.size();
    Matrix res(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                res[i][j] += a[i][k] * b[k][j];
    return res;
}

// Adds two matrices
Matrix addMatrix(const Matrix& a, const Matrix& b) {
    int n = a.size();
    Matrix res(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            res[i][j] = a[i][j] + b[i][j];
    return res;
}

// Subtracts matrix b from a
Matrix subtractMatrix(const Matrix& a, const Matrix& b) {
    int n = a.size();
    Matrix res(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            res[i][j] = a[i][j] - b[i][j];
    return res;
}

// Pads matrix to size x size
Matrix padMatrix(const Matrix& mat, int size) {
    int n = mat.size();
    Matrix res(size, vector<int>(size, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            res[i][j] = mat[i][j];
    return res;
}

// Extracts top-left n x n from a matrix
Matrix extractMatrix(const Matrix& mat, int n) {
    Matrix res(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            res[i][j] = mat[i][j];
    return res;
}

// Splits a matrix into quadrants
void splitMatrix(const Matrix& mat, Matrix& a11, Matrix& a12, Matrix& a21, Matrix& a22) {
    int n = mat.size() / 2;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            a11[i][j] = mat[i][j];
            a12[i][j] = mat[i][j + n];
            a21[i][j] = mat[i + n][j];
            a22[i][j] = mat[i + n][j + n];
        }
}

// Joins 4 matrices into one
Matrix joinMatrix(const Matrix& a11, const Matrix& a12, const Matrix& a21, const Matrix& a22) {
    int n = a11.size();
    Matrix res(2 * n, vector<int>(2 * n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            res[i][j] = a11[i][j];
            res[i][j + n] = a12[i][j];
            res[i + n][j] = a21[i][j];
            res[i + n][j + n] = a22[i][j];
        }
    return res;
}

// Strassen's recursive multiplication
Matrix strassenMultiply(const Matrix& a, const Matrix& b) {
    int n = a.size();
    if (n == 1)
        return {{a[0][0] * b[0][0]}};

    int newSize = n / 2;
    Matrix a11(newSize, vector<int>(newSize)), a12(newSize, vector<int>(newSize)),
            a21(newSize, vector<int>(newSize)), a22(newSize, vector<int>(newSize)),
            b11(newSize, vector<int>(newSize)), b12(newSize, vector<int>(newSize)),
            b21(newSize, vector<int>(newSize)), b22(newSize, vector<int>(newSize));

    splitMatrix(a, a11, a12, a21, a22);
    splitMatrix(b, b11, b12, b21, b22);

    // Seven Strassen multiplications
    Matrix m1 = strassenMultiply(addMatrix(a11, a22), addMatrix(b11, b22));
    Matrix m2 = strassenMultiply(addMatrix(a21, a22), b11);
    Matrix m3 = strassenMultiply(a11, subtractMatrix(b12, b22));
    Matrix m4 = strassenMultiply(a22, subtractMatrix(b21, b11));
    Matrix m5 = strassenMultiply(addMatrix(a11, a12), b22);
    Matrix m6 = strassenMultiply(subtractMatrix(a21, a11), addMatrix(b11, b12));
    Matrix m7 = strassenMultiply(subtractMatrix(a12, a22), addMatrix(b21, b22));

    // Compute result quadrants
    Matrix c11 = addMatrix(subtractMatrix(addMatrix(m1, m4), m5), m7);
    Matrix c12 = addMatrix(m3, m5);
    Matrix c21 = addMatrix(m2, m4);
    Matrix c22 = addMatrix(subtractMatrix(addMatrix(m1, m3), m2), m6);

    return joinMatrix(c11, c12, c21, c22);
}

// Determines multiplication method and handles padding
Matrix multiply(Matrix a, Matrix b) {
    int n = a.size();
    if (n <= 16)
        return traditionalMultiply(a, b);

    int size = 1;
    while (size < n) size <<= 1;

    if (n != size) {
        a = padMatrix(a, size);
        b = padMatrix(b, size);
    }

    Matrix result = strassenMultiply(a, b);

    if (n != size)
        result = extractMatrix(result, n);

    return result;
}

int main() {
    int n;
    cin >> n;
    Matrix a = inputMatrix(n);
    Matrix b = inputMatrix(n);

    Matrix result = multiply(a, b);

    // Output the result on one line with proper spacing
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            cout << result[i][j];
            if (!(i == n - 1 && j == n - 1))
                cout << " ";
        }

    return 0;
}
