#pragma once


#include <cstdio>      // std::FILE, std::fopen, std::fprintf, std::fclose
#include <memory>      // std::unique_ptr
#include <string>      // std::string
#include <stdexcept>   // std::runtime_error

//
// Logger wraps a FILE* in a std::unique_ptr with a custom deleter.
// When Logger goes out of scope, the file is automatically closed.
//
class Logger {
public:
    // Construct a Logger that appends to `filename`.
    // Throws std::runtime_error if fopen fails.
    explicit Logger(const std::string& filename);

    // Disable copy (cannot copy a unique_ptr)
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Enable move
    Logger(Logger&&) noexcept = default;
    Logger& operator=(Logger&&) noexcept = default;

    // Write `msg` (with a newline) to the log file.
    void log(const std::string& msg);

private:
    // Custom deleter type for FILE*
    using FilePtr = std::unique_ptr<std::FILE, int(*)(std::FILE*)>;

    FilePtr file_;
};


