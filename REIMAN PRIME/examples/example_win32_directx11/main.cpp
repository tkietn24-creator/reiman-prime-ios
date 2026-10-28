#include "main.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "imgui_internal.h"
#include <tchar.h>
#include <dwmapi.h>
#include "auth/json.hpp"
#include "auth/skStr.h"
#include <thread>
#pragma comment(lib, "Dwmapi.lib")
#include <ShObjIdl_core.h>
#include <winhttp.h>
#include "atlsecurity.h"

//#include "Dependencies/Freez.h"
#include "Fonts.h"
#include "image.h"
#include <fstream>
#include <string>
#include "DiscordSDK/src/discord_rpc.h"

//#include "Memory/all.h"
#include "Particles/AnimVector.h"
#include <shlobj.h>
#include <set>
#include "icons.h"
#include "SoundPlayer.h"
#include "protection/AntiDllSecurity.h"
#include "protection/Anti-Virtual Machine.h"
#pragma comment(lib, "normaliz.lib")
#include <windows.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "notification.h"
#include "ChamsPipe.h"
#include "auth/auth.hpp"


bool injectSuccess = false;
static int dnd_counter = 0;
static bool checkbox[50];
static int slider_int = false;
const char* themes[]{ "Head","Chest", "Legs", "Hands" };
const char* auto_stop[]{ "Betwen shots", "Force accuracy", "Power accuracy", "Auto sleep" };
static int combo;
int lag1, lag2, lag3, lag4, lag5, lag6, lag7, lag8, lag9, lag10;
static int keybind, key1, key2, key3, key4, key5, key6, key7, key10, key11;
int lag11;
; static int TabsRB;
static int iTabs;
static int menu_state;
static float text_animation = 0.00f;
static float loader_animation = 0.f;
static bool text_animation_hide = true;
float color_edit[4];
bool authenticed = false;
std::string MemoryLogs = skCrypt("Status:").decrypt();
static int64_t eptime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
bool allDownloaded = true;
extern "C"
{
    NTSTATUS NTAPI NtSuspendProcess(HANDLE ProcessHandle);
    NTSTATUS NTAPI NtResumeProcess(HANDLE ProcessHandle);
}

namespace fonts
{
    ImFont* inter_bold = nullptr;
    ImFont* poppins = nullptr;
    ImFont* roboto = nullptr;
    ImFont* texte = nullptr;
    ImFont* icon = nullptr;
    ImFont* Nevan = nullptr;
}

namespace pic
{
    ID3D11ShaderResourceView* aimbot = nullptr;
    ID3D11ShaderResourceView* shieldoxcy = nullptr;
    ID3D11ShaderResourceView* visuals = nullptr;
    ID3D11ShaderResourceView* skins = nullptr;
    ID3D11ShaderResourceView* settings = nullptr;
    ID3D11ShaderResourceView* combo_widget = nullptr;
    ID3D11ShaderResourceView* input_widget = nullptr;
    ID3D11ShaderResourceView* menu_settings_icon = nullptr;
    ID3D11ShaderResourceView* circle_success = nullptr;
    ID3D11ShaderResourceView* circle_error = nullptr;
    ID3D11ShaderResourceView* Fahimlogo = nullptr;
}

bool toggleX = false;
bool toggle5 = false;
bool toggle1 = false;
bool toggle = false;
bool toggle2 = false;
bool toggle14 = false;
bool toggle16 = false;
bool isProcessFrozen = false;
bool hotkeypressed1 = false;
bool hotkeypressed2 = false;
bool hotkeypressed3 = false;
int wallkey;
bool ak47;
int showwatermark;
bool Chamsredantena;
bool TWODCHAMS;
bool fixrb;
bool AimbotControl;
bool Chamsesprgbbox;
bool Chamsespbox;
bool scaremotehack;
bool Magicbuttelv1;
bool Magicbuttelv2;
bool m1014emotehack;
bool loademotehack;
bool mp40emote;
bool PinToTop;
bool m82b;
bool sniperscopetrack;
bool fakedamagefix;
bool Magicbuttelv11;
bool Speedhackprizrakxiter;
bool Camerahackprizrakxiter;
bool Blackskyprizrakxiter;
bool snipercopetracking;
bool famasemotehack;
bool Vbadgeprizrakxiter;
bool anticheatprizrakxiter;
bool antiblacklistpriztakxiter;
bool xm8emotehack;
bool aimbottracking1;
bool camera;
bool speed;
bool cameracontrol;
bool SpeedControl;
bool internet;
bool aimbotex;
bool resetguest;
bool aimbotex2;
bool aimbotv2;
bool aimbotdrag;
bool MinimizeKey = false;
bool allswitch;
bool sniperdelay;
bool glitchfire;
bool externaloff;
bool bwallhack;
bool snipercope;
bool allsniperswitch;
bool sniperaim;
bool quicksniper;
bool aimfov;
bool norecoil;
bool headtracking;
bool nr;
bool mg;
bool snipercopefov;
bool wx;
bool bfastreload;
bool Charms2D;
bool charms3D;
bool wallhackv2;
bool chams;
bool charmsmenu;
bool stream;
bool ModeStream = false;
static bool selfdestruct = false;
bool scope;
bool scope4x;
bool blacksky;
bool cameraup;
bool speedex;
bool speedbypass;
bool wallhackbypas;
bool camerabypass;
bool emubypass;
bool camerav1;
bool camerav2;
bool camerav3;
bool sniperscope2;
bool sniperswitch2;
bool hdcursor;
bool onlyred;
bool FastMadikit;
bool bfakelag1;
bool aimawm;
bool aimbotscope;
bool aimfov180;
bool aimbotboady;
bool femalefix;
bool leandinContorl;
bool leandin;
bool Charms2D1;
bool bigdamage;
bool Awmlocation;
bool fastrevive;
bool RemoveTrojen;
bool OptimizePc;
bool esp1;
bool esp2;
bool esp3;
bool antii22;
bool esp4;
bool esp5;
bool esp6;
bool esp7;
bool esp8;
bool esp9;
bool esp10;
bool esp99;
bool esp98;
bool loadInternalCheat;
bool aimbotfix;
bool Loadflyhack1;
bool flaycontroll;
bool FastLandingControl;
bool chams1;
bool chams2;
bool chams3;
bool chams4;

namespace var
{
    bool OptimizePc;
    bool xm8emotehack;
    bool RemoveTrojen;
    bool allsniperswitch;
    bool Chamsredantena;
    bool Chamsesprgbbox;
    bool Chamsespbox;
    bool balasmagicv1;
    bool fakedamagefix;
    bool balasmagicv2;
    bool ak47;
    bool snipercope;
    bool snipercopefov;
    bool wallhackv2;
    bool balasmagicv11;
    bool bfastreload;
    bool PinToTop;
    bool famasemotehack;
    bool speedhackprizrak;
    bool snipercopetracking;
    bool mp40emote;
    bool resetguest;
    bool camerahackv2;
    bool m1014emotehack;
    bool loademotehack;
    bool TWODCHAMS;
    bool scaremotehack;
    bool vbadge;
    bool AimbotControl;
    bool m82b;
    bool anticheatprizrak;
    bool sniperscopetrack;
    bool anticheatprizrakxiter;
    bool antiblacklistpriztakxiter;
    bool aimawm;
    bool allswitch;
    bool speed;
    bool camera;
    bool cameracontrol;
    bool SpeedControl;
    bool sniperdelay;
    bool glitchfire;
    bool sniperswitch2;
    bool sniperscope2;
    bool camerav1;
    bool camerav2;
    bool camerav3;
    bool internet;
    bool emubypass;
    bool speedbypass;
    bool wallhackbypas;
    bool camerabypass;
    bool speedex;
    bool cameraup;
    bool blacksky;
    bool aimbotv2;
    bool scope;
    bool scope4x;
    bool onlyred;
    bool fastreload;
    bool ModeStream = false;
    bool aimbotex;
    bool fixrb;
    bool aimbotex2;
    bool aimbotdrag;
    bool externaloff;
    bool sniperscope;
    bool mg;
    bool norecoil;
    bool Sniperaim;
    bool quicksniper;
    bool aimfov;
    bool headtracking;
    bool nr;
    bool chams;
    bool charmsmenu;
    bool Charms2D;
    bool charms3D;
    bool wallhack;
    bool hdcursor;
    bool stream;
    bool FastMadikit;
    bool fakelag1;
    bool aimbottracking;
    bool aimbotscope;
    bool aimfov180;
    bool aimbotboady;
    bool femalefix;
    bool leandinContorl;
    bool leandin;
    bool Charms2D1;
    bool bigdamage;
    bool Awmlocation;
    bool fastrevive;
    bool esp1;
    bool esp2;
    bool esp3;
    bool antii22;
    bool esp4;
    bool esp5;
    bool esp6;
    bool esp7;
    bool esp8;
    bool esp9;
    bool esp10;
    bool esp99;
    bool esp98;
    bool loadInternalCheat;
    bool aimbotfix;
    bool Loadflyhack1;
    bool flaycontroll;
    bool FastLandingControl;
    bool chams1;
    bool chams2;
    bool chams3;
    bool chams4;
}





struct c_bytes
{
    std::vector<DWORD_PTR> SpeedHackBytes;
    std::vector<DWORD_PTR> CameraHackBytes;
    std::vector<DWORD_PTR> leandinHackBytes;
    std::vector<DWORD_PTR> EmoteHackBytes;
    std::vector<DWORD_PTR> flyhackHackBytes;
};  c_bytes bytes;


