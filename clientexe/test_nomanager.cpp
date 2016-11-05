#include "test_nomanager.h"
#include <windows.h>
#include <QDebug>
#include "result_checker.h"
#include <cassert>
#include "../serverdll/component1.h"
#include "../serverdll/component2.h"
#include "../unknown.h"

void CTestNoManager::run(HMODULE hModule) {
    Server_DllGetClassObjectPseudo getClassObjectPseudo;
    getClassObjectPseudo = (Server_DllGetClassObjectPseudo) GetProcAddress(hModule, "DllGetClassObjectPseudo");
    assert(getClassObjectPseudo != NULL);

    CTestNoManager manager(getClassObjectPseudo);
    manager.testFactoryComponent1();
    manager.testFactoryComponent2();
}

void CTestNoManager::testFactoryComponent1() {
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

void CTestNoManager::testFactoryComponent2() {
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
