/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab1.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLab1
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_QueryInterface(/* in */ IEcoLab1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoLab1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1_AddRef(/* in */ IEcoLab1Ptr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoLab1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1_Release(/* in */ IEcoLab1Ptr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab1((IEcoLab1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

static uint32_t CEcoLab1_GetItemSize(int16_t dataType) {
    switch (dataType) {
        case ECO_LAB1_SORT_CHAR:
            return sizeof(int8_t);
        case ECO_LAB1_SORT_INT32:
            return sizeof(int32_t);
        case ECO_LAB1_SORT_FLOAT:
            return sizeof(float_t);
        case ECO_LAB1_SORT_DOUBLE:
            return sizeof(double_t);
        default:
            return 0;
    }
}

static uint8_t CEcoLab1_GetKeyByte(const char_t* pItem, int16_t dataType, uint32_t pass) {
    uint32_t key32 = 0;
    uint64_t key64 = 0;
    uint32_t shift = pass * 8U;

    switch (dataType) {
        case ECO_LAB1_SORT_CHAR: {
            int8_t value = *((const int8_t*)pItem);
            key32 = (uint32_t)((uint8_t)value ^ 0x80U);
            return (uint8_t)key32;
        }
        case ECO_LAB1_SORT_INT32: {
            int32_t value = *((const int32_t*)pItem);
            key32 = ((uint32_t)value) ^ 0x80000000U;
            return (uint8_t)((key32 >> shift) & 0xFFU);
        }
        case ECO_LAB1_SORT_FLOAT: {
            union {
                float_t f;
                uint32_t u;
            } bits;
            bits.f = *((const float_t*)pItem);
            key32 = (bits.u & 0x80000000U) ? (~bits.u) : (bits.u ^ 0x80000000U);
            return (uint8_t)((key32 >> shift) & 0xFFU);
        }
        case ECO_LAB1_SORT_DOUBLE: {
            union {
                double_t d;
                uint64_t u;
            } bits;
            bits.d = *((const double_t*)pItem);
            key64 = (bits.u & 0x8000000000000000ULL) ? (~bits.u) : (bits.u ^ 0x8000000000000000ULL);
            return (uint8_t)((key64 >> shift) & 0xFFULL);
        }
        default:
            return 0;
    }
}

static int16_t ECOCALLMETHOD CEcoLab1_CountingSort(/* in */ IEcoLab1Ptr_t me, /* inout */ void* pData, /* in */ uint32_t count, /* in */ int16_t dataType) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    uint32_t itemSize = 0;
    uint32_t passCount = 0;
    uint32_t i = 0;
    uint32_t b = 0;
    uint32_t position = 0;
    uint32_t counts[256];
    char_t* pTemp = 0;
    char_t* pSrc = 0;
    char_t* pDst = 0;
    char_t* pSwap = 0;
    char_t* pSrcItem = 0;
    char_t* pDstItem = 0;
    uint8_t key = 0;
    uint32_t c = 0;
    uint32_t outIndex = 0;
    uint32_t j = 0;

    if (me == 0 || pData == 0) {
        return ERR_ECO_POINTER;
    }

    if (count < 2U) {
        return ERR_ECO_SUCCESES;
    }

    itemSize = CEcoLab1_GetItemSize(dataType);
    if (itemSize == 0U) {
        return ERR_ECO_INVALIDARG;
    }

    if (pCMe->m_pIMem == 0) {
        return ERR_ECO_POINTER;
    }

    pTemp = (char_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, itemSize * count);
    if (pTemp == 0) {
        return ERR_ECO_OUTOFMEMORY;
    }

    pSrc = (char_t*)pData;
    pDst = pTemp;
    passCount = itemSize;

    for (i = 0; i < 256U; ++i) {
        counts[i] = 0U;
    }

    for (b = 0; b < passCount; ++b) {
        for (i = 0; i < 256U; ++i) {
            counts[i] = 0U;
        }

        for (i = 0; i < count; ++i) {
            key = CEcoLab1_GetKeyByte(pSrc + i * itemSize, dataType, b);
            counts[key]++;
        }

        position = 0U;
        for (i = 0; i < 256U; ++i) {
            c = counts[i];
            counts[i] = position;
            position += c;
        }

        for (i = 0; i < count; ++i) {
            key = CEcoLab1_GetKeyByte(pSrc + i * itemSize, dataType, b);
            outIndex = counts[key]++;
            j = 0;

            pSrcItem = pSrc + i * itemSize;
            pDstItem = pDst + outIndex * itemSize;
            for (j = 0; j < itemSize; ++j) {
                pDstItem[j] = pSrcItem[j];
            }
        }

        pSwap = pSrc;
        pSrc = pDst;
        pDst = pSwap;
    }

    if (pSrc != (char_t*)pData) {
        for (i = 0; i < count * itemSize; ++i) {
            ((char_t*)pData)[i] = pSrc[i];
        }
    }

    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, pTemp);
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoLab1(/*in*/ IEcoLab1Ptr_t me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;



    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return result;
}

/* Create Virtual Table IEcoLab1 */
IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
    CEcoLab1_QueryInterface,
    CEcoLab1_AddRef,
    CEcoLab1_Release,
    CEcoLab1_CountingSort
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoLab1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab1** ppIEcoLab1) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab1* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    /* Проверка указателей */
    if (ppIEcoLab1 == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem, (void **)&pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab1*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoLab1 */
    pCMe->m_pVTblIEcoLab1 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoLab1 = (IEcoLab1*)pCMe;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoLab1(/* in */ IEcoLab1* pIEcoLab1) {
    CEcoLab1* pCMe = (CEcoLab1*)pIEcoLab1;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1 != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
