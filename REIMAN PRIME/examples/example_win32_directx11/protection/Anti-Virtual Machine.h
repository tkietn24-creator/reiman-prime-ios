

bool isDebuggerViaPEB() {
#ifdef _M_IX86  // 32-bit
    return ((*(PBYTE*)__readfsdword(0x30))[2] != 0);
#elif _M_X64    // 64-bit
    return ((*(PBYTE*)__readgsqword(0x60))[2] != 0);
#endif
}



void checkPEBDebug() {
    if (isDebuggerViaPEB()) {
        MessageBoxA(0, "Debugger Detected via PEB!", "PEB", MB_ICONERROR);
        ExitProcess(0);
    }
}


bool hasHardwareBreakpoints1() {
    CONTEXT ctx = {};
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;

    if (GetThreadContext(GetCurrentThread(), &ctx)) {
        return (ctx.Dr0 || ctx.Dr1 || ctx.Dr2 || ctx.Dr3);
    }

    return false;
}

void checkHardwareBreakpoints() {
    if (hasHardwareBreakpoints1()) {
        MessageBoxA(0, "Hardware Breakpoints Detected!", "Anti-Debug", MB_ICONERROR);
        ExitProcess(0);
    }
}


#include <Windows.h>
#include <winternl.h>

typedef NTSTATUS(NTAPI* NtQueryInformationProcessPtr)(
    HANDLE,
    PROCESSINFOCLASS,
    PVOID,
    ULONG,
    PULONG
    );

bool isDebugPortOpen() {
    HMODULE hNtDll = GetModuleHandleA("ntdll.dll");
    if (!hNtDll) return false;

    auto NtQueryInformationProcess = (NtQueryInformationProcessPtr)GetProcAddress(hNtDll, "NtQueryInformationProcess");
    if (!NtQueryInformationProcess) return false;

    DWORD debugPort = 0;
    NTSTATUS status = NtQueryInformationProcess(
        GetCurrentProcess(),
        (PROCESSINFOCLASS)0x7,  // ProcessDebugPort
        &debugPort,
        sizeof(debugPort),
        nullptr
    );

    return (NT_SUCCESS(status) && debugPort != 0);
}

void checkDebugPort() {
    if (isDebugPortOpen()) {
        MessageBoxA(0, "Debugger Detected via DebugPort!", "Anti-Debug", MB_ICONERROR);
        ExitProcess(0);
    }
}

bool isAnalysisToolRunning() {
    const char* suspiciousWindows[] = {
        "Cheat Engine",
        "x64dbg",
        "x32dbg",
        "x64dbg.exe",
        "scylla",           // Scylla
        "OllyDbg",
        "IDA",              // IDA Pro
        "Process Hacker",
        "Process Explorer",
        "DBG",
        "DbgView",
        "Fiddler",
        "Immunity Debugger"
    };

    for (const char* windowName : suspiciousWindows) {
        if (FindWindowA(nullptr, windowName)) {
            return true;
        }
    }

    return false;
}

void checkAnalysisTools() {
    if (isAnalysisToolRunning()) {
        MessageBoxA(0, "Analysis tool detected!", "Anti-Analysis", MB_ICONERROR);
        ExitProcess(0);
    }
}

bool isVirtualMachine() {
    const char* suspiciousDevices[] = {
        "\\\\.\\VBoxMiniRdrDN",     // VirtualBox
        "\\\\.\\VBoxGuest",
        "\\\\.\\pipe\\VBoxMini",
        "\\\\.\\pipe\\vmware",
        "\\\\.\\HGFS",              // VMware shared folder
        "\\\\.\\vmci",
        "\\\\.\\VBoxMouse",
        "\\\\.\\VBoxSF",
        "\\\\.\\VBoxVideo",
        "\\\\.\\VMSrvc",            // Virtual PC
        "\\\\.\\VMTools",
        "\\\\.\\pipe\\qemu"
    };

    for (const char* device : suspiciousDevices) {
        HANDLE h = CreateFileA(device, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
        if (h != INVALID_HANDLE_VALUE) {
            CloseHandle(h);
            return true;
        }
    }

    return false;
}

void checkVirtualMachine() {
    if (isVirtualMachine()) {
        MessageBoxA(0, "Please Remove Vmwere!", "Anti-VM", MB_ICONERROR);
        ExitProcess(0);
    }
}

bool isFunctionHooked(void* func) {
    BYTE* bytes = (BYTE*)func;


    if (bytes[0] == 0xE9 || bytes[0] == 0xCC || bytes[0] == 0x90) {
        return true;
    }

    return false;
}

void checkForHooks() {
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");

    if (!ntdll) return;

    void* NtQuery = GetProcAddress(ntdll, "NtQueryInformationProcess");
    void* NtClose = GetProcAddress(ntdll, "NtClose");

    if (isFunctionHooked(NtQuery) || isFunctionHooked(NtClose)) {
        MessageBoxA(0, "Hook Detected!", "Anti-Hook", MB_ICONERROR);
        ExitProcess(0);
    }
}

void launchDecoyProcess() {
    STARTUPINFOA si = { 0 };
    PROCESS_INFORMATION pi = { 0 };

    si.cb = sizeof(si);

    // شغل برنامج شكله بريء زي المفكرة
    if (CreateProcessA(
        "C:\\Windows\\System32\\Svchost.exe", 
        nullptr,
        nullptr,
        nullptr,
        FALSE,
        CREATE_NO_WINDOW,
        nullptr,
        nullptr,
        &si,
        &pi
    )) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}


