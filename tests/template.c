#include "../Unity/unity.h"  // Unity testing framework header
#include "capture.h"         // Helpers to capture stdout/stderr output
#include <stdlib.h>          // For exit()

// This function runs before each test
void setUp(void)
{
    // Optional: initialize variables, allocate memory, etc.
}

// This function runs after each test
void tearDown(void)
{
    // Optional: free resources, reset states, etc.
}

// Sample test function demonstrating how to capture and check printed output
void test_sample(void)
{
    char *res;

    // Start capturing stdout, returns -1 on failure
    int capture = start_capture_stdout();
    if (capture == -1)
        exit(12);  // Exit if capture fails

    // Print the string that will be captured
    printf("We are cooking \n");

    // Stop capturing stdout and get captured string
    res = close_capture_stdout();

    // Assert captured output matches expected string
    TEST_ASSERT_EQUAL_STRING("We are cooking \n", res);
}

// Main function to run Unity tests
int main(void)
{
    UNITY_BEGIN();            // Start Unity test session
    RUN_TEST(test_sample);    // Run the sample test
    return UNITY_END();       // End Unity session and return result
}
