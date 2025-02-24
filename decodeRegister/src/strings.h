// strings.h
#ifndef STRINGS_H
#define STRINGS_H

#include <string>

namespace StringConstants {
    // String constants used throughout the application.
    extern const std::string USAGE_MESSAGE;          // Message displayed for incorrect command-line usage.
    extern const std::string RESET_PROMPT;           // Prompt to reset the current value.
    extern const std::string INPUT_PROMPT;           // Prompt for user input.
    extern const std::string APPLYING_MESSAGE;       // Message indicating an operation is being applied.
    extern const std::string NOW_AT_MESSAGE;         // Message showing the current value.
    extern const std::string DECODE_HEADER;          // Header for decoded output.
    extern const std::string START_BIT_PREFIX;       // Prefix for start bit in output.
    extern const std::string END_BIT_PREFIX;         // Prefix for end bit in output.
    extern const std::string BITMASK_PREFIX;         // Prefix for bitmask in output.
    extern const std::string MATCH_NOT_FOUND;        // Message when a bitmask match is not found.
    extern const std::string INVALID_NUMBER_FORMAT;  // Error message for invalid number format.
    extern const std::string INPUT_EMPTY;            // Error message for empty input.
    extern const std::string FAILED_TO_OPEN_FILE;     // Error message when file open fails.
    extern const std::string ERROR_PARSING_BIT_RANGE; // Error message when bit range parsing fails.
    extern const std::string ERROR_LOADING_DB;       // Error message when database loading fails.
    extern const std::string UNEXPECTED_ERROR;       // Error message for unexpected errors.
    extern const std::string INVALID_NUMBER_FORMAT_IN;// Error message for number format in token.
}

#endif // STRINGS_H
