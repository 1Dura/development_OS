/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Standard library for tests only */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _MSC_VER
#define ECO_CDECL __cdecl
#else
#define ECO_CDECL
#endif

/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"

static int ECO_CDECL cmp_int32(const void* a, const void* b) {
    int32_t lhs = *((const int32_t*)a);
    int32_t rhs = *((const int32_t*)b);
    if (lhs < rhs) {
        return -1;
    }
    if (lhs > rhs) {
        return 1;
    }
    return 0;
}

static int ECO_CDECL cmp_int8(const void* a, const void* b) {
    int32_t lhs = (int32_t)(*((const int8_t*)a));
    int32_t rhs = (int32_t)(*((const int8_t*)b));
    if (lhs < rhs) {
        return -1;
    }
    if (lhs > rhs) {
        return 1;
    }
    return 0;
}

static int ECO_CDECL cmp_float(const void* a, const void* b) {
    float_t lhs = *((const float_t*)a);
    float_t rhs = *((const float_t*)b);
    if (lhs < rhs) {
        return -1;
    }
    if (lhs > rhs) {
        return 1;
    }
    return 0;
}

static int ECO_CDECL cmp_double(const void* a, const void* b) {
    double_t lhs = *((const double_t*)a);
    double_t rhs = *((const double_t*)b);
    if (lhs < rhs) {
        return -1;
    }
    if (lhs > rhs) {
        return 1;
    }
    return 0;
}

