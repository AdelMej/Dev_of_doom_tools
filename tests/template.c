#include "../Unity/unity.h"
#include "capture.h"
#include <stdlib.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_sample(void)
{
	char * res;
	int capture = start_capture_stdout();
	if (capture == -1)
		exit(12);

	printf("We are cooking \n");

	res = close_capture_stdout();
	TEST_ASSERT_EQUAL_STRING("We are cooking \n", res);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_sample);
    return UNITY_END();
}
