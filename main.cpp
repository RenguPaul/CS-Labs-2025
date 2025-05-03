#include <iostream>
#include "/home/pavel/BAUMAN_PROJECTS/CS-2025-PR/CS-Labs-2025/Polynomial/Polynomial.h"
#include "/home/pavel/BAUMAN_PROJECTS/CS-2025-PR/CS-Labs-2025/Term/Term.h"

void demonstrateTermAndPolynomial() {
    std::cout << "=== Combined Demonstration ===\n";

    std::cout << "\n--- Term Examples ---\n";
    Term t1(3, 2);
    Term t2(-1, 1);
    Term t3(5, 0);
    Term t4(0, 3);

    std::cout << "t1: " << t1 << "\n";
    std::cout << "t2: " << t2 << "\n";
    std::cout << "t3: " << t3 << "\n";
    std::cout << "t4: " << t4 << "\n";

    Term sum = t1 + Term(-2, 2);
    std::cout << "3x^2 + (-2x^2) = " << sum << "\n";

    Term product = t1 * t2;
    std::cout << "3x^2 * (-x) = " << product << "\n";

    std::cout << "\n--- Polynomial Examples ---\n";
    Polynomial p1(t1);
    Polynomial p2;
    p2 += t2;
    p2 += t3;

    std::cout << "p1: " << p1 << "\n";
    std::cout << "p2: " << p2 << "\n";

    Polynomial p3 = p1 + p2;
    std::cout << "p1 + p2 = " << p3 << "\n";

    Polynomial p4 = p1 * p2;
    std::cout << "p1 * p2 = " << p4 << "\n";

    Polynomial p5;
    p5 += Term(2, 3);
    p5 += Term(-1, 1);
    p5 += Term(4, 0);
    std::cout << "p5: " << p5 << "\n";

    Polynomial p6 = p5 * Term(-1, 2);
    std::cout << "p5 * (-x^2) = " << p6 << "\n\n";
}

void combinedInteractiveMode() {
    std::cout << "=== Combined Interactive Mode ===\n";

    while (true) {
        std::cout << "\nOptions:\n";
        std::cout << "1. Work with single Terms\n";
        std::cout << "2. Work with Polynomials\n";
        std::cout << "3. Create Polynomial from multiple Terms\n";
        std::cout << "0. Exit\n";
        std::cout << "Your choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 0) break;

        if (choice == 1) {
            Term t1, t2;
            std::cout << "Enter first term (e.g. 3x^2, -5, x): ";
            std::cin >> t1;
            std::cout << "Enter second term: ";
            std::cin >> t2;

            std::cout << "\nResults:\n";
            std::cout << t1 << " + " << t2 << " = ";
            try {
                std::cout << (t1 + t2) << "\n";
            } catch (const std::invalid_argument& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
            std::cout << t1 << " * " << t2 << " = " << (t1 * t2) << "\n";
        }
        else if (choice == 2) {
            Polynomial p1, p2;
            std::cout << "Enter first polynomial (e.g. 3x^2 - x + 5): ";
            std::cin >> p1;
            std::cout << "Enter second polynomial: ";
            std::cin >> p2;

            std::cout << "\nResults:\n";
            std::cout << "Sum: " << (p1 + p2) << "\n";
            std::cout << "Product: " << (p1 * p2) << "\n";
        }
        else if (choice == 3) {
            Polynomial p;
            std::cout << "Building a polynomial. Enter terms one by one (enter '0' to finish):\n";

            while (true) {
                Term t;
                std::cout << "Enter term (or '0' to finish): ";
                std::cin >> t;

                if (t.getCoefficient() == 0 && t.getExponent() == 0) break;

                p += t;
                std::cout << "Current polynomial: " << p << "\n";
            }

            std::cout << "Final polynomial: " << p << "\n";

            std::cout << "\nAdditional operations:\n";
            std::cout << "1. Multiply by a term\n";
            std::cout << "2. Add another polynomial\n";
            std::cout << "0. Continue\n";
            std::cout << "Your choice: ";
            std::cin >> choice;
            std::cin.ignore();

            if (choice == 1) {
                Term t;
                std::cout << "Enter term to multiply by: ";
                std::cin >> t;
                p *= t;
                std::cout << "Result: " << p << "\n";
            }
            else if (choice == 2) {
                Polynomial p2;
                std::cout << "Enter polynomial to add: ";
                std::cin >> p2;
                p += p2;
                std::cout << "Result: " << p << "\n";
            }
        }
    }
}

int main() {

    demonstrateTermAndPolynomial();
    combinedInteractiveMode();

    return 0;
}
