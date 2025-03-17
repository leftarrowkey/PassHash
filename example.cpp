#include <chrono>
#include <string>
#include <iostream>
#include "pass_hash.hpp"

int main() {
    using namespace std::chrono_literals;
    std::string password;
    std::cin >> password;
    unsigned long count = PassHash::get_minimum_count("$2b$", 250ms);
    std::chrono::steady_clock clock;
    auto start = clock.now();
    std::string hash_1 = PassHash::hash_password(password, "$2b$", count);
    auto end = clock.now();
    std::chrono::duration<double, std::milli> time_taken = end - start;
    std::cout << time_taken.count() << std::endl;
    std::cout << hash_1 << std::endl;
    std::string password2;
    std::cin >> password2;
    if (PassHash::check_password(password2, hash_1)) {
        std::cout << ":)" << std::endl;
    } else {
        std::cout << ":(" << std::endl;
    }
    return 0;
}
