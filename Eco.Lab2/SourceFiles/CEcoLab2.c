/*
 * CEcoLab2 implementation
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"
#include "IdEcoLab1.h"
#include "CEcoLab2.h"

#include <stddef.h>
#include <stdio.h>

static uint32_t ECOCALLMETHOD CEcoLab2_AddRef(IEcoCalculatorXPtr_t me);
static uint32_t ECOCALLMETHOD CEcoLab2_Release(IEcoCalculatorXPtr_t me);

static CEcoLab2* CEcoLab2_FromY(IEcoCalculatorYPtr_t me) {
    return (CEcoLab2*)((char_t*)me - offsetof(CEcoLab2, m_pVTblIY));
}

static CEcoLab2* CEcoLab2_FromLab1(IEcoLab1Ptr_t me) {
    return (CEcoLab2*)((char_t*)me - offsetof(CEcoLab2, m_pVTblILab1));
}

static int16_t CEcoLab2_QueryInterface(CEcoLab2* pCMe, const UGUID* riid, void** ppv) {
    if (pCMe == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    if (IsEqualUGUID(riid, &IID_IEcoUnknown) || IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        *ppv = &pCMe->m_pVTblIX;
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIY;
    }
    else if (IsEqualUGUID(riid, &IID_IEcoLab1)) {
        *ppv = &pCMe->m_pVTblILab1;
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }

    CEcoLab2_AddRef((IEcoCalculatorXPtr_t)pCMe);
    return ERR_ECO_SUCCESES;
}

/* IEcoCalculatorX */
static int16_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorX_QueryInterface(
    IEcoCalculatorXPtr_t me, const UGUID* riid, void** ppv) {
    return CEcoLab2_QueryInterface((CEcoLab2*)me, riid, ppv);
}

static uint32_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorX_AddRef(IEcoCalculatorXPtr_t me) {
    return CEcoLab2_AddRef(me);
}

static uint32_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorX_Release(IEcoCalculatorXPtr_t me) {
    return CEcoLab2_Release(me);
}

static int32_t ECOCALLMETHOD CEcoLab2_Addition(IEcoCalculatorXPtr_t me, int16_t a, int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    if (pCMe == 0 || pCMe->m_pIX == 0) {
        return 0;
    }
    return pCMe->m_pIX->pVTbl->Addition(pCMe->m_pIX, a, b);
}

static int16_t ECOCALLMETHOD CEcoLab2_Subtraction(IEcoCalculatorXPtr_t me, int16_t a, int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    if (pCMe == 0 || pCMe->m_pIX == 0) {
        return 0;
    }
    return pCMe->m_pIX->pVTbl->Subtraction(pCMe->m_pIX, a, b);
}

/* IEcoCalculatorY */
static int16_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorY_QueryInterface(
    IEcoCalculatorYPtr_t me, const UGUID* riid, void** ppv) {
    return CEcoLab2_QueryInterface(CEcoLab2_FromY(me), riid, ppv);
}

static uint32_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorY_AddRef(IEcoCalculatorYPtr_t me) {
    return CEcoLab2_AddRef((IEcoCalculatorXPtr_t)CEcoLab2_FromY(me));
}

static uint32_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorY_Release(IEcoCalculatorYPtr_t me) {
    return CEcoLab2_Release((IEcoCalculatorXPtr_t)CEcoLab2_FromY(me));
}

static int32_t ECOCALLMETHOD CEcoLab2_Multiplication(IEcoCalculatorYPtr_t me, int16_t a, int16_t b) {
    CEcoLab2* pCMe = CEcoLab2_FromY(me);
    if (pCMe == 0 || pCMe->m_pIY == 0) {
        return 0;
    }
    return pCMe->m_pIY->pVTbl->Multiplication(pCMe->m_pIY, a, b);
}

static int16_t ECOCALLMETHOD CEcoLab2_Division(IEcoCalculatorYPtr_t me, int16_t a, int16_t b) {
    CEcoLab2* pCMe = CEcoLab2_FromY(me);
    if (pCMe == 0 || pCMe->m_pIY == 0) {
        return 0;
    }
    return pCMe->m_pIY->pVTbl->Division(pCMe->m_pIY, a, b);
}

