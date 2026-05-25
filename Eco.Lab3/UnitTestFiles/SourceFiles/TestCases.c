#include "TestCases.h"
#include "IEcoBase1.h"

static int16_t check_int_array(const int32_t* data, const int32_t* expected, uint32_t count) {
    uint32_t i = 0;
    for (i = 0; i < count; ++i) {
        if (data[i] != expected[i]) {
            return -1;
        }
    }
    return 0;
}

void test_integer_array_first(IEcoLab1* pIcomp) {
    int32_t arr[] = { 5, -7, 0, 12, 5, -1, 3, -7 };
    int32_t expected[] = { -7, -7, -1, 0, 3, 5, 5, 12 };
    uint32_t nmemb = sizeof(arr) / sizeof(arr[0]);
    int16_t result = -1;

    printf("\n=== TEST 1: CountingSort int32 ===\n");
    result = pIcomp->pVTbl->CountingSort(pIcomp, arr, nmemb, ECO_LAB1_SORT_INT32);
    printf("CountingSort result: %s\n",
        (result == 0 && check_int_array(arr, expected, nmemb) == 0) ? "OK" : "FAIL");
}

void test_integer_array_second(IEcoLab1* pIcomp) {
    int32_t arr[] = { 128, 2, 512, 16, -32, 4, 1, 256, 8, 64 };
    int32_t expected[] = { -32, 1, 2, 4, 8, 16, 64, 128, 256, 512 };
    uint32_t nmemb = sizeof(arr) / sizeof(arr[0]);
    int16_t result = -1;

    printf("\n=== TEST 2: CountingSort int32 ===\n");
    result = pIcomp->pVTbl->CountingSort(pIcomp, arr, nmemb, ECO_LAB1_SORT_INT32);
    printf("CountingSort result: %s\n",
        (result == 0 && check_int_array(arr, expected, nmemb) == 0) ? "OK" : "FAIL");
}
