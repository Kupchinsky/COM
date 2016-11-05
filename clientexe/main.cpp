#include <QDebug>
#include <QException>
#include <QDir>
#include <windows.h>
#include <cassert>

#include "../serverdll/component1.h"
#include "../serverdll/component2.h"
#include "../unknown.h"

class InvalidResultException: public QException {
    long result;
public:
    InvalidResultException(long result) {
        this->result = result;
    }

    QString what() {
        return QString("Not successfull result: ") + QString::number(result);
    }
};

void checkResult(_HRESULT result);

typedef _HRESULT __stdcall (*CreateInstancePseudo)(_REFCLSID rclsid, _REFIID riid, void **ppv);
CreateInstancePseudo createInstancePseudo;

typedef _HRESULT __stdcall (*GetClassObjectPseudo)(_REFCLSID rclsid, _REFIID riid, void **ppv);
GetClassObjectPseudo getClassObjectPseudo;

void testQueryInterfaceComponent1();
void testQueryInterfaceComponent2();

void testFactoryComponent1();
void testFactoryComponent2();

int main(int argc, char **argv)
{
    if (argc < 2) {
        qDebug() << "No args!";
        return 1;
    }

    qDebug() << "Exception test";
    try {
        checkResult(E_INVALIDARG);
        qDebug() << "Test failed. Exception not throwed, fail!";
    } catch (InvalidResultException& e) {
        qDebug() << "Test passed. Exception throwed: " << e.what();
    }

    qDebug() << "Loading " << argv[1];

    HMODULE hModule = LoadLibraryA(argv[1]);
    assert(hModule != NULL);

    createInstancePseudo = (CreateInstancePseudo) GetProcAddress(hModule, "CreateInstancePseudo");
    assert(createInstancePseudo != NULL);

    getClassObjectPseudo = (GetClassObjectPseudo) GetProcAddress(hModule, "GetClassObjectPseudo");
    assert(getClassObjectPseudo != NULL);

    try {
        testQueryInterfaceComponent1();
        testQueryInterfaceComponent2();

        testFactoryComponent1();
        testFactoryComponent2();
    } catch (InvalidResultException& e) {
        qDebug() << "Test failed. Exception throwed: " << e.what();
    }

    FreeLibrary(hModule);
    return 0;
}

void checkResult(_HRESULT result) {
    if (result != _S_OK) {
        throw InvalidResultException(result);
    }
}

void testQueryInterfaceComponent1() {
    IUnknownPseudo *iUnkPtr;
    checkResult(createInstancePseudo(CLSID_Component1,  IID_IUnknownPseudo, (void**)&iUnkPtr));
    qDebug() << "Instance of IUnknownPseudo created";

    IComponent1faceX *iXPtr;
    checkResult(iUnkPtr->QueryInterface(IID_IComponent1faceX, (void**)&iXPtr));
    qDebug() << "Query interface called for IID_IComponent1faceX";

    iXPtr->methodX1();
    iXPtr->methodX2();

    IComponent1faceY *iYPtr;
    checkResult(iUnkPtr->QueryInterface(IID_IComponent1faceY, (void**)&iYPtr));
    qDebug() << "Query interface called for IID_IComponent1faceY";

    iYPtr->methodY1();
    iYPtr->methodY2();

    iXPtr->Release();
    iYPtr->Release();
    iUnkPtr->Release();
    qDebug() << "Released";
}

void testQueryInterfaceComponent2() {
    IUnknownPseudo *iUnkPtr;
    checkResult(createInstancePseudo(CLSID_Component2,  IID_IUnknownPseudo, (void**)&iUnkPtr));
    qDebug() << "Instance of IUnknownPseudo created";

    IComponent2faceX *iXPtr;
    checkResult(iUnkPtr->QueryInterface(IID_IComponent2faceX, (void**)&iXPtr));
    qDebug() << "Query interface called for IID_IComponent2faceX";

    iXPtr->methodX1();
    iXPtr->methodX2();

    IComponent2faceY *iYPtr;
    checkResult(iUnkPtr->QueryInterface(IID_IComponent2faceY, (void**)&iYPtr));
    qDebug() << "Query interface called for IID_IComponent2faceY";

    iYPtr->methodY1();
    iYPtr->methodY2();

    iXPtr->Release();
    iYPtr->Release();
    iUnkPtr->Release();
    qDebug() << "Released";
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