DWORD WINAPI DoWork1(LPVOID lpParam)
{
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Working in Thread 1: " << i << std::endl;
        Sleep(1000);
    }
    return 0;
}

void ImGuiCustomText(const char* text, ImVec2 size, ImU32 backgroundColor, ImU32 textColor)
{
    ImVec2 textSize = ImGui::CalcTextSize(text);
    ImVec2 textPos = ImGui::GetCursorScreenPos();
    ImGui::GetWindowDrawList()->AddRectFilled

    (
        textPos,
        ImVec2(textPos.x + size.x, textPos.y + size.y),
        backgroundColor
    );

    ImVec2 textOffset
    (
        (size.x - textSize.x) * 0.5f,
        (size.y - textSize.y) * 0.5f
    );

    ImVec2 centeredTextPos = ImVec2(textPos.x + textOffset.x, textPos.y + textOffset.y);
    ImGui::SetCursorScreenPos(centeredTextPos);
    ImGui::PushStyleColor(ImGuiCol_Text, textColor);
    ImGui::Text(text);
    ImGui::PopStyleColor();
}

bool RemoveFileIfExists(const char* filePath) {
    return DeleteFileA(filePath) != 0;
}
bool FileExists(const std::string& path)
{
    std::ifstream file(path);
    return file.good();
}


static char login[64] = { "" };
static char Key[64] = { "" };
static char pass[64] = { "" };







DWORD ProcessId = 0;
HANDLE ProcessHandle;

int GetPid(const char* procname)
{
    if (procname == NULL) return 0;
    DWORD pid = 0;
    DWORD threadCount = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    Process32First(hSnap, &pe);
    while (Process32Next(hSnap, &pe)) {
        if (_tcsicmp(pe.szExeFile, procname) == 0) {
            if ((int)pe.cntThreads > threadCount) {
                threadCount = pe.cntThreads;
                pid = pe.th32ProcessID;
            }
        }
    }
    return pid;
}
#include <windows.h>
DWORD GetProcId(const char* procName)
{
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);
        if (Process32First(hSnap, &procEntry)) {
            do {
                if (!_stricmp(procEntry.szExeFile, procName))
                {
                    procId = procEntry.th32ProcessID; https://discord.gg/vzKWFcMqxc
                break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}

BOOL AttackProcess(const char* procname)
{
    DWORD ProcId = GetPid(procname);
    if (ProcId == 0) return false;
    ProcessId = ProcId;
    ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, ProcessId);
    return ProcessHandle != nullptr;
}

const char* GetEmulatorRunning()
{
    if (GetPid(skCrypt("HD-Player.exe").decrypt()) != 0)
        return skCrypt("HD-Player.exe").decrypt();
    else if (GetPid("MEmuHeadless.exe") != 0)
        return "MEmuHeadless.exe";
    else if (GetPid("LdVBoxHeadless.exe") != 0)
        return "LdVBoxHeadless.exe";
    else if (GetPid("AndroidProcess.exe") != 0)
        return "AndroidProcess.exe";
    else if (GetPid("Nox.exe") != 0)
        return "Nox.exe";
    return nullptr;
}
std::thread scopeThread;
std::atomic<bool> stopThread(false);


bool keepBlocking = true;

void BlockTaskManager() {
    while (keepBlocking) {
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnap != INVALID_HANDLE_VALUE) {
            PROCESSENTRY32 pe;
            pe.dwSize = sizeof(pe);
            if (Process32First(hSnap, &pe)) {
                do {
                    if (_stricmp(pe.szExeFile, "Taskmgr.exe") == 0) {
                        HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
                        if (hProc) {
                            TerminateProcess(hProc, 0);
                            CloseHandle(hProc);
                        }
                    }
                } while (Process32Next(hSnap, &pe));
            }
            CloseHandle(hSnap);
        }
        Sleep(500);



    }
}

