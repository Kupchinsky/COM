#ifndef TEST_NOMANAGER_H
#define TEST_NOMANAGER_H

#include "../pseudo_definitions.h"
#include <windows.h>

class CTestNoManager {
    Server_DllGetClassObjectPseudo getClassObjectPseudo;
    Server_DllRegisterServer dllRegisterServer;
    Server_DllUnregisterServer dllUnregisterServer;

    CTestNoManager(Server_DllGetClassObjectPseudo _getClassObjectPseudo,
                   Server_DllRegisterServer _dllRegisterServer,
                   Server_DllUnregisterServer _dllUnregisterServer):
        getClassObjectPseudo(_getClassObjectPseudo),
        dllRegisterServer(_dllRegisterServer),
        dllUnregisterServer(_dllUnregisterServer) {
    }

    void testRegister();
    void testUnregister();
    void testFactoryComponent1();
    void testFactoryComponent2();
public:
    static void run(HMODULE hModule);
};

#endif // TEST_NOMANAGER_H
