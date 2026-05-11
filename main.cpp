#include "utils.hpp"

#include <iostream>
#include <map>
#include <string>
#include <limits>

// ── Helpers ───────────────────────────────────────────────────────────────────

static void clear_screen() {
    std::cout << "\n" << std::string(50, '-') << "\n";
}

static std::string prompt(const std::string& label) {
    std::string value;
    std::cout << label;
    std::getline(std::cin, value);
    return value;
}

static std::string prompt_password(const std::string& label) {
    // Simple password prompt (no echo hiding — requires platform libs)
    return prompt(label);
}

// ── Menu actions ──────────────────────────────────────────────────────────────

void do_signup(std::map<std::string, std::string>& users) {
    clear_screen();
    std::cout << "=== SIGN UP ===\n";

    // Email: keep asking until valid
    std::string email;
    while (true) {
        email = prompt("Email: ");
        try {
            check_email(email);
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "✗ " << e.what() << "\n  Please try again.\n";
        }
    }

    // Check duplicate
    if (users.count(email)) {
        std::cout << "✗ An account with that email already exists.\n";
        return;
    }

    std::string password = prompt_password("Password: ");
    if (password.empty()) {
        std::cout << "✗ Password cannot be empty.\n";
        return;
    }

    // Hash and store
    users[email] = hash_password(password);
    std::cout << "✓ Account created for " << email << ".\n";
}

std::string do_login(const std::map<std::string, std::string>& users) {
    clear_screen();
    std::cout << "=== LOGIN ===\n";

    std::string email = prompt("Email: ");
    std::string password = prompt_password("Password: ");

    auto it = users.find(email);
    if (it == users.end()) {
        std::cout << "✗ No account found for that email.\n";
        return "";
    }

    if (!verify_password(password, it->second)) {
        std::cout << "✗ Incorrect password.\n";
        return "";
    }

    std::cout << "✓ Welcome, " << email << "!\n";
    return email;   // return logged-in user
}

void do_logout(std::string& logged_in_user) {
    clear_screen();
    std::cout << "✓ Goodbye, " << logged_in_user << ". You have been logged out.\n";
    logged_in_user.clear();
}

// ── Main ──────────────────────────────────────────────────────────────────────

int main() {
    std::map<std::string, std::string> users;   // email → bcrypt hash
    std::string logged_in_user;                 // empty = logged out

    while (true) {
        clear_screen();

        if (logged_in_user.empty()) {
            // ── Logged-out menu ──
            std::cout << "=== MAIN MENU ===\n";
            std::cout << "  [1] Sign up\n";
            std::cout << "  [2] Login\n";
            std::cout << "  [0] Exit\n";
            std::cout << "Choice: ";

            std::string choice;
            std::getline(std::cin, choice);

            if      (choice == "1") do_signup(users);
            else if (choice == "2") logged_in_user = do_login(users);
            else if (choice == "0") { std::cout << "Bye!\n"; break; }
            else    std::cout << "✗ Invalid option.\n";

        } else {
            // ── Logged-in menu ──
            std::cout << "=== MAIN MENU (logged in as " << logged_in_user << ") ===\n";
            std::cout << "  [3] Logout\n";
            std::cout << "  [0] Exit\n";
            std::cout << "Choice: ";

            std::string choice;
            std::getline(std::cin, choice);

            if      (choice == "3") do_logout(logged_in_user);
            else if (choice == "0") { std::cout << "Bye!\n"; break; }
            else    std::cout << "✗ Invalid option.\n";
        }

        // Pause so the user can read output before the menu redraws
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}
