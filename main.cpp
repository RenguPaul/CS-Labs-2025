#include "/home/pavel/BAUMAN_PROJECTS/CS-2025-PR/CS-Labs-2025/Test/Test.h"
#include "/home/pavel/BAUMAN_PROJECTS/CS-2025-PR/CS-Labs-2025/Exam/Exam.h"
#include "/home/pavel/BAUMAN_PROJECTS/CS-2025-PR/CS-Labs-2025/FinalExam/FinalExam.h"
#include "/home/pavel/BAUMAN_PROJECTS/CS-2025-PR/CS-Labs-2025/Trial/Trial.h"
#include "/home/pavel/BAUMAN_PROJECTS/CS-2025-PR/CS-Labs-2025/MyVector/MyVector.h"
#include <iostream>
#include <limits>

void safeInput(char* buffer, int size) {
    std::cin.getline(buffer, size);
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void print(const MyVector<Test*>& container) {
    for (size_t i = 0; i < container.get_size(); ++i) {
        std::cout << "[" << i << "] ";
        container[i]->show();
        std::cout << std::endl;
    }
}

void remove(MyVector<Test*>& container, size_t index) {
    if (index >= container.get_size()) {
        std::cout << "Error: Index out of range\n";
        return;
    }
    delete container[index];
    container.delete_element(container[index]);
}

void clear(MyVector<Test*>& container) {
    for (size_t i = 0; i < container.get_size(); ++i) {
        delete container[i];
    }
    while (container.get_size() > 0) {
        container.delete_element(container[0]);
    }
}

void demonstrationMode() {
    std::cout << "\n=== DEMONSTRATION MODE ===\n";

    MyVector<Test*> tests;

    tests.add_element(new Exam("Midterm Math", 20, "Mathematics", 90));
    tests.add_element(new FinalExam("Calculus Final", 30, "Mathematics", 180, true));
    tests.add_element(new Trial("Programming Test", 15, 3));

    std::cout << "\nAll tests:\n";
    print(tests);

    std::cout << "\nRemoving test at index 1...\n";
    remove(tests, 1);

    std::cout << "\nRemaining tests:\n";
    print(tests);

    std::cout << "\nClearing all tests...\n";
    clear(tests);

    std::cout << "\nContainer size after clear: " << tests.get_size() << std::endl;
}

void interactiveMode() {
    MyVector<Test*> tests;
    int choice;
    const int BUFFER_SIZE = 100;
    char buffer[BUFFER_SIZE];

    do {
        std::cout << "\n=== INTERACTIVE MODE ===\n"
                  << "1. Add Exam\n"
                  << "2. Add Final Exam\n"
                  << "3. Add Trial\n"
                  << "4. Print All Tests\n"
                  << "5. Remove Test\n"
                  << "6. Clear All Tests\n"
                  << "0. Exit\n"
                  << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                char name[BUFFER_SIZE], subject[BUFFER_SIZE];
                int questions, duration;

                std::cout << "Exam name: ";
                safeInput(name, BUFFER_SIZE);
                std::cout << "Subject: ";
                safeInput(subject, BUFFER_SIZE);
                std::cout << "Number of questions: ";
                std::cin >> questions;
                std::cout << "Duration (minutes): ";
                std::cin >> duration;
                std::cin.ignore();

                tests.add_element(new Exam(name, questions, subject, duration));
                break;
            }
            case 2: {
                char name[BUFFER_SIZE], subject[BUFFER_SIZE];
                int questions, duration;
                char thesis;

                std::cout << "Final exam name: ";
                safeInput(name, BUFFER_SIZE);
                std::cout << "Subject: ";
                safeInput(subject, BUFFER_SIZE);
                std::cout << "Number of questions: ";
                std::cin >> questions;
                std::cout << "Duration (minutes): ";
                std::cin >> duration;
                std::cout << "Includes thesis defense? (y/n): ";
                std::cin >> thesis;
                std::cin.ignore();

                tests.add_element(new FinalExam(name, questions, subject, duration, thesis == 'y' || thesis == 'Y'));
                break;
            }
            case 3: {
                char name[BUFFER_SIZE];
                int questions, attempts;

                std::cout << "Trial name: ";
                safeInput(name, BUFFER_SIZE);
                std::cout << "Number of questions: ";
                std::cin >> questions;
                std::cout << "Attempts allowed: ";
                std::cin >> attempts;
                std::cin.ignore();

                tests.add_element(new Trial(name, questions, attempts));
                break;
            }
            case 4:
                print(tests);
                break;
            case 5: {
                size_t index;
                print(tests);
                std::cout << "Enter index to remove: ";
                std::cin >> index;
                std::cin.ignore();

                remove(tests, index);
                break;
            }
            case 6:
                clear(tests);
                std::cout << "All tests cleared.\n";
                break;
            case 0:
                clear(tests);
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

int main() {
    int mode;

    std::cout << "Select mode:\n"
              << "1. Demonstration\n"
              << "2. Interactive\n"
              << "Choice: ";
    std::cin >> mode;
    std::cin.ignore();

    if (mode == 1) {
        demonstrationMode();
    } else if (mode == 2) {
        interactiveMode();
    } else {
        std::cout << "Invalid mode selected.\n";
    }

    return 0;
}
