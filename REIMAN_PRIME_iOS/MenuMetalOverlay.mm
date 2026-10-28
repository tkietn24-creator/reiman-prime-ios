#import "MenuMetalOverlay.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_metal.h"
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>

// ============================================================================
// HỆ THỐNG MÀU SẮC THUẦN CHẤT REIMAN PRIME CHO ĐẠI CA (PORT TỪ COLOR.H)
// ============================================================================
namespace ReimanColors {
    // Màu chủ đạo đỏ neon Neon Cyber Red
    static const ImU32 MainRed         = IM_COL32(230, 14, 80, 255);
    static const ImU32 MainRedGlow     = IM_COL32(255, 20, 70, 90);
    static const ImU32 DarkRed         = IM_COL32(124, 22, 53, 255);
    static const ImU32 SecondColor     = IM_COL32(28, 29, 32, 255);

    // Bảng màu nền Window & Tabs
    static const ImU32 MenuBg          = IM_COL32(12, 12, 16, 248);
    static const ImU32 HeaderBg        = IM_COL32(16, 17, 21, 255);
    static const ImU32 ChildBg         = IM_COL32(18, 19, 24, 230);
    static const ImU32 BorderRed       = IM_COL32(230, 20, 60, 200);
    static const ImU32 BorderInactive  = IM_COL32(35, 38, 46, 255);

    // Bảng màu các widget
    static const ImU32 WidgetBg        = IM_COL32(24, 25, 31, 255);
    static const ImU32 WidgetHover     = IM_COL32(38, 28, 35, 255);
    static const ImU32 TextWhite       = IM_COL32(255, 255, 255, 255);
    static const ImU32 TextGray        = IM_COL32(145, 148, 160, 255);
    static const ImU32 GreenStatus     = IM_COL32(0, 255, 110, 255);
}

// ============================================================================
// HIỆU ỨNG HẠT LƠ LỬNG KẾT NỐI MẠNG NHỆN (PORT TỪ ANIMVECTOR.H SANG METAL IOS)
// ============================================================================
struct NetworkParticle {
    ImVec2 pos;
    ImVec2 vel;
    float alpha;
    float radius;
};

static std::vector<NetworkParticle> g_particles;
static const int MAX_PARTICLES = 65;
static const float CONNECT_DISTANCE = 85.0f;

static void InitOrUpdateParticles(ImVec2 min_bounds, ImVec2 max_bounds) {
    // Khởi tạo danh sách hạt nếu chưa có
    if (g_particles.empty()) {
        for (int i = 0; i < MAX_PARTICLES; ++i) {
            NetworkParticle p;
            p.pos = ImVec2(min_bounds.x + (float)(rand() % (int)(std::max(1.0f, max_bounds.x - min_bounds.x + 1.0f))),
                           min_bounds.y + (float)(rand() % (int)(std::max(1.0f, max_bounds.y - min_bounds.y + 1.0f))));
            p.vel = ImVec2(((float)(rand() % 100) / 50.0f - 1.0f) * 0.45f,
                           ((float)(rand() % 100) / 50.0f - 1.0f) * 0.45f);
            p.radius = 1.5f + (float)(rand() % 20) / 10.0f;
            p.alpha = 0.3f + (float)(rand() % 70) / 100.0f;
            g_particles.push_back(p);
        }
    }

    // Cập nhật tọa độ hạt bay lơ lửng
    for (auto& p : g_particles) {
        p.pos.x += p.vel.x;
        p.pos.y += p.vel.y;

        // Va chạm viền đảo hướng mượt mà
        if (p.pos.x < min_bounds.x) { p.pos.x = min_bounds.x; p.vel.x *= -1.0f; }
        if (p.pos.x > max_bounds.x) { p.pos.x = max_bounds.x; p.vel.x *= -1.0f; }
        if (p.pos.y < min_bounds.y) { p.pos.y = min_bounds.y; p.vel.y *= -1.0f; }
        if (p.pos.y > max_bounds.y) { p.pos.y = max_bounds.y; p.vel.y *= -1.0f; }
    }
}

static void DrawNetworkParticles(ImDrawList* draw_list, ImVec2 min_bounds, ImVec2 max_bounds) {
    InitOrUpdateParticles(min_bounds, max_bounds);

    // 1. Vẽ các đường tơ kết nối mạng nhện giữa các hạt gần nhau
    for (size_t i = 0; i < g_particles.size(); ++i) {
        for (size_t j = i + 1; j < g_particles.size(); ++j) {
            float dx = g_particles[i].pos.x - g_particles[j].pos.x;
            float dy = g_particles[i].pos.y - g_particles[j].pos.y;
            float dist = std::sqrt(dx * dx + dy * dy);

            if (dist < CONNECT_DISTANCE) {
                float factor = 1.0f - (dist / CONNECT_DISTANCE);
                int line_alpha = (int)(factor * 110.0f);
                // Đường kết nối màu đỏ ánh kim REIMAN
                ImU32 line_color = IM_COL32(230, 20, 60, line_alpha);
                draw_list->AddLine(g_particles[i].pos, g_particles[j].pos, line_color, 1.0f);
            }
        }
    }

    // 2. Vẽ từng hạt sáng và vầng hào quang (glow)
    for (const auto& p : g_particles) {
        int dot_alpha = (int)(p.alpha * 200.0f);
        ImU32 dot_color = IM_COL32(255, 60, 100, dot_alpha);
        ImU32 glow_color = IM_COL32(230, 14, 80, (int)(dot_alpha * 0.4f));

        draw_list->AddCircleFilled(p.pos, p.radius + 1.5f, glow_color, 12);
        draw_list->AddCircleFilled(p.pos, p.radius, dot_color, 12);
    }
}

