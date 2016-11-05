#include "test_nomanager.h"
#include <windows.h>

void CTestNoManager::run(HMODULE hModule) {

    Server_DllGetClassObjectPseudo getClassObjectPseudo;
    getClassObjectPseudo = (Server_DllGetClassObjectPseudo) GetProcAddress(hModule, "DllGetClassObjectPseudo");
    assert(getClassObjectPseudo != NULL);

}

void testFactoryComponent1() {
    IClassFactoryPseudo *iCfPtr;
    checkResult(getClassObjectPseudo(CLSID_Component1, IID_IClassFactoryPseudo, (void**)&iCfPtr));
    qDebug() << "Instance of IClassFactoryPseudo created";

    IComponent1faceX *iXPtr;
    checkResult(iCfPtr->CreateInstance(IID_IComponent1faceX, (void**)&iXPtr));
    qDebug() << "Query interface called for IID_IComponent1faceX";

    iXPtr->methodX1();
    iXPtr->methodX2();

    IComponent1faceY *iYPtr;
    checkResult(iCfPtr->CreateInstance(IID_IComponent1faceY, (void**)&iYPtr));
    qDebug() << "Query interface called for IID_IComponent1faceY";

    iYPtr->methodY1();
    iYPtr->methodY2();

    iXPtr->Release();
    iYPtr->Release();
    iCfPtr->Release();
    qDebug() << "Released";
}

void testFactoryComponent2() {
    IClassFactoryPseudo *iCfPtr;
    checkResult(getClassObjectPseudo(CLSID_Component2, IID_IClassFactoryPseudo, (void**)&iCfPtr));
    qDebug() << "Instance of IClassFactoryPseudo created";

    IComponent2faceX *iXPtr;
    checkResult(iCfPtr->CreateInstance(IID_IComponent2faceX, (void**)&iXPtr));
    qDebug() << "Query interface called for IID_IComponent2faceX";

    iXPtr->methodX1();
    iXPtr->methodX2();

    IComponent2faceY *iYPtr;
    checkResult(iCfPtr->CreateInstance(IID_IComponent2faceY, (void**)&iYPtr));
    qDebug() << "Query interface called for IID_IComponent2faceY";

    iYPtr->methodY1();
    iYPtr->methodY2();

    iXPtr->Release();
    iYPtr->Release();
    iCfPtr->Release();
    qDebug() << "Released";
}
