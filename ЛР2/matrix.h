#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix {
public:
    static int method_cnt;
    Matrix(); // ����������� �� ���������
    Matrix(int size); // ����������� � ����������
    Matrix(const Matrix&); // ����������� �����������
    ~Matrix(); // ����������
    void input();
    void output() const;
    Matrix multiply(const Matrix&) const;
    Matrix transpose() const;
    int determinant() const;
    static int getcount();
    Matrix operator=(const Matrix&);
    Matrix operator-(const Matrix&) const;
    int operator()() const;
    int& operator()(int row, int column);
    friend Matrix operator+(const Matrix&, const Matrix&);

private:
    int size;
    int** data;
    void freeMemory();
};

#endif
