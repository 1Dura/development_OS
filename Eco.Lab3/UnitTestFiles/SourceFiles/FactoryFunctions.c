#include "FactoryFunctions.h"

#include "IEcoConnectionPointContainer.h"
#include "CEcoLab1Sink.h"
#include "CEcoLab1SinkSecond.h"
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
                            /*out*/ IEcoConnectionPoint** ppICPSecond) {
    int16_t result = -1;
    IEcoLab1* pIEcoLab1 = 0;
    IEcoConnectionPointContainer* pICPC = 0;
    IEcoConnectionPoint* pICP = 0;

    /* Получение интерфейса сервера*/
    //CEcoLab1
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) ppIEcoLab1);
    pIEcoLab1 = *ppIEcoLab1;
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        return result;
    }

    /* Проверка поддержки подключений обратного интерфейса */
    //CEcoLab1 (только для работы с подключениями)
    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void **)&pICPC);
    if (result != 0 || pICPC == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        return result;
    }

    /* Запрос на получения интерфейса точки подключения */
    // CEcoLab1->m_pVTblICPC->FindConnectionPoint 
    // получаем реализацию интерфейса из компонента CEcoLab1ConnectionPoint
    result = pICPC->pVTbl->FindConnectionPoint(pICPC, &IID_IEcoLab1EventFirst, ppICPFirst);
    pICP = *ppICPFirst;
    if (result != 0 || pICP == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        return result;
    }

    result = pICPC->pVTbl->FindConnectionPoint(pICPC, &IID_IEcoLab1EventSecond, ppICPSecond);
    pICP = *ppICPSecond;
    if (result != 0 || pICP == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        return result;
    }
    /* Освобождение интерфейса */
    pICPC->pVTbl->Release(pICPC);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция CreateAndConnectClientSinkFirst
 * </сводка>
 *
 * <описание>
 *   Функция подключения обратных интерфейсов для соытия EventFirst к серверу
 * </описание>
 *
 */
int16_t ConnectClientSinkFirst(/*in*/ IEcoMemoryAllocator1* pIMem, /*in*/ IEcoConnectionPoint* pICP, 
                                /*out*/ IEcoLab1EventFirst** ppIEcoLab1Sink,  
                                /*out*/ uint32_t* cAdvise) {
    int16_t result = -1;
    IEcoUnknown* pISinkUnk = 0;

    result = createCEcoLab1Sink(pIMem, ppIEcoLab1Sink);

    if ((*ppIEcoLab1Sink) != 0) {
        result = (*ppIEcoLab1Sink)->pVTbl->QueryInterface(*ppIEcoLab1Sink, &IID_IEcoUnknown,(void **)&pISinkUnk);
        if (result != 0 || pISinkUnk == 0) {

            printf("Cant Query Unknown Interface of Sink\n");
            return result;
        }
        /* Подключение */
        //сохранение информации в списке подключений  ConnectionPoint c QueryInterface подключаемого объекта для связзи
        result = pICP->pVTbl->Advise(pICP, pISinkUnk, cAdvise);
        /* Проверка */
        if (result == 0 && (*cAdvise) != 0) {
            /* Сюда можно добавить код */
           
        }
        else {
            printf("Sink connection failed. Result: %d, Cookie: %d\n", result, *cAdvise);
            result = -1;
            return result;
        }
        /* Освобождение интерфейса */
        pISinkUnk->pVTbl->Release(pISinkUnk);
        result = 0;
    }

    return result;
}

/*
 *
 * <сводка>
 *   Функция CreateAndConnectClientSinkSecond
 * </сводка>
 *
 * <описание>
 *   Функция подключения обратных интерфейсов для соытия EventFirst к серверу
 * </описание>
 *
 */
int16_t ConnectClientSinkSecond(/*in*/ IEcoMemoryAllocator1* pIMem, /*in*/ IEcoConnectionPoint* pICP, 
                                /*out*/ IEcoLab1EventSecond** ppIEcoLab1Sink,
								/*out*/ uint32_t* cAdvise) {
    int16_t result = -1;
    IEcoUnknown* pISinkUnk = 0;

    result = createCEcoLab1SinkSecond(pIMem, ppIEcoLab1Sink);

    if ((*ppIEcoLab1Sink) != 0) {
        result = (*ppIEcoLab1Sink)->pVTbl->QueryInterface(*ppIEcoLab1Sink, &IID_IEcoUnknown,(void **)&pISinkUnk);
        if (result != 0 || pISinkUnk == 0) {

            printf("Cant Query Unknown Interface of Sink\n");
            return result;
        }
        /* Подключение */
        //сохранение информации в списке подключений  ConnectionPoint c QueryInterface подключаемого объекта для связзи
        result = pICP->pVTbl->Advise(pICP, pISinkUnk, cAdvise);
        /* Проверка */
        if (result == 0 && (*cAdvise) != 0) {
            /* Сюда можно добавить код */
           
        }
        else {
            printf("Sink connection failed. Result: %d, Cookie: %d\n", result, *cAdvise);
            result = -1;
            return result;
        }
        /* Освобождение интерфейса */
        pISinkUnk->pVTbl->Release(pISinkUnk);
        result = 0;
    }

    return result;
}
