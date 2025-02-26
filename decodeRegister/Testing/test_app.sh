#!/bin/bash
PROJECT_PATH="$1"
BUILD_CONFIG="$2"
PROJECT_NAME="$3"

echo "$PROJECT_PATH/$BUILD_CONFIG/$PROJECT_NAME";

# Configuration
APP_NAME="$PROJECT_PATH/$BUILD_CONFIG/$PROJECT_NAME" # Replace with your application's executable name
TEST_DIR="$PROJECT_PATH/Testing"      # Directory for test JSON files
OUTPUT_DIR="./test_output"  # Directory to store output files
EXPECTED_DIR="./expected_output" # Directory containing expected output files

# Create output directory if it doesn't exist
mkdir -p "$OUTPUT_DIR"
# If output directory exists remove any existing out files
rm -f "$OUTPUT_DIR/*.out"

run_test() {
  local test_name="$1"
  local args="$2"
  local expected_file="$3"
  local output_file="$OUTPUT_DIR/$test_name.out"

  echo "Running test: $test_name"
  echo "	--APP: $APP_NAME ARGS: $args"

  "$APP_NAME" $args > "$output_file" 2>&1  # Redirect stdout and stderr

  if [ -f "$expected_file" ]; then
    diff "$output_file" "$expected_file"
    if [ $? -eq 0 ]; then
      echo "  Test $test_name passed!"
    else
      echo "  Test $test_name failed! Differences found."
    fi
  else
    echo "  WARNING: Expected output file '$expected_file' not found. Test '$test_name' output was generated to '$output_file'."
  fi

  echo "------------------------"
}

# Function to run a test with interactive input
run_interactive_test() {
  local test_name="$1"
  local args="$2"
  local input="$3"
  local expected_file="$4"
  local output_file="$OUTPUT_DIR/$test_name.out"

  echo "Running interactive test: $test_name"
  echo "	--APP: $APP_NAME ARGS: $args"

  echo -e "$input" | "$APP_NAME" $args > "$output_file" 2>&1

  if [ -f "$expected_file" ]; then
    diff "$output_file" "$expected_file"
    if [ $? -eq 0 ]; then
      echo "  Test $test_name passed!"
    else
      echo "  Test $test_name failed! Differences found."
    fi
  else
    echo "  WARNING: Expected output file '$expected_file' not found. Test '$test_name' output was generated to '$output_file'."
  fi

  echo "------------------------"
}

# Test Cases (adjust based on your app's functionality)
# Example test: help message
run_test "help_test" "-h" "$EXPECTED_DIR/help.txt"

# Example test: valid JSON file, then exit with empty input
run_interactive_test "valid_json" "-f $TEST_DIR/valid_register.json" "" "$EXPECTED_DIR/valid_json.txt"

# Example test: valid JSON file, then set register value
run_interactive_test "valid_json_set_register" "-f $TEST_DIR/valid_register.json" "0x1234" "$EXPECTED_DIR/valid_json_set_register.txt"

# Example test: invalid JSON file
run_test "invalid_json" "-f $TEST_DIR/invalid_register.json" "$EXPECTED_DIR/invalid_json.txt"

# Add more test cases as needed...

echo "Testing complete."

exit 1
# Cleanup (optional): Remove output files
# rm -rf "$OUTPUT_DIR"