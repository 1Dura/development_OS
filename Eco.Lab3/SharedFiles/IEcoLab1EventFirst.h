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

#ifndef __I_ECOLAB1EVENTFIRST_H__
#define __I_ECOLAB1EVENTFIRST_H__

#include "IEcoBase1.h"

/* IEcoLab1EventFirst IID = {B6D38661-6827-46D9-9135-FD4B204A68D7} */
#ifndef __IID_IEcoLab1EventFirst
static const UGUID IID_IEcoLab1EventFirst = {0x01, 0x10, 0xB6, 0xD3, 0x86, 0x61, 0x68, 0x27, 0x46, 0xD9, 0x91, 0x35, 0xFD, 0x4B, 0x20, 0x4A, 0x68, 0xD7};
#endif /* __IID_IEcoLab1EventFirst */

/* Обратный интерфейс */
typedef struct IEcoLab1VTblEventFirst {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface )(/* in */ struct IEcoLab1EventFirst* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (ECOCALLMETHOD *AddRef )(/* in */ struct IEcoLab1EventFirst* me);
    uint32_t (ECOCALLMETHOD *Release )(/* in */ struct IEcoLab1EventFirst* me);

    /* IEcoLab1EventFirst */
    int16_t (ECOCALLMETHOD *OnMyCallback)(/* in */ struct IEcoLab1EventFirst* me, /* in */ const void *base, /* in */ uint32_t nmemb, /* in */ uint32_t size, /*in*/ void* search_result);

} IEcoLab1VTblEventFirst, *IEcoLab1VTblEventFirstPtr;

interface IEcoLab1EventFirst {
    struct IEcoLab1VTblEventFirst *pVTbl;
} IEcoLab1EventFirst;


#endif /* __I_ECOLAB1EVENTFIRST_H__ */
