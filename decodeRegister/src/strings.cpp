// strings.cpp
#include "strings.h"

namespace StringConstants {
    const std::string USAGE_MESSAGE = "Usage: ";
    const std::string RESET_PROMPT = "POReset Val (to reset enter '.') :";
    const std::string INPUT_PROMPT = "Enter Values (comma separated multiple) then press enter\nPress Enter on Blank Line To Exit\n";
    const std::string APPLYING_MESSAGE = "Applying ";
    const std::string NOW_AT_MESSAGE = "Now At: ";
    const std::string DECODE_HEADER = "--------Decodes to--------";
    const std::string START_BIT_PREFIX = "s:";
    const std::string END_BIT_PREFIX = "e:";
    const std::string BITMASK_PREFIX = "bm:";
    const std::string MATCH_NOT_FOUND = "Match Not Found";
    const std::string INVALID_NUMBER_FORMAT = "Invalid number format: ";
    const std::string INPUT_EMPTY = "Input string cannot be empty.";
    const std::string FAILED_TO_OPEN_FILE = "Failed to open file: ";
    const std::string ERROR_PARSING_BIT_RANGE = "Error parsing bit range: ";
    const std::string ERROR_LOADING_DB = "Error loading DB: ";
    const std::string UNEXPECTED_ERROR = "An unexpected error occurred: ";
    const std::string INVALID_NUMBER_FORMAT_IN = "Error: Invalid number format in '";
    const std::string FILE_DESCRIPTION="register descriptor JSON file";
    const std::string VERBOSE_DESCRIPTON="set verbosity level (0=none, 1=minimal, 2=default)";
    const std::string REG_DESCRIPTION="Register initial value";
    const std::string HELP_OPTION = "help,h";
    const std::string FILE_OPTION = "file,f";
    const std::string REG_OPTION = "reg,r";
    const std::string VERBOSE_OPTION = "verbose,v";
    const std::string ERROR_PASSING_VERBOSE = "Error: Invalid verbosity level. Use 0, 1 or 2(Default).\n";
    const std::string HELP_DESCRIPTION = "produce help message";
    const std::string ERROR_NO_FLAGS_ARRAY = "Error: JSON file must contain a non-empty 'flags' array.";
    const std::string ERROR_NO_DATA_ENTRIES = "Error: At least one 'flags' entry must contain a non-empty 'data' array.";
    const std::string ERROR_BIT_COUNT = "Error: Total bit count in JSON file is not 32. Found: ";

}
