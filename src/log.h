#ifndef LOG_H
#define LOG_H

#include <stdexcept>
#include <cstring>
#include <source_location>

void log_fatal(std::exception&& error, const std::source_location& location = std::source_location::current());
void log_error(std::exception&& error, const std::source_location& location = std::source_location::current());
void log_warn(std::string&& text, const std::source_location& location = std::source_location::current());
void log_info(std::string&& text, const std::source_location& location = std::source_location::current());
void log_verbose(std::string&& text, const std::source_location& location = std::source_location::current());

#endif
