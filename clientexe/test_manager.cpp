#include "test_manager.h"
#include <windows.h>
#include <QDebug>
#include "result_checker.h"
#include <cassert>
#include "../serverdll/component1.h"
#include "../serverdll/component2.h"
#include "../unknown.h"

void CTestManager::run(HMODULE hModule) {
    Manager_CreateInstancePseudo createInstancePseudo;
    createInstancePseudo = (Manager_CreateInstancePseudo) GetProcAddress(hModule, "CreateInstancePseudo");
    assert(createInstancePseudo != NULL);

    Manager_GetClassObjectPseudo getClassObjectPseudo;
    getClassObjectPseudo = (Manager_GetClassObjectPseudo) GetProcAddress(hModule, "GetClassObjectPseudo");
    assert(getClassObjectPseudo != NULL);

    Manager_FreeUnusedLibraries freeUnusedLibraries;
    freeUnusedLibraries = (Manager_FreeUnusedLibraries) GetProcAddress(hModule, "FreeUnusedLibraries");
    assert(freeUnusedLibraries != NULL);

    CTestManager tester(createInstancePseudo, getClassObjectPseudo, freeUnusedLibraries);
    tester.testFactoryComponent1();
    tester.testFactoryComponent2();

    freeUnusedLibraries();
}

void CTestManager::testFactoryComponent1() {
    IClassFactoryPseudo *iCfPtr;
    ResultChecker::check(getClassObjectPseudo(CLSID_Component1, IID_IClassFactoryPseudo, (void**)&iCfPtr));
    qDebug() << "Instance of IClassFactoryPseudo created";

    IComponent1faceX *iXPtr;
    ResultChecker::check(iCfPtr->CreateInstance(IID_IComponent1faceX, (void**)&iXPtr));
    qDebug() << "Query interface called for IID_IComponent1faceX";

    iXPtr->methodX1();
    iXPtr->methodX2();

    IComponent1faceY *iYPtr;
    ResultChecker::check(iCfPtr->CreateInstance(IID_IComponent1faceY, (void**)&iYPtr));
    qDebug() << "Query interface called for IID_IComponent1faceY";

    iYPtr->methodY1();
    iYPtr->methodY2();

    iXPtr->Release();
    iYPtr->Release();
    iCfPtr->Release();
    qDebug() << "Released";
}

void CTestManager::testFactoryComponent2() {
    IClassFactoryPseudo *iCfPtr;
    ResultChecker::check(getClassObjectPseudo(CLSID_Component2, IID_IClassFactoryPseudo, (void**)&iCfPtr));
    qDebug() << "Instance of IClassFactoryPseudo created";

    IComponent2faceX *iXPtr;
    ResultChecker::check(iCfPtr->CreateInstance(IID_IComponent2faceX, (void**)&iXPtr));
    qDebug() << "Query interface called for IID_IComponent2faceX";

    iXPtr->methodX1();
    iXPtr->methodX2();

    IComponent2faceY *iYPtr;
    ResultChecker::check(iCfPtr->CreateInstance(IID_IComponent2faceY, (void**)&iYPtr));
    qDebug() << "Query interface called for IID_IComponent2faceY";

    iYPtr->methodY1();
    iYPtr->methodY2();

    iXPtr->Release();
    iYPtr->Release();
    iCfPtr->Release();
    qDebug() << "Released";
}
