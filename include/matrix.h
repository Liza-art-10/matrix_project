#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>

class Matrix {
private:
    int rows_;
    int cols_;
    double** data_;

    void clear() {
        if (data_ != nullptr) {
            for (int i = 0; i < rows_; ++i) {
                delete[] data_[i];
            }
            delete[] data_;
            data_ = nullptr;
        }
        rows_ = 0;
        cols_ = 0;
    }

    void allocate(int rows, int cols) {
        if (rows <= 0 || cols <= 0) {
            throw std::invalid_argument("Matrix dimensions must be positive");
        }
        rows_ = rows;
        cols_ = cols;
        data_ = new double*[rows_];
        for (int i = 0; i < rows_; ++i) {
            data_[i] = new double[cols_]{0};
        }
    }

public:
    // Конструкторы
    Matrix(int rows, int cols) : rows_(0), cols_(0), data_(nullptr) {
        allocate(rows, cols);
    }

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

    // Операторы с присваиванием (НОВЫЕ)
    Matrix& operator+=(const Matrix& other) {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Matrix dimensions mismatch for addition");
        }
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                data_[i][j] += other.data_[i][j];
            }
        }
        return *this;
    }

    Matrix& operator-=(const Matrix& other) {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Matrix dimensions mismatch for subtraction");
        }
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                data_[i][j] -= other.data_[i][j];
            }
        }
        return *this;
    }

    Matrix& operator*=(double scalar) {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                data_[i][j] *= scalar;
            }
        }
        return *this;
    }

    // Операторы ввода/вывода (НОВЫЕ)
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    friend std::istream& operator>>(std::istream& is, Matrix& matrix);

    // Операторы без присваивания (УЖЕ БЫЛИ РЕАЛИЗОВАНЫ)
    friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator*(const Matrix& matrix, double scalar);
    friend Matrix operator*(double scalar, const Matrix& matrix);
};

// Операторы без присваивания (реализация)
inline Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.rows_ != rhs.rows_ || lhs.cols_ != rhs.cols_) {
        throw std::invalid_argument("Matrix dimensions mismatch for addition");
    }
    Matrix result(lhs.rows_, lhs.cols_);
    for (int i = 0; i < lhs.rows_; ++i) {
        for (int j = 0; j < lhs.cols_; ++j) {
            result.data_[i][j] = lhs.data_[i][j] + rhs.data_[i][j];
        }
    }
    return result;
}

inline Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.rows_ != rhs.rows_ || lhs.cols_ != rhs.cols_) {
        throw std::invalid_argument("Matrix dimensions mismatch for subtraction");
    }
    Matrix result(lhs.rows_, lhs.cols_);
    for (int i = 0; i < lhs.rows_; ++i) {
        for (int j = 0; j < lhs.cols_; ++j) {
            result.data_[i][j] = lhs.data_[i][j] - rhs.data_[i][j];
        }
    }
    return result;
}

inline Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.cols_ != rhs.rows_) {
        throw std::invalid_argument("Matrix dimensions mismatch for multiplication");
    }
    Matrix result(lhs.rows_, rhs.cols_);
    for (int i = 0; i < lhs.rows_; ++i) {
        for (int j = 0; j < rhs.cols_; ++j) {
            result.data_[i][j] = 0;
            for (int k = 0; k < lhs.cols_; ++k) {
                result.data_[i][j] += lhs.data_[i][k] * rhs.data_[k][j];
            }
        }
    }
    return result;
}

inline Matrix operator*(const Matrix& matrix, double scalar) {
    Matrix result(matrix.rows_, matrix.cols_);
    for (int i = 0; i < matrix.rows_; ++i) {
        for (int j = 0; j < matrix.cols_; ++j) {
            result.data_[i][j] = matrix.data_[i][j] * scalar;
        }
    }
    return result;
}

inline Matrix operator*(double scalar, const Matrix& matrix) {
    return matrix * scalar;
}

// Операторы ввода/вывода (реализация)
inline std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.rows_; ++i) {
        for (int j = 0; j < matrix.cols_; ++j) {
            os << matrix.data_[i][j];
            if (j < matrix.cols_ - 1) os << ' ';
        }
        if (i < matrix.rows_ - 1) os << '\n';
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, Matrix& matrix) {
    int rows, cols;
    is >> rows >> cols;
    
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
