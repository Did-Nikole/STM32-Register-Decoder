# Bit Decoder

A command-line tool for decoding bit patterns based on a JSON configuration file. This utility is particularly useful for embedded systems developers and anyone working with hardware registers where bit-level interpretation is crucial.

## Features

* **JSON Configuration:** Define bit ranges and their corresponding value mappings in a simple JSON file.
* **Flexible Number Parsing:** Supports hexadecimal (0x...), octal (0o...), binary (0b...), and decimal number formats.
* **Bitwise Operations:** Apply bitwise AND (&) and OR (|) operations to modify the current value.
* **Interactive Command-Line Interface:** Enter values and view decoded results in real-time.
* **Clear Output:** Displays the bit range, bitmask, and decoded value for each configured entry.

## Getting Started

### Prerequisites

* A C++ compiler (e.g., g++)
* CMake (optional, for build automation)
* nlohmann/json library (for JSON parsing)

### Installation

1.  **Clone the Repository:**

    ```bash
    git clone [repository_url]
    cd bit-decoder
    ```

2.  **Install nlohmann/json:**

    * If you're using a package manager like vcpkg or Conan, install it that way.
    * Otherwise, download the header-only library from [https://github.com/nlohmann/json](https://github.com/nlohmann/json) and include it in your project's include path.

3.  **Build the Project:**

    * **Manual Compilation:**

        ```bash
        g++ main.cpp strings.cpp -o bit-decoder -lnlohmann_json
        ```

    * **Using CMake (Recommended):**

        1.  Create a `CMakeLists.txt` file in the project root:

            ```cmake
            cmake_minimum_required(VERSION 3.10)
            project(BitDecoder)

            find_package(nlohmann_json REQUIRED)

            add_executable(bit-decoder main.cpp strings.cpp)
            target_link_libraries(bit-decoder nlohmann_json::nlohmann_json)
            ```

        2.  Run CMake:

            ```bash
            mkdir build
            cd build
            cmake ..
            make
            ```

4.  **Run the Application:**

    ```bash
    ./bit-decoder <your_config_file.json>
    ```

    Replace `<your_config_file.json>` with the path to your JSON configuration file.

## Usage

1.  **Create a JSON Configuration File:**

    Example `stm32f103xxx_clock.json`:

    ```json
    {
      "por": "0x00000000",
      "flags": [
        {
          "bit": "2:0 Clock Source",
          "data": [
            "000: HSI oscillator",
            "001: HSE oscillator",
            "010: PLL oscillator"
          ]
        },
        {
          "bit": "4 PLL enabled",
          "data": [
            "0: Disabled",
            "1: Enabled"
          ]
        }
      ]
    }
    ```

2.  **Run the Application:**

    ```bash
    ./bit-decoder stm32f103xxx_clock.json
    ```

3.  **Enter Values:**

    * Enter numbers in decimal, hexadecimal (0x...), octal (0o...), or binary (0b...) format.
    * Use comma-separated values to apply multiple operations at once.
    * Use `&` for bitwise AND and `|` for bitwise OR operations.
    * Enter `.` to reset the value to the power-on reset (POR) value.
    * Press Enter without input to exit.

    Example input: `0x05, &0x01, |0x10`

## JSON Configuration Format

* **`por` (optional):** The power-on reset value as a string.
* **`flags` (required):** An array of bit range definitions.
    * **`bit` (required):** A string defining the bit range and description (e.g., "Bits 2:0 Clock Source").
    * **`data` (required):** An array of value mappings in the format "bit_pattern: description" (e.g., "000: HSI oscillator").

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues.

## License

This project is licensed under the **GNU General Public License v2.0**. See the `[LICENSE](LICENCE)` file for details.

## Author

[Nikole Smith](https://github.com/Did-Nikole)
