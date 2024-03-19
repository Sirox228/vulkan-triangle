#include <iostream>
#include "log.h"

enum log_levels {
	LOG_LEVEL_NONE,
	LOG_LEVEL_WARN,
	LOG_LEVEL_INFO,
	LOG_LEVEL_VERBOSE
};

// by default we show only warnings
log_levels log_level = LOG_LEVEL_WARN;

void log_fatal(std::exception&& error, const std::source_location& location) {
	std::cerr << "FATAL ERROR: " << location.file_name() << " -> " << location.function_name() << " : " << error.what() << std::endl;
	throw error;
} 

void log_error(std::exception&& error, const std::source_location& location) {
	std::cerr << "ERROR: " << location.file_name() << " -> " << location.function_name() << " : " << error.what() << std::endl;
} 

void log_warn(std::string&& text, const std::source_location& location) {
	if (log_level >= LOG_LEVEL_WARN) {
		std::cout << "WARNING: " <<  location.file_name() << " -> " << location.function_name() << " : " << text << std::endl;
	}
}

void log_info(std::string&& text, const std::source_location& location) {
	if (log_level >= LOG_LEVEL_INFO) {
		std::cout << "INFO: " << location.file_name() << " -> " << location.function_name() << " : " << text << std::endl;
	}
}

void log_verbose(std::string&& text, const std::source_location& location) {
	if (log_level >= LOG_LEVEL_VERBOSE) {
		std::cout << "VERBOSE: " << location.file_name() << " -> " << location.function_name() << " : " << text << std::endl;
	}
}