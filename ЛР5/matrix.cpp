#include "matrix.h"
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace std;

// Конструктор по умолчанию
Matrix::Matrix() : rows(0), cols(0), data(nullptr) {}

// Конструктор с параметром
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    data = new int* [rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new int[cols];
    }
}

// Конструктор копирования
Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    data = new int* [rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;
}


void Matrix::freeMemory() {
    if (data) {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }
}


Matrix Matrix::multiply(const Matrix& other) const {
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < cols; k++) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}


Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}


// Перегруженная операция присваивания
Matrix Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        freeMemory();
        rows = other.rows;
        cols = other.cols;
        data = new int* [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }
    return *this;
}

// Перегруженная операция вычитания
Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

// Перегруженная операция сложения
Matrix operator+(const Matrix& m1, const Matrix& m2) {
    Matrix result(m1.rows, m1.cols);
    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.cols; j++) {
            result.data[i][j] = m1.data[i][j] + m2.data[i][j];
        }
    }
    return result;
}

// Перегрузка оператора ввода для матриц
istream& operator>>(istream& is, Matrix& matrix) {
    cout << "Add matrix numbers " << matrix.rows << "x" << matrix.cols << ":" << endl;
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            while (true) {
                int value;
                is >> value;
                if (is.fail()) {
                    is.clear(); // Сброс состояния
                    is.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем некорректный ввод
                    cout << "Invalid input, please enter a number: ";
                } else {
                    matrix.data[i][j] = value;
                    break;
                }
            }
        }
    }
    return is;
}

// Перегрузка оператора вывода для матриц
ostream& operator<<(ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            os << matrix.data[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

// Сохранение матрицы в текстовый файл
ofstream& operator<<(ofstream& ofs, const Matrix& matrix) {
    ofs << matrix.rows << " " << matrix.cols << endl;
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            ofs << matrix.data[i][j] << " ";
        }
        ofs << endl;
    }
    return ofs;
}


// Загрузка матрицы из текстового файла
ifstream& operator>>(ifstream& ifs, Matrix& matrix) {
    ifs >> matrix.rows >> matrix.cols;
    matrix.resize(matrix.rows, matrix.cols);
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            ifs >> matrix.data[i][j];
        }
    }
    return ifs;
}


// Метод для сохранения матрицы в бинарный файл
void Matrix::saveToBinary(const string& filename) const {
    ofstream ofs(filename, ios::binary );
    if (ofs.is_open()) {
        ofs << *this; // Используем перегруженный оператор для записи
        ofs.close();
    }
}

// Метод для загрузки матрицы из бинарного файла
void Matrix::loadFromBinary(const string& filename) {
    ifstream ifs(filename, ios::binary);
    if (ifs.is_open()) {
        ifs >> *this; // Используем перегруженный оператор для чтения
        ifs.close();
    }
}

// Печать матрицы
void Matrix::print() const {
    cout << "Square matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

void IdentityMatrix::print() const {
    cout << "Identity matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

void RectangularMatrix::print() const {
    cout << "Rectangular matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix::resize(int newRows, int newCols) {
    freeMemory();
    rows = newRows;
    cols = newCols;
    data = new int*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new int[cols]();
    }
}

bool List::isEmptyList(const List& list) {
    return head == nullptr;
}

void List::append(List& list,  Matrix* data) {
    Node* newNode = new Node(data);
    if (isEmptyList(list)) {
        list.head = newNode;
    }
    else {
        Node* tail = list.head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = list.head;
        list.head->prev = newNode;
    }
    list.size++;
}

Node* List::findNode(const List& list, int index) {
    if (index < 0 || index >= list.size) {
        cout << "Out of bounds \n";
        return nullptr;
    }
    Node* current = list.head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

void List::insertNode(List& list, int index, Matrix* newMatrix) {
    if (index < 0 || index > list.size) {
        cout << "Out of bounds \n";
        return;
    }
    Node* newNode = new Node(newMatrix);

    if (list.size == 0) {
        list.head = newNode;
        newNode->next = newNode->prev = newNode;
        cout << "Inserted first node. Head data:" << endl;
        newNode->data->print();
    } else if (index == 0) {
        Node* tail = list.head->prev;
        newNode->next = list.head;
        newNode->prev = tail;
        tail->next = newNode;
        list.head->prev = newNode;
        list.head = newNode;
        cout << "Inserted node at the beginning." << endl;
        newNode->data->print();
    } else if (index == list.size) {
        append(list, newMatrix);
        return;
    } else {
        Node* current = findNode(list, index);
        Node* previous = current->prev;
        newNode->next = current;
        newNode->prev = previous;
        previous->next = newNode;
        current->prev = newNode;
        cout << "Inserted node in the middle. Data:" << endl;
        newNode->data->print();
    }

    list.size++;
    cout << "List size after insertion: " << list.size << endl;
}

void List::deleteNode(List& list, int index) {
    if (index < 0 || index >= list.size) {
        cout << "Out of bounds \n";
        return;
    }
    Node* removeNode = findNode(list, index);
    if (list.size == 1) {
        delete removeNode;
        list.head = nullptr;
        cout << "Node deleted \n";
    }
    else {
        Node* prevNode = removeNode->prev;
        Node* nextNode = removeNode->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        if (removeNode == list.head) {
            list.head = nextNode;
        }
        delete removeNode;
        cout << "Node deleted \n";
    }
    list.size--;
}

void List::displayNode(const List& list, int index) {
    if (size == 0) {
        cout << "List is empty \n";
        return;
    }
    Node* node = findNode(list, index);
    if (node != nullptr && node->data != nullptr) {
        cout << "Matrix at index " << index << ":\n";
        node->data->print();
    } else {
        cout << "Node does not exist or contains no matrix \n";
    }
}

void List::deleteList(List& list) {
    while (size > 0) {
        deleteNode(list, 0);
    }
    cout << "List deleted \n";
}

void List::display(const List& list) {
    if (isEmptyList(list)) {
        cout << "List is empty \n";
        return;
    }
    Node* current = head;
    int counter = 1;
    do {
        cout << counter << ") " << endl;
        if (current->data != nullptr) {
            current->data->print();
        } else {
            cout << "Matrix is empty \n";
        }
        current = current->next;
        counter++;
    } while (current != list.head);
}

bool Matrix::operator==(const Matrix& other) const {
    if (this->rows != other.rows || this->cols != other.cols) {
        return false;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (this->data[i][j] != other.data[i][j]) {
                return false;
            }
        }
    }

    return true;
}

void Menu_print::matrixTypes() {
    cout << "Choose type of Matrix:" << endl;
    cout << "1. Square" << endl;
    cout << "2. Idenitity" << endl;
    cout << "3. Rectangular" << endl;
    cout << "0. Exit" << endl;
}

void Menu_print::mathOptions() {
    cout << "Choose option:" << endl;
    cout << "1. Matrix addition" << endl;
    cout << "2. Matrix subtraction" << endl;
    cout << "3. Matrix multiplication" << endl;
    cout << "4. Transposition" << endl;
    cout << "5. Save to file" << endl;
    cout << "6. Load from file" << endl;
    cout << "7. Save to bin file" << endl;
    cout << "8. Load from bin file" << endl;
    cout << "0. Exit" << endl;
}

void Menu_print::listOptions() {
    cout << "Choose option:" << endl;
    cout << "1. Delete list" << endl;
    cout << "2. Insert node" << endl;
    cout << "3. Delete node" << endl;
    cout << "4. Find node" << endl;
    cout << "0. Exit" << endl;
}