// ============================================================================
// TRẠNG THÁI TOÀN CỤC CỦA MENU REIMAN PRIME (DÀNH RIÊNG CHO ĐẠI CA)
// ============================================================================
static bool show_menu = true;
static bool show_pill_icon = true;

// Tọa độ của icon viên thuốc (mặc định góc trên bên trái màn hình)
static ImVec2 pill_pos = ImVec2(50.0f, 60.0f);
static bool pill_dragging = false;
static ImVec2 pill_drag_offset = ImVec2(0.0f, 0.0f);

// Tọa độ và kích thước thực tế của Menu REIMAN PRIME (Đồng bộ với HitTest cảm ứng)
static ImVec2 g_menu_pos = ImVec2(70.0f, 40.0f);
static ImVec2 g_menu_size = ImVec2(675.0f, 545.0f);

// Kích thước menu chuẩn theo chỉ lệnh Đại ca: 675 x 545 px
static const float MENU_WIDTH = 675.0f;
static const float MENU_HEIGHT = 545.0f;

// Trạng thái khởi tạo overlay
static BOOL s_isInitialized = NO;

// Cấu hình Aimbot
static bool aimbot_enabled = true;
static bool silent_aim = false;
static bool auto_fire = false;
static bool show_fov = true;
static float aim_fov = 95.0f;
static float aim_smooth = 3.8f;
static int aim_hitbox = 0;
static const char* hitboxes[] = { "Head", "Neck", "Chest", "Pelvis" };

// Cấu hình ESP & Visuals
static bool esp_box = true;
static bool esp_skeleton = true;
static bool esp_lines = false;
static bool esp_health = true;
static bool esp_distance = true;
static bool esp_names = true;
static float esp_max_distance = 400.0f;

// Cấu hình Chams & Color
static bool chams_enabled = true;
static bool chams_wireframe = false;
static float chams_vis_color[4] = { 0.9f, 0.05f, 0.25f, 1.0f };
static float chams_invis_color[4] = { 0.1f, 0.6f, 1.0f, 1.0f };

// Tab hiện tại
static int active_tab = 0;

// ============================================================================
// HÀM TẠO GIAO DIỆN THEME REIMAN PRIME CHUẨN XÁC TỪ COLOR.H
// ============================================================================
static void ApplyReimanPrimeTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    style.WindowRounding    = 12.0f;
    style.ChildRounding     = 8.0f;
    style.FrameRounding     = 6.0f;
    style.PopupRounding     = 6.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding      = 6.0f;
    style.TabRounding       = 6.0f;

    style.WindowBorderSize  = 1.5f;
    style.FrameBorderSize   = 1.0f;
    style.PopupBorderSize   = 1.0f;
    style.WindowPadding     = ImVec2(16.0f, 16.0f);
    style.FramePadding      = ImVec2(10.0f, 6.0f);
    style.ItemSpacing       = ImVec2(10.0f, 10.0f);
    style.ScrollbarSize     = 10.0f;

    // Palette chuẩn REIMAN PRIME
    colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]          = ImVec4(0.55f, 0.55f, 0.60f, 1.00f);
    colors[ImGuiCol_WindowBg]              = ImVec4(0.05f, 0.05f, 0.07f, 0.97f);
    colors[ImGuiCol_ChildBg]               = ImVec4(0.08f, 0.08f, 0.10f, 0.88f);
    colors[ImGuiCol_PopupBg]               = ImVec4(0.07f, 0.07f, 0.09f, 0.98f);
    colors[ImGuiCol_Border]                = ImVec4(0.90f, 0.05f, 0.31f, 0.75f); // Đỏ Neon viền ngoài
    colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]               = ImVec4(0.11f, 0.11f, 0.14f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.24f, 0.12f, 0.16f, 1.00f);
    colors[ImGuiCol_FrameBgActive]         = ImVec4(0.35f, 0.10f, 0.15f, 1.00f);
    colors[ImGuiCol_TitleBg]               = ImVec4(0.06f, 0.06f, 0.08f, 1.00f);
    colors[ImGuiCol_TitleBgActive]         = ImVec4(0.08f, 0.08f, 0.11f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.04f, 0.04f, 0.05f, 0.75f);
    colors[ImGuiCol_MenuBarBg]             = ImVec4(0.08f, 0.08f, 0.10f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.05f, 0.05f, 0.07f, 0.40f);
    colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.50f, 0.08f, 0.18f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.75f, 0.10f, 0.25f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.95f, 0.10f, 0.30f, 1.00f);
    colors[ImGuiCol_CheckMark]             = ImVec4(0.95f, 0.08f, 0.32f, 1.00f);
    colors[ImGuiCol_SliderGrab]            = ImVec4(0.90f, 0.08f, 0.30f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]      = ImVec4(1.00f, 0.20f, 0.40f, 1.00f);
    colors[ImGuiCol_Button]                = ImVec4(0.18f, 0.12f, 0.15f, 1.00f);
    colors[ImGuiCol_ButtonHovered]         = ImVec4(0.70f, 0.10f, 0.25f, 1.00f);
    colors[ImGuiCol_ButtonActive]          = ImVec4(0.92f, 0.12f, 0.32f, 1.00f);
    colors[ImGuiCol_Header]                = ImVec4(0.28f, 0.08f, 0.14f, 1.00f);
    colors[ImGuiCol_HeaderHovered]         = ImVec4(0.68f, 0.10f, 0.24f, 0.85f);
    colors[ImGuiCol_HeaderActive]          = ImVec4(0.90f, 0.12f, 0.32f, 1.00f);
    colors[ImGuiCol_Separator]             = ImVec4(0.85f, 0.08f, 0.28f, 0.55f);
    colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.95f, 0.12f, 0.35f, 0.80f);
    colors[ImGuiCol_SeparatorActive]       = ImVec4(1.00f, 0.18f, 0.40f, 1.00f);
}

