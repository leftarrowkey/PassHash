#include "pass_hash.hpp"
#include <cerrno>
#include <chrono>
#include <cmath>
#include <crypt.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>
#include <ratio>
#include <string>

const unsigned long MINIMUM_COST = 11;

std::string PassHash::generate_setting(const char *prefix,
                                       unsigned long count) {
    char salt[CRYPT_GENSALT_OUTPUT_SIZE];
    crypt_gensalt_rn(prefix, count, nullptr, 0, salt,
                     CRYPT_GENSALT_OUTPUT_SIZE);
    if (errno != 0) {
        std::cerr << errno << std::endl;
        std::perror("failed to generate salt");
    }
    std::string salt_string(salt);
    return salt_string;
}

std::string PassHash::generate_hash(std::string password, std::string setting) {
    crypt_data *result = new crypt_data();
    crypt_rn(password.c_str(), setting.c_str(), result, sizeof(*result));
    if (errno != 0) {
        std::cout << errno << std::endl;
        std::perror("hashing failed");
    }
    std::string hash(result->output);
    delete result;
    return hash;
}

std::string PassHash::hash_password(std::string password, const char *prefix,
                          unsigned long count) {
    std::string setting = PassHash::generate_setting(prefix, count);
    std::string hash = PassHash::generate_hash(password, setting);
    return hash;
}

bool PassHash::check_password(std::string password, std::string hash) {
    std::string new_hash = PassHash::generate_hash(password, hash);
    return hash == new_hash;
}

unsigned long PassHash::get_minimum_count(const char *prefix,
                                std::chrono::duration<double> desired_time) {
    std::chrono::steady_clock clock;
    std::string setting = PassHash::generate_setting(prefix, MINIMUM_COST);
    auto start = clock.now();
    std::string hash = PassHash::generate_hash("benchmark", setting);
    auto end = clock.now();
    std::chrono::duration<double, std::milli> time_taken = end - start;
    unsigned long count =
        MINIMUM_COST + std::ceil(std::log2(desired_time / time_taken));
    return count;
}
