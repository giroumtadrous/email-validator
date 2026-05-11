#include "utils.hpp"

#include <regex>
#include <stdexcept>
#include <string>

void check_email(const std::string& email) {
    // Pattern: at least one char, '@', at least one char, '.', at least one char
    const std::regex pattern(R"(.+@.+\..+)");

    if (!std::regex_match(email, pattern)) {
        throw std::invalid_argument(
            "Invalid email address: \"" + email + "\". "
            "Expected format: user@domain.extension"
        );
    }
}
