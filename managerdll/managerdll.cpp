#include "managerdll.h"
#include "../pseudo_definitions.h"
#include "../localregistry.h"
#include <windows.h>
#include <cassert>
#include <QList>
#include <QDebug>

static QMap<QString, HMODULE> loadedLibraries;

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved) {
    if (dwReason == DLL_PROCESS_DETACH) {
        if (!loadedLibraries.empty()) {
            qDebug() << "Attention! Some modules not unloaded:";

            foreach (QString path, loadedLibraries.keys()) {
                qDebug() << "[" << path << "]";
            }
        }
    }

    return TRUE;
}

_HRESULT MANAGERDLLSHARED_EXPORT GetClassObjectPseudo(_REFCLSID rclsid, _REFIID riid, void **ppv) {
    if (!ppv) {
        return _E_INVALIDARG;
    }

    *ppv = NULL;

    CLocalRegistry *registry = CLocalRegistry::getInstance().get();
    QString path;

    if (registry->queryComponentModule(rclsid, path)) {
        HMODULE hModule = NULL;

        if (loadedLibraries.contains(path)) {
            hModule = loadedLibraries.value(path);
        } else {
            hModule = LoadLibraryA(path.toStdString().c_str());

            if (hModule != NULL) {
                loadedLibraries.insert(path, hModule);
                qDebug() << "Module loaded: " << path;
            }
        }

        if (hModule != NULL) {
            Server_DllGetClassObjectPseudo dllGetClassObjectPseudo =
                    (Server_DllGetClassObjectPseudo) GetProcAddress(hModule, "DllGetClassObjectPseudo");

            if (dllGetClassObjectPseudo != NULL) {
                return dllGetClassObjectPseudo(rclsid, riid, ppv);
            }
        } else {
            qDebug() << "Something went wrong. Module not found or not loaded: " << path;
        }
    }

    return _E_CLASSNOTAVAILABLE;
}

_HRESULT MANAGERDLLSHARED_EXPORT CreateInstancePseudo(_REFCLSID rclsid, _REFIID riid, void **ppv) {
    if (!ppv) {
        return _E_INVALIDARG;
    }

    IClassFactoryPseudo *cf = NULL;
    _HRESULT result = GetClassObjectPseudo(rclsid, IID_IClassFactoryPseudo, (void**) &cf);

    if (result != _S_OK) {
        return result;
    }

    result = cf->CreateInstance(riid, ppv);
    cf->Release();

    return result;
}

void MANAGERDLLSHARED_EXPORT FreeUnusedLibraries() {
    QMap<QString, HMODULE>::iterator iterator = loadedLibraries.begin();

    while (iterator != loadedLibraries.end()) {
        HMODULE hModule = iterator.value();

        Server_DllCanUnloadNow dllCanUnloadNow = (Server_DllCanUnloadNow) GetProcAddress(hModule, "DllCanUnloadNow");
        assert (dllCanUnloadNow != NULL);

        if (dllCanUnloadNow() == _S_OK) {
            FreeLibrary(hModule);
            qDebug() << "Module unloaded: " << iterator.key();

            iterator = loadedLibraries.erase(iterator);
        } else {
            ++iterator;
        }
    }
}
