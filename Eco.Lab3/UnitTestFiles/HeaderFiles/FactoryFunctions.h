#ifndef __FACTORY_FUNCTIONS__
#define __FACTORY_FUNCTIONS__

#include "IEcoBase1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IEcoLab1EventFirst.h"
#include "IEcoLab1EventSecond.h"
#include "IdEcoLab1.h"
#include "IEcoConnectionPoint.h"

/*
 *
 * <сводка>
 *   Функция CreateServerComponent
 * </сводка>
 *
 * <описание>
 *   Функция создания серверных компонентов
 * </описание>
 *
 */
int16_t CreateServerComponent(/*in*/ IEcoInterfaceBus1* pIBus, 
                            /*out*/ IEcoLab1** ppIEcoLab1,
                            /*out*/ IEcoConnectionPoint** ppICPFirst,
                            /*out*/ IEcoConnectionPoint** ppICPSecond);

/*
 *
 * <сводка>
 *   Функция CreateAndConnectClientSink
 * </сводка>
 *
 * <описание>
 *   Функция подключения обратных интерфейсов к серверу
 * </описание>
 *
 */
int16_t ConnectClientSinkFirst(/*in*/ IEcoMemoryAllocator1* pIMem, 
									/*in*/ IEcoConnectionPoint* pICP, 
                                    /*out*/ IEcoLab1EventFirst** ppIEcoLab1Sink,  
                                    /*out*/ uint32_t* cAdvise);

int16_t ConnectClientSinkSecond(/*in*/ IEcoMemoryAllocator1* pIMem, /*in*/ IEcoConnectionPoint* pICP, 
                                /*out*/ IEcoLab1EventSecond** ppIEcoLab1Sink,  
                                /*out*/ uint32_t* cAdvise);
#endif /* __FACTORY_FUNCTIONS__ */