// ============================================================================
// VẼ ICON HÌNH VIÊN THUỐC (PILL ICON) ĐỂ BẬT/TẮT MENU CHO ĐẠI CA
// ============================================================================
static void DrawPillToggleButton() {
    if (!show_pill_icon) return;

    const float pill_width = 115.0f;
    const float pill_height = 38.0f;
    const float pill_rounding = pill_height * 0.5f;

    ImGui::SetNextWindowPos(pill_pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(pill_width, pill_height), ImGuiCond_Always);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration |
                             ImGuiWindowFlags_NoBackground |
                             ImGuiWindowFlags_NoScrollWithMouse |
                             ImGuiWindowFlags_NoSavedSettings |
                             ImGuiWindowFlags_NoFocusOnAppearing;

    ImGui::Begin("##PillToggleWindow", NULL, flags);

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 p_min = pill_pos;
    ImVec2 p_max = ImVec2(p_min.x + pill_width, p_min.y + pill_height);

    ImGuiIO& io = ImGui::GetIO();
    bool is_hovered = (io.MousePos.x >= p_min.x && io.MousePos.x <= p_max.x &&
                       io.MousePos.y >= p_min.y && io.MousePos.y <= p_max.y);

    if (is_hovered && ImGui::IsMouseClicked(0)) {
        pill_dragging = true;
        pill_drag_offset = ImVec2(io.MousePos.x - pill_pos.x, io.MousePos.y - pill_pos.y);
    }

    if (pill_dragging) {
        if (ImGui::IsMouseDown(0)) {
            pill_pos = ImVec2(io.MousePos.x - pill_drag_offset.x, io.MousePos.y - pill_drag_offset.y);
            if (pill_pos.x < 0) pill_pos.x = 0;
            if (pill_pos.y < 0) pill_pos.y = 0;
            if (pill_pos.x + pill_width > io.DisplaySize.x) pill_pos.x = io.DisplaySize.x - pill_width;
            if (pill_pos.y + pill_height > io.DisplaySize.y) pill_pos.y = io.DisplaySize.y - pill_height;
        } else {
            pill_dragging = false;
        }
    }

    // 1. Hiệu ứng tỏa sáng Neon đỏ (Glow Pulse) cho viên thuốc
    float pulse = (std::sin((float)ImGui::GetTime() * 3.5f) + 1.0f) * 0.5f;
    int glow_alpha = 60 + (int)(pulse * 55.0f);
    draw_list->AddRect(ImVec2(p_min.x - 3, p_min.y - 3), ImVec2(p_max.x + 3, p_max.y + 3),
                       IM_COL32(230, 14, 80, glow_alpha), pill_rounding + 3.0f, 0, 4.0f);

    // 2. Thân viên thuốc kim loại tối màu
    ImU32 pill_bg_col = is_hovered ? IM_COL32(28, 29, 36, 250) : IM_COL32(16, 17, 22, 240);
    draw_list->AddRectFilled(p_min, p_max, pill_bg_col, pill_rounding);

    // 3. Viền đỏ rực sắc bén của REIMAN PRIME
    draw_list->AddRect(p_min, p_max, ReimanColors::BorderRed, pill_rounding, 0, 1.8f);

    // 4. Đèn LED trạng thái viên thuốc (Xanh lá khi Menu bật, Đỏ khi ẩn)
    ImVec2 led_center = ImVec2(p_min.x + 19.0f, p_min.y + (pill_height * 0.5f));
    ImU32 led_color = show_menu ? ReimanColors::GreenStatus : ReimanColors::MainRed;
    draw_list->AddCircleFilled(led_center, 4.5f, led_color);
    draw_list->AddCircle(led_center, 6.8f, IM_COL32(255, 255, 255, 120), 12, 1.0f);

    // 5. Chữ hiển thị nhãn thương hiệu
    ImVec2 text_pos = ImVec2(p_min.x + 34.0f, p_min.y + 10.0f);
    draw_list->AddText(text_pos, IM_COL32(245, 245, 245, 255), "REIMAN");

    // 6. Nút vô hình bao trọn viên thuốc để click bật/tắt
    ImGui::SetCursorPos(ImVec2(0, 0));
    if (ImGui::InvisibleButton("##PillHitbox", ImVec2(pill_width, pill_height))) {
        if (!pill_dragging) {
            show_menu = !show_menu;
        }
    }

    ImGui::End();
}

