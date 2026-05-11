#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <map>

// Validates the format of an email address.
// Throws std::invalid_argument if the email does not match the expected pattern.
void check_email(const std::string& email);

// Hashes a plain-text password using bcrypt.
std::string hash_password(const std::string& password);

// Verifies a plain-text password against a bcrypt hash.
bool verify_password(const std::string& password, const std::string& hash);

#endif // UTILS_HPP