PipeClient client;

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  

    WNDCLASSEXW wc;
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = NULL;
    wc.cbWndExtra = NULL;
    wc.hInstance = nullptr;
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = L"REIMAN PRIME";
    wc.lpszClassName = L"REIMAN PRIME";
    wc.hIconSm = LoadIcon(0, IDI_APPLICATION);
    RegisterClassExW(&wc);
    hwnd = CreateWindowExW(NULL, wc.lpszClassName, L"REIMAN PRIME", WS_POPUP, (GetSystemMetrics(SM_CXSCREEN) / 2) - (menu_size.x / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (menu_size.y / 2), menu_size.x, menu_size.y, 0, 0, 0, 0);
    SetWindowLongA(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 255, LWA_ALPHA);
    MARGINS margins = { -1 };
    DwmExtendFrameIntoClientArea(hwnd, &margins);
    SetWindowRgn(hwnd, CreateRoundRectRgn(0, 0, menu_size.x, menu_size.y, 10, 10), TRUE);
    POINT mouse;
    rc = { 0 };
    GetWindowRect(hwnd, &rc);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.Fonts->AddFontFromMemoryTTF(&inter_bold, sizeof inter_bold, 17.f, NULL, io.Fonts->GetGlyphRangesCyrillic());

    io.Fonts->AddFontFromMemoryTTF(&PoppinsRegular, sizeof PoppinsRegular, 22, NULL, io.Fonts->GetGlyphRangesCyrillic());

    bold_font = io.Fonts->AddFontFromMemoryTTF(&PoppinsBold, sizeof PoppinsBold, 40, NULL, io.Fonts->GetGlyphRangesCyrillic());

    semibold_font = io.Fonts->AddFontFromMemoryTTF(&SFProDisplaySemibold, sizeof SFProDisplaySemibold, 15, NULL, io.Fonts->GetGlyphRangesCyrillic());

    semibold_font1 = io.Fonts->AddFontFromMemoryTTF(&SFProDisplaySemibold, sizeof SFProDisplaySemibold, 30, NULL, io.Fonts->GetGlyphRangesCyrillic());

    bold_font1 = io.Fonts->AddFontFromMemoryTTF(&Nevan, sizeof Nevan, 40, NULL, io.Fonts->GetGlyphRangesCyrillic());

    bold_font2 = io.Fonts->AddFontFromMemoryTTF(&Nevan, sizeof Nevan, 30, NULL, io.Fonts->GetGlyphRangesCyrillic());

    second_font = io.Fonts->AddFontFromMemoryTTF(&PoppinsRegular, sizeof PoppinsRegular, 18, NULL, io.Fonts->GetGlyphRangesCyrillic());

    second_font1 = io.Fonts->AddFontFromMemoryTTF(&PoppinsRegular, sizeof PoppinsRegular, 25, NULL, io.Fonts->GetGlyphRangesCyrillic());


    icon_font = io.Fonts->AddFontFromMemoryTTF(&icomoon, sizeof icomoon, 20, NULL, io.Fonts->GetGlyphRangesCyrillic());

    fonts::roboto = io.Fonts->AddFontFromMemoryTTF(&Nevan, sizeof Nevan, 22, NULL, io.Fonts->GetGlyphRangesCyrillic());

    if (pic::input_widget == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, input_widget, sizeof(input_widget), &info, pump, &pic::input_widget, 0);

    if (pic::combo_widget == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, combo_widget, sizeof(combo_widget), &info, pump, &pic::combo_widget, 0);

    if (pic::Fahimlogo == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, Fahimlogo, sizeof(Fahimlogo), &info, pump, &pic::Fahimlogo, 0);

    if (pic::aimbot == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, aimbot, sizeof(aimbot), &info, pump, &pic::aimbot, 0);


    if (pic::aimbot == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, aimbot, sizeof(aimbot), &info, pump, &pic::aimbot, 0);
    if (pic::visuals == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, visuals, sizeof(visuals), &info, pump, &pic::visuals, 0);
    if (pic::skins == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, skins, sizeof(skins), &info, pump, &pic::skins, 0);
    if (pic::settings == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, settings, sizeof(settings), &info, pump, &pic::settings, 0);

    if (pic::shieldoxcy == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, shieldoxcy, sizeof(shieldoxcy), &info, pump, &pic::shieldoxcy, 0);

    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    ImVec4 clear_color = ImVec4(0.6f, 0.6f, 0.6f, 1.00f);
    ImGuiStyle& s = ImGui::GetStyle();

    s.FramePadding = ImVec2(5, 3);
    s.WindowPadding = ImVec2(0, 0);
    s.FrameRounding = 8.f;
    s.WindowRounding = 8.f;
    s.WindowBorderSize = 0.f;
    s.PopupBorderSize = 0.f;
    s.WindowPadding = ImVec2(0, 0);
    s.ChildBorderSize = 10;
    s.WindowShadowSize = 0;
    int Fix = 0;

    bool done = false;
    while (!done)
    {
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {
            ImGuiStyle* style = &ImGui::GetStyle();
            style->WindowPadding = ImVec2(0, 0);
            style->WindowBorderSize = 0;
            style->ItemSpacing = ImVec2(10, 10);
            style->ScrollbarSize = 8.f;

            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(497, 497));
            ImGui::Begin(skCrypt("Genral").decrypt(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus); 
            {
                main_window = ImGui::GetCurrentWindow();
                auto draw = ImGui::GetWindowDrawList();
                const auto& p = ImGui::GetWindowPos();
                draw->AddRectFilled(p, p + menu_size, ImColor(10, 10, 10, 200), 2);

                if (menu_state == 1)
                {
                    draw->AddRectFilled(p, p + ImVec2(755, 50), ImColor(10, 10, 10));
                    draw->AddRectFilled(p, p + ImVec2(70, 755), ImColor(10, 10, 10, 20), ImDrawFlags_RoundCornersTop);
                    draw->AddRectFilled(p + ImVec2(0, 50), p + ImVec2(755, 52), second_color);
                    draw->AddRectFilled(p + ImVec2(120, 55), p + ImVec2(122, 755), second_color);


                    if (!loader_animation)
                        loader_animation = GetTickCount();
                    if (GetTickCount() > loader_animation + (1 * 5))
                    {

                        if (text_animation_hide)
                        {
                            if (text_animation < 0.80f)
                                text_animation += 0.04f / ImGui::GetIO().Framerate * 60.f;
                            if (text_animation >= 0.80f)
                                text_animation_hide = false;
                        }

                        else
                        {
                            if (text_animation > 0.00f)
                                text_animation -= 0.04f / ImGui::GetIO().Framerate * 60.f;
                            if (text_animation <= 0.00f)
                                text_animation_hide = true;

                        }
                        loader_animation = 0;
                    }

                    const auto& CurrentWindowPos = ImGui::GetWindowPos();
                    const auto& pWindowDrawList = ImGui::GetWindowDrawList();
                    const auto& pForegroundDrawList = ImGui::GetForegroundDrawList();


                 
                    static double nameStartTime = -1.0;
                    if (nameStartTime < 0.0) nameStartTime = ImGui::GetTime();
                    const double elapsed = ImGui::GetTime() - nameStartTime;
                    const std::string firstWord = "REIMAN";
                    const std::string secondWord = "  PRIME";
                    const float lettersPerSecond = 3.0f;
                    const int totalLetters = (int)firstWord.size() + (int)secondWord.size();
                    const float typeDuration = (float)totalLetters / lettersPerSecond;
                    const float pauseDuration = 0.6f;
                    const float cycleDuration = typeDuration + pauseDuration;
                    const float cyclePos = fmodf((float)elapsed, cycleDuration);
                    int visibleLetters = (cyclePos >= typeDuration)
                        ? totalLetters
                        : (int)floorf(cyclePos * lettersPerSecond);
                    const int firstVisible = (std::min)((int)firstWord.size(), visibleLetters);
                    const int secondVisible = (std::max)(0, visibleLetters - (int)firstWord.size());

                    ImGui::PushFont(fonts::roboto);
                    {
                        // Photo-like reveal: flash effect + photo-developing fade
                        const float appearAnimDuration = 0.35f;
                        const float flashDuration = 0.08f; // quick flash like camera
                        float xCursor = 0.0f;
                        ImVec2 basePosFirst = ImVec2(140, 15);
                        ImDrawList* dl = ImGui::GetForegroundDrawList();

                        for (int i = 0; i < firstVisible; ++i)
                        {
                            float charAppearTime = (float)i / lettersPerSecond;
                            float timeSinceAppear = cyclePos - charAppearTime;
                            if (timeSinceAppear < 0.0f) continue;

                            float t = timeSinceAppear / appearAnimDuration;
                            if (t > 1.0f) t = 1.0f;
                            if (t < 0.0f) t = 0.0f;

                            // Photo flash effect (bright white flash at start)
                            float flashT = timeSinceAppear / flashDuration;
                            bool inFlash = flashT < 1.0f && flashT >= 0.0f;

                            // Photo-developing effect: start with sepia/white, fade to full color
                            float photoT = (t - flashDuration / appearAnimDuration) / (1.0f - flashDuration / appearAnimDuration);
                            if (photoT < 0.0f) photoT = 0.0f;
                            if (photoT > 1.0f) photoT = 1.0f;

                            char buf[2] = { firstWord[(size_t)i], 0 };
                            ImVec2 charSize = ImGui::CalcTextSize(buf);
                            ImVec2 charPos = basePosFirst + ImVec2(xCursor, 0);

                            // Flash effect (bright white glow)
                            if (inFlash)
                            {
                                float flashIntensity = 1.0f - flashT;
                                ImVec4 flashCol = ImVec4(1.0f, 1.0f, 1.0f, flashIntensity * 0.9f);
                                dl->AddRectFilled(charPos - ImVec2(2, 2), charPos + charSize + ImVec2(2, 2), ImGui::GetColorU32(flashCol), 2.0f);
                            }

                            // Photo-developing color transition
                            ImVec4 baseColor = ImGui::ColorConvertU32ToFloat4(ImColor(main_color));
                            if (photoT < 1.0f)
                            {
                                // Start with sepia/white tint, transition to full color
                                float sepiaMix = 1.0f - photoT;
                                baseColor.x = baseColor.x * (1.0f - sepiaMix * 0.3f) + sepiaMix * 0.95f;
                                baseColor.y = baseColor.y * (1.0f - sepiaMix * 0.3f) + sepiaMix * 0.95f;
                                baseColor.z = baseColor.z * (1.0f - sepiaMix * 0.2f) + sepiaMix * 0.9f;
                                baseColor.w *= (0.3f + photoT * 0.7f); // fade in
                            }
                            else
                            {
                                baseColor.w = 1.0f;
                            }

                            ImU32 textCol = ImGui::GetColorU32(baseColor);

                            // Draw with photo-like glow
                            float glowSize = 150.f * (0.5f + photoT * 0.5f);
                            ImGui::ShadowText(buf, textCol, textCol, glowSize, charPos);

                            xCursor += charSize.x;
                        }

                        xCursor = 0.0f;
                        ImVec2 basePosSecond = ImVec2(260, 15);
                        for (int i = 0; i < (std::min)((int)secondWord.size(), secondVisible); ++i)
                        {
                            int absoluteIndex = (int)firstWord.size() + i;
                            float charAppearTime = (float)absoluteIndex / lettersPerSecond;
                            float timeSinceAppear = cyclePos - charAppearTime;
                            if (timeSinceAppear < 0.0f) continue;

                            float t = timeSinceAppear / appearAnimDuration;
                            if (t > 1.0f) t = 1.0f;
                            if (t < 0.0f) t = 0.0f;

                            float flashT = timeSinceAppear / flashDuration;
                            bool inFlash = flashT < 1.0f && flashT >= 0.0f;

                            float photoT = (t - flashDuration / appearAnimDuration) / (1.0f - flashDuration / appearAnimDuration);
                            if (photoT < 0.0f) photoT = 0.0f;
                            if (photoT > 1.0f) photoT = 1.0f;

                            char buf[2] = { secondWord[(size_t)i], 0 };
                            ImVec2 charSize = ImGui::CalcTextSize(buf);
                            ImVec2 charPos = basePosSecond + ImVec2(xCursor, 0);

                            if (inFlash)
                            {
                                float flashIntensity = 1.0f - flashT;
                                ImVec4 flashCol = ImVec4(1.0f, 1.0f, 1.0f, flashIntensity * 0.9f);
                                dl->AddRectFilled(charPos - ImVec2(2, 2), charPos + charSize + ImVec2(2, 2), ImGui::GetColorU32(flashCol), 2.0f);
                            }

                            ImVec4 white = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                            if (photoT < 1.0f)
                            {
                                float sepiaMix = 1.0f - photoT;
                                white.x = white.x * (1.0f - sepiaMix * 0.3f) + sepiaMix * 0.95f;
                                white.y = white.y * (1.0f - sepiaMix * 0.3f) + sepiaMix * 0.95f;
                                white.z = white.z * (1.0f - sepiaMix * 0.2f) + sepiaMix * 0.9f;
                                white.w = 0.3f + photoT * 0.7f;
                            }

                            ImU32 whiteCol = ImGui::GetColorU32(white);
                            float glowSize = 110.f * (0.5f + photoT * 0.5f);
                            ImGui::ShadowText(buf, whiteCol, whiteCol, glowSize, charPos);
                            xCursor += charSize.x;
                        }
                    }
                    ImGui::PopFont();


                    ImGui::PushFont(fonts::inter_bold);
                    ImGui::ShadowText(skCrypt("V1.0").decrypt(), ImColor(255, 0, 0), ImColor(255, 0, 0), 90.f, ImVec2(430, 21));
                    ImGui::PopFont();


                    ImGui::SetCursorPos({ 140, 465 });
                    ImVec2 textSize = ImGui::CalcTextSize(MemoryLogs.c_str());
                    ImVec2 textPos = ImGui::GetCursorScreenPos();
                    ImU32 backgroundColor = ImColor(0, 0, 0);
                    ImGui::GetWindowDrawList()->AddRectFilled(textPos, ImVec2(textPos.x + textSize.x, textPos.y + textSize.y), backgroundColor);
                    ImGui::ShadowText(MemoryLogs.c_str(), ImColor(main_color), ImColor(main_color), 70.f, ImVec2(textPos));

                    ImGui::SetCursorPos(ImVec2(10, 60));
                    ImGui::BeginChild(skCrypt("Tabs").decrypt(), ImVec2(0, 320), false);

                    static int tabs1 = 0, sub_tabs = 0;
                    const ImVec2& spacing = style->ItemSpacing;

                  
                    if (ImGui::IsItemHovered())
                    {
                        ImGui::SetTooltip(" REIMAN PRIME ");
                    }

                    if (ImGui::Tabs(0 == tabs1, pic::aimbot, "Aim", ImVec2(130 - spacing.x * 3, 35), NULL)) tabs1 = 0;
                    if (ImGui::Tabs(1 == tabs1, pic::visuals, "Esp", ImVec2(130 - spacing.x * 3, 35), NULL)) tabs1 = 1;
                    if (ImGui::Tabs(2 == tabs1, pic::skins, "Misc", ImVec2(130 - spacing.x * 3, 35), NULL)) tabs1 = 2;
                    if (ImGui::Tabs(3 == tabs1, pic::settings, "Setting", ImVec2(130 - spacing.x * 3, 35), NULL)) tabs1 = 3;

                    ImGui::EndChild();



                    if (GetAsyncKeyState(key3) & 0x1)
                    {
                        toggle1 = !toggle1;
                        var::cameracontrol = !toggle1;

                        if (toggle1)
                        {
                            std::thread taskThread([]()
                                {
                                    var::camera = false;
                                  
                                });
                            taskThread.detach();
                        }
                        else
                        {
                            std::thread taskThread([]()
                                {
                                    var::camera = true;
                                  
                                });
                            taskThread.detach();
                        }
                    }
                    if (GetAsyncKeyState(key6) & 0x1)
                    {
                        toggle14 = !toggle14;
                        FastLandingControl = !toggle14;

                        if (toggle14)
                        {
                            std::thread taskThread([]()
                                {
                                    FastLandingControl = false;
                                  

                                });
                            taskThread.detach();
                        }
                        else
                        {
                            std::thread taskThread([]()
                                {
                                    FastLandingControl = true;
                                
                                });
                            taskThread.detach();
                        }
                    }

                    if (GetAsyncKeyState(key11) & 0x1)
                    {
                        toggle16 = !toggle16;
                        flaycontroll = !toggle16;

                        if (toggle16)
                        {
                            std::thread taskThread([]()
                                {
                                    flaycontroll = false;
                                   

                                });
                            taskThread.detach();
                        }
                        else
                        {
                            std::thread taskThread([]()
                                {
                                    flaycontroll = true;
                                   
                                });
                            taskThread.detach();
                        }
                    }

                    if (GetAsyncKeyState(key5) & 0x1)
                    {
                        toggle5 = !toggle5;
                        var::AimbotControl = !toggle1;

                        if (toggle5)
                        {
                            std::thread taskThread([]()
                                {
                                    var::aimbotex2 = false;
                                   
                                });
                            taskThread.detach();
                        }
                        else
                        {
                            std::thread taskThread([]()
                                {
                                    var::aimbotex2 = true;
                                    
                                });
                            taskThread.detach();
                        }
                    }

                    if (done)
                        break;
                    if (GetAsyncKeyState(VK_DELETE) & 1)
                    {
                        exit(0);
                    }

                    if (GetAsyncKeyState(VK_HOME) & 0x1)
                    {
                        MinimizeKey = !MinimizeKey;

                        if (MinimizeKey)
                        {
                            ShowWindow(hwnd, SW_MINIMIZE);
                        }
                        else
                        {
                            ShowWindow(hwnd, SW_RESTORE);
                        }
                    }

                    if (GetAsyncKeyState(key7) & 0x1)
                    {
                        toggleX = !toggleX;
                        var::SpeedControl = !toggleX;

                        if (toggleX)
                        {
                            std::thread taskThread([]()
                                {
                                    var::speed = false;
                                   
                                });
                            taskThread.detach();
                        }
                        else
                        {
                            std::thread taskThread([]()
                                {
                                    var::speed = true;
                                 
                                });
                            taskThread.detach();
                        }
                    }
                    /*if (GetAsyncKeyState(lag11) & 0x1)
                    {
                        FreezeHR = !FreezeHR;

                        Beep(500, 400);
                        Beep(FreezeHR ? 1500 : 800, 100);

                        if (FreezeHR)
                        {
                            CreateThread(NULL, 0, FakeFreezeHR, NULL, 0, NULL);
                            MemoryLogs = "Freeze Enemy (Freeze) - Enabled!";
                        }
                        else
                        {
                            MemoryLogs = "Freeze Enemy (Freeze) - Disabled!";
                        }
                    }*/

                    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


                    if (tabs1 == 0)
                    {
                        ImGui::SetCursorPos(ImVec2(157, 80));
                        ImGui::BeginChild("AimHacks", ImVec2(300, 500), false);

                        if (aimbotex2 = ImGui::Checkbox("Aimbot Head Pro", &var::aimbotex2, "Apply In Each Game", &key4))
                        {
                            if (var::aimbotex2)
                            {
                                std::thread taskThread([]()
                                    {
                                        if (!AttackProcess(GetEmulatorRunning()))
                                        {
                                            ErrorEmulator();
                                            notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Emulator Not Found!", main_color);
                                            MemoryLogs = skCrypt("Emulator Not Found!").decrypt();
                                            var::aimbotex2 = false;
                                        }
                                        else
                                        {
                                          
                                        }
                                    });
                                taskThread.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip("Aimbot Safe");
                        }
                        if (aimbotfix = ImGui::Checkbox("Aimbot Colider", &var::aimbotfix, "Apply In Lobby"))
                        {
                            if (var::aimbotfix)
                            {
                                std::thread taskThread([]()
                                    {
                                        if (!AttackProcess(GetEmulatorRunning()))
                                        {
                                            ErrorEmulator();
                                            notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Emulator Not Found!", main_color);
                                            MemoryLogs = skCrypt("Emulator Not Found!").decrypt();
                                            var::aimbotfix = false;
                                        }
                                        else
                                        {
                                         
                                        }
                                    });
                                taskThread.detach();
                            }
                            else
                            {
                                std::thread taskThread([]()
                                    {
                                        if (!AttackProcess(GetEmulatorRunning()))
                                        {
                                            ErrorEmulator();
                                            notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Emulator Not Found!", main_color);
                                            MemoryLogs = skCrypt("Emulator Not Found!").decrypt();
                                            var::aimbotfix = false;
                                        }
                                        else
                                        {
                                        
                                        }
                                    });
                                taskThread.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip("Aimbot Colider Safe");
                        }


                    /*    if (snipercope = ImGui::Checkbox("Sniper Scope", &var::snipercope, "Apply In Training", &Key19))
                        {
                            if (var::snipercope)
                            {
                                std::thread taskThread([]()
                                    {
                                        if (!AttackProcess(GetEmulatorRunning()))
                                        {
                                            ErrorEmulator();
                                            notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Emulator Not Found!", main_color);
                                            MemoryLogs = skCrypt("Emulator Not Found!").decrypt();
                                            var::snipercope = false;
                                            return;
                                        }
                                        else
                                        {
                                          
                                        }
                                    });
                                taskThread.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip("Sniper Scope Safe");
                        }*/





                        if (sniperswitch2 = ImGui::Checkbox("Sniper Switch", &var::sniperswitch2, "Apply In Training"))
                        {
                            if (var::sniperswitch2)
                            {
                                std::thread taskThread2([]()
                                    {
                                        if (!AttackProcess(GetEmulatorRunning()))
                                        {
                                            ErrorEmulator();
                                            notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Emulator Not Found!", main_color);
                                            MemoryLogs = skCrypt("Emulator Not Found!").decrypt();
                                            var::sniperswitch2 = false;
                                            return;
                                        }
                                        else
                                        {
                                       
                                        }
                                    });
                                taskThread2.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip("Sniper Switch Safe");
                        }


                        if (snipercopefov = ImGui::Checkbox("Sniper Fov", &var::snipercopefov, "Apply In Training"))
                        {
                            if (var::snipercopefov)
                            {
                                std::thread taskThread1([]()
                                    {
                                        if (!AttackProcess(GetEmulatorRunning()))
                                        {
                                            ErrorEmulator();
                                            notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Emulator Not Found!", main_color);
                                            MemoryLogs = skCrypt("Emulator Not Found!").decrypt();
                                            var::snipercopefov = false;
                                            return;
                                        }
                                        else
                                        {
                               
                                        }
                                    });
                                taskThread1.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip("Sniper Fov Safe");
                        }


                        if (allswitch = ImGui::Checkbox("Glitch Fire", &var::allswitch, "Apply in Training"))
                        {
                            if (var::allswitch)
                            {
                                std::thread taskThread([]()
                                    {
                                        if (!AttackProcess(GetEmulatorRunning()))
                                        {
                                            ErrorEmulator();
                                            notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Emulator Not Found!", main_color);
                                            MemoryLogs = skCrypt("Emulator Not Found!").decrypt();
                                            var::allswitch = false;
                                            return;
                                        }
                                        else
                                        {
                                     
                                        }
                                    });
                                taskThread.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip("Glitch Fire Safe");
                        }

                        if (norecoil = ImGui::Checkbox("No Recoil ", &var::norecoil, "Apply in Training"))
                        {
                            if (var::norecoil)
                            {
                                std::thread taskThread([]()
                                    {
                                        if (!AttackProcess(GetEmulatorRunning()))
                                        {
                                            ErrorEmulator();
                                            notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Emulator Not Found!", main_color);
                                            MemoryLogs = skCrypt("Emulator Not Found!").decrypt();
                                            var::norecoil = false;
                                            return;
                                        }
                                        else
                                        {
                                       
                                        }
                                    });
                                taskThread.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip("No Recoil ");
                        }

                        move_window();
                        ImGui::EndChild();
                    }


                    if (tabs1 == 1)
                    {
                        ImGui::SetCursorPos(ImVec2(157, 80));
                        ImGui::BeginChild(skCrypt("Visuals").decrypt(), ImVec2(300, 500), false);



                        if (!var::Chamsesprgbbox)
                        {
                            if (Chamsesprgbbox = ImGui::Checkbox(skCrypt("Connect Chams").decrypt(), &var::Chamsesprgbbox, skCrypt("Open In Emulator").decrypt()))
                            {
                                if (var::Chamsesprgbbox)
                                {
                                    std::thread taskThread([]()
                                        {
                                            const char* dllPath = "C:\\Windows\\SysWOW64\\ChamsController.dll";
                                            const char* procname = "HD-Player.exe";
                                            DWORD procId = GetPid(procname);
                                            if (procId != 0) {
                                                HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);
                                                if (hProc && hProc != INVALID_HANDLE_VALUE) {
                                                    void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
                                                    bool shayan = WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);
                                                    HANDLE RemoteThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);
                                                    if (shayan)
                                                    {


                                                        Beep(1000, 600);
                                                        notificationSystem.Notification("REIMAN PRIME", "Chams Menu : Activated!", main_color);
                                                        MemoryLogs = "Chams Menu : Activated!";
                                                        client.Connect();

                                                    }
                                                    else
                                                    {
                                                        Beep(600, 300);
                                                        notificationSystem.Notification("REIMAN PRIME", "Chams Menu : Failed!", main_color);
                                                        MemoryLogs = "Chams Menu : Failed!";

                                                    }
                                                    if (RemoteThread)
                                                    {
                                                        CloseHandle(RemoteThread);
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                ErrorEmulator();
                                                notificationSystem.Notification("REIMAN PRIME", "Emulator Not Found!", main_color);
                                                MemoryLogs = "Emulator Not Found!";

                                            }
                                        });
                                    taskThread.detach();
                                }
                            }
                            if (ImGui::IsItemHovered())
                            {
                                ImGui::SetTooltip(skCrypt("Connect Chams").decrypt());

                            }
                        }



                        if (Charms2D = ImGui::Checkbox(skCrypt("Chams Menu").decrypt(), &var::Charms2D, skCrypt("Open In Emulator").decrypt()))
                        {
                            if (var::Charms2D)
                            {
                                std::thread taskThread([]()
                                    {
                                        const char* dllPath = "C:\\Windows\\SysWOW64\\menuhhtr.dll";

                                        const char* procname = "HD-Player.exe";
                                        DWORD procId = GetPid(procname);
                                        if (procId != 0) {
                                            HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);
                                            if (hProc && hProc != INVALID_HANDLE_VALUE) {
                                                void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
                                                bool shayan = WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);
                                                HANDLE RemoteThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);
                                                if (shayan)
                                                {

                                                    Beep(1000, 600);
                                                    notificationSystem.Notification("REIMAN PRIME", "Chams Menu : Activated!", main_color);
                                                    MemoryLogs = "Chams Menu : Activated!";

                                                }
                                                else
                                                {
                                                    Beep(600, 300);
                                                    notificationSystem.Notification("REIMAN PRIME", "Chams Menu : Failed!", main_color);
                                                    MemoryLogs = "Chams Menu : Failed!";
                                                    var::Charms2D = false;
                                                }
                                                if (RemoteThread)
                                                {
                                                    CloseHandle(RemoteThread);
                                                }
                                            }
                                        }
                                        else
                                        {
                                            ErrorEmulator();
                                            notificationSystem.Notification("REIMAN PRIME", "Emulator Not Found!", main_color);
                                            MemoryLogs = "Emulator Not Found!";
                                            var::Charms2D = false;
                                        }
                                    });
                                taskThread.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip(skCrypt("Chams Menu").decrypt());

                        }



                        if (Chamsespbox = ImGui::Checkbox(skCrypt("Chams 3D").decrypt(), &var::Chamsespbox, skCrypt("Open In Emulator").decrypt()))
                        {
                            if (var::Chamsespbox)
                            {
                                std::thread taskThread([]()
                                    {
                                        client.SendCommand("chams3d");
                                        Beep(500, 700);
                                    });
                                taskThread.detach();

                            }
                            else
                            {
                                std::thread taskThread([]()
                                    {
                                        client.SendCommand("chams3d");
                                        Beep(500, 700);
                                    });
                                taskThread.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip(skCrypt("Chams 3D").decrypt());

                        }


                        if (TWODCHAMS = ImGui::Checkbox(skCrypt("Chams Wokung").decrypt(), &var::TWODCHAMS, skCrypt("Open In Emulator").decrypt()))
                        {
                            if (var::TWODCHAMS)
                            {
                                std::thread taskThread([]()
                                    {
                                        client.SendCommand("wokungex");
                                        Beep(500, 700);
                                    });
                                taskThread.detach();

                            }
                            else
                            {
                                std::thread taskThread([]()
                                    {
                                        client.SendCommand("wokungex");
                                        Beep(500, 700);
                                    });
                                taskThread.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip(skCrypt("Chams Wokung").decrypt());

                        }

                        if (chams1 = ImGui::Checkbox(skCrypt("Chams Box 3D").decrypt(), &var::chams1, skCrypt("Open In Emulator").decrypt()))
                        {
                            if (var::chams1)
                            {
                                std::thread taskThread([]()
                                    {
                                        client.SendCommand("box3d");
                                        Beep(500, 700);
                                    });
                                taskThread.detach();

                            }
                            else
                            {
                                std::thread taskThread([]()
                                    {
                                        client.SendCommand("box3d");
                                        Beep(500, 700);
                                    });
                                taskThread.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip(skCrypt("Chams Box 3D").decrypt());

                        }

                        if (chams2 = ImGui::Checkbox(skCrypt("HD 4K MAP").decrypt(), &var::chams2, skCrypt("Open In Emulator").decrypt()))
                        {
                            if (var::chams2)
                            {
                                std::thread taskThread([]()
                                    {
                                        client.SendCommand("hdrmap");
                                        Beep(500, 700);
                                    });
                                taskThread.detach();

                            }
                            else
                            {
                                std::thread taskThread([]()
                                    {
                                        client.SendCommand("hdrmap");
                                        Beep(500, 700);
                                    });
                                taskThread.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip(skCrypt("HDR 4K MAP").decrypt());

                        }

                        /*  static bool injectSuccess = false;
                          if (ImGui::Checkbox("Enable Esp Line", &var::loadInternalCheat)) {

                              injectSuccess = false;

                              std::vector<std::pair<std::string, std::string>> files = {
                                  {"https://github.com/fahimXiter/Fahim-Xiter/raw/refs/heads/main/Client.dll", "C:\\Windows\\Temp\\Client.dll"},
                                  {"https://github.com/fahimXiter/Fahim-Xiter/raw/refs/heads/main/cimgui.dll", "C:\\Windows\\Temp\\cimgui.dll"},
                                  {"https://github.com/fahimXiter/Fahim-Xiter/raw/refs/heads/main/AotBst.dll", "C:\\Windows\\Temp\\AotBst.dll"},
                              };
                              notificationSystem.Notification("REIMAN PRIME", "Emulator Not Found!", main_color);
                              for (const auto& file : files) {
                                  RemoveFileIfExists(file.second.c_str());
                              }

                              bool allDownloaded = true;
                              for (const auto& file : files) {
                                  HRESULT hr = URLDownloadToFileA(nullptr, file.first.c_str(), file.second.c_str(), 0, nullptr);
                                  if (SUCCEEDED(hr)) {
                                      SetFileAttributesA(file.second.c_str(), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
                                      std::cout << "File downloaded and hidden: " << file.second << std::endl;
                                  }
                                  else {
                                      std::cerr << "Failed to download file: " << file.first << ". Error code: " << hr << std::endl;
                                      allDownloaded = false;
                                  }
                              }

                              if (allDownloaded && AttackProcess("HD-Player.exe")) {
                                  DWORD procID = Getid("HD-Player.exe");
                                  if (procID == 0) {
                                      std::cerr << "Failed to find process ID for HD-Player.exe" << std::endl;
                                  }
                                  else {
                                      HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
                                      if (!handle) {
                                          std::cerr << "Failed to open process. Error code: " << GetLastError() << std::endl;
                                      }
                                      else {
                                          for (const auto& file : { files[1], files[2] }) {
                                              const char* DllPath = file.second.c_str();
                                              size_t pathLen = strlen(DllPath) + 1;

                                              LPVOID pDllPath = VirtualAllocEx(handle, nullptr, pathLen, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
                                              if (!pDllPath) {
                                                  std::cerr << "Memory allocation failed. Error code: " << GetLastError() << std::endl;
                                                  continue;
                                              }

                                              if (!WriteProcessMemory(handle, pDllPath, (LPCVOID)DllPath, pathLen, nullptr)) {
                                                  std::cerr << "Failed to write memory. Error code: " << GetLastError() << std::endl;
                                                  VirtualFreeEx(handle, pDllPath, 0, MEM_RELEASE);
                                                  continue;
                                              }

                                              HANDLE hThread = CreateRemoteThread(handle, nullptr, 0,
                                                  (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"), "LoadLibraryA"),
                                                  pDllPath, 0, nullptr);

                                              if (hThread) {
                                                  WaitForSingleObject(hThread, INFINITE);
                                                  CloseHandle(hThread);
                                              }
                                              else {
                                                  std::cerr << "Failed to create remote thread. Error code: " << GetLastError() << std::endl;
                                              }

                                              VirtualFreeEx(handle, pDllPath, 0, MEM_RELEASE);
                                          }

                                          CloseHandle(handle);
                                          injectSuccess = true;
                                          notificationSystem.Notification("Notification", "Internal cheat loaded successfully!", main_color);
                                          Beep(2000, 500);
                                      }
                                  }
                              }



                              ImGui::Separator();


                              if (injectSuccess) {
                                  esp3 = ImGui::Checkbox("Esp Line", &var::esp3, " ");
                                  if (esp3) {
                                      HWND hWnd = FindWindowW(NULL, L"REIMAN PRIME.Ui");
                                      const UINT msg = var::esp3 ? 0x0411 : 0x0511;
                                      if (hWnd) PostMessage(hWnd, msg, 0, 0);
                                      else MessageBoxA(NULL, "   ", "Failed To Apply !", MB_OK | MB_ICONERROR);
                                  }

                                  ImGui::Separator();
                                  esp4 = ImGui::Checkbox("ESP Box", &var::esp4, " ");
                                  if (esp4) {
                                      HWND hWnd = FindWindowW(NULL, L"REIMAN PRIME.Ui");
                                      const UINT msg = var::esp4 ? 0x0412 : 0x0512;
                                      if (hWnd) PostMessage(hWnd, msg, 0, 0);
                                      else MessageBoxA(NULL, "Failed To Apply !", "Failed To Apply !", MB_OK | MB_ICONERROR);
                                  }

                                  ImGui::Separator();
                                  esp5 = ImGui::Checkbox("ESP Full Box", &var::esp5, " ");
                                  if (esp5) {
                                      HWND hWnd = FindWindowW(NULL, L"REIMAN PRIME.Ui");
                                      const UINT msg = var::esp5 ? 0x0413 : 0x0513;
                                      if (hWnd) PostMessage(hWnd, msg, 0, 0);
                                      else MessageBoxA(NULL, "Failed To Apply !", "Failed To Apply !", MB_OK | MB_ICONERROR);
                                  }

                                  ImGui::Separator();
                                  esp6 = ImGui::Checkbox("ESP Information", &var::esp6, " ");
                                  if (esp6) {
                                      HWND hWnd = FindWindowW(NULL, L"REIMAN PRIME.Ui");
                                      const UINT msg = var::esp6 ? 0x0417 : 0x0517;
                                      if (hWnd) PostMessage(hWnd, msg, 0, 0);
                                      else MessageBoxA(NULL, "Failed To Apply !", "Failed To Apply !", MB_OK | MB_ICONERROR);
                                  }

                                  ImGui::Separator();

                                  esp7 = ImGui::Checkbox("ESP Skeleton", &var::esp7, " ");
                                  if (esp7) {
                                      HWND hWnd = FindWindowW(NULL, L"REIMAN PRIME.Ui");
                                      const UINT msg = var::esp7 ? 0x0415 : 0x0515;
                                      if (hWnd) PostMessage(hWnd, msg, 0, 0);
                                      else MessageBoxA(NULL, "Failed To Apply !", "Failed To Apply !", MB_OK | MB_ICONERROR);
                                  }

                                  ImGui::Separator();



                                  esp99 = ImGui::Checkbox("ESP Weapon", &var::esp99, " ");
                                  if (esp7) {
                                      HWND hWnd = FindWindowW(NULL, L"REIMAN PRIME.Ui");
                                      const UINT msg = var::esp99 ? 0x0422 : 0x0524;
                                      if (hWnd) PostMessage(hWnd, msg, 0, 0);
                                      else MessageBoxA(NULL, "Failed To Apply !", "Failed To Apply !", MB_OK | MB_ICONERROR);
                                  }

                                  ImGui::Separator();




                                  esp8 = ImGui::Checkbox("ESP Fix Line", &var::esp8, " ");
                                  if (esp8) {
                                      HWND hWnd = FindWindowW(NULL, L"REIMAN PRIME.Ui");
                                      const UINT msg = var::esp8 ? 0x0409 : 0x0508;
                                      if (hWnd) PostMessage(hWnd, msg, 0, 0);
                                      else MessageBoxA(NULL, "Failed To Apply !", "Failed To Apply !", MB_OK | MB_ICONERROR);
                                  }



                                  ImGui::Separator();
                                  esp10 = ImGui::Checkbox("Stream Mode", &var::esp10, " ");
                                  if (esp10) {
                                      HWND hWnd = FindWindowW(NULL, L"REIMAN PRIME.Ui");
                                      const UINT msg = var::esp10 ? 0x0404 : 0x0504;
                                      if (hWnd) PostMessage(hWnd, msg, 0, 0);
                                  }

                                  ImGui::Separator();



                                  esp98 = ImGui::Checkbox("try again adb", &var::esp98, " ");
                                  if (esp98) {
                                      HWND hWnd = FindWindowW(NULL, L"REIMAN PRIME.Ui");
                                      const UINT msg = var::esp98 ? 0x0423 : 0x0525;
                                      if (hWnd) PostMessage(hWnd, msg, 0, 0);
                                      else MessageBoxA(NULL, "Failed To Apply !", "Failed To Apply !", MB_OK | MB_ICONERROR);
                                  }
                              }
                          }





                      }*/
                        move_window();
                        ImGui::EndChild();
                    }









                    if (tabs1 == 2)
                    {
                        ImGui::SetCursorPos(ImVec2(157, 80));
                        ImGui::BeginChild("Settings", ImVec2(300, 500), false);



                        if (fakedamagefix = ImGui::Checkbox("Female Damage Fix", &var::fakedamagefix, "Apply In Login"))
                        {
                            if (var::fakedamagefix)
                            {
                                std::thread taskThread([]()
                                    {
                                        if (!AttackProcess(GetEmulatorRunning()))
                                        {
                                            ErrorEmulator();
                                            notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Emulator Not Found!", main_color);
                                            MemoryLogs = skCrypt("Emulator Not Found!").decrypt();
                                            var::fakedamagefix = false;
                                            return;
                                        }
                                        else
                                        {
                                        //    all.FakeDamageFix();
                                        }
                                    });
                                taskThread.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip("Female Fix Safe");
                        }

                        if (camera = ImGui::Checkbox("Camera Left", &var::camera, "Apply In Training", &key3))
                        {
                            if (var::camera)
                            {
                                std::thread taskThread([]()
                                    {
                                        if (!AttackProcess(GetEmulatorRunning()))
                                        {
                                            ErrorEmulator();
                                            notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Emulator Not Found!", main_color);
                                            MemoryLogs = skCrypt("Emulator Not Found!").decrypt();
                                            var::camera = false;
                                            return;
                                        }
                                        else
                                        {
                                          
                                        }
                                    });
                                taskThread.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip("Camera Hack Safe");
                        }
                        if (leandin = ImGui::Checkbox("Car Fly + Fast landing", &var::leandin, "Apply In Training", &key6))
                        {
                            if (var::leandin)
                            {
                                std::thread taskThread([]()
                                    {
                                        if (!AttackProcess(GetEmulatorRunning()))
                                        {

                                            notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Emulator Not Found!", main_color);
                                            MemoryLogs = skCrypt("Emulator Not Found!").decrypt();   ErrorEmulator();

                                            var::leandin = false;
                                            return;
                                        }
                                        else
                                        {
                                           
                                        }
                                    });
                                taskThread.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip("Car Fly + Fast landing");
                        }
                        if (Loadflyhack1 = ImGui::Checkbox("Flay Hack X", &var::Loadflyhack1, "Apply In Training", &key11))
                        {
                            if (var::Loadflyhack1)
                            {
                                std::thread taskThread([]() {
                                    if (!AttackProcess(GetEmulatorRunning()))
                                    {

                                        notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Emulator Not Found!", main_color);
                                        MemoryLogs = skCrypt("Emulator Not Found!").decrypt();   ErrorEmulator();

                                        var::Loadflyhack1 = false;
                                        return;
                                    }
                                    else
                                    {
                                      
                                    }
                                    });
                                taskThread.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip("Flay Hack X Safe");
                        }


                        if (speed = ImGui::Checkbox("Speed Hack [ Risk ]", &var::speed, "Apply In Training", &key7))
                        {
                            if (var::speed)
                            {
                                std::thread taskThread([]()
                                    {
                                        if (!AttackProcess(GetEmulatorRunning()))
                                        {
                                            ErrorEmulator();
                                            notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Emulator Not Found!", main_color);
                                            MemoryLogs = skCrypt("Emulator Not Found!").decrypt();
                                            var::speed = false;
                                            return;
                                        }
                                        else
                                        {
                                           
                                        }
                                    });
                                taskThread.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip("Speed Hack Risk");
                        }

                      /*  ImGui::Checkbox("Freeze Enemy", &checkbox[10], "Apply In Each Game", &lag11);

                        if (GetAsyncKeyState(lag11) & 0x1)
                        {

                            FreezeHR = !FreezeHR.load();


                            Beep(500, 120);
                            Beep(FreezeHR ? 1200 : 600, 80);

                            if (FreezeHR.load())
                            {

                                if (FreHR == nullptr)
                                {

                                    CreateThread(NULL, 0, FakeFreezeHR, NULL, 0, NULL);
                                }
                                else
                                {

                                    CreateThread(NULL, 0, FakeFreezeHR, NULL, 0, NULL);
                                }
                            }
                            else
                            {

                            }
                        }*/





                        move_window();
                        ImGui::EndChild();
                    }

                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                    if (tabs1 == 3)
                    {
                        ImGui::SetCursorPos(ImVec2(157, 80));
                        ImGui::BeginChild("Settings", ImVec2(300, 500), false);

                        if (ModeStream = ImGui::Checkbox("Stream Mode", &var::ModeStream, "Hide From Screenshare"))
                        {
                            if (ModeStream)
                            {
                                if (var::ModeStream)
                                {
                                    notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Stream Mode : Enabled!", main_color);
                                    MemoryLogs = "Stream Mode : Enabled!";
                                    SetWindowDisplayAffinity(GetActiveWindow(), WDA_EXCLUDEFROMCAPTURE);
                                    ITaskbarList* pTaskList = NULL;
                                    HRESULT initRet = CoInitialize(NULL);
                                    HRESULT createRet = CoCreateInstance(CLSID_TaskbarList,
                                        NULL,
                                        CLSCTX_INPROC_SERVER,
                                        IID_ITaskbarList,
                                        (LPVOID*)&pTaskList);

                                    if (createRet == S_OK)
                                    {
                                        pTaskList->DeleteTab(GetActiveWindow());
                                        pTaskList->Release();
                                    }
                                    CoUninitialize();
                                }
                                else
                                {
                                    notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Stream Mode : Disabled!", main_color);
                                    MemoryLogs = "Stream Mode : Disabled!";
                                    SetWindowDisplayAffinity(GetActiveWindow(), WDA_NONE);
                                    ITaskbarList* pTaskList = NULL;
                                    HRESULT initRet = CoInitialize(NULL);
                                    HRESULT createRet = CoCreateInstance(CLSID_TaskbarList,
                                        NULL,
                                        CLSCTX_INPROC_SERVER,
                                        IID_ITaskbarList,
                                        (LPVOID*)&pTaskList);

                                    if (createRet == S_OK)
                                    {
                                        pTaskList->AddTab(GetActiveWindow());

                                        pTaskList->Release();
                                    }
                                    CoUninitialize();
                                }
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip("Streaming Mode");
                        }

                        if (resetguest = ImGui::Checkbox("Reset Guest", &var::resetguest, "Apply In Login"))
                        {
                            if (var::resetguest)
                            {
                                std::thread taskThread([]()
                                    {
                                        if (!AttackProcess(GetEmulatorRunning()))
                                        {
                                            ErrorEmulator();
                                            notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Emulator Not Found!", main_color);
                                            MemoryLogs = skCrypt("Emulator Not Found!").decrypt();
                                            var::resetguest = false;
                                        }
                                        else
                                        {
                                           // FahimFast.ResetGuest();
                                        }
                                    });
                                taskThread.detach();
                            }
                            else
                            {

                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip("Delete Guest Account");
                        }


                        if (internet = ImGui::Checkbox("Block Internet", &var::internet, "Apply In Login"))
                        {
                            if (var::internet)
                            {
                                std::thread taskThread([]()
                                    {
                                        if (!AttackProcess(GetEmulatorRunning()))
                                        {
                                            ErrorEmulator();
                                            notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Emulator Not Found!", main_color);
                                            MemoryLogs = skCrypt("Emulator Not Found!").decrypt();
                                            var::internet = false;
                                            return;
                                        }
                                        else
                                        {
                                            WinExec("netsh advfirewall firewall add rule name=\"FF Block In1\" dir=in action=block program=\"%ProgramFiles%\\BlueStacks_nxt\\HD-Player.exe\"", SW_HIDE); //Bluestacks 5
                                            WinExec("netsh advfirewall firewall add rule name=\"FF Block In1\" dir=out action=block program=\"%ProgramFiles%\\Bluestacks_nxt\\HD-Player.exe\"", SW_HIDE); //Bluestacks 5
                                            WinExec("netsh advfirewall firewall add rule name=\"FF Block In2\" dir=in action=block program=\"%ProgramFiles%\\BlueStacks\\HD-Player.exe\"", SW_HIDE); //Bluestacks 4
                                            WinExec("netsh advfirewall firewall add rule name=\"FF Block In2\" dir=out action=block program=\"%ProgramFiles%\\Bluestacks\\HD-Player.exe\"", SW_HIDE); //Bluestacks 4
                                            WinExec("netsh advfirewall firewall add rule name=\"FF Block In3\" dir=in action=block program=\"%ProgramFiles%\\BlueStacks_msi2\\HD-Player.exe\"", SW_HIDE); //Msi 4
                                            WinExec("netsh advfirewall firewall add rule name=\"FF Block In3\" dir=out action=block program=\"%ProgramFiles%\\Bluestacks_msi2\\HD-Player.exe\"", SW_HIDE);; //Msi 4
                                            WinExec("netsh advfirewall firewall add rule name=\"FF Block In6\" dir=in action=block program=\"%ProgramFiles%\\BlueStacks_msi5\\HD-Player.exe\"", SW_HIDE); //Msi 5 xxx
                                            WinExec("netsh advfirewall firewall add rule name=\"FF Block In6\" dir=out action=block program=\"%ProgramFiles%\\BlueStacks_msi5\\HD-Player.exe\"", SW_HIDE);; //Msi 5 xxx
                                            WinExec("netsh advfirewall firewall add rule name=\"FF Block In4\" dir=in action=block program=\"%ProgramData%\\BlueStacks_msi5\\HD-Player.exe\"", SW_HIDE); //Msi 5
                                            WinExec("netsh advfirewall firewall add rule name=\"FF Block In4\" dir=out action=block program=\"%ProgramData%\\Bluestacks_msi5\\HD-Player.exe\"", SW_HIDE); //Msi 5
                                            WinExec("netsh advfirewall firewall add rule name=\"FF Block In5\" dir=in action=block program=\"%ProgramFiles(x86)%\\SmartGaGa\\ProjectTitan\\Engine\\ProjectTitan.exe\"", SW_HIDE); //Smart Gaga
                                            WinExec("netsh advfirewall firewall add rule name=\"FF Block In5\" dir=out action=block program=\"%ProgramFiles(x86)%\\SmartGaGa\\ProjectTitan\\Engine\\ProjectTitan.exe\"", SW_HIDE); //Smart Gaga
                                            Beep(600, 250);
                                            notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Internet Blocked!", main_color);
                                            MemoryLogs = "Internet : Blocked!";
                                            internet = true;
                                        }
                                    });
                                taskThread.detach();
                            }
                            else
                            {
                                std::thread taskThread([]()
                                    {
                                        WinExec("netsh advfirewall firewall delete rule name=all program=\"%ProgramFiles%\\BlueStacks_nxt\\HD-Player.exe\"", SW_HIDE); //Bluestacks 5
                                        WinExec("netsh advfirewall firewall delete rule name=all program=\"%ProgramFiles%\\BlueStacks\\HD-Player.exe\"", SW_HIDE); //Bluestacks 4
                                        WinExec("netsh advfirewall firewall delete rule name=all program=\"%ProgramFiles%\\BlueStacks_msi2\\HD-Player.exe\"", SW_HIDE); //Msi 4
                                        WinExec("netsh advfirewall firewall delete rule name=all program=\"%ProgramFiles%\\BlueStacks_msi5\\HD-Player.exe\"", SW_HIDE); //Msi 5 xxx
                                        WinExec("netsh advfirewall firewall delete rule name=all program=\"%ProgramData%\\BlueStacks_msi5\\HD-Player.exe\"", SW_HIDE); //Msi 5
                                        WinExec("netsh advfirewall firewall delete rule name=all program=\"%ProgramFiles(x86)%\\SmartGaGa\\ProjectTitan\\Engine\\ProjectTitan.exe\"", SW_HIDE); //Smart Gag
                                        Beep(600, 250);
                                        notificationSystem.Notification(skCrypt("REIMAN PRIME").decrypt(), "Internet Resumed!", main_color);
                                        MemoryLogs = "Internet : Resumed!";
                                        internet = false;
                                    });
                                taskThread.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip("Block Internat");
                        }

                        if (PinToTop = ImGui::Checkbox("Pin To Top", &var::PinToTop, "Lock Panel On Screen"))
                        {
                            if (var::PinToTop)
                            {
                                std::thread taskThread([]()
                                    {
                                        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                                    });
                                taskThread.detach();
                            }
                            else
                            {
                                std::thread taskThread([]()
                                    {
                                        SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                                    });
                                taskThread.detach();
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::SetTooltip("Pin To Top");
                        }

                        /*  if (ImGui::ColorEdit3("Panel Theme", (float*)&main_color))
                          if (ImGui::IsItemHovered())
                          {
                              ImGui::SetTooltip("Change Panel Colour");
                          }*/
                        move_window();
                        ImGui::EndChild();
                    }

                   
                }
                else
                {
                    draw->AddRectFilled(p, p + ImVec2(755, 50), ImColor(10, 10, 10));
                    draw->AddRectFilled(p + ImVec2(0, 50), p + ImVec2(755, 52), second_color);
                    {

                        if (!loader_animation)
                            loader_animation = GetTickCount();
                        if (GetTickCount() > loader_animation + (1 * 15))
                        {

                            if (text_animation_hide)
                            {

                                if (text_animation < 0.80f)
                                    text_animation += 0.04f / ImGui::GetIO().Framerate * 60.f;
                                if (text_animation >= 0.80f)
                                    text_animation_hide = false;
                            }

                            else
                            {
                                if (text_animation > 0.00f)
                                    text_animation -= 0.04f / ImGui::GetIO().Framerate * 60.f;
                                if (text_animation <= 0.00f)
                                    text_animation_hide = true;

                            }
                            loader_animation = 0;
                        }


                        const auto& CurrentWindowPos = ImGui::GetWindowPos();
                        const auto& pWindowDrawList = ImGui::GetWindowDrawList();
                        const auto& pForegroundDrawList = ImGui::GetForegroundDrawList();

                    
                        static double loginNameStartTime = -1.0;
                        if (loginNameStartTime < 0.0) loginNameStartTime = ImGui::GetTime();
                        const double loginElapsed = ImGui::GetTime() - loginNameStartTime;
                        const std::string loginFirst = "REIMAN";
                        const std::string loginSecond = "   PRIME";
                        const float loginLettersPerSecond = 3.0f;
                        const int loginTotalLetters = (int)loginFirst.size() + (int)loginSecond.size();
                        const float loginTypeDuration = (float)loginTotalLetters / loginLettersPerSecond;
                        const float loginPauseDuration = 0.6f;
                        const float loginCycleDuration = loginTypeDuration + loginPauseDuration;
                        const float loginCyclePos = fmodf((float)loginElapsed, loginCycleDuration);
                        int loginVisibleLetters = (loginCyclePos >= loginTypeDuration)
                            ? loginTotalLetters
                            : (int)floorf(loginCyclePos * loginLettersPerSecond);
                        const int loginFirstVisible = (std::min)((int)loginFirst.size(), loginVisibleLetters);
                        const int loginSecondVisible = (std::max)(0, loginVisibleLetters - (int)loginFirst.size());

                        ImGui::PushFont(fonts::roboto);
                        {
                            // Photo-like reveal: flash effect + photo-developing fade
                            const float appearAnimDuration = 0.35f;
                            const float flashDuration = 0.08f; // quick flash like camera
                            float xCursor = 0.0f;
                            ImVec2 basePosFirst = ImVec2(140, 15);
                            ImDrawList* dl = ImGui::GetForegroundDrawList();

                            for (int i = 0; i < loginFirstVisible; ++i)
                            {
                                float charAppearTime = (float)i / loginLettersPerSecond;
                                float timeSinceAppear = loginCyclePos - charAppearTime;
                                if (timeSinceAppear < 0.0f) continue;

                                float t = timeSinceAppear / appearAnimDuration;
                                if (t > 1.0f) t = 1.0f;
                                if (t < 0.0f) t = 0.0f;

                                // Photo flash effect (bright white flash at start)
                                float flashT = timeSinceAppear / flashDuration;
                                bool inFlash = flashT < 1.0f && flashT >= 0.0f;

                                // Photo-developing effect: start with sepia/white, fade to full color
                                float photoT = (t - flashDuration / appearAnimDuration) / (1.0f - flashDuration / appearAnimDuration);
                                if (photoT < 0.0f) photoT = 0.0f;
                                if (photoT > 1.0f) photoT = 1.0f;

                                char buf[2] = { loginFirst[(size_t)i], 0 };
                                ImVec2 charSize = ImGui::CalcTextSize(buf);
                                ImVec2 charPos = basePosFirst + ImVec2(xCursor, 0);

                                // Flash effect (bright white glow)
                                if (inFlash)
                                {
                                    float flashIntensity = 1.0f - flashT;
                                    ImVec4 flashCol = ImVec4(1.0f, 1.0f, 1.0f, flashIntensity * 0.9f);
                                    dl->AddRectFilled(charPos - ImVec2(2, 2), charPos + charSize + ImVec2(2, 2), ImGui::GetColorU32(flashCol), 2.0f);
                                }

                                // Photo-developing color transition
                                ImVec4 baseColor = ImGui::ColorConvertU32ToFloat4(ImColor(main_color));
                                if (photoT < 1.0f)
                                {
                                    // Start with sepia/white tint, transition to full color
                                    float sepiaMix = 1.0f - photoT;
                                    baseColor.x = baseColor.x * (1.0f - sepiaMix * 0.3f) + sepiaMix * 0.95f;
                                    baseColor.y = baseColor.y * (1.0f - sepiaMix * 0.3f) + sepiaMix * 0.95f;
                                    baseColor.z = baseColor.z * (1.0f - sepiaMix * 0.2f) + sepiaMix * 0.9f;
                                    baseColor.w *= (0.3f + photoT * 0.7f); // fade in
                                }
                                else
                                {
                                    baseColor.w = 1.0f;
                                }

                                ImU32 textCol = ImGui::GetColorU32(baseColor);

                                // Draw with photo-like glow
                                float glowSize = 150.f * (0.5f + photoT * 0.5f);
                                ImGui::ShadowText(buf, textCol, textCol, glowSize, charPos);

                                xCursor += charSize.x;
                            }

                            xCursor = 0.0f;
                            ImVec2 basePosSecond = ImVec2(260, 15);
                            for (int i = 0; i < (std::min)((int)loginSecond.size(), loginSecondVisible); ++i)
                            {
                                int absoluteIndex = (int)loginFirst.size() + i;
                                float charAppearTime = (float)absoluteIndex / loginLettersPerSecond;
                                float timeSinceAppear = loginCyclePos - charAppearTime;
                                if (timeSinceAppear < 0.0f) continue;

                                float t = timeSinceAppear / appearAnimDuration;
                                if (t > 1.0f) t = 1.0f;
                                if (t < 0.0f) t = 0.0f;

                                float flashT = timeSinceAppear / flashDuration;
                                bool inFlash = flashT < 1.0f && flashT >= 0.0f;

                                float photoT = (t - flashDuration / appearAnimDuration) / (1.0f - flashDuration / appearAnimDuration);
                                if (photoT < 0.0f) photoT = 0.0f;
                                if (photoT > 1.0f) photoT = 1.0f;

                                char buf[2] = { loginSecond[(size_t)i], 0 };
                                ImVec2 charSize = ImGui::CalcTextSize(buf);
                                ImVec2 charPos = basePosSecond + ImVec2(xCursor, 0);

                                if (inFlash)
                                {
                                    float flashIntensity = 1.0f - flashT;
                                    ImVec4 flashCol = ImVec4(1.0f, 1.0f, 1.0f, flashIntensity * 0.9f);
                                    dl->AddRectFilled(charPos - ImVec2(2, 2), charPos + charSize + ImVec2(2, 2), ImGui::GetColorU32(flashCol), 2.0f);
                                }

                                ImVec4 white = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                                if (photoT < 1.0f)
                                {
                                    float sepiaMix = 1.0f - photoT;
                                    white.x = white.x * (1.0f - sepiaMix * 0.3f) + sepiaMix * 0.95f;
                                    white.y = white.y * (1.0f - sepiaMix * 0.3f) + sepiaMix * 0.95f;
                                    white.z = white.z * (1.0f - sepiaMix * 0.2f) + sepiaMix * 0.9f;
                                    white.w = 0.3f + photoT * 0.7f;
                                }

                                ImU32 whiteCol = ImGui::GetColorU32(white);
                                float glowSize = 110.f * (0.5f + photoT * 0.5f);
                                ImGui::ShadowText(buf, whiteCol, whiteCol, glowSize, charPos);
                                xCursor += charSize.x;
                            }
                        }
                        ImGui::PopFont();

                       

                        static bool showPassword = false;
                        ImGuiInputTextFlags passwordFlags = showPassword ? ImGuiInputTextFlags_None : ImGuiInputTextFlags_Password;

                        ImGui::SetCursorPos(ImVec2(105, 220));
                        ImGui::BeginChild(skCrypt("Inputs").decrypt(), ImVec2(500, 280), false, ImGuiWindowFlags_NoScrollbar);
                        ImGui::InputTextEx(skCrypt("##0").decrypt(), skCrypt("Username").decrypt(), login, 16, ImVec2(290, 43), ImGuiInputTextFlags_None);
                        ImGui::InputTextEx(skCrypt("##1").decrypt(), skCrypt("Password").decrypt(), pass, 16, ImVec2(290, 43), passwordFlags);
                        ImGui::InputTextEx(skCrypt("##2").decrypt(), skCrypt("License").decrypt(), Key, 16, ImVec2(290, 43), ImGuiInputTextFlags_None);

                        if (ImGui::Button(skCrypt("Login").decrypt(), ImVec2(290, 40)))
                        {
                            std::thread taskThread([]()
                                {
                                  
                                        menu_state = 1;
                                      
                                        notificationSystem.Notification("REIMAN PRIME", "Login : Success!", main_color);
                                        MemoryLogs = "Login: Success!";
                                     
                                });
                            taskThread.detach();
                        }

                        if (ImGui::Button(skCrypt("Register").decrypt(), ImVec2(290, 43)))
                        {
                            std::thread taskThread([]()
                                {
                                    ShellExecute(NULL, skCrypt("open").decrypt(), skCrypt("https://discord.gg/vzKWFcMqxc").decrypt(), NULL, NULL, SW_SHOWNORMAL);
                                });
                            taskThread.detach();
                        }

                    }ImGui::EndChild();
                }
                dot_draw();
                Trinage_background();
                notificationSystem.DrawNotification();
            }
            move_window();
            ImGui::End();
        }
        ImGui::Render();
        const float clear_color_with_alpha[4] = { 0 };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        g_pSwapChain->Present(1, 0);
    }
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
    return 0;
}
