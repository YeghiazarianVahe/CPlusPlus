#include "../include/Logger.hpp"

Logger::Logger(const std::string& filename)
    : file_{ std::fopen(filename.c_str(), "a"), &std::fclose }
{
    if (!file_) {
        throw std::runtime_error("Logger: cannot open file " + filename);
    }
}

void Logger::log(const std::string& msg) {
    std::fprintf(file_.get(), "%s\n", msg.c_str());
}

