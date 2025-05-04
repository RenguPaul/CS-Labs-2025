#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <list>
#include <map>

void printList(const std::list<int>& lst) {
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

void processList(std::list<int>& lst) {
    std::cout << "Исходный список: ";
    printList(lst);

    auto it = lst.begin();
    while (it != lst.end()) {
        lst.insert(std::next(it), -*it);
        std::advance(it, 2);
    }

    lst.remove_if([](int x) { return x < 0; });

    std::cout << "Измененный список: ";
    printList(lst);
}

class Planet {
    private:
        std::string name;
        int satellites;
    public:
        Planet(const std::string& n, int s) : name(n), satellites(s) {}

        std::string getName() const { return name; }
        int getSatellites() const { return satellites; }

        friend std::ostream& operator<<(std::ostream& os, const Planet& p) {
            os << p.name << " (спутников: " << p.satellites << ")";
            return os;
        }
    };


void printPlanets(const std::list<Planet>& planets) {
    for (const auto& planet : planets) {
        std::cout << planet << std::endl;
    }
}

Planet findMaxSatellites(const std::list<Planet>& planets) {
    return *std::max_element(planets.begin(), planets.end(),
        [](const Planet& a, const Planet& b) {
            return a.getSatellites() < b.getSatellites();
        });
}

class Point {
    public:
        double x, y;
        Point() { x = y = 0; }
        Point(double a, double b) { x = a; y = b; }

        bool operator<(const Point& other) const {
            return (x*x + y*y) < (other.x*other.x + other.y*other.y);
        }

        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }

        double distanceFromOrigin() const {
            return std::sqrt(x*x + y*y);
        }
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

void printPoints(const std::vector<Point>& points) {
    for (const auto& p : points) {
        std::cout << p << std::endl;
    }
}

Point findFurthestPoint(const std::vector<Point>& points) {
    return *std::max_element(points.begin(), points.end());
}


void printVector(const std::vector<float>& vec) {
    for (float num : vec) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}


void task_1() {
    std::string text1, text2;
    int count1 = 0, count2 = 0;

    std::cout << "Введите первый текст: ";
    std::getline(std::cin, text1);

    for (char c : text1) {
        if (c == '.' || c == '!' || c == '?') {
            count1++;
        }
    }

    std::cout << "Введите второй текст: ";
    std::getline(std::cin, text2);

    for (char c : text2) {
        if (c == '.' || c == '!' || c == '?') {
            count2++;
        }
    }

    std::cout << "Количество предложений в первом тексте: " << count1 << std::endl;
    std::cout << "Количество предложений во втором тексте: " << count2 << std::endl;

}

void task_2() {
    std::string input, output;

    std::cout << "Введите строку: ";
    std::getline(std::cin, input);

    for (char c : input) {
        if (c != ' ' && c != '.' && c != ',') {
            output += c;
        }
    }

    std::cout << "Результат: " << output << std::endl;
}

void task_3() {
    std::ifstream inputFile("a.txt");
    std::ofstream outputFile("b.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть входной файл!" << std::endl;
        return ;
    }

    if (!outputFile.is_open()) {
        std::cerr << "Не удалось создать выходной файл!" << std::endl;
        return ;
    }

    char ch;
    while (inputFile.get(ch)) {
        if (islower(ch)) {
            ch = toupper(ch);
        }
        outputFile << ch;
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Преобразование завершено успешно!" << std::endl;
}

void task_4() {
    std::vector<float> numbers;

    for (int i = 0; i < 25; ++i) {
        numbers.push_back(i + 0.5f);
    }

    std::cout << "Исходный вектор:\n";
    printVector(numbers);
    std::cout << "\n";

    numbers.erase(numbers.begin() + 1);

    std::cout << "Вектор после удаления элемента с индексом 1:\n";
    printVector(numbers);
}

void task_5() {
    std::vector<Point> points = {
        Point(1.2, 6.3),
        Point(4.0, 0.7),
        Point(7.2, 0.8),
        Point(5.3, 3.0),
        Point(4.9, 6.6),
        Point(9.3, 0.2)
    };

    std::cout << "Исходные точки:" << std::endl;
    printPoints(points);
    std::cout << std::endl;

    Point furthest = findFurthestPoint(points);
    std::cout << "Наиболее удаленная точка от центра: " << furthest
              << " (расстояние: " << furthest.distanceFromOrigin() << ")"
              << std::endl << std::endl;

    double shift;
    std::cout << "Введите величину сдвига по оси X: ";
    std::cin >> shift;

    for (auto& p : points) {
        p.x -= shift;
    }

    std::cout << "Точки после сдвига:" << std::endl;
    printPoints(points);
}

void task_6() {
    std::list<int> myList = {1, -2, 3, -4, 5};

    processList(myList);
}

void task_7() {
    std::list<Planet> planets = {
        Planet("Меркурий", 0),
        Planet("Венера", 0),
        Planet("Земля", 1),
        Planet("Марс", 2),
        Planet("Юпитер", 69),
        Planet("Сатурн", 62),
        Planet("Уран", 27),
        Planet("Нептун", 14),
        Planet("Плутон", 10)
    };

    std::cout << "Список планет:" << std::endl;
    printPlanets(planets);
    std::cout << std::endl;

    Planet maxSatPlanet = findMaxSatellites(planets);
    std::cout << "Планета с наибольшим количеством спутников: "
              << maxSatPlanet << std::endl;
    return ;

}

void task_8() {
    std::map<char, int> charMap;
    charMap['A'] = 1;
    charMap['B'] = 2;
    charMap['C'] = 3;
    charMap['D'] = 4;
    charMap['E'] = 5;

    std::cout << "Исходное отображение:\n";
    for (const auto& pair : charMap) {
        std::cout << pair.first << " -> " << pair.second << "\n";
    }

    charMap.erase('C');

    std::cout << "\nПосле удаления 'C':\n";
    for (const auto& pair : charMap) {
        std::cout << pair.first << " -> " << pair.second << "\n";
    }

    return ;
}

void task_9() {
    std::string states[] = {"Wyoming", "Colorado", "Nevada", "Montana", "Arizona", "Idaho"};
    int pops[] = {470, 2890, 800, 787, 2718, 944};

    std::map<std::string, int> statePopulation;

    for (int i = 0; i < 6; ++i) {
        statePopulation[states[i]] = pops[i];
    }

    std::cout << "Список штатов и их население (в тысячах):\n";
    for (const auto& pair : statePopulation) {
        std::cout << pair.first << ": " << pair.second << " тыс.\n";
    }

    std::string query;
    std::cout << "\nВведите название штата для поиска: ";
    std::cin >> query;

    auto it = statePopulation.find(query);
    if (it != statePopulation.end()) {
        std::cout << "Население " << query << ": " << it->second << " тыс. человек\n";
    } else {
        std::cout << "Штат '" << query << "' не найден в базе данных.\n";
    }

    return ;
}

int main(){
    task_1();
    task_2();
    task_3();
    task_4();
    task_5();
    task_6();
    task_7();
    task_8();
    task_9();
    return 0;
}
