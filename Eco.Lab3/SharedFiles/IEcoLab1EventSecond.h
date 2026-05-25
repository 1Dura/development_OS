/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoLab1
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECOLAB1EVENTSECOND_H__
#define __I_ECOLAB1EVENTSECOND_H__

#include "IEcoBase1.h"

/* IEcoLab1EventSecond IID = {B6D38661-6827-46D9-9135-FD4B204A68D8} */
#ifndef __IID_IEcoLab1EventSecond
static const UGUID IID_IEcoLab1EventSecond = {0x01, 0x10, 0xB6, 0xD3, 0x86, 0x61, 0x68, 0x27, 0x46, 0xD9, 0x91, 0x35, 0xFD, 0x4B, 0x20, 0x4A, 0x68, 0xD8};
#endif /* __IID_IEcoLab1EventSecond */

/* Обратный интерфейс */
typedef struct IEcoLab1VTblEventSecond {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface )(/* in */ struct IEcoLab1EventSecond* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (ECOCALLMETHOD *AddRef )(/* in */ struct IEcoLab1EventSecond* me);
    uint32_t (ECOCALLMETHOD *Release )(/* in */ struct IEcoLab1EventSecond* me);

    /* IEcoLab1EventSecond */
    int16_t (ECOCALLMETHOD *OnMyCallback)(/* in */ struct IEcoLab1EventSecond* me, /* in */ const void *base, /* in */ uint32_t nmemb, /* in */ uint32_t size, /*in*/ void* search_result);

} IEcoLab1VTblEventSecond, *IEcoLab1VTblEventSecondPtr;

interface IEcoLab1EventSecond {
    struct IEcoLab1VTblEventSecond *pVTbl;
} IEcoLab1EventSecond;


#endif /* __I_ECOLAB1EVENTSECOND_H__ */
