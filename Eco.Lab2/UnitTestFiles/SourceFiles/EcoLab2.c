/*
 * EcoLab2 unit test entrypoint
 */

#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"

#include "IEcoLab1.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"

#include "IdEcoLab2.h"
#include "IdEcoLab1.h"
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"

static int16_t CheckInt32Sorted(const int32_t* data, const int32_t* expected, uint32_t count) {
    uint32_t i = 0;
    for (i = 0; i < count; ++i) {
        if (data[i] != expected[i]) {
            return -1;
        }
    }
    return 0;
}

int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = ERR_ECO_POINTER;

    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;

    IEcoCalculatorX* pICalcX = 0;
    IEcoCalculatorY* pICalcY = 0;
    IEcoLab1* pIEcoLab1 = 0;

    IEcoCalculatorX* pICalcX_FromY = 0;
    IEcoCalculatorY* pICalcY_FromX = 0;
    IEcoLab1* pILab1_FromX = 0;
    IEcoLab1* pILab1_FromY = 0;
    IEcoCalculatorX* pICalcX_FromLab1 = 0;
    IEcoCalculatorY* pICalcY_FromLab1 = 0;
    IEcoUnknown* pIUnk_FromX = 0;
    IEcoUnknown* pIUnk_FromY = 0;
    IEcoUnknown* pIUnk_FromLab1 = 0;

    if (pIUnk == 0) {
        return ERR_ECO_POINTER;
    }

    result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void**)&pISys);
    if (result != 0 || pISys == 0) {
        goto Release;
    }

    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void**)&pIBus);
    if (result != 0 || pIBus == 0) {
        goto Release;
    }

