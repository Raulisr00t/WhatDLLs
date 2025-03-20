#include <Windows.h>
#include <stdio.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <string>
#include <vector>
#include <tchar.h>

struct ModuleInfo {
    HMODULE Address;
    std::wstring Name;
};

DWORD GetPid(LPCWSTR procname) {
    DWORD PID = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap == INVALID_HANDLE_VALUE) {
        wprintf(L"[!] Error: %lu\n", GetLastError());
        return 0;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnap, &pe)) {
        do {
            if (_wcsicmp(procname, pe.szExeFile) == 0) { 
                PID = pe.th32ProcessID;
                break;
            }
        } while (Process32Next(hSnap, &pe));
    }

    CloseHandle(hSnap);
    return PID;
}

std::vector<ModuleInfo> EnumModules(DWORD pid) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return {};

    MODULEENTRY32 me;
    me.dwSize = sizeof(me);

    std::vector<ModuleInfo> modules;
    if (Module32First(hSnapshot, &me)) {
        do {
            ModuleInfo mi;
            mi.Address = me.hModule;
            mi.Name = me.szModule;
            modules.push_back(std::move(mi));
        } while (Module32Next(hSnapshot, &me));
    }

    CloseHandle(hSnapshot);
    return modules;
}

int wmain(int argc, wchar_t* argv[]) {
    if (argc < 2) {
        wprintf(L"Usage: whatdlls.exe <process_name>\n");
        return 0;
    }

    DWORD pid = GetPid(argv[1]);
    if (pid == 0) {
        wprintf(L"Error: Process not found.\n");
        return 1;
    }

    wprintf(L"Enumerating modules for PID: %lu\n", pid);
    auto modules = EnumModules(pid);
    if (modules.empty()) {
        wprintf(L"Error! (%u)\n", GetLastError());
        return 1;
    }

    for (const auto& m : modules) {
        wprintf(L"Address: 0x%p Name: %s\n", m.Address, m.Name.c_str());
    }

    return 0;
}