// ============================================================================
// HIỆU ỨNG CHỮ GÕ TYPEWRITER + FLASH MÁY ẢNH (PORT TỪ MAIN.CPP CỦA ĐẠI CA)
// ============================================================================
static void DrawTypewriterHeader(ImDrawList* draw_list, ImVec2 base_pos) {
    static double start_time = -1.0;
    if (start_time < 0.0) start_time = ImGui::GetTime();
    double elapsed = ImGui::GetTime() - start_time;

    const std::string text = "REIMAN PRIME";
    const float letters_per_sec = 4.0f;
    const float type_duration = (float)text.size() / letters_per_sec;
    const float pause_duration = 1.2f;
    const float cycle_duration = type_duration + pause_duration;
    const float cycle_pos = std::fmod((float)elapsed, cycle_duration);

    int visible_letters = (cycle_pos >= type_duration)
        ? (int)text.size()
        : (int)std::floor(cycle_pos * letters_per_sec);

    std::string current_str = text.substr(0, visible_letters);

    // Vẽ chữ REIMAN PRIME với hiệu ứng đổ bóng phát sáng đỏ
    draw_list->AddText(ImVec2(base_pos.x + 1, base_pos.y + 1), IM_COL32(230, 14, 80, 150), current_str.c_str());
    draw_list->AddText(base_pos, ReimanColors::TextWhite, current_str.c_str());

    // Hiệu ứng con trỏ nhấp nháy
    if (std::fmod((float)elapsed, 0.6f) > 0.3f && visible_letters < (int)text.size()) {
        ImVec2 text_size = ImGui::CalcTextSize(current_str.c_str());
        draw_list->AddRectFilled(ImVec2(base_pos.x + text_size.x + 2, base_pos.y + 2),
                                 ImVec2(base_pos.x + text_size.x + 5, base_pos.y + text_size.y - 2),
                                 ReimanColors::MainRed);
    }
}