/* IEcoLab1 */
static int16_t ECOCALLMETHOD CEcoLab2_IEcoLab1_QueryInterface(
    IEcoLab1Ptr_t me, const UGUID* riid, void** ppv) {
    return CEcoLab2_QueryInterface(CEcoLab2_FromLab1(me), riid, ppv);
}

static uint32_t ECOCALLMETHOD CEcoLab2_IEcoLab1_AddRef(IEcoLab1Ptr_t me) {
    return CEcoLab2_AddRef((IEcoCalculatorXPtr_t)CEcoLab2_FromLab1(me));
}

static uint32_t ECOCALLMETHOD CEcoLab2_IEcoLab1_Release(IEcoLab1Ptr_t me) {
    return CEcoLab2_Release((IEcoCalculatorXPtr_t)CEcoLab2_FromLab1(me));
}

static int16_t ECOCALLMETHOD CEcoLab2_CountingSort(
    IEcoLab1Ptr_t me, void* pData, uint32_t count, int16_t dataType) {
    CEcoLab2* pCMe = CEcoLab2_FromLab1(me);
    if (pCMe == 0 || pCMe->m_pInnerLab1 == 0) {
        return ERR_ECO_POINTER;
    }
    return pCMe->m_pInnerLab1->pVTbl->CountingSort(
        pCMe->m_pInnerLab1, pData, count, dataType);
}

IEcoCalculatorXVTbl g_x9322111622484742AE0682819447843DVTblD = {
    CEcoLab2_IEcoCalculatorX_QueryInterface,
    CEcoLab2_IEcoCalculatorX_AddRef,
    CEcoLab2_IEcoCalculatorX_Release,
    CEcoLab2_Addition,
    CEcoLab2_Subtraction
};

IEcoCalculatorYVTbl g_xBD6414C29096423EA90C04D77AFD1CADVTblD = {
    CEcoLab2_IEcoCalculatorY_QueryInterface,
    CEcoLab2_IEcoCalculatorY_AddRef,
    CEcoLab2_IEcoCalculatorY_Release,
    CEcoLab2_Multiplication,
    CEcoLab2_Division
};

IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTblD = {
    CEcoLab2_IEcoLab1_QueryInterface,
    CEcoLab2_IEcoLab1_AddRef,
    CEcoLab2_IEcoLab1_Release,
    CEcoLab2_CountingSort
};

static uint32_t ECOCALLMETHOD CEcoLab2_AddRef(IEcoCalculatorXPtr_t me) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    if (me == 0) {
        return (uint32_t)-1;
    }
    return ++pCMe->m_cRef;
}

static uint32_t ECOCALLMETHOD CEcoLab2_Release(IEcoCalculatorXPtr_t me) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    if (me == 0) {
        return (uint32_t)-1;
    }

    --pCMe->m_cRef;
    if (pCMe->m_cRef == 0) {
        deleteCEcoLab2((IEcoCalculatorXPtr_t)pCMe);
        return 0;
    }

    return pCMe->m_cRef;
}

int16_t ECOCALLMETHOD createCEcoLab2(
    IEcoUnknownPtr_t pIUnkSystem,
    IEcoUnknownPtr_t pIUnkOuter,
    IEcoCalculatorXPtr_t* ppIEcoLab2) {

    int16_t result = ERR_ECO_POINTER;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab2* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    (void)pIUnkOuter;

    if (ppIEcoLab2 == 0 || pIUnkSystem == 0) {
        return result;
    }

    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem, (void**)&pISys);
    if (result != 0 || pISys == 0) {
        return ERR_ECO_NOSYSTEM;
    }

    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void**)&pIBus);
    if (result != 0 || pIBus == 0) {
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_NOBUS;
    }

    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**)&pIMem);
    if (result != 0 || pIMem == 0) {
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    pCMe = (CEcoLab2*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab2));
    if (pCMe == 0) {
        pIMem->pVTbl->Release(pIMem);
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_OUTOFMEMORY;
    }

    pCMe->m_pVTblIX = &g_x9322111622484742AE0682819447843DVTblD;
    pCMe->m_pVTblIY = &g_xBD6414C29096423EA90C04D77AFD1CADVTblD;
    pCMe->m_pVTblILab1 = &g_x277FC00C35624096AFCFC125B94EEC90VTblD;
    pCMe->m_cRef = 1;
    pCMe->m_pIMem = pIMem;
    pCMe->m_pISys = pISys;
    pCMe->m_Name = 0;
    pCMe->m_pIX = 0;
    pCMe->m_pIY = 0;
    pCMe->m_pInnerLab1 = 0;

    *ppIEcoLab2 = (IEcoCalculatorXPtr_t)pCMe;

    pIBus->pVTbl->Release(pIBus);
    return ERR_ECO_SUCCESES;
}