#ifdef ECO_LIB
    /* Register component under test and dependencies used by EcoLab2 */
    result = pIBus->pVTbl->RegisterComponent(
        pIBus,
        &CID_EcoLab2,
        (IEcoUnknown*)GetIEcoComponentFactoryPtr_F87CD666E6314B33B2B4508FDCD4BE15);
    if (result != 0) {
        goto Release;
    }
    printf("EcoLab2: %s\n", result == 0 ? "OK" : "FAIL");

    result = pIBus->pVTbl->RegisterComponent(
        pIBus,
        &CID_EcoLab1,
        (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0) {
        goto Release;
    }
    printf("EcoLab1: %s\n", result == 0 ? "OK" : "FAIL");

    result = pIBus->pVTbl->RegisterComponent(
        pIBus,
        &CID_EcoCalculatorA,
        (IEcoUnknown*)GetIEcoComponentFactoryPtr_4828F6552E4540E78121EBD220DC360E);
    if (result != 0) {
        goto Release;
    }
    printf("EcoCalculatorA: %s\n", result == 0 ? "OK" : "FAIL");

    // result = pIBus->pVTbl->RegisterComponent(
    //     pIBus,
    //     &CID_EcoCalculatorB,
    //     (IEcoUnknown*)GetIEcoComponentFactoryPtr_AE202E543CE54550899603BD70C62565);
    // if (result != 0) {
    //     goto Release;
    // }
    // printf("EcoCalculatorB: %s\n", result == 0 ? "OK" : "FAIL");

    // result = pIBus->pVTbl->RegisterComponent(
    //     pIBus,
    //     &CID_EcoCalculatorD,
    //     (IEcoUnknown*)GetIEcoComponentFactoryPtr_3A8E44677E82475CB4A3719ED8397E61);
    // if (result != 0) {
    //     goto Release;
    // }
    // printf("EcoCalculatorD: %s\n", result == 0 ? "OK" : "FAIL");

    result = pIBus->pVTbl->RegisterComponent(
        pIBus,
        &CID_EcoCalculatorE,
        (IEcoUnknown*)GetIEcoComponentFactoryPtr_872FEF1DE3314B87AD44D1E7C232C2F0);
    if (result != 0) {
        goto Release;
    }
    printf("EcoCalculatorE: %s\n", result == 0 ? "OK" : "FAIL");
#endif

    /* 1) Create EcoLab2 and obtain all primary interfaces */
    result = pIBus->pVTbl->QueryComponent(
        pIBus,
        &CID_EcoLab2,
        0,
        &IID_IEcoCalculatorX,
        (void**)&pICalcX);
    printf("Get IEcoCalculatorX: %s\n", (result == 0 && pICalcX) ? "OK" : "FAIL");
    if (result != 0 || pICalcX == 0) {
        goto Release;
    }
    

    result = pIBus->pVTbl->QueryComponent(
        pIBus,
        &CID_EcoLab2,
        0,
        &IID_IEcoCalculatorY,
        (void**)&pICalcY);
    printf("Get IEcoCalculatorY: %s\n", (result == 0 && pICalcY) ? "OK" : "FAIL");
    if (result != 0 || pICalcY == 0) {
        goto Release;
    }
    
    result = pIBus->pVTbl->QueryComponent(
        pIBus,
        &CID_EcoLab2,
        0,
        &IID_IEcoLab1,
        (void**)&pIEcoLab1);
    printf("Get IEcoLab1 (aggregated): %s\n", (result == 0 && pIEcoLab1) ? "OK" : "FAIL");
    if (result != 0 || pIEcoLab1 == 0) {
        goto Release;
    }
   

    printf("\n--- QueryInterface checks ---\n");

    result = pICalcX->pVTbl->QueryInterface(pICalcX, &IID_IEcoCalculatorY, (void**)&pICalcY_FromX);
    printf("X -> Y: %s\n", (result == 0 && pICalcY_FromX) ? "OK" : "FAIL");

    result = pICalcX->pVTbl->QueryInterface(pICalcX, &IID_IEcoLab1, (void**)&pILab1_FromX);
    printf("X -> Lab1: %s\n", (result == 0 && pILab1_FromX) ? "OK" : "FAIL");

    result = pICalcY->pVTbl->QueryInterface(pICalcY, &IID_IEcoCalculatorX, (void**)&pICalcX_FromY);
    printf("Y -> X: %s\n", (result == 0 && pICalcX_FromY) ? "OK" : "FAIL");

    result = pICalcY->pVTbl->QueryInterface(pICalcY, &IID_IEcoLab1, (void**)&pILab1_FromY);
    printf("Y -> Lab1: %s\n", (result == 0 && pILab1_FromY) ? "OK" : "FAIL");

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pICalcX_FromLab1);
    printf("Lab1 -> X: %s\n", (result == 0 && pICalcX_FromLab1) ? "OK" : "FAIL");

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&pICalcY_FromLab1);
    printf("Lab1 -> Y: %s\n", (result == 0 && pICalcY_FromLab1) ? "OK" : "FAIL");

    printf("\n--- Smoke test ---\n");

    if (pICalcX) {
        int32_t sum = pICalcX->pVTbl->Addition(pICalcX, 2, 3);
        printf("Addition(2,3) = %d\n", sum);
    }

    if (pICalcY) {
        int32_t mul = pICalcY->pVTbl->Multiplication(pICalcY, 4, 5);
        printf("Multiplication(4,5) = %d\n", mul);
    }

    if (pIEcoLab1) {
        int32_t data[] = { 5, -7, 0, 12, 5, -1, 3, -7 };
        int32_t expected[] = { -7, -7, -1, 0, 3, 5, 5, 12 };
        result = pIEcoLab1->pVTbl->CountingSort(
            pIEcoLab1,
            data,
            (uint32_t)(sizeof(data) / sizeof(data[0])),
            ECO_LAB1_SORT_INT32);
        if (result == 0) {
            result = CheckInt32Sorted(data, expected, (uint32_t)(sizeof(data) / sizeof(data[0])));
        }
        printf("CountingSort(int32): %s\n", result == 0 ? "OK" : "FAIL");
        if (result != 0) {
            goto Release;
        }
    }

    printf("\n=== TEST FINISHED ===\n");
    result = ERR_ECO_SUCCESES;

Release:
    if (pIUnk_FromLab1 != 0) {
        pIUnk_FromLab1->pVTbl->Release(pIUnk_FromLab1);
    }
    if (pIUnk_FromY != 0) {
        pIUnk_FromY->pVTbl->Release(pIUnk_FromY);
    }
    if (pIUnk_FromX != 0) {
        pIUnk_FromX->pVTbl->Release(pIUnk_FromX);
    }

    if (pICalcY_FromLab1 != 0) {
        pICalcY_FromLab1->pVTbl->Release(pICalcY_FromLab1);
    }
    if (pICalcX_FromLab1 != 0) {
        pICalcX_FromLab1->pVTbl->Release(pICalcX_FromLab1);
    }

    if (pILab1_FromY != 0) {
        pILab1_FromY->pVTbl->Release(pILab1_FromY);
    }
    if (pILab1_FromX != 0) {
        pILab1_FromX->pVTbl->Release(pILab1_FromX);
    }

    if (pICalcX_FromY != 0) {
        pICalcX_FromY->pVTbl->Release(pICalcX_FromY);
    }
    if (pICalcY_FromX != 0) {
        pICalcY_FromX->pVTbl->Release(pICalcY_FromX);
    }

    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }
    if (pICalcY != 0) {
        pICalcY->pVTbl->Release(pICalcY);
    }
    if (pICalcX != 0) {
        pICalcX->pVTbl->Release(pICalcX);
    }

    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}
