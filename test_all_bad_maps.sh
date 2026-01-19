#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Directories
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BAD_MAPS_DIR="$SCRIPT_DIR/map/bad"
BINARY="$SCRIPT_DIR/cub3D"

# Test counters
TOTAL=0
PASSED=0
FAILED=0
LEAKED=0

# Check if binary exists
if [ ! -f "$BINARY" ]; then
    echo -e "${RED}Error: Binary not found at $BINARY${NC}"
    echo "Please build the project first with 'make'"
    exit 1
fi

echo -e "${YELLOW}========================================${NC}"
echo -e "${YELLOW}Testing all bad map files${NC}"
echo -e "${YELLOW}========================================${NC}\n"

# Test each .cub file in the bad directory
for map_file in "$BAD_MAPS_DIR"/*.cub; do
    if [ ! -f "$map_file" ]; then
        continue
    fi
    
    TOTAL=$((TOTAL + 1))
    map_name=$(basename "$map_file")
    
    echo -n "Testing: $map_name ... "
    
    # Run with valgrind and capture output
    VALGRIND_OUTPUT=$(valgrind --leak-check=full --show-leak-kinds=all --suppressions="$SCRIPT_DIR/mlx.supp" "$BINARY" "$map_file" 2>&1)
    
    # Check if there's an error message (should fail gracefully)
    if echo "$VALGRIND_OUTPUT" | grep -q "^Error"; then
        # Check for memory leaks
        if echo "$VALGRIND_OUTPUT" | grep -q "All heap blocks were freed"; then
            echo -e "${GREEN}PASS${NC} (no leaks)"
            PASSED=$((PASSED + 1))
        elif echo "$VALGRIND_OUTPUT" | grep -q "definitely lost: 0 bytes"; then
            echo -e "${GREEN}PASS${NC} (no leaks)"
            PASSED=$((PASSED + 1))
        else
            echo -e "${RED}FAIL${NC} (memory leak detected)"
            LEAKED=$((LEAKED + 1))
            # Show leak details
            echo "$VALGRIND_OUTPUT" | grep -A 5 "LEAK SUMMARY" | head -10
        fi
    else
        echo -e "${RED}FAIL${NC} (no error message)"
        FAILED=$((FAILED + 1))
    fi
done

# Test summary
echo -e "\n${YELLOW}========================================${NC}"
echo -e "${YELLOW}Test Summary${NC}"
echo -e "${YELLOW}========================================${NC}"
echo "Total tests:     $TOTAL"
echo -e "Passed:         ${GREEN}$PASSED${NC}"
echo -e "Memory leaks:   ${RED}$LEAKED${NC}"
echo -e "Other failures: ${RED}$FAILED${NC}"

# Exit code
if [ $LEAKED -eq 0 ] && [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "\n${RED}Some tests failed!${NC}"
    exit 1
fi
