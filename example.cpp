#include <chrono>
#include <string>
#include <iostream>
#include "pass_hash.hpp"

int main() {
	// include the time unit suffixes
    using namespace std::chrono_literals;

	// the first password
    std::string password;
    std::cin >> password;

	// get the count needed for hashing to take 250ms
    unsigned long count = PassHash::get_minimum_count(PassHash::AlgoPrefixes::BCRYPT, 250ms);

	// get the hash of the first password
    std::string hash_1 = PassHash::hash_password(password, PassHash::AlgoPrefixes::BCRYPT, count);
    std::cout << hash_1 << std::endl;

	// the second password
    std::string password2;
    std::cin >> password2;

	// print :) if the passwords match, otherwise :(
    if (PassHash::check_password(password2, hash_1)) {
        std::cout << ":)" << std::endl;
    } else {
        std::cout << ":(" << std::endl;
    }
    return 0;
}
