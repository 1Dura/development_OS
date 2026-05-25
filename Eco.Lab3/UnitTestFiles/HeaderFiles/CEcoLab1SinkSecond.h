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
 *   Данный заголовок описывает реализацию компонента CEcoLab1SinkSecond
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECOLAB1_SINK_SECOND_H__
#define __C_ECOLAB1_SINK_SECOND_H__

#include "IEcoLab1.h"
#include "IEcoLab1EventSecond.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab1SinkSecond {

    /* Таблица функций интерфейса IEcoLab1EventFirst */
    IEcoLab1VTblEventSecond* m_pVTblIEcoLab1EventSecond;

    /* Вспомогательные функции */
    int16_t (ECOCALLMETHOD *Advise)(/* in */ struct CEcoLab1SinkSecond* me, /* in */IEcoLab1 *pIEcoLab1);
    int16_t (ECOCALLMETHOD *Unadvise)(/* in */ struct CEcoLab1SinkSecond* me, /* in */IEcoLab1 *pIEcoLab1);

    /* Счетчик ссылок */
    uint32_t m_cRef;
    uint32_t m_cCookie;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;


} CEcoLab1SinkSecond, *CEcoLab1SinkSecondPtr;

/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoLab1SinkSecond(/* in */ IEcoMemoryAllocator1* pIMem, /* out */ IEcoLab1EventSecond** ppIEcoLab1EventSecond);
/* Удаление */
void ECOCALLMETHOD deleteCEcoLab1SinkSecond(/* in */ IEcoLab1EventSecond* pIEcoLab1EventSecond);

#endif /* __C_ECOLAB1_SINK_SECOND_H__ */
