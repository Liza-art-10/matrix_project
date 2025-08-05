#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>  // Для обработки ошибок

class Matrix {
private:
    int rows_;      // Количество строк
    int cols_;      // Количество столбцов
    double** data_; // Двумерный массив данных

    // Освобождаем память
    void clear() {
        if (data_ != nullptr) {
            for (int i = 0; i < rows_; ++i) {
                delete[] data_[i];
            }
            delete[] data_;
            data_ = nullptr;
            rows_ = 0;
            cols_ = 0;
        }
    }

    // Выделяем новую память
    void allocate(int rows, int cols) {
        if (rows <= 0 || cols <= 0) {
            throw std::invalid_argument("Размеры матрицы должны быть положительными");
        }
        rows_ = rows;
        cols_ = cols;
        data_ = new double*[rows_];
        for (int i = 0; i < rows_; ++i) {
            data_[i] = new double[cols_]{0}; // Инициализация нулями
        }
    }

public:
    // Основной конструктор
    Matrix(int rows, int cols) : rows_(0), cols_(0), data_(nullptr) {
        allocate(rows, cols);
    }

    // Конструктор по умолчанию
    Matrix() : rows_(0), cols_(0), data_(nullptr) {}

    // Деструктор
    ~Matrix() {
        clear();
    }

    // Конструктор копирования
    Matrix(const Matrix& other) : Matrix() {
        *this = other;
    }

    // Оператор присваивания
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            clear();
            allocate(other.rows_, other.cols_);
            for (int i = 0; i < rows_; ++i) {
                for (int j = 0; j < cols_; ++j) {
                    data_[i][j] = other.data_[i][j];
                }
            }
        }
        return *this;
    }

    // Оператор += (сложение с присваиванием)
    Matrix& operator+=(const Matrix& other) {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Размеры матриц не совпадают для сложения");
        }
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                data_[i][j] += other.data_[i][j];
            }
        }
        return *this;
    }

    // Оператор -= (вычитание с присваиванием)
    Matrix& operator-=(const Matrix& other) {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Размеры матриц не совпадают для вычитания");
        }
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                data_[i][j] -= other.data_[i][j];
            }
        }
        return *this;
    }

    // Оператор *= (умножение на число)
    Matrix& operator*=(double scalar) {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                data_[i][j] *= scalar;
            }
        }
        return *this;
    }

    // Дружественные функции для ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    friend std::istream& operator>>(std::istream& is, Matrix& matrix);
};

// Оператор вывода
inline std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.rows_; ++i) {
        for (int j = 0; j < matrix.cols_; ++j) {
            os << matrix.data_[i][j];
            if (j < matrix.cols_ - 1) os << ' '; // Пробел между элементами
        }
        if (i < matrix.rows_ - 1) os << '\n'; // Перенос строки
    }
    return os;
}

// Оператор ввода
inline std::istream& operator>>(std::istream& is, Matrix& matrix) {
    int rows, cols;
    is >> rows >> cols;  // Сначала читаем размеры
    
    if (rows != matrix.rows_ || cols != matrix.cols_) {
        matrix.clear();
        matrix.allocate(rows, cols);
    }
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            is >> matrix.data_[i][j];
        }
    }
    return is;
}

#endif // MATRIX_H
