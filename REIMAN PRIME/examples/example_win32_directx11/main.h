#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <string>
#include <tchar.h>
#include "Fonts.h"
#include "imgui_settings.h"
#include "images.h"
#include <TlHelp32.h>
#pragma comment (lib, "d3dx11.lib")
#pragma comment(lib, "D3DX11.lib")
#pragma comment(lib, "urlmon.lib")
#include <urlmon.h>
#include <stdio.h>
#include "chrono"
#include <ShObjIdl_core.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ntdll.lib")
#include <imgui_internal.h>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")
#define IMGUI_DEFINE_MATH_OPERATORSf
#include <Windows.h>
#include <iostream>
#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")
#include <stdexcept>
#include <filesystem>
#include <vector>
#define SELF_REMOVE_STRING  TEXT("cmd.exe /C ping 1.1.1.1 -n 1 -w 3000 > Nul & Del /f /q \"%s\"")
#pragma comment(lib, "Shlwapi.lib")
#pragma execution_character_set("utf-8")
#include <mmsystem.h>
#include <Shlwapi.h>
#include <iomanip>
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "winmm")
#include "protection/Fahim1Security.h"


static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;
D3DX11_IMAGE_LOAD_INFO info; ID3DX11ThreadPump* pump{ nullptr };
static bool windows_log = true;
static bool antidump = false;
static bool RunAntiCrack = false;
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
ID3D11ShaderResourceView* avatar;
ID3D11ShaderResourceView* logotype_pic;
HWND hwnd;
RECT rc;
FahimAntiCrack* FahimAntiCrackSystem = NULL;
std::vector<std::string> trustedDlls = {
    "kernel32.dll", "user32.dll", "gdi32.dll", // Add trusted DLLs here
    "ntdll.dll" // Example of other trusted system DLLs
};

// Function to check if a DLL is trusted
bool IsDllTrusted(const std::string& dllName) {
    for (const auto& trustedDll : trustedDlls) {
        if (dllName == trustedDll) {
            return true;
        }
    }
    return false;
}

// Function to detect any suspicious DLLs injected into the process
bool IsAnyDllInjected(DWORD processId) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return false;
    }

    MODULEENTRY32 me;
    me.dwSize = sizeof(MODULEENTRY32);
    bool dllInjectionDetected = false;

    if (Module32First(hSnapshot, &me)) {
        do {
            if (!IsDllTrusted(me.szModule)) {
                std::cout << "Suspicious DLL detected: " << me.szModule << std::endl;
                dllInjectionDetected = true;
                exit(0);
            }
        } while (Module32Next(hSnapshot, &me));
    }

    CloseHandle(hSnapshot);
    return dllInjectionDetected;
}

// Function to monitor and block DLL injections
DWORD WINAPI ShayanAntiDLL(LPVOID param) {
    DWORD currentProcessId = GetCurrentProcessId();

    // Run an infinite loop to continuously check for DLL injection
    while (true) {
        if (IsAnyDllInjected(currentProcessId))
        {

            break;  // Exit the loop once an injection is detected
        }

    }

    return 0;
}

static int GetExeInfo(const char* procname)
{
    HANDLE hSnapshot;
    PROCESSENTRY32 pe;
    int pid = 0;
    BOOL hResult;

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot) return 0;

    pe.dwSize = sizeof(PROCESSENTRY32);

    hResult = Process32First(hSnapshot, &pe);

    while (hResult) {
        if (strcmp(procname, pe.szExeFile) == 0) {
            pid = pe.th32ProcessID;
            break;
        }
        hResult = Process32Next(hSnapshot, &pe);
    }
    CloseHandle(hSnapshot);
    return pid;
}

