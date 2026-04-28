#ifndef ARCADE_EXCEPTIONS_HPP
#define ARCADE_EXCEPTIONS_HPP

#include <exception>
#include <string>

class ArcadeException : public std::exception {
protected:
    std::string message;
public:
    explicit ArcadeException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InsufficientTokensException : public ArcadeException {
public:
    explicit InsufficientTokensException(const std::string& msg) 
        : ArcadeException("[Token Error] " + msg) {}
};

class MachineOccupiedException : public ArcadeException {
public:
    explicit MachineOccupiedException(const std::string& msg) 
        : ArcadeException("[Availability Error] " + msg) {}
};

class InvalidConfigurationException : public ArcadeException {
public:
    explicit InvalidConfigurationException(const std::string& msg) 
        : ArcadeException("[Config Error] " + msg) {}
};

class NeedsMaintenanceException : public ArcadeException {
public:
    explicit NeedsMaintenanceException(const std::string& msg) 
        : ArcadeException("[Maintenance] " + msg) {}
};

#endif 