// ============================================================================
// VẼ GIAO DIỆN CHÍNH MENU REIMAN PRIME: CHUẨN XÁC KÍCH THƯỚC 675 x 545 PX
// TỰ ĐỘNG THÍCH ỨNG THEO MÀN HÌNH LANDSCAPE CỦA IPHONE/IPAD MÀ KHÔNG BỊ TRÀN
// ============================================================================
static void DrawReimanPrimeMainMenu() {
    if (!show_menu) return;

    ImGuiIO& io = ImGui::GetIO();

    // Tính toán kích thước thích ứng chuẩn 675 x 545 px
    float actual_width = MENU_WIDTH;
    float actual_height = MENU_HEIGHT;

    // Nếu màn hình iPhone nhỏ hơn 675x545 ở chế độ ngang, căn chỉnh để không bị khuất nút bấm
    if (io.DisplaySize.x > 200.0f && io.DisplaySize.x < (MENU_WIDTH + 20.0f)) {
        actual_width = io.DisplaySize.x - 20.0f;
    }
    if (io.DisplaySize.y > 200.0f && io.DisplaySize.y < (MENU_HEIGHT + 20.0f)) {
        actual_height = io.DisplaySize.y - 20.0f;
    }

    g_menu_size = ImVec2(actual_width, actual_height);

    // Ép kích thước cố định chuẩn xác cho Đại ca
    ImGui::SetNextWindowSize(g_menu_size, ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(70.0f, 30.0f), ImGuiCond_FirstUseEver);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoCollapse |
                                    ImGuiWindowFlags_NoTitleBar;

    if (ImGui::Begin("##ReimanPrimeMainWindow", &show_menu, window_flags)) {
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 win_pos = ImGui::GetWindowPos();
        ImVec2 win_size = ImGui::GetWindowSize();

        // Cập nhật tọa độ Menu thời gian thực để Touch HitTest chuẩn xác 100%
        g_menu_pos = win_pos;
        g_menu_size = win_size;

        // 1. ĐỔ BÓNG NGOÀI NEON RED TOẢ ÁNH SÁNG XUNG QUANH TOÀN MENU
        draw_list->AddRect(ImVec2(win_pos.x - 2, win_pos.y - 2),
                           ImVec2(win_pos.x + win_size.x + 2, win_pos.y + win_size.y + 2),
                           ReimanColors::MainRedGlow, 14.0f, 0, 5.0f);

        // 2. HIỆU ỨNG HẠT BỤI MẠNG NHỆN CHẠY NGAY TRONG NỀN MENU
        DrawNetworkParticles(draw_list, win_pos, ImVec2(win_pos.x + win_size.x, win_pos.y + win_size.y));

        // 3. THANH HEADER TRÊN CÙNG
        ImVec2 header_min = win_pos;
        ImVec2 header_max = ImVec2(win_pos.x + win_size.x, win_pos.y + 55.0f);
        draw_list->AddRectFilled(header_min, header_max, ReimanColors::HeaderBg, 12.0f, ImDrawFlags_RoundCornersTop);
        draw_list->AddLine(ImVec2(win_pos.x, win_pos.y + 55.0f), ImVec2(win_pos.x + win_size.x, win_pos.y + 55.0f), ReimanColors::BorderRed, 1.8f);

        // Hiệu ứng chữ gõ phím REIMAN PRIME phát sáng
        DrawTypewriterHeader(draw_list, ImVec2(win_pos.x + 22.0f, win_pos.y + 17.0f));

        // Version Tag
        ImGui::SetCursorPos(ImVec2(175.0f, 18.0f));
        ImGui::TextColored(ImVec4(0.85f, 0.10f, 0.30f, 1.0f), "V2.4 iOS");

        // Trạng thái Connected
        ImGui::SameLine(win_size.x - 200.0f);
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.45f, 1.0f), "[ METAL 120 FPS ]");

        // Nút tắt menu nhỏ (X) góc phải trên cùng
        ImGui::SameLine(win_size.x - 45.0f);
        ImGui::SetCursorPosY(12.0f);
        if (ImGui::Button("X##CloseBtn", ImVec2(28.0f, 28.0f))) {
            show_menu = false;
        }

        ImGui::SetCursorPosY(68.0f);

        // 4. KHU VỰC CỘT TRÁI (DANH SÁCH TAB) & CỘT PHẢI (NỘI DUNG TÍNH NĂNG)
        const float nav_width = 145.0f;
        const float content_height = win_size.y - 80.0f;

        // Cột trái: Tab điều hướng với màu đỏ Cyber
        ImGui::BeginChild("##NavColumn", ImVec2(nav_width, content_height), true);
        {
            ImVec2 tab_size = ImVec2(nav_width - 20.0f, 40.0f);

            // Nút tab với hiệu ứng đổi màu và glow
            if (active_tab == 0) ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.80f, 0.08f, 0.28f, 1.0f));
            if (ImGui::Button(active_tab == 0 ? "> AIMBOT <" : "AIMBOT", tab_size)) { active_tab = 0; }
            if (active_tab == 0) ImGui::PopStyleColor();
            ImGui::Spacing();

            if (active_tab == 1) ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.80f, 0.08f, 0.28f, 1.0f));
            if (ImGui::Button(active_tab == 1 ? "> VISUALS <" : "VISUALS", tab_size)) { active_tab = 1; }
            if (active_tab == 1) ImGui::PopStyleColor();
            ImGui::Spacing();

            if (active_tab == 2) ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.80f, 0.08f, 0.28f, 1.0f));
            if (ImGui::Button(active_tab == 2 ? "> CHAMS <" : "CHAMS", tab_size)) { active_tab = 2; }
            if (active_tab == 2) ImGui::PopStyleColor();
            ImGui::Spacing();

            if (active_tab == 3) ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.80f, 0.08f, 0.28f, 1.0f));
            if (ImGui::Button(active_tab == 3 ? "> SETTINGS <" : "SETTINGS", tab_size)) { active_tab = 3; }
            if (active_tab == 3) ImGui::PopStyleColor();

            // Nút thu nhỏ menu xuống thanh viên thuốc
            ImGui::SetCursorPosY(content_height - 50.0f);
            if (ImGui::Button("MINIMIZE", ImVec2(nav_width - 20.0f, 34.0f))) {
                show_menu = false;
            }
        }
        ImGui::EndChild();

        ImGui::SameLine();

        // Cột phải: Nội dung chi tiết các chức năng
        const float content_width = win_size.x - nav_width - 35.0f;
        ImGui::BeginChild("##ContentArea", ImVec2(content_width, content_height), true);
        {
            if (active_tab == 0) {
                // TAB AIMBOT
                ImGui::TextColored(ImVec4(0.95f, 0.10f, 0.30f, 1.0f), "--- AIMBOT CONFIGURATION ---");
                ImGui::Separator();
                ImGui::Spacing();

                ImGui::Checkbox("Enable Aimbot Lock", &aimbot_enabled);
                ImGui::Checkbox("Silent Aim (Direct Memory Override)", &silent_aim);
                ImGui::Checkbox("Auto Fire / TriggerBot", &auto_fire);
                ImGui::Checkbox("Draw FOV Circle", &show_fov);

                ImGui::Spacing();
                ImGui::SliderFloat("FOV Radius", &aim_fov, 10.0f, 360.0f, "%.1f deg");
                ImGui::SliderFloat("Smooth Factor", &aim_smooth, 1.0f, 20.0f, "%.1f");
                ImGui::Combo("Target Hitbox", &aim_hitbox, hitboxes, IM_ARRAYSIZE(hitboxes));

            } else if (active_tab == 1) {
                // TAB VISUALS (ESP)
                ImGui::TextColored(ImVec4(0.95f, 0.10f, 0.30f, 1.0f), "--- VISUALS & ESP RADAR ---");
                ImGui::Separator();
                ImGui::Spacing();

                ImGui::Checkbox("2D Bounding Box", &esp_box);
                ImGui::Checkbox("Bone Skeleton ESP", &esp_skeleton);
                ImGui::Checkbox("Snaplines (Bottom-Center)", &esp_lines);
                ImGui::Checkbox("Player Health Bar", &esp_health);
                ImGui::Checkbox("Distance Tag", &esp_distance);
                ImGui::Checkbox("Player Nickname & Team", &esp_names);

                ImGui::Spacing();
                ImGui::SliderFloat("Render Distance Limit", &esp_max_distance, 50.0f, 1000.0f, "%.0f m");

            } else if (active_tab == 2) {
                // TAB CHAMS
                ImGui::TextColored(ImVec4(0.95f, 0.10f, 0.30f, 1.0f), "--- WALLHACK CHAMS ---");
                ImGui::Separator();
                ImGui::Spacing();

                ImGui::Checkbox("Enable Metal Chams", &chams_enabled);
                ImGui::Checkbox("Wireframe Mode", &chams_wireframe);

                ImGui::Spacing();
                ImGui::Text("Visible Enemy Color:");
                ImGui::ColorEdit4("##VisCol", chams_vis_color);

                ImGui::Spacing();
                ImGui::Text("Behind Walls (Invisible) Color:");
                ImGui::ColorEdit4("##InvisCol", chams_invis_color);

            } else if (active_tab == 3) {
                // TAB SETTINGS
                ImGui::TextColored(ImVec4(0.95f, 0.10f, 0.30f, 1.0f), "--- SYSTEM & CONFIGURATION ---");
                ImGui::Separator();
                ImGui::Spacing();

                ImGui::Checkbox("Show Floating Pill Toggle Icon", &show_pill_icon);

                ImGui::Spacing();
                if (ImGui::Button("Reset Pill Icon Position", ImVec2(220.0f, 36.0f))) {
                    pill_pos = ImVec2(50.0f, 60.0f);
                }

                ImGui::Spacing();
                if (ImGui::Button("Save Configuration", ImVec2(220.0f, 36.0f))) {
                    // Logic lưu cấu hình tùy chỉnh
                }

                ImGui::SameLine();
                if (ImGui::Button("Load Configuration", ImVec2(220.0f, 36.0f))) {
                    // Logic tải cấu hình tùy chỉnh
                }

                ImGui::Spacing();
                ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Tip: Cham vao vien thuoc tren man hinh de bat/tat Menu.");
            }
        }
        ImGui::EndChild();
    }
    ImGui::End();
}