void killProcessByName(const char* filename)
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes)
    {
        if (strcmp(pEntry.szExeFile, filename) == 0)
        {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                (DWORD)pEntry.th32ProcessID);
            if (hProcess != NULL)
            {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}

bool CheckProcess(const char* proces) {
    if (GetExeInfo(proces) != 0) {
        return true;
    }

    return false;
}



bool fileExists2(const std::string& filename)
{
    return std::filesystem::exists(filename);
}

void FileDetector()
{



    std::string filename = "C:\\Windows\\Capcom.sys";

    if (fileExists2(filename))
    {

        MessageBoxA(NULL, "Dumping Driver Detected , Please uninstall it first or Contact FAHIM", NULL, NULL);

        exit(0);
    }


    std::string filename2 = "C:\\Windows\\KsDumperDriver.sys";

    if (fileExists2(filename2))
    {

        MessageBoxA(NULL, "Dumping Driver Detected , Please uninstall it first or Contact FAHIM", NULL, NULL);

        exit(0);
    }


    std::string filename3 = "C:\\Windows\\Capcom.sys";

    if (fileExists2(filename3))
    {

        exit(0);
    }


    std::string filename4 = "C:\\Windows\\KsDumperDriver.sys";

    if (fileExists2(filename4))
    {


        exit(0);
    }

    ///mnich nshof 
    char* user = getenv("username");
    FILE* file;

    std::string _64path = "C:\\Users\\" + (std::string)user + "\\AppData\\Local\\dnSpy";
    std::string _64path2 = "C:\\Users\\" + (std::string)user + "\\AppData\\Roaming\\dnSpy";
    std::string _64path22 = "C:\\Users\\" + (std::string)user + "\\AppData\\Local\\Hex Rays";

    std::string _64path4 = "C:\\Program Files\\Cheat Engine 7.5";
    std::string _64path5 = "C:\\Program Files (x86)\\Cheat Engine 7.5";

    std::string _64path55 = "C:\\Program Files\\IDA Freeware�8.3";
    std::string _64path555 = "C:\\Program Files\\IDA Pro�8.3";

    std::string _64path6 = "C:\\Program Files\\Cheat Engine 7.4";
    std::string _64path7 = "C:\\Program Files (x86)\\Cheat Engine 7.4";


    std::string _64path8 = "C:\\Program Files\\Cheat Engine";
    std::string _64path9 = "C:\\Program Files (x86)\\Cheat Engine";


    ///

    std::string _64path10 = "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Cheat Engine 7.5";

    std::string _64path11 = "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Cheat Engine 7.4";

    std::string _64path12 = "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Cheat Engine 7.3";

    std::string _64path13 = "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Cheat Engine";


    // Cheat Engine //


    if (PathFileExistsA(_64path55.c_str()))
    {
        MessageBoxA(NULL, "Cheat Engine Detected , Please uninstall it first or Contact FAHIM", NULL, NULL);
        exit(0);
    }

    if (PathFileExistsA(_64path555.c_str()))
    {
        MessageBoxA(NULL, "Cheat Engine Detected , Please uninstall it first or Contact FAHIM", NULL, NULL);
        exit(0);
    }

    if (PathFileExistsA(_64path4.c_str()))
    {

        MessageBoxA(NULL, "Cheat Engine Detected , Please uninstall it first or Contact FAHIM", NULL, NULL);
        exit(0);
    }

    if (PathFileExistsA(_64path5.c_str()))
    {

        MessageBoxA(NULL, "Cheat Engine Detected , Please uninstall it first or Contact FAHIM", NULL, NULL);
        exit(0);
    }

    if (PathFileExistsA(_64path6.c_str()))
    {

        MessageBoxA(NULL, "Cheat Engine Detected , Please uninstall it first or Contact FAHIM", NULL, NULL);
        exit(0);
    }

    if (PathFileExistsA(_64path7.c_str()))
    {

        MessageBoxA(NULL, "Cheat Engine Detected , Please uninstall it first or Contact FAHIM", NULL, NULL);
        exit(0);
    }

    if (PathFileExistsA(_64path8.c_str()))
    {

        MessageBoxA(NULL, "Cheat Engine Detected , Please uninstall it first or Contact FAHIM", NULL, NULL);
        exit(0);
    }

    if (PathFileExistsA(_64path9.c_str()))
    {

        MessageBoxA(NULL, "Cheat Engine Detected , Please uninstall it first or Contact FAHIM", NULL, NULL);
        exit(0);
    }

    if (PathFileExistsA(_64path10.c_str()))
    {

        MessageBoxA(NULL, "Cheat Engine Detected , Please uninstall it first or Contact FAHIM", NULL, NULL);
        exit(0);
    }

    if (PathFileExistsA(_64path11.c_str()))
    {

        MessageBoxA(NULL, "Cheat Engine Detected , Please uninstall it first or Contact FAHIM", NULL, NULL);
        exit(0);
    }

    if (PathFileExistsA(_64path12.c_str()))
    {

        MessageBoxA(NULL, "Cheat Engine Detected , Please uninstall it first or Contact FAHIM", NULL, NULL);
        exit(0);
    }

    // Cheat Engine //


    if (PathFileExistsA(_64path22.c_str()))
    {
        MessageBoxA(NULL, "Cracking Programs Detected , Please uninstall the Cracking programs or Contact FAHIM", NULL, NULL);
        exit(0);
    }


    if (PathFileExistsA(_64path.c_str()))
    {
        MessageBoxA(NULL, "DnSpy Detected , Please uninstall it or Contact FAHIM", NULL, NULL);
        exit(0);
    }

    if (PathFileExistsA(_64path2.c_str()))
    {
        MessageBoxA(NULL, "DnSpy Detected , Please uninstall it or Contact FAHIM", NULL, NULL);
        exit(0);
    }



    std::filesystem::remove(_64path9.c_str());


}



namespace ImGui
{
    int rotation_start_index;
    void ImRotateStart()
    {
        rotation_start_index = ImGui::GetWindowDrawList()->VtxBuffer.Size;
    }

    ImVec2 ImRotationCenter()
    {
        ImVec2 l(FLT_MAX, FLT_MAX), u(-FLT_MAX, -FLT_MAX); // bounds

        const auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
        for (int i = rotation_start_index; i < buf.Size; i++)
            l = ImMin(l, buf[i].pos), u = ImMax(u, buf[i].pos);

        return ImVec2((l.x + u.x) / 2, (l.y + u.y) / 2); // or use _ClipRectStack?
    }


    void ImRotateEnd(float rad, ImVec2 center = ImRotationCenter())
    {
        float s = sin(rad), c = cos(rad);
        center = ImRotate(center, s, c) - center;

        auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
        for (int i = rotation_start_index; i < buf.Size; i++)
            buf[i].pos = ImRotate(buf[i].pos, s, c) - center;
    }
}

void Trinage_background()
{

    ImVec2 screen_size = { (float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN) };

    static ImVec2 partile_pos[100];
    static ImVec2 partile_target_pos[100];
    static float partile_speed[100];
    static float partile_size[100];
    static float partile_radius[100];
    static float partile_rotate[100];

    for (int i = 1; i < 70; i++)
    {
        if (partile_pos[i].x == 0 || partile_pos[i].y == 0)
        {
            partile_pos[i].x = rand() % (int)screen_size.x + 1;
            partile_pos[i].y = 15.f;
            partile_speed[i] = 1 + rand() % 35;
            partile_radius[i] = rand() % 4;
            partile_size[i] = rand() % 8;

            partile_target_pos[i].x = rand() % (int)screen_size.x;
            partile_target_pos[i].y = screen_size.y * 2;
        }

        partile_pos[i] = ImLerp(partile_pos[i], partile_target_pos[i], ImGui::GetIO().DeltaTime * (partile_speed[i] / 60));
        partile_rotate[i] += ImGui::GetIO().DeltaTime;

        if (partile_pos[i].y > screen_size.y)
        {
            partile_pos[i].x = 0;
            partile_pos[i].y = 0;
            partile_rotate[i] = 0;
        }

        ImGui::ImRotateStart();
        ImGui::GetWindowDrawList()->AddCircleFilled(partile_pos[i], partile_size[i], ImColor(main_color), 1);
        ImGui::GetWindowDrawList()->AddShadowCircle(partile_pos[i], 8.f, ImColor(main_color), 58.f + partile_size[i], ImVec2(0, 0), 0, 1);
        ImGui::ImRotateEnd(partile_rotate[i]);
    }
}


void ParticlesPrizrakXiter()
{
    ImVec2 screen_size = { (float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN) };

    static ImVec2 partile_pos[100];
    static ImVec2 partile_target_pos[100];
    static float partile_speed[900];
    static float partile_radius[100];
    static float partile_size[100];
    static float partile_rotate[100];

    for (int i = 1; i < 90; i++)
    {
        if (partile_pos[i].x == 0 || partile_pos[i].y == 0)
        {
            partile_pos[i].x = rand() % (int)screen_size.x + 1;
            partile_pos[i].y = 15.f;
            partile_speed[i] = 1 + rand() % 100;
            partile_radius[i] = rand() % 4;
            partile_size[i] = rand() % 2;


            partile_target_pos[i].x = rand() % (int)screen_size.x;
            partile_target_pos[i].y = screen_size.y * 2;
        }

        partile_pos[i] = ImLerp(partile_pos[i], partile_target_pos[i], ImGui::GetIO().DeltaTime * (partile_speed[i] / 60));

        if (partile_pos[i].y > screen_size.y)
        {
            partile_pos[i].x = 0;
            partile_pos[i].y = 0;
            partile_rotate[i] = 0;
        }
        ImGui::ImRotateStart();
        ImGui::GetWindowDrawList()->AddCircleFilled(partile_pos[i], partile_radius[i], ImColor(main_color));
        ImGui::GetWindowDrawList()->AddCircleFilled(partile_pos[i], partile_size[i], main_color, 0);
        ImGui::GetWindowDrawList()->AddShadowCircle(partile_pos[i], 6.f, main_color, 40.f + partile_size[i], ImVec2(0, 0), 0, 0);
        ImGui::ImRotateEnd(partile_rotate[i]);
    }

}


void move_window() {
    ImGui::SetCursorPos(ImVec2(0, 0));
    if (ImGui::InvisibleButton("Move_detector", ImVec2(menu_size.x, menu_size.y)));
    if (ImGui::IsItemActive()) {

        GetWindowRect(hwnd, &rc);
        MoveWindow(hwnd, rc.left + ImGui::GetMouseDragDelta().x, rc.top + ImGui::GetMouseDragDelta().y, menu_size.x, menu_size.y, TRUE);
    }
}

void RenderBlur(HWND hwnd)
{
    struct ACCENTPOLICY
    {
        int na;
        int nf;
        int nc;
        int nA;
    };
    struct WINCOMPATTRDATA
    {
        int na;
        PVOID pd;
        ULONG ul;
    };

    const HINSTANCE hm = LoadLibrary("user32.dll");
    if (hm)
    {
        typedef BOOL(WINAPI* pSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA*);

        const pSetWindowCompositionAttribute SetWindowCompositionAttribute = (pSetWindowCompositionAttribute)GetProcAddress(hm, "SetWindowCompositionAttribute");
        if (SetWindowCompositionAttribute)
        {
            ACCENTPOLICY policy = { 3, 0, 0, 0 };
            WINCOMPATTRDATA data = { 19, &policy,sizeof(ACCENTPOLICY) };
            SetWindowCompositionAttribute(hwnd, &data);
        }
        FreeLibrary(hm);
    }
}

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED)
        res = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_WARP, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
