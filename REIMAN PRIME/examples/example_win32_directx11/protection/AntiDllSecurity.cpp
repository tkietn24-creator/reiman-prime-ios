#include "AntiDllSecurity.h"
#include <psapi.h>
#include <windows.h>
#include <thread>
#include <atomic>
#include <vector>
#include <vector>
#include <string>

std::atomic<bool> AntiDllSecurity::isMonitoring = false;
std::vector<std::string> AntiDllSecurity::initialModules;

std::string GetModuleName(HMODULE hModule) {
    char moduleName[MAX_PATH];
    if (GetModuleFileNameExA(GetCurrentProcess(), hModule, moduleName, sizeof(moduleName) / sizeof(char))) {
        return std::string(moduleName);
    }
    return "";
}

void AntiDllSecurity::CaptureInitialModules() {
    HMODULE hMods[1024];
    DWORD cbNeeded;
    if (EnumProcessModules(GetCurrentProcess(), hMods, sizeof(hMods), &cbNeeded)) {
        for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
            std::string moduleName = GetModuleName(hMods[i]);
            initialModules.push_back(moduleName);
        }
    }
}

bool AntiDllSecurity::IsInjectedLibrary() {
    HMODULE hMods[1024];
    DWORD cbNeeded;
    bool suspiciousDllFound = false;

    if (EnumProcessModules(GetCurrentProcess(), hMods, sizeof(hMods), &cbNeeded)) {
        for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
            std::string currentModuleName = GetModuleName(hMods[i]);
            bool found = false;

            for (const auto& initialModule : initialModules) {
                if (currentModuleName == initialModule) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                suspiciousDllFound = true;
                break;
            }
        }
    }
    return suspiciousDllFound;
}

void AntiDllSecurity::PatchLoadLibraryA() {
    HMODULE kernelModule = GetModuleHandleW(L"kernelbase.dll");
    FARPROC loadLibraryA = GetProcAddress(kernelModule, "LoadLibraryA");
    BYTE hookedCode[] = { 0xC2, 0x04, 0x00 };

    SIZE_T writtenBytes;
    WriteProcessMemory(GetCurrentProcess(), loadLibraryA, hookedCode, sizeof(hookedCode), &writtenBytes);
}

void AntiDllSecurity::PatchLoadLibraryW() {
    HMODULE kernelModule = GetModuleHandleW(L"kernelbase.dll");
    FARPROC loadLibraryW = GetProcAddress(kernelModule, "LoadLibraryW");
    BYTE hookedCode[] = { 0xC2, 0x04, 0x00 };

    SIZE_T writtenBytes;
    WriteProcessMemory(GetCurrentProcess(), loadLibraryW, hookedCode, sizeof(hookedCode), &writtenBytes);
}

void AntiDllSecurity::EnableBinarySignatureMitigation() {
    PROCESS_MITIGATION_BINARY_SIGNATURE_POLICY policy = {};
    policy.MicrosoftSignedOnly = 1;

    SetProcessMitigationPolicy(ProcessSignaturePolicy, &policy, sizeof(policy));
}

void AntiDllSecurity::ApplyProtections() {
    EnableBinarySignatureMitigation();
}

void AntiDllSecurity::MonitorForDllInjection() {
    while (isMonitoring) {
        if (IsInjectedLibrary()) {
            MessageBoxW(NULL, L"Suspicious DLL detected during runtime!", L"Security Alert", MB_ICONERROR);
            ExitProcess(1);
        }
        Sleep(1000);
    }
}

void AntiDllSecurity::StartMonitoring() {
    CaptureInitialModules();
    isMonitoring = true;
    std::thread monitoringThread(MonitorForDllInjection);
    monitoringThread.detach();
}

void AntiDllSecurity::StopMonitoring() {
    isMonitoring = false;
}