// ============================================================================
// LỚP OVERLAY METAL CHO IOS (UIVIEW SUBCLASS TƯƠNG THÍCH 100% VỚI UNITY/FREE FIRE)
// ============================================================================
@implementation MenuMetalOverlay

+ (instancetype)sharedInstance {
    static MenuMetalOverlay *instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[MenuMetalOverlay alloc] initWithFrame:[UIScreen mainScreen].bounds];
    });
    return instance;
}

// Hàm tìm kiếm Window đang hoạt động của game Free Fire (Unity Engine)
+ (UIWindow *)findGameWindow {
    UIWindow *targetWindow = nil;

    // 1. Tìm thông qua UIWindowScene trên iOS 13+ đến iOS 18+
    if (@available(iOS 13.0, *)) {
        for (UIScene *scene in [UIApplication sharedApplication].connectedScenes) {
            if (scene.activationState == UISceneActivationStateForegroundActive && [scene isKindOfClass:[UIWindowScene class]]) {
                UIWindowScene *windowScene = (UIWindowScene *)scene;
                for (UIWindow *w in windowScene.windows) {
                    if (w.isKeyWindow || !w.hidden) {
                        targetWindow = w;
                        break;
                    }
                }
            }
            if (targetWindow) break;
        }
    }

    // 2. Fallback duyệt toàn bộ danh sách windows của ứng dụng
    if (!targetWindow) {
        for (UIWindow *w in [UIApplication sharedApplication].windows) {
            if (w.isKeyWindow || !w.hidden) {
                targetWindow = w;
                break;
            }
        }
    }

    // 3. Fallback lấy keyWindow hoặc window đầu tiên trong mảng
    if (!targetWindow) {
        targetWindow = [UIApplication sharedApplication].keyWindow;
    }
    if (!targetWindow && [UIApplication sharedApplication].windows.count > 0) {
        targetWindow = [UIApplication sharedApplication].windows.firstObject;
    }

    return targetWindow;
}

