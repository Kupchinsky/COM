#ifndef TEST_MANAGER_H
#define TEST_MANAGER_H

#include "../pseudo_definitions.h"
#include <windows.h>

class CTestManager {
    Manager_CreateInstancePseudo createInstancePseudo;
    Manager_GetClassObjectPseudo getClassObjectPseudo;
    Manager_FreeUnusedLibraries freeUnusedLibraries;

    CTestManager(Manager_CreateInstancePseudo _createInstancePseudo,
                   Manager_GetClassObjectPseudo _getClassObjectPseudo,
                   Manager_FreeUnusedLibraries _freeUnusedLibraries):
        createInstancePseudo(_createInstancePseudo),
        getClassObjectPseudo(_getClassObjectPseudo),
        freeUnusedLibraries(_freeUnusedLibraries) {
    }
public:
    static void run(HMODULE hModule);
};

#endif // TEST_MANAGER_H
