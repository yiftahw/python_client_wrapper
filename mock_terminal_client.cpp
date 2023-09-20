#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <cstdlib>
#include <cstdint>

#define PROMPT "> "

class CommandHandler {
public:
    CommandHandler() {
        counter = 0;
        help_string = "Available commands:\n";
        
        addFunction("help", 
                    "print this help message", 
                    [this]() { std::cout << help_string; counter++; });

        addFunction("hello", 
                    "say Hello!", 
                    [this]() { std::cout << "Hello!\n"; counter++; });

        addFunction("print", 
                    "print how many times this session got a command", 
                    [this]() { std::cout << "Function calls: " << counter << std::endl; counter++; });

        addFunction("exit", 
                    "exit the program", 
                    []() { std::cout << "Exiting program.\n"; exit(0); });
    }

    void addFunction(const std::string& name, const std::string& hint, std::function<void()> callback) {
        commands[name] = callback;
        help_string += name + " - " + hint + "\n";
    }

    void run() {
        std::cout << "Enter a command, or help for more info.\n";
        while (true) {
            std::cout << PROMPT;
            std::string input;
            std::cin >> input;

            if (commands.find(input) != commands.end()) {
                commands[input]();
            } else {
                std::cout << "Invalid command. Type 'help' for a list of commands.\n";
            }
        }
    }

private:
    std::map<std::string, std::function<void()>> commands;
    std::string help_string;
    uint32_t counter;
};

int main() {
    CommandHandler handler;
    handler.run();
    return 0;
}