- (void)setupOverlay {
    @try {
        if (s_isInitialized) {
            return;
        }

        UIWindow *gameWindow = [MenuMetalOverlay findGameWindow];
        // Nếu cửa sổ game chưa sẵn sàng hoặc kích thước chưa được layout thì thử lại sau 1 giây
        if (!gameWindow || gameWindow.bounds.size.width < 100.0f || gameWindow.bounds.size.height < 100.0f) {
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                [self setupOverlay];
            });
            return;
        }

        // Thiết lập kích thước UIView phủ vừa khít cửa sổ game Free Fire
        self.frame = gameWindow.bounds;
        self.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
        self.backgroundColor = [UIColor clearColor];
        self.userInteractionEnabled = YES;
        self.opaque = NO;

        // Khởi tạo Apple Metal Device & Command Queue
        self.device = MTLCreateSystemDefaultDevice();
        if (!self.device) {
            return;
        }
        self.commandQueue = [self.device newCommandQueue];

        // Khởi tạo MTKView trong suốt bao phủ toàn bộ màn hình
        self.metalView = [[MTKView alloc] initWithFrame:self.bounds device:self.device];
        self.metalView.delegate = self;
        self.metalView.clearColor = MTLClearColorMake(0.0f, 0.0f, 0.0f, 0.0f);
        self.metalView.backgroundColor = [UIColor clearColor];
        self.metalView.framebufferOnly = NO;
        self.metalView.opaque = NO;
        self.metalView.preferredFramesPerSecond = 120; // Hỗ trợ 120Hz ProMotion trên iPhone/iPad
        self.metalView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
        [self addSubview:self.metalView];

        // Khởi tạo Dear ImGui Context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = NULL; // Tắt hoàn toàn việc ghi file ini để không bao giờ văng do iOS Sandbox Permission

        CGFloat scale = [UIScreen mainScreen].nativeScale;
        if (scale <= 0.0f) scale = 2.0f;
        io.DisplayFramebufferScale = ImVec2(scale, scale);
        io.DisplaySize = ImVec2(self.bounds.size.width, self.bounds.size.height);

        // Kích hoạt giao diện REIMAN PRIME Cyber Red
        ApplyReimanPrimeTheme();

        // Khởi tạo Backend Metal của Dear ImGui
        ImGui_ImplMetal_Init(self.device);

        // Gắn thẳng Overlay vào làm lớp con trên cùng của Game Window Free Fire
        [gameWindow addSubview:self];
        [gameWindow bringSubviewToFront:self];

        s_isInitialized = YES;
    } @catch (NSException *exception) {
        // Bắt mọi ngoại lệ để không bao giờ làm văng game của Đại ca
    }
}

// Cập nhật lại khung nhìn khi xoay màn hình điện thoại
- (void)layoutSubviews {
    [super layoutSubviews];
    if (self.superview) {
        self.frame = self.superview.bounds;
        self.metalView.frame = self.bounds;
        if (ImGui::GetCurrentContext()) {
            ImGuiIO& io = ImGui::GetIO();
            io.DisplaySize = ImVec2(self.bounds.size.width, self.bounds.size.height);
        }
    }
}

