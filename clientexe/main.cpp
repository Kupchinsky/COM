#include <QDebug>
#include <QException>
#include <windows.h>
#include <cassert>

#include "../serverdll/component1.h"
#include "../serverdll/component2.h"
#include "../serverdll/unknown.h"

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

void checkResult(long result) {
    if (result != S_OK) {
        throw InvalidResultException(result);
    }
}

typedef ULONG (*CreateInstancePseudo)(int rclsid, int riid, void **ppv);
CreateInstancePseudo createInstancePseudo = NULL;

void testQueryInterface() {
    IUnknownPseudo *iUnkPtr;
    checkResult(createInstancePseudo(CLSID_Component1,  IID_IUnknown, (void**)&iUnkPtr));
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

void testQueryInterface2() {
    IUnknownPseudo *iUnkPtr;
    checkResult(createInstancePseudo(CLSID_Component2,  IID_IUnknown, (void**)&iUnkPtr));
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

int main(int argc, char *argv[])
{
    qDebug() << "Exception test";
    try {
        checkResult(E_INVALIDARG);
        qDebug() << "Test failed. Exception not throwed, fail!";
    } catch (InvalidResultException& e) {
        qDebug() << "Test passed. Exception throwed: " << e.what();
    }

    HMODULE hModule = LoadLibraryA("..\\build-serverdll-Desktop_Qt_5_6_0_MinGW_32bit-Release\\release\\serverdll.dll");
    assert(hModule != NULL);

    createInstancePseudo = (CreateInstancePseudo) GetProcAddress(hModule, "_Z20CreateInstancePseudoiiPPv");
    assert(createInstancePseudo != NULL);

    testQueryInterface();
    testQueryInterface2();

    FreeLibrary(hModule);
    return 0;
}
