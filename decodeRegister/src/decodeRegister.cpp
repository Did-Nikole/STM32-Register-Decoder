// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <regex>
#include <iomanip>
#include <nlohmann/json.hpp>
#include "strings.h" // Include the header with string constants

using json = nlohmann::json;

// TableEntry class to store bit range and value mappings.
class TableEntry {
public:
    int start = 0;       // Start bit of the range.
    int end = -1;        // End bit of the range.
    std::string desc;    // Description of the bit range.
    std::map<std::string, std::string> vals; // Map of bit patterns to descriptions.

    // Returns the description of the TableEntry.
    std::string toString() const {
        return desc;
    }

    // Finds a matching value for a given bit string.
    std::string findMatch(const std::string& bits) const {
        for (const auto& pair : vals) {
            if (matches(pair.first, bits)) {
                return pair.second;
            }
        }
        throw std::runtime_error(StringConstants::MATCH_NOT_FOUND);
    }

    // Checks if a bit pattern matches a given mask.
    static bool matches(const std::string& entry, const std::string& mask) {
        if (entry.length() != mask.length()) {
            return false;
        }
        for (size_t i = 0; i < entry.length(); ++i) {
            if (entry[i] != 'x' && entry[i] != mask[i]) {
                return false;
            }
        }
        return true;
    }

    // Extracts a bit value from a long long integer.
    static std::string getBitValue(long long val, int start, int size) {
        long long mask = (1LL << size) - 1;
        long long bit = (val >> start) & mask;
        std::bitset <32>bs(bit);
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(size) << bs.to_string().substr(32 - size);
        return ss.str();
    }

    // Returns the size of the bit range.
    int size() const {
        return (end - start) + 1;
    }

    // Checks if the TableEntry is valid (has values).
    bool isValid() const {
        return !vals.empty();
    }

    // Adds a bit pattern and description to the TableEntry.
    void addVals(const std::string& pattern, const std::string& desc) {
        vals[pattern] = desc;
    }

    // Sets the bit range and description for the TableEntry.
    void setBits(const std::string& startStr, const std::string& endStr, const std::string& desc) {
        try {
            end = std::stoi(endStr);
            start = startStr.empty() ? end : std::stoi(startStr);
            this->desc = desc;
        } catch (const std::invalid_argument& e) {
            std::cerr << StringConstants::ERROR_PARSING_BIT_RANGE << e.what() << std::endl;
        }
    }
};

// Converts a long long integer to a binary string with padding.
std::string longToBinaryStringWithPadding(long long number) {
    std::bitset <32>bs(number);
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(32) << bs.to_string();
    return ss.str();
}

// Parses a number string, handling different number formats (hex, octal, binary, decimal).
long long parseNumber(const std::string& input) {
    if (input.empty()) {
        throw std::invalid_argument(StringConstants::INPUT_EMPTY);
    }
    try {
        if (input.substr(0, 2) == "0x" || input.substr(0, 2) == "0X") {
            return std::stoll(input.substr(2), nullptr, 16);
        } else if (input.substr(0, 2) == "0o" || input.substr(0, 2) == "0O") {
            return std::stoll(input.substr(2), nullptr, 8);
        } else if (input.substr(0, 2) == "0b" || input.substr(0, 2) == "0B") {
            return std::stoll(input.substr(2), nullptr, 2);
        } else {
            return std::stoll(input);
        }
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument(StringConstants::INVALID_NUMBER_FORMAT + input);
    }
}


// Processes a number string, handling bitwise operations and parsing.
long long processNumber(const std::string& inputStr, long long storedValue) {
    try {
        if (inputStr[0] == '&') {
            long long number = parseNumber(inputStr.substr(1));
            return storedValue & number;
        } else if (inputStr[0] == '|') {
            long long number = parseNumber(inputStr.substr(1));
            return storedValue | number;
        } else {
            return parseNumber(inputStr);
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Invalid number format in '" << inputStr << "'" << std::endl;
        return storedValue;
    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
        return storedValue;
    }
}

int main(int argc, char* argv[]) {
    // Check for correct command-line usage.
    if (argc != 2) {
        std::cerr << StringConstants::USAGE_MESSAGE << argv[0] << " <file_name.json>" << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    long long resetVal = 0;
    std::vector<TableEntry> entries;
    std::regex bitMatch(R"(Bits?\s([0-9]{1,2})(?::([0-9]{1,2}))?\s(.*))");
    std::regex valMatch(R"(([01xX]{0,32}):\s(.*))");

    // Load the database from the JSON file.
    auto loadDB = [&](const std::string& file) -> long long {
        long long por = -1;
        try {
            std::ifstream ifs(file);
            // Check if the file opened successfully.
            if (!ifs.is_open()) {
                throw std::runtime_error(StringConstants::FAILED_TO_OPEN_FILE + file);
            }
            json j = json::parse(ifs);
            if (j.contains("por")) {
                por = parseNumber(j["por"].get<std::string>());
            }
            if (j.contains("flags")) {
                for (const auto& je : j["flags"]) {
                    TableEntry te;
                    std::string bitStr = je["bit"].get<std::string>();
                    std::smatch match;
                    if (std::regex_match(bitStr, match, bitMatch)) {
                        te.setBits(match[2].str(), match[1].str(), match[3].str());
                    }
                    if (je.contains("data")) {
                        for (const auto& s : je["data"]) {
                            std::string valStr = s.get<std::string>();
                            if (std::regex_match(valStr, match, valMatch)) {
                                te.addVals(match[1].str(), match[2].str());
                            }
                        }
                    }
                    if (te.isValid()) {
                        entries.push_back(te);
                    }
                }
            }
        } catch (const std::exception& e) {
            std::cerr << StringConstants::ERROR_LOADING_DB << e.what() << std::endl;
        }
        return por;
    };

    resetVal = loadDB(filename);
    long long currentVal = resetVal;

    std::string line;
    // Main loop for user interaction.
    while (true) {
        std::cout << StringConstants::RESET_PROMPT << longToBinaryStringWithPadding(resetVal) << std::endl;
        std::cout << StringConstants::INPUT_PROMPT << std::endl;
        std::getline(std::cin, line);
        // Reset the current value.
        if (line[0] == '.') {
            currentVal = resetVal;
        } else if (line.empty()) {
            break;
        } else {
            std::stringstream ss(line);
            std::string token;
            while (std::getline(ss, token, ',')) {
                std::cout << StringConstants::APPLYING_MESSAGE << token << "\t";
                currentVal = processNumber(token, currentVal);
                std::cout << StringConstants::NOW_AT_MESSAGE << longToBinaryStringWithPadding(currentVal) << "\t" << std::endl;
                std::cout << StringConstants::DECODE_HEADER << std::endl;
                std::stringstream decodeSs;
                // Decode the current value using the loaded TableEntries.
                for (const auto& te : entries) {
                    std::string mask = TableEntry::getBitValue(currentVal, te.start, te.size());
                    decodeSs << te.toString() << std::endl;
                    decodeSs << StringConstants::START_BIT_PREFIX << te.start << "\t" << StringConstants::END_BIT_PREFIX << te.end << "\t" << StringConstants::BITMASK_PREFIX << std::setw(16) << mask << "\t";
                    try {
                        decodeSs << te.findMatch(mask);
                    } catch (const std::exception& e) {
                        decodeSs << StringConstants::MATCH_NOT_FOUND;
                    }
                    decodeSs << std::endl;
                }
                std::cout << decodeSs.str();
            }
        }
    }
    return 0;
}
