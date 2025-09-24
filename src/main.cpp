#include "matrix.h"
#include <iostream>

int main() {
    try {
        std::cout << "=== Testing Matrix Class ===\n\n";
        
        Matrix A;
        Matrix B;
        
        std::cout << "Enter matrix A (format: rows columns elements):\n";
        std::cin >> A;
        
        std::cout << "Enter matrix B (format: rows columns elements):\n";
        std::cin >> B;
        
        std::cout << "\nMatrix A:\n" << A << "\n\n";
        std::cout << "Matrix B:\n" << B << "\n\n";
        
        // Test new operators with assignment
        std::cout << "=== Testing New Operators (with assignment) ===\n";
        
        Matrix C = A;
        C += B;
        std::cout << "A += B:\n" << C << "\n\n";
        
        C -= B;
        std::cout << "After C -= B (should equal A):\n" << C << "\n\n";
        
        C *= 2.5;
        std::cout << "C *= 2.5:\n" << C << "\n\n";
        
        // Test previously implemented operators
        std::cout << "=== Testing Previously Implemented Operators ===\n";
        
        Matrix D = A + B;
        std::cout << "A + B:\n" << D << "\n\n";
        
        Matrix E = A - B;
        std::cout << "A - B:\n" << E << "\n\n";
        
        Matrix F = A * B;
        std::cout << "A * B (matrix multiplication):\n" << F << "\n\n";
        
        Matrix G = A * 2.0;
        std::cout << "A * 2.0:\n" << G << "\n\n";
        
        Matrix H = 3.0 * B;
        std::cout << "3.0 * B:\n" << H << "\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
