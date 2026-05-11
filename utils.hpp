#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

// Validates the format of an email address.
// Throws std::invalid_argument if the email does not match the expected pattern.
void check_email(const std::string& email);

#endif // UTILS_HPP
