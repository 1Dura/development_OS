/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoLab2
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoLab2
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

#ifndef __ID_ECOLAB2_H__
#define __ID_ECOLAB2_H__

#include "IEcoBase1.h"

/* EcoLab2 CID = {F87CD666-E631-4B33-B2B4-508FDCD4BE15} */
#ifndef __CID_EcoLab2
static const UGUID CID_EcoLab2 = {0x01, 0x10, {0xF8, 0x7C, 0xD6, 0x66, 0xE6, 0x31, 0x4B, 0x33, 0xB2, 0xB4, 0x50, 0x8F, 0xDC, 0xD4, 0xBE, 0x15}};
#endif /* __CID_EcoLab2 */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_F87CD666E6314B33B2B4508FDCD4BE15;
#endif

#endif /* __ID_ECOLAB2_H__ */
