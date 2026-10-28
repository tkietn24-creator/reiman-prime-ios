#import "MenuMetalOverlay.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_metal.h"
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
            p.pos = ImVec2(min_bounds.x + (float)(rand() % (int)(max_bounds.x - min_bounds.x + 1)),
                           min_bounds.y + (float)(rand() % (int)(max_bounds.y - min_bounds.y + 1)));
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

// Kích thước menu theo đúng chuẩn chỉ lệnh Đại ca: 675 x 545 px
static const float MENU_WIDTH = 675.0f;
static const float MENU_HEIGHT = 545.0f;

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
// ============================================================================
static void DrawReimanPrimeMainMenu() {
    if (!show_menu) return;

    // Ép kích thước cố định chuẩn xác 675 x 545 px cho Đại ca
    ImGui::SetNextWindowSize(ImVec2(MENU_WIDTH, MENU_HEIGHT), ImGuiCond_Always);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoCollapse |
                                    ImGuiWindowFlags_NoTitleBar;

    if (ImGui::Begin("##ReimanPrimeMainWindow", &show_menu, window_flags)) {
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 win_pos = ImGui::GetWindowPos();
        ImVec2 win_size = ImGui::GetWindowSize();

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
        const float content_height = MENU_HEIGHT - 80.0f;

        // Cột trái: Tab điều hướng với màu đỏ Cyber
        ImGui::BeginChild("##NavColumn", ImVec2(nav_width, content_height), true);
        {
            ImVec2 tab_size = ImVec2(nav_width - 20.0f, 44.0f);

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
            ImGui::SetCursorPosY(content_height - 55.0f);
            if (ImGui::Button("MINIMIZE", ImVec2(nav_width - 20.0f, 36.0f))) {
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
                    // Logic lưu config
                }

                ImGui::SameLine();
                if (ImGui::Button("Load Configuration", ImVec2(220.0f, 36.0f))) {
                    // Logic nạp config
                }

                ImGui::Spacing();
                ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Tip: Chạm vào viên thuốc trên màn hình để bật/tắt Menu.");
            }
        }
        ImGui::EndChild();
    }
    ImGui::End();
}

// ============================================================================
// LỚP OVERLAY METAL CHO IOS (WINDOW VÀ MTKVIEW CHẠY TRỰC TIẾP)
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

- (void)setupOverlay {
    // Tầng hiển thị cao nhất đè lên tất cả ứng dụng và game trên iOS
    self.windowLevel = UIWindowLevelAlert + 100.0f;
    self.backgroundColor = [UIColor clearColor];
    self.hidden = NO;
    self.userInteractionEnabled = YES;

    // Khởi tạo Apple Metal Device & Command Queue
    self.device = MTLCreateSystemDefaultDevice();
    self.commandQueue = [self.device newCommandQueue];

    // Khởi tạo MTKView trong suốt bao phủ toàn bộ màn hình
    self.metalView = [[MTKView alloc] initWithFrame:self.bounds device:self.device];
    self.metalView.delegate = self;
    self.metalView.clearColor = MTLClearColorMake(0.0f, 0.0f, 0.0f, 0.0f);
    self.metalView.backgroundColor = [UIColor clearColor];
    self.metalView.framebufferOnly = NO;
    self.metalView.opaque = NO;
    self.metalView.preferredFramesPerSecond = 120; // Hỗ trợ 120Hz ProMotion trên iPhone/iPad
    [self addSubview:self.metalView];

    UIViewController *rootVC = [[UIViewController alloc] init];
    rootVC.view.backgroundColor = [UIColor clearColor];
    self.rootViewController = rootVC;

    // Khởi tạo ImGui Context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = NULL;

    CGFloat scale = [UIScreen mainScreen].nativeScale;
    io.DisplaySize = ImVec2(self.bounds.size.width, self.bounds.size.height);
    io.DisplayFramebufferScale = ImVec2(scale, scale);

    // Kích hoạt giao diện REIMAN PRIME Cyber Red
    ApplyReimanPrimeTheme();

    // Khởi tạo Backend Metal của Dear ImGui
    ImGui_ImplMetal_Init(self.device);
}

// Xử lý Touch Input từ ngón tay truyền vào Dear ImGui
- (void)updateTouch:(UIEvent *)event isDown:(bool)isDown {
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
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(self.bounds.size.width, self.bounds.size.height);
}

- (void)drawInMTKView:(MTKView *)view {
    ImGuiIO& io = ImGui::GetIO();
    io.DeltaTime = 1.0f / (float)view.preferredFramesPerSecond;

    id<MTLCommandBuffer> commandBuffer = [self.commandQueue commandBuffer];
    MTLRenderPassDescriptor *renderPassDescriptor = view.currentRenderPassDescriptor;

    if (renderPassDescriptor != nil) {
        ImGui_ImplMetal_NewFrame(renderPassDescriptor);
        ImGui::NewFrame();

        // 1. Vẽ icon hình viên thuốc để bật / ẩn Menu
        DrawPillToggleButton();

        // 2. Vẽ Menu REIMAN PRIME chuẩn kích thước 675 x 545 px với hiệu ứng hạt và màu đỏ Cyber
        DrawReimanPrimeMainMenu();

        // Render toàn bộ lệnh vẽ ra Metal Pipeline
        ImGui::Render();
        id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
        [renderEncoder pushDebugGroup:@"ReimanPrimeMetalRender"];
        ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData(), commandBuffer, renderEncoder);
        [renderEncoder popDebugGroup];
        [renderEncoder endEncoding];

        [commandBuffer presentDrawable:view.currentDrawable];
    }

    [commandBuffer commit];
}

@end

// ============================================================================
// HÀM KHỞI CHẠY TỰ ĐỘNG KHI DYLIB NẠP VÀO APP HOẶC GAME
// ============================================================================
__attribute__((constructor)) static void InitializeReimanPrimeHook() {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [[MenuMetalOverlay sharedInstance] setupOverlay];
    });
}
