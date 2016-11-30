#include "serverdll.h"
#include <windows.h>

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved) {
    if (dwReason == DLL_PROCESS_ATTACH) {
        g_hModule = (HMODULE) hModule;
    }

    return TRUE;
}

BOOL HelperWriteKey(HKEY roothk, const char *lpSubKey, LPCSTR val_name, DWORD dwType, void *lpvData, DWORD dwDataSize) {
    //roothk:either of HKCR, HKLM, etc
    //lpSubKey: the key relative to 'roothk'
    //val_name:the key value name where the data will be written
    //dwType:the type of data that will be written ,REG_SZ,REG_BINARY, etc.
    //lpvData:a pointer to the data buffer
    //dwDataSize:the size of the data pointed to by lpvData

    HKEY hk;
    if (ERROR_SUCCESS != RegCreateKeyA(roothk, lpSubKey, &hk)) {
        return FALSE;
    }

    if (ERROR_SUCCESS != RegSetValueExA(hk, val_name, 0, dwType, (CONST BYTE *)lpvData, dwDataSize)) {
        return FALSE;
    }

    if (ERROR_SUCCESS != RegCloseKey(hk)) {
        return FALSE;
    }

    return TRUE;
}

HRESULT SERVERDLLSHARED_EXPORT DllRegisterServer() {
    WCHAR *lpwszClsid;

    char szBuff[MAX_PATH];
    char szClsid[MAX_PATH];
    char szInproc[MAX_PATH];
    char szProgId[MAX_PATH];
    char szDescriptionVal[256];

    StringFromCLSID(LIBID_ProcessManager, &lpwszClsid);

    sprintf(szClsid, "%S", lpwszClsid);
    sprintf(szInproc, "%s\\%s\\%s", "clsid", szClsid, "InprocServer32");
    sprintf(szProgId, "%s\\%s\\%s", "clsid", szClsid, "ProgId");

    sprintf(szBuff, "%s", "Process Manager");
    sprintf(szDescriptionVal, "%s\\%s", "clsid", szClsid);

    HelperWriteKey(HKEY_CLASSES_ROOT, szDescriptionVal, NULL, REG_SZ, (void*)szBuff, strlen(szBuff));

    GetModuleFileNameA(g_hModule, szBuff, sizeof(szBuff));
    HelperWriteKey(HKEY_CLASSES_ROOT, szInproc, NULL, REG_SZ, (void*)szBuff, strlen(szBuff));

    strcpy(szBuff, ProgId);
    HelperWriteKey(HKEY_CLASSES_ROOT, szProgId, NULL, REG_SZ, (void*)szBuff, strlen(szBuff));

    sprintf(szBuff, "%s", "Fast Addition Algorithm");
    HelperWriteKey(HKEY_CLASSES_ROOT, ProgId, NULL, REG_SZ, (void*)szBuff, strlen(szBuff));

    sprintf(szProgId, "%s\\%s", ProgId, "CLSID");
    HelperWriteKey(HKEY_CLASSES_ROOT, szProgId, NULL, REG_SZ, (void*)szClsid, strlen(szClsid));

    return 1;
}

HRESULT SERVERDLLSHARED_EXPORT DllUnregisterServer() {

    char szKeyName[256];
    char szClsid[256];
    WCHAR *lpwszClsid;

    sprintf(szKeyName, "%s\\%s", ProgId, "CLSID");
    RegDeleteKeyA(HKEY_CLASSES_ROOT, szKeyName);
    RegDeleteKeyA(HKEY_CLASSES_ROOT, ProgId);

    StringFromCLSID(LIBID_ProcessManager, &lpwszClsid);
    sprintf(szClsid, "%S", lpwszClsid);
    sprintf(szKeyName, "%s\\%s\\%s", "CLSID", szClsid, "InprocServer32");
    RegDeleteKeyA(HKEY_CLASSES_ROOT, szKeyName);

    sprintf(szKeyName, "%s\\%s\\%s", "CLSID", szClsid, "ProgId");
    RegDeleteKeyA(HKEY_CLASSES_ROOT, szKeyName);

    sprintf(szKeyName, "%s\\%s", "CLSID", szClsid);
    RegDeleteKeyA(HKEY_CLASSES_ROOT, szKeyName);

    return 1;
}

HRESULT SERVERDLLSHARED_EXPORT DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv) {
    if (!ppv) {
        return E_INVALIDARG;
    }

    *ppv = NULL;

    if (rclsid == LIBID_ProcessManager) {
        CProcessMonitorImplFactory *cf = new CProcessMonitorImplFactory();
        return cf->QueryInterface(riid, ppv);
    }

    return CLASS_E_CLASSNOTAVAILABLE;
}

HRESULT SERVERDLLSHARED_EXPORT DllCanUnloadNow() {
    return g_ObjectsInUse == 0 ? S_OK : S_FALSE;
}
