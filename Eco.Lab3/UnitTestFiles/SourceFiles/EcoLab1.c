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


/* Eco OS */
#include "IEcoBase1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IEcoLab1EventFirst.h"
#include "IdEcoLab1.h"
#include "IdEcoList1.h"
#include "CEcoLab1Sink.h"
#include "CEcoLab1SinkSecond.h"
#include "IEcoConnectionPointContainer.h"

#include "FactoryFunctions.h"
#include "TestCases.h"

#include <stdio.h>


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
    
    IEcoSystem1* pISys = 0;             /* Указатель на системный интерфейс */
    IEcoInterfaceBus1* pIBus = 0;       /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoMemoryAllocator1* pIMem = 0;    /* Указатель на интерфейс работы с памятью */
    
    char_t* name = 0;
    char_t* copyName = 0;
    
    
    IEcoLab1* pIEcoLab1_1 = 0;                    /* Указатель на тестируемый интерфейс */
    IEcoConnectionPoint* pICP_1_First = 0;              /* Указатель на интерфейс точки подключения */
    IEcoConnectionPoint* pICP_1_Second = 0;              /* Указатель на интерфейс точки подключения */

    IEcoLab1* pIEcoLab1_2 = 0;                    /* Указатель на тестируемый интерфейс */
    IEcoConnectionPoint* pICP_2_First = 0;              /* Указатель на интерфейс точки подключения */
    IEcoConnectionPoint* pICP_2_Second = 0;              /* Указатель на интерфейс точки подключения */

    IEcoLab1EventFirst* pIEcoLab1Sink_1 = 0;          /* Указатель на обратный интерфейс */
    IEcoLab1EventSecond* pIEcoLab1Sink_2 = 0;          /* Указатель на обратный интерфейс */
    
    uint32_t cAdvise1_1 = 0;                       /*id подключения к конкретному connectionPOint*/
    uint32_t cAdvise1_2 = 0;                       /*id подключения к конкретному connectionPOint*/
    
    uint32_t cAdvise2_1 = 0;                       /*id подключения к конкретному connectionPOint*/
    uint32_t cAdvise2_2 = 0;                       /*id подключения к конкретному connectionPOint*/

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
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoList1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_53884AFC93C448ECAA929C8D3A562281);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif

//получние стандартных интерфейсов
{
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }
} 
    CreateServerComponent(pIBus, &pIEcoLab1_1, &pICP_1_First, &pICP_1_Second);
    ConnectClientSinkFirst(pIMem, pICP_1_First, &pIEcoLab1Sink_1, &cAdvise1_1);
    ConnectClientSinkSecond(pIMem, pICP_1_Second, &pIEcoLab1Sink_2, &cAdvise2_1);

    CreateServerComponent(pIBus, &pIEcoLab1_2, &pICP_2_First, &pICP_2_Second);
    ConnectClientSinkFirst(pIMem, pICP_2_First, &pIEcoLab1Sink_1, &cAdvise1_2);
    ConnectClientSinkSecond(pIMem, pICP_2_Second, &pIEcoLab1Sink_2, &cAdvise2_2);

	test_integer_array_first(pIEcoLab1_1);
	test_integer_array_second(pIEcoLab1_2);
	
    if (pIEcoLab1Sink_1 != 0) {
        /* Отключение */
        result = pICP_1_First->pVTbl->Unadvise(pICP_1_First, cAdvise1_1);
        result = pICP_2_First->pVTbl->Unadvise(pICP_2_First, cAdvise1_2);
        pIEcoLab1Sink_1->pVTbl->Release(pIEcoLab1Sink_1);
    }

    if (pIEcoLab1Sink_2 != 0) {
        /* Отключение */
        result = pICP_1_Second->pVTbl->Unadvise(pICP_1_Second, cAdvise2_1);
        result = pICP_2_Second->pVTbl->Unadvise(pICP_2_Second, cAdvise2_2);
        pIEcoLab1Sink_2->pVTbl->Release(pIEcoLab1Sink_2);
    }

    pICP_1_Second->pVTbl->Release(pICP_1_Second);
    pICP_1_First->pVTbl->Release(pICP_1_First);
    pICP_2_Second->pVTbl->Release(pICP_2_Second);
    pICP_2_First->pVTbl->Release(pICP_2_First);
Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1_1 != 0) {
        pIEcoLab1_1->pVTbl->Release(pIEcoLab1_1);
    }

    if (pIEcoLab1_2 != 0) {
        pIEcoLab1_2->pVTbl->Release(pIEcoLab1_2);
    }

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}
