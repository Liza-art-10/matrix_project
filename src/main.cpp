#include "matrix.h"
#include <iostream>

int main() {
    try {
        std::cout << "=== Тестирование класса Matrix ===\n\n";
        
        Matrix A;
        Matrix B;
        
        // Ввод матриц через оператор >>
        std::cout << "Введите матрицу A (формат: строки столбцы элементы):\n";
        std::cin >> A;
        
        std::cout << "Введите матрицу B (формат: строки столбцы элементы):\n";
        std::cin >> B;
        
        // Вывод исходных матриц
        std::cout << "\nМатрица A:\n" << A << "\n\n";
        std::cout << "Матрица B:\n" << B << "\n\n";
        
        // Тест оператора +=
        Matrix C = A;
        C += B;
        std::cout << "A += B:\n" << C << "\n\n";
        
        // Тест оператора -=
        C -= B;
        std::cout << "Результат после C -= B (должен быть равен A):\n" << C << "\n\n";
        
        // Тест оператора *=
        C *= 2.5;
        std::cout << "C *= 2.5:\n" << C << "\n";
        
    } catch (const std::exception& e) {
        std::cerr << "\nОшибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
