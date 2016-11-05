#ifndef TEST_NOMANAGER_H
#define TEST_NOMANAGER_H

#include "../pseudo_definitions.h"
#include <windows.h>

class CTestNoManager {
    Server_DllGetClassObjectPseudo getClassObjectPseudo;

    CTestNoManager(Server_DllGetClassObjectPseudo _getClassObjectPseudo): getClassObjectPseudo(_getClassObjectPseudo) {
    }

    void testFactoryComponent1();
    void testFactoryComponent2();
public:
    static void run(HMODULE hModule);
};

#endif // TEST_NOMANAGER_H
