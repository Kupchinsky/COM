#include <QDebug>
#include <QException>
#include <windows.h>
#include <cassert>

#include "../pseudo_definitions.h"
#include "test_nomanager.h"
#include "result_checker.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        qDebug() << "No args!";
        return 1;
    }

    qDebug() << "Exception test";
    try {
        ResultChecker::check(_E_INVALIDARG);
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
