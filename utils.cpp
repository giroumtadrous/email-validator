#include "utils.hpp"
#include <crypt.h>
#include <regex>
#include <stdexcept>
#include <string>
#include <cstring>

// ── Email validation ──────────────────────────────────────────────────────────

void check_email(const std::string& email) {
    const std::regex pattern(R"(.+@.+\..+)");
    if (!std::regex_match(email, pattern)) {
        throw std::invalid_argument(
            "Invalid email address: \"" + email + "\". "
            "Expected format: user@domain.extension"
        );
    }
}

// ── Password hashing (bcrypt via libcrypt) ────────────────────────────────────

std::string hash_password(const std::string& password) {
    // Generate a bcrypt salt with cost factor 12
    const char* salt = crypt_gensalt("$2b$", 12, nullptr, 0);
    if (!salt) {
        throw std::runtime_error("Failed to generate bcrypt salt.");
    }

    const char* hashed = crypt(password.c_str(), salt);
    if (!hashed) {
        throw std::runtime_error("Failed to hash password.");
    }

    return std::string(hashed);
}

bool verify_password(const std::string& password, const std::string& hash) {
    const char* result = crypt(password.c_str(), hash.c_str());
    if (!result) return false;
    return (hash == std::string(result));
}