// ============================================================================
// HỆ THỐNG XUYÊN THẤU CẢM ỨNG (TOUCH PASSTHROUGH) CHO PHÉP CHƠI GAME KHÔNG BỊ CHẶN
// Chỉ nhận cảm ứng khi chạm đúng vào Viên thuốc hoặc Menu, còn lại nhường 100% cho Free Fire
// ============================================================================
- (UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event {
    if (!self.userInteractionEnabled || self.hidden || self.alpha < 0.01) {
        return nil;
    }

    // 1. Kiểm tra nếu chạm vào icon hình viên thuốc (Pill icon)
    if (show_pill_icon) {
        const float pill_width = 115.0f;
        const float pill_height = 38.0f;
        CGRect pillRect = CGRectMake(pill_pos.x - 10.0f, pill_pos.y - 10.0f, pill_width + 20.0f, pill_height + 20.0f);
        if (CGRectContainsPoint(pillRect, point)) {
            return self;
        }
    }

    // 2. Kiểm tra nếu chạm vào khung Menu REIMAN PRIME (khi Menu đang mở)
    if (show_menu) {
        CGRect menuRect = CGRectMake(g_menu_pos.x, g_menu_pos.y, g_menu_size.x, g_menu_size.y);
        if (CGRectContainsPoint(menuRect, point)) {
            return self;
        }
    }

    // 3. Nếu chạm ra ngoài: trả về nil để xuyên thấu 100% cảm ứng vào game Free Fire
    return nil;
}

// Xử lý Touch Input từ ngón tay truyền vào Dear ImGui
- (void)updateTouch:(UIEvent *)event isDown:(bool)isDown {
    if (!ImGui::GetCurrentContext()) return;
    ImGuiIO& io = ImGui::GetIO();
    NSSet *touches = [event allTouches];
    for (UITouch *touch in touches) {
        CGPoint point = [touch locationInView:self.metalView];
        io.AddMousePosEvent(point.x, point.y);
        io.AddMouseButtonEvent(0, isDown);
    }
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [self updateTouch:event isDown:true];
    [super touchesBegan:touches withEvent:event];
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [self updateTouch:event isDown:true];
    [super touchesMoved:touches withEvent:event];
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [self updateTouch:event isDown:false];
    [super touchesEnded:touches withEvent:event];
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [self updateTouch:event isDown:false];
    [super touchesCancelled:touches withEvent:event];
}

- (void)toggleMenu {
    show_menu = !show_menu;
}

#pragma mark - MTKViewDelegate

- (void)mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size {
    if (ImGui::GetCurrentContext()) {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(self.bounds.size.width, self.bounds.size.height);
    }
}

- (void)drawInMTKView:(MTKView *)view {
    @try {
        if (!s_isInitialized || !ImGui::GetCurrentContext()) {
            return;
        }

        id<CAMetalDrawable> drawable = view.currentDrawable;
        MTLRenderPassDescriptor *renderPassDescriptor = view.currentRenderPassDescriptor;

        // Nếu drawable hoặc renderPass chưa sẵn sàng thì bỏ qua frame này, tuyệt đối không commit rỗng
        if (!drawable || !renderPassDescriptor) {
            return;
        }

        // Đảm bảo overlay luôn nổi lên trên cùng mỗi vài giây phòng khi Free Fire load màn chơi
        static int s_frontCounter = 0;
        if (++s_frontCounter % 120 == 0) {
            if (self.superview && [self.superview.subviews lastObject] != self) {
                [self.superview bringSubviewToFront:self];
            }
        }

        ImGuiIO& io = ImGui::GetIO();
        float fps = (float)view.preferredFramesPerSecond;
        if (fps <= 0.0f) fps = 60.0f;
        io.DeltaTime = 1.0f / fps;
        io.DisplaySize = ImVec2(view.bounds.size.width, view.bounds.size.height);

        id<MTLCommandBuffer> commandBuffer = [self.commandQueue commandBuffer];
        if (!commandBuffer) {
            return;
        }

        ImGui_ImplMetal_NewFrame(renderPassDescriptor);
        ImGui::NewFrame();

        // 1. Vẽ icon hình viên thuốc để bật / ẩn Menu
        DrawPillToggleButton();

        // 2. Vẽ Menu REIMAN PRIME chuẩn kích thước 675 x 545 px với hiệu ứng hạt và màu đỏ Cyber
        DrawReimanPrimeMainMenu();

        // Render toàn bộ lệnh vẽ ra Metal Pipeline
        ImGui::Render();
        id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
        if (renderEncoder) {
            [renderEncoder pushDebugGroup:@"ReimanPrimeMetalRender"];
            ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData(), commandBuffer, renderEncoder);
            [renderEncoder popDebugGroup];
            [renderEncoder endEncoding];
        }

        [commandBuffer presentDrawable:drawable];
        [commandBuffer commit];
    } @catch (NSException *exception) {
        // Bắt ngoại lệ render an toàn
    }
}

@end

// ============================================================================
// HÀM KHỞI CHẠY TỰ ĐỘNG KHI DYLIB NẠP VÀO APP HOẶC GAME FREE FIRE
// Đợi game khởi động xong hoàn toàn mới nạp Menu để tránh văng trong lúc load splash/movie
// ============================================================================
__attribute__((constructor)) static void InitializeReimanPrimeHook() {
    // 1. Lắng nghe thông báo khi Free Fire đã kết thúc quá trình khởi động ban đầu
    [[NSNotificationCenter defaultCenter] addObserverForName:UIApplicationDidFinishLaunchingNotification
                                                      object:nil
                                                       queue:[NSOperationQueue mainQueue]
                                                  usingBlock:^(NSNotification * _Nonnull note) {
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            [[MenuMetalOverlay sharedInstance] setupOverlay];
        });
    }];

    // 2. Kích hoạt timer dự phòng 5 giây (phòng trường hợp dylib nạp sau khi notification đã kích hoạt)
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [[MenuMetalOverlay sharedInstance] setupOverlay];
    });
}
