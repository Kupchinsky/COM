#include <QDebug>
#include <QException>
#include <QDir>
#include <windows.h>
#include <cassert>

#include "pseudo_definitions.h"
#include "test_nomanager.h"
#include "../serverdll/component1.h"
#include "../serverdll/component2.h"
#include "../unknown.h"

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

    qDebug() << "Testing no-manager work...";

    try {
        CTestNoManager::run(hModule);
    } catch (InvalidResultException& e) {
        qDebug() << "Test failed. Exception throwed: " << e.what();
    }

    FreeLibrary(hModule);
    qDebug() << "Test passed.";

    return 0;
}