static int check_int32_equal(const int32_t* a, const int32_t* b, uint32_t count) {
    uint32_t i = 0;
    for (i = 0; i < count; ++i) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

static int check_int8_equal(const int8_t* a, const int8_t* b, uint32_t count) {
    uint32_t i = 0;
    for (i = 0; i < count; ++i) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

static int check_float_equal(const float_t* a, const float_t* b, uint32_t count) {
    uint32_t i = 0;
    for (i = 0; i < count; ++i) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

static int check_double_equal(const double_t* a, const double_t* b, uint32_t count) {
    uint32_t i = 0;
    for (i = 0; i < count; ++i) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

static int run_case_int32(IEcoLab1* pIEcoLab1, uint32_t count) {
    int16_t result = 0;
    int32_t* dataMine = 0;
    int32_t* dataQsort = 0;
    uint32_t i = 0;
    clock_t t0 = 0;
    clock_t t1 = 0;
    double_t myTime = 0.0;
    double_t qsortTime = 0.0;

    dataMine = (int32_t*)malloc(sizeof(int32_t) * count);
    dataQsort = (int32_t*)malloc(sizeof(int32_t) * count);
    if (dataMine == 0 || dataQsort == 0) {
        free(dataMine);
        free(dataQsort);
        return -1;
    }

    for (i = 0; i < count; ++i) {
        dataMine[i] = (int32_t)(rand() % 200001) - 100000;
        dataQsort[i] = dataMine[i];
    }

    t0 = clock();
    result = pIEcoLab1->pVTbl->CountingSort(pIEcoLab1, dataMine, count, ECO_LAB1_SORT_INT32);
    t1 = clock();
    myTime = (double_t)(t1 - t0) / (double_t)CLOCKS_PER_SEC;

    t0 = clock();
    qsort(dataQsort, count, sizeof(int32_t), cmp_int32);
    t1 = clock();
    qsortTime = (double_t)(t1 - t0) / (double_t)CLOCKS_PER_SEC;

    if (result != 0 || !check_int32_equal(dataMine, dataQsort, count)) {
        printf("[int32 ] n=%u : FAIL\n", (unsigned int)count);
        free(dataMine);
        free(dataQsort);
        return -1;
    }

    printf("[int32 ] n=%u : counting=%.6f s, qsort=%.6f s\n", (unsigned int)count, myTime, qsortTime);
    free(dataMine);
    free(dataQsort);
    return 0;
}

static int run_case_int8(IEcoLab1* pIEcoLab1, uint32_t count) {
    int16_t result = 0;
    int8_t* dataMine = 0;
    int8_t* dataQsort = 0;
    uint32_t i = 0;
    clock_t t0 = 0;
    clock_t t1 = 0;
    double_t myTime = 0.0;
    double_t qsortTime = 0.0;

    dataMine = (int8_t*)malloc(sizeof(int8_t) * count);
    dataQsort = (int8_t*)malloc(sizeof(int8_t) * count);
    if (dataMine == 0 || dataQsort == 0) {
        free(dataMine);
        free(dataQsort);
        return -1;
    }

    for (i = 0; i < count; ++i) {
        dataMine[i] = (int8_t)((rand() % 255) - 128);
        dataQsort[i] = dataMine[i];
    }

    t0 = clock();
    result = pIEcoLab1->pVTbl->CountingSort(pIEcoLab1, dataMine, count, ECO_LAB1_SORT_CHAR);
    t1 = clock();
    myTime = (double_t)(t1 - t0) / (double_t)CLOCKS_PER_SEC;

    t0 = clock();
    qsort(dataQsort, count, sizeof(int8_t), cmp_int8);
    t1 = clock();
    qsortTime = (double_t)(t1 - t0) / (double_t)CLOCKS_PER_SEC;

    if (result != 0 || !check_int8_equal(dataMine, dataQsort, count)) {
        printf("[char  ] n=%u : FAIL\n", (unsigned int)count);
        free(dataMine);
        free(dataQsort);
        return -1;
    }

    printf("[char  ] n=%u : counting=%.6f s, qsort=%.6f s\n", (unsigned int)count, myTime, qsortTime);
    free(dataMine);
    free(dataQsort);
    return 0;
}

static int run_case_float(IEcoLab1* pIEcoLab1, uint32_t count) {
    int16_t result = 0;
    float_t* dataMine = 0;
    float_t* dataQsort = 0;
    uint32_t i = 0;
    clock_t t0 = 0;
    clock_t t1 = 0;
    double_t myTime = 0.0;
    double_t qsortTime = 0.0;

    dataMine = (float_t*)malloc(sizeof(float_t) * count);
    dataQsort = (float_t*)malloc(sizeof(float_t) * count);
    if (dataMine == 0 || dataQsort == 0) {
        free(dataMine);
        free(dataQsort);
        return -1;
    }

    for (i = 0; i < count; ++i) {
        dataMine[i] = (float_t)((rand() % 200001) - 100000) / 10.0f;
        dataQsort[i] = dataMine[i];
    }

    t0 = clock();
    result = pIEcoLab1->pVTbl->CountingSort(pIEcoLab1, dataMine, count, ECO_LAB1_SORT_FLOAT);
    t1 = clock();
    myTime = (double_t)(t1 - t0) / (double_t)CLOCKS_PER_SEC;

    t0 = clock();
    qsort(dataQsort, count, sizeof(float_t), cmp_float);
    t1 = clock();
    qsortTime = (double_t)(t1 - t0) / (double_t)CLOCKS_PER_SEC;

    if (result != 0 || !check_float_equal(dataMine, dataQsort, count)) {
        printf("[float ] n=%u : FAIL\n", (unsigned int)count);
        free(dataMine);
        free(dataQsort);
        return -1;
    }

    printf("[float ] n=%u : counting=%.6f s, qsort=%.6f s\n", (unsigned int)count, myTime, qsortTime);
    free(dataMine);
    free(dataQsort);
    return 0;
}

static int run_case_double(IEcoLab1* pIEcoLab1, uint32_t count) {
    int16_t result = 0;
    double_t* dataMine = 0;
    double_t* dataQsort = 0;
    uint32_t i = 0;
    clock_t t0 = 0;
    clock_t t1 = 0;
    double_t myTime = 0.0;
    double_t qsortTime = 0.0;

    dataMine = (double_t*)malloc(sizeof(double_t) * count);
    dataQsort = (double_t*)malloc(sizeof(double_t) * count);
    if (dataMine == 0 || dataQsort == 0) {
        free(dataMine);
        free(dataQsort);
        return -1;
    }

    for (i = 0; i < count; ++i) {
        dataMine[i] = (double_t)((rand() % 2000001) - 1000000) / 100.0;
        dataQsort[i] = dataMine[i];
    }

    t0 = clock();
    result = pIEcoLab1->pVTbl->CountingSort(pIEcoLab1, dataMine, count, ECO_LAB1_SORT_DOUBLE);
    t1 = clock();
    myTime = (double_t)(t1 - t0) / (double_t)CLOCKS_PER_SEC;

    t0 = clock();
    qsort(dataQsort, count, sizeof(double_t), cmp_double);
    t1 = clock();
    qsortTime = (double_t)(t1 - t0) / (double_t)CLOCKS_PER_SEC;

    if (result != 0 || !check_double_equal(dataMine, dataQsort, count)) {
        printf("[double] n=%u : FAIL\n", (unsigned int)count);
        free(dataMine);
        free(dataQsort);
        return -1;
    }

    printf("[double] n=%u : counting=%.6f s, qsort=%.6f s\n", (unsigned int)count, myTime, qsortTime);
    free(dataMine);
    free(dataQsort);
    return 0;
}

static int run_all_benchmarks(IEcoLab1* pIEcoLab1) {
    uint32_t sizes[6];
    uint32_t i = 0;

    sizes[0] = 1000U;
    sizes[1] = 10000U;
    sizes[2] = 50000U;
    sizes[3] = 100000U;
    sizes[4] = 250000U;
    sizes[5] = 500000U;

    printf("=== EcoLab1 Counting Sort vs qsort ===\n");
    srand(12345U);

    for (i = 0; i < 6U; ++i) {
        if (run_case_int32(pIEcoLab1, sizes[i]) != 0) {
            return -1;
        }
        if (run_case_int8(pIEcoLab1, sizes[i]) != 0) {
            return -1;
        }
        if (run_case_float(pIEcoLab1, sizes[i]) != 0) {
            return -1;
        }
        if (run_case_double(pIEcoLab1, sizes[i]) != 0) {
            return -1;
        }
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }


    result = run_all_benchmarks(pIEcoLab1);

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

