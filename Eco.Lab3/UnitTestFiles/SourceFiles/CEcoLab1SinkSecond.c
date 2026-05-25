/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1SinkSecond
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1SinkSecond
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "CEcoLab1SinkSecond.h"
#include "IEcoConnectionPointContainer.h"
#include <stdio.h>

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1SinkSecond_QueryInterface(/* in */ struct IEcoLab1EventSecond* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    if ( IsEqualUGUID(riid, &IID_IEcoLab1EventSecond ) ) {
        *ppv = me;
        me->pVTbl->AddRef(me);
        return 0;
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown ) ) {
        *ppv = me;
        me->pVTbl->AddRef(me);
        return 0;
    }

    *ppv = 0;

    return -1;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1SinkSecond_AddRef(/* in */ struct IEcoLab1EventSecond* me) {
    CEcoLab1SinkSecond* pCMe = (CEcoLab1SinkSecond*)me;

    if (me == 0 ) {
        return -1;
    }

    pCMe->m_cRef++;
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1SinkSecond_Release(/* in */ struct IEcoLab1EventSecond* me) {
    CEcoLab1SinkSecond* pCMe = (CEcoLab1SinkSecond*)me;

    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab1SinkSecond((IEcoLab1EventSecond*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

static void draw_array(const void *base, uint32_t nmemb, uint32_t size, /*in*/ void* search_result) {
    uint32_t i = 0;
    if (base == NULL || nmemb == 0 || size == 0) {
        printf("Invalid array parameters\n");
        return;
    }
    
    printf("Sorted array in reverse order (%u elements, %u bytes each):\n", nmemb, size);
    printf("[ ");
    
    // Отображаем массив в обратном порядке
    for (i = 0; i < nmemb; i++) {
        const uint8_t *byte_ptr = (const uint8_t *)base + ((nmemb - 1 - i) * size);
        int32_t value = 0;
        
        // Извлекаем значение в зависимости от размера элемента
        switch (size) {
            case 1:
                value = *(const int8_t *)byte_ptr;
                break;
            case 2:
                value = *(const int16_t *)byte_ptr;
                break;
            case 4:
                value = *(const int32_t *)byte_ptr;
                break;
            default:
                printf("Unsupported element size\n");
                return;
        }
        
        printf("%d", value);
        if (i < nmemb - 1) printf(", ");
    }
    
    printf(" ]\n");
    printf("Sorting callback received\n");
}

/*
 *
 * <сводка>
 *   Функция OnMyCallback
 * </сводка>
 *
 * <описание>
 *   Функция обратного вызова
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1SinkSecond_OnMyCallback(/* in */ struct IEcoLab1EventSecond* me, /* in */ const void *base, /* in */ uint32_t nmemb, /* in */ uint32_t size, /*in*/ void* search_result) {
    CEcoLab1SinkSecond* pCMe = (CEcoLab1SinkSecond*)me;

    if (me == 0 ) {
        return -1;
    }

	printf("Hello from EcoLab1Second callback!\n");
    draw_array(base, nmemb, size, search_result);

    return 0;
}


/*
 *
 * <сводка>
 *   Функция Advise
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1SinkSecond_Advise(/* in */ struct CEcoLab1SinkSecond* me, /* in */IEcoLab1 *pIEcoLab1) {
    IEcoConnectionPointContainer* pCPC = 0;
    IEcoConnectionPoint* pCP = 0;
    int16_t result = 0;

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void**)&pCPC);

    if (result == 0 && pCPC != 0) {
        result = pCPC->pVTbl->FindConnectionPoint(pCPC, &IID_IEcoLab1EventSecond, &pCP);
        pCPC->pVTbl->Release(pCPC);
        pCPC = 0;
        if (result == 0 && pCP != 0) {

            result = pCP->pVTbl->Advise(pCP, (IEcoUnknown*)me, &me->m_cCookie);
            pCP->pVTbl->Release(pCP);
            pCP = 0;
        }
    }

    return result;
}

/*
 *
 * <сводка>
 *   Функция Unadvise
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1SinkSecond_Unadvise(/* in */ struct CEcoLab1SinkSecond* me, /* in */IEcoLab1 *pIEcoLab1) {
    IEcoConnectionPointContainer* pCPC = 0;
    IEcoConnectionPoint * pCP = 0;
    int16_t result = 0;

    if (me->m_cCookie) {
        result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void**)&pCPC);
        if (result == 0) {
            result = pCPC->pVTbl->FindConnectionPoint(pCPC, &IID_IEcoLab1EventSecond, &pCP);
            pCPC->pVTbl->Release(pCPC);
            pCPC = 0;
            if (result == 0) {
                result = pCP->pVTbl->Unadvise(pCP, me->m_cCookie);
                pCP->pVTbl->Release(pCP);
                pCP = 0;
            }
        }
    }
    return result;
}

/* Create Virtual Table IEcoLab1VTblEventSecond */
IEcoLab1VTblEventSecond g_xB6D38661682746D99135FD4B204A68D8VTblEventSecond = {
    CEcoLab1SinkSecond_QueryInterface,
    CEcoLab1SinkSecond_AddRef,
    CEcoLab1SinkSecond_Release,
    CEcoLab1SinkSecond_OnMyCallback
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
int16_t ECOCALLMETHOD createCEcoLab1SinkSecond(/* in */ IEcoMemoryAllocator1* pIMem, /* out */ IEcoLab1EventSecond** ppIEcoLab1EventSecond) {
    int16_t result = -1;
    CEcoLab1SinkSecond* pCMe = 0;

    /* Проверка указателей */
    if (ppIEcoLab1EventSecond == 0 || pIMem == 0 ) {
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab1SinkSecond*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1SinkSecond));

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;
    pCMe->m_pIMem->pVTbl->AddRef(pCMe->m_pIMem);

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoP2PEvents */
    pCMe->m_pVTblIEcoLab1EventSecond = &g_xB6D38661682746D99135FD4B204A68D8VTblEventSecond;

    *ppIEcoLab1EventSecond = (IEcoLab1EventSecond*)pCMe;

    return 0;
};

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
void ECOCALLMETHOD deleteCEcoLab1SinkSecond(IEcoLab1EventSecond* pIEcoLab1EventSecond) {
    CEcoLab1SinkSecond* pCMe = (CEcoLab1SinkSecond*)pIEcoLab1EventSecond;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1EventSecond != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
};
