/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab2
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoLab2
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECOLAB2_H__
#define __C_ECOLAB2_H__

#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"
#include "IEcoLab1.h"

#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab2 {
    /* Таблица функций интерфейса IEcoCalculatorX */
    IEcoCalculatorXVTbl* m_pVTblIX;

    /* Таблица функций интерфейса IEcoCalculatorY */
    IEcoCalculatorYVTbl* m_pVTblIY;

    /* Таблица функций интерфейса IEcoLab1 */
    IEcoLab1VTbl* m_pVTblILab1;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    char_t* m_Name;

    /* Указатель на интерфейс X */
    IEcoCalculatorX* m_pIX;
    /* Указатель на интерфейс Y */
    IEcoCalculatorY* m_pIY;
    
    IEcoLab1* m_pInnerLab1;
} CEcoLab2, *CEcoLab2Ptr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoLab2(/*in*/ IEcoCalculatorXPtr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoLab2(/* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter, /* out */ IEcoCalculatorXPtr_t* ppIEcoLab2);
/* Удаление */
void ECOCALLMETHOD deleteCEcoLab2(/* in */ IEcoCalculatorXPtr_t pIEcoLab2);

#endif /* __C_ECOLAB2_H__ */
