#include "matrix.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace std;

// ����������� �� ���������
Matrix::Matrix() : size(0), data(nullptr) {}

// ����������� � ����������
Matrix::Matrix(int size) : size(size) {
    data = new int* [size];
    for (int i = 0; i < size; i++) {
        data[i] = new int[size];
    }
}

// ����������� �����������
Matrix::Matrix(const Matrix& other) : size(other.size) {
    data = new int* [size];
    for (int i = 0; i < size; i++) {
        data[i] = new int[size];
        for (int j = 0; j < size; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

// ����������
Matrix::~Matrix() {
    freeMemory();
}

// ������������ ������
void Matrix::freeMemory() {
    if (data) {
        for (int i = 0; i < size; i++) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }
}

// �������� ���������
Matrix Matrix::multiply(const Matrix& other) const {
    Matrix result(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < size; k++) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

// ���������������� �������
Matrix Matrix::transpose() const {
    Matrix result(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.data[i][j] = data[j][i];
        }
    }
    return result;
}

// ������������� �������� ������������
Matrix Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        freeMemory();
        size = other.size;
        data = new int* [size];
        for (int i = 0; i < size; i++) {
            data[i] = new int[size];
            for (int j = 0; j < size; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }
    return *this;
}

// ������������� �������� ���������
Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

// ������������� �������� ��������
Matrix operator+(const Matrix& m1, const Matrix& m2) {
    Matrix result(m1.size);
    for (int i = 0; i < m1.size; i++) {
        for (int j = 0; j < m1.size; j++) {
            result.data[i][j] = m1.data[i][j] + m2.data[i][j];
        }
    }
    return result;
}

// ���������� ��������� ����� ��� ������
std::istream& operator>>(std::istream& is, Matrix& matrix) {
    std::cout << "Add matrix numbers " << matrix.size << "x" << matrix.size << ":" << std::endl;
    for (int i = 0; i < matrix.size; i++) {
        for (int j = 0; j < matrix.size; j++) {
            while (true) {
                int value;
                is >> value;
                if (is.fail()) {
                    is.clear(); // ����� ���������
                    is.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������� ������������ ����
                    std::cout << "Invalid input, please enter a number: ";
                } else {
                    matrix.data[i][j] = value;
                    break;
                }
            }
        }
    }
    return is;
}

// ���������� ��������� ������ ��� ������
std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    os << matrix.size << std::endl; // ����� ������� �������
    for (int i = 0; i < matrix.size; i++) {
        for (int j = 0; j < matrix.size; j++) {
            os << matrix.data[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

// ���������� ������� � �������� ����
std::ofstream& operator<<(std::ofstream& ofs, const Matrix& matrix) {
    ofs.write(reinterpret_cast<const char*>(&matrix.size), sizeof(matrix.size)); // ���������� ������ �������
    for (int i = 0; i < matrix.size; ++i) {
        ofs.write(reinterpret_cast<const char*>(matrix.data[i]), matrix.size * sizeof(int)); // ���������� ������
    }
    return ofs;
}

// �������� ������� �� ��������� �����
std::ifstream& operator>>(std::ifstream& ifs, Matrix& matrix) {
    ifs.read(reinterpret_cast<char*>(&matrix.size), sizeof(matrix.size)); // ��������� ������ �������
    matrix.resize(matrix.size); // �������� ������ �������
    for (int i = 0; i < matrix.size; ++i) {
        ifs.read(reinterpret_cast<char*>(matrix.data[i]), matrix.size * sizeof(int)); // ��������� ������
    }
    return ifs;
}

// ����� ��� ���������� ������� � �������� ����
void Matrix::saveToBinary(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::binary );
    if (ofs.is_open()) {
        ofs << *this; // ���������� ������������� �������� ��� ������
        ofs.close();
    }
}

// ����� ��� �������� ������� �� ��������� �����
void Matrix::loadFromBinary(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (ifs.is_open()) {
        ifs >> *this; // ���������� ������������� �������� ��� ������
        ifs.close();
    }
}

// ������ �������
void Matrix::print() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

// ������� ��������� ������� �������
void Matrix::resize(int newSize) {
    freeMemory();
    size = newSize;
    data = new int* [size];
    for (int i = 0; i < size; i++) {
        data[i] = new int[size]();
    }
}