int16_t ECOCALLMETHOD initCEcoLab2(IEcoCalculatorXPtr_t me, IEcoUnknownPtr_t pIUnkSystem) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result = ERR_ECO_POINTER;

    if (me == 0 || pIUnkSystem == 0) {
        return result;
    }

    printf("CEcoLab2: initialization started\n");

    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem, (void**)&pISys);
    if (result != 0 || pISys == 0) {
        printf("CEcoLab2: failed to get IEcoSystem\n");
        return result;
    }

    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void**)&pIBus);
    pISys->pVTbl->Release(pISys);
    if (result != 0 || pIBus == 0) {
        printf("CEcoLab2: failed to get IEcoInterfaceBus1\n");
        return result;
    }

    result = pIBus->pVTbl->QueryComponent(
        pIBus, &CID_EcoCalculatorB, 0, &IID_IEcoCalculatorX, (void**)&pCMe->m_pIX);
    if (result != 0 || pCMe->m_pIX == 0) {
        result = pIBus->pVTbl->QueryComponent(
            pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**)&pCMe->m_pIX);
    }
    if (result != 0 || pCMe->m_pIX == 0) {
        printf("CEcoLab2: failed to obtain IEcoCalculatorX\n");
        pIBus->pVTbl->Release(pIBus);
        return result;
    }
    printf("CEcoLab2: IEcoCalculatorX obtained\n");

    result = pIBus->pVTbl->QueryComponent(
        pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**)&pCMe->m_pIY);
    if (result != 0 || pCMe->m_pIY == 0) {
        result = pIBus->pVTbl->QueryComponent(
            pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY, (void**)&pCMe->m_pIY);
    }
    if (result != 0 || pCMe->m_pIY == 0) {
        printf("CEcoLab2: failed to obtain IEcoCalculatorY\n");
        pIBus->pVTbl->Release(pIBus);
        return result;
    }
    printf("CEcoLab2: IEcoCalculatorY obtained\n");

    result = pIBus->pVTbl->QueryComponent(
        pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**)&pCMe->m_pInnerLab1);
    pIBus->pVTbl->Release(pIBus);
    if (result != 0 || pCMe->m_pInnerLab1 == 0) {
        printf("CEcoLab2: failed to obtain EcoLab1\n");
        return result;
    }

    printf("CEcoLab2: EcoLab1 obtained and exposed through outer IEcoLab1\n");
    printf("CEcoLab2: initialization finished\n");

    return ERR_ECO_SUCCESES;
}

void ECOCALLMETHOD deleteCEcoLab2(IEcoCalculatorXPtr_t pIEcoLab2) {
    CEcoLab2* pCMe = (CEcoLab2*)pIEcoLab2;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab2 == 0) {
        return;
    }

    pIMem = pCMe->m_pIMem;

    if (pCMe->m_Name != 0) {
        pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
    }
    if (pCMe->m_pIX != 0) {
        pCMe->m_pIX->pVTbl->Release(pCMe->m_pIX);
    }
    if (pCMe->m_pIY != 0) {
        pCMe->m_pIY->pVTbl->Release(pCMe->m_pIY);
    }
    if (pCMe->m_pInnerLab1 != 0) {
        pCMe->m_pInnerLab1->pVTbl->Release(pCMe->m_pInnerLab1);
    }
    if (pCMe->m_pISys != 0) {
        pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
    }

    pIMem->pVTbl->Free(pIMem, pCMe);
    pIMem->pVTbl->Release(pIMem);
}
