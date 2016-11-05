#include <QDebug>
#include <QException>
#include <windows.h>
#include <cassert>

#include "../pseudo_definitions.h"
#include "test_nomanager.h"
#include "test_manager.h"
#include "result_checker.h"

int main(int argc, char **argv)
{
    if (argc < 3) {
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

    qDebug() << "Testing no-manager work...";
    qDebug() << "Loading " << argv[1];

    HMODULE hModule = LoadLibraryA(argv[1]);
    assert(hModule != NULL);

    bool bError = false;

    try {
        CTestNoManager::run(hModule);
    } catch (InvalidResultException& e) {
        qDebug() << "Test failed. Exception throwed: " << e.what();
        bError = true;
    }

    FreeLibrary(hModule);

    if (!bError) {
        qDebug() << "Test passed.";
    } else {
        return 1;
    }

    qDebug() << "Testing manager work...";
    qDebug() << "Loading " << argv[2];

    hModule = LoadLibraryA(argv[2]);
    assert(hModule != NULL);

    try {
        CTestManager::run(hModule);
    } catch (InvalidResultException& e) {
        qDebug() << "Test failed. Exception throwed: " << e.what();
        bError = true;
    }

    FreeLibrary(hModule);

    if (!bError) {
        qDebug() << "Test passed.";
    } else {
        return 1;
    }

    return 0;
}
