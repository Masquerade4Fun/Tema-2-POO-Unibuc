#ifndef ARCADE_EXCEPTIONS_HPP
#define ARCADE_EXCEPTIONS_HPP

#include <exception>
#include <string>
#include <iostream>

template <typename T> class ArcadeException;
template <typename U> std::ostream& operator<<(std::ostream& os, const ArcadeException<U>& ex);

template <typename T>
class ArcadeException : public std::exception {
protected:
    std::string message;
    T errorData;  // de ex: -> token , sau alte exceptii daca este apartul blocat in curs de reparatii
public:
    ArcadeException(const std::string& msg, T data) : message(msg), errorData(data) {}
    
    const char* what() const noexcept override {
        return message.c_str(); //ptr la arr
    }
        T getErrorData() const { 
        return errorData; 
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const ArcadeException<U>& ex);
};

template <typename U>
std::ostream& operator<<(std::ostream& os, const ArcadeException<U>& ex) {
    os << ex.what() << " | [Date interne eroare: " << ex.errorData << "]";
    return os;
}

class InsufficientTokensException : public ArcadeException<int> {
public:
    explicit InsufficientTokensException(const std::string& msg, int missingTokens) 
        : ArcadeException<int>("[Token Error] " + msg, missingTokens) {}
};

class MachineOccupiedException : public ArcadeException<std::string> {
public:
    explicit MachineOccupiedException(const std::string& msg, const std::string& machineName) 
        : ArcadeException<std::string>("[Availability Error] " + msg, machineName) {}
};

class InvalidConfigurationException : public ArcadeException<std::string> {
public:
    explicit InvalidConfigurationException(const std::string& msg, const std::string& configInfo) 
        : ArcadeException<std::string>("[Config Error] " + msg, configInfo) {}
};

class NeedsMaintenanceException : public ArcadeException<int> {
public:
    explicit NeedsMaintenanceException(const std::string& msg, int conditionDrop) 
        : ArcadeException<int>("[Maintenance] " + msg, conditionDrop) {}
};

#endif