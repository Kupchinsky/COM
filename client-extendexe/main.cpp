#include <QDebug>
#include <QException>
#include <windows.h>
#include <cassert>

#include "../pseudo_definitions.h"
#include "../clientexe/result_checker.h"
#include "../server-extenddll/component1ex.h"

int main(int argc, char *argv[])
{
    // Args: extenddll managerdll
    if (argc < 3) {
        qDebug() << "No args!";
        return 1;
    }

    qDebug() << "Registering extend component...";
    qDebug() << "Loading " << argv[1];

    HMODULE hModule = LoadLibraryA(argv[1]);
    assert(hModule != NULL);

    Server_DllRegisterServer dllRegisterServer;
    dllRegisterServer = (Server_DllRegisterServer) GetProcAddress(hModule, "DllRegisterServer");
    assert(dllRegisterServer != NULL);

    qDebug() << "Attempt to register...";
    dllRegisterServer();

    FreeLibrary(hModule);

    qDebug() << "Testing extend component work through manager...";
    qDebug() << "Loading " << argv[2];

    hModule = LoadLibraryA(argv[2]);
    assert(hModule != NULL);

    Manager_CreateInstancePseudo createInstancePseudo;
    createInstancePseudo = (Manager_CreateInstancePseudo) GetProcAddress(hModule, "CreateInstancePseudo");
    assert(createInstancePseudo != NULL);

    Manager_FreeUnusedLibraries freeUnusedLibraries;
    freeUnusedLibraries = (Manager_FreeUnusedLibraries) GetProcAddress(hModule, "FreeUnusedLibraries");
    assert(freeUnusedLibraries != NULL);

    bool bError = false;

    try {
        IComponentEx1face *ptr = NULL;
        ResultChecker::check(createInstancePseudo(CLSID_ComponentEx1, IID_IComponentEx1face, (void**) &ptr));

        qDebug() << "Attempt to use new method...";
        ptr->methodX4();

        qDebug() << "Attempt to query and use original component interfaces...";
        IComponent1faceX *ptrX = NULL;
        ResultChecker::check(ptr->QueryInterface(IID_IComponent1faceX, (void**) &ptrX));
        ptrX->methodX1();
        ptrX->Release();

        IComponent1faceY *ptrY = NULL;
        ResultChecker::check(ptr->QueryInterface(IID_IComponent1faceY, (void**) &ptrY));
        ptrY->methodY1();
        ptrY->Release();

        ptr->Release();
    } catch (InvalidResultException& e) {
        qDebug() << "Test failed. Exception throwed: " << e.what();
        bError = true;
    }

    freeUnusedLibraries();
    FreeLibrary(hModule);

    if (!bError) {
        qDebug() << "Test passed.";
    } else {
        return 1;
    }

    return 0;
}
