#include "utils.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

int main() {
    std::string email;

    while (true) {
        std::cout << "Enter your email address: ";
        std::getline(std::cin, email);

        try {
            check_email(email);
            std::cout << "✓ Email accepted: " << email << std::endl;
            break; // valid email — exit the loop
        } catch (const std::invalid_argument& e) {
            std::cerr << "✗ Error: " << e.what() << std::endl;
            std::cout << "Please try again.\n\n";
        }
    }

    return 0;
}
