#ifndef ANTIDLLSECURITY_H
#define ANTIDLLSECURITY_H

#include <Windows.h>
#include <Psapi.h>
#include <string>
#include <algorithm>
#include <thread>
#include <vector>
#include <atomic>

class AntiDllSecurity {
public:
    static std::atomic<bool> isMonitoring;
    static void PatchLoadLibraryA();
    static void PatchLoadLibraryW();
    static void EnableBinarySignatureMitigation();
    static bool IsInjectedLibrary();
    static void ApplyProtections();
    static void CaptureInitialModules();
    static void MonitorForDllInjection();
    static void StartMonitoring();
    static void StopMonitoring();
    static std::vector<std::string> initialModules;
};

#endif
