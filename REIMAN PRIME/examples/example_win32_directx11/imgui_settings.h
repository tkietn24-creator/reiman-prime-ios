#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

inline ImColor main_color(255, 0, 0);

inline ImColor background_color(25, 25, 25);

inline ImColor second_color(40, 40, 40);

inline ImColor text_color[2] = { ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 150) };

inline ImVec2 menu_size = ImVec2(497, 497);

inline float anim_speed = 15.f;

inline ImVec2 frame_size = ImVec2(299, 49);

namespace ImStyle {

    inline ImVec4 general_color12 = ImColor(255, 255, 255);

    inline ImVec4 general_color23 = ImColor(236, 255, 0, 0);

    inline ImVec4 general_color21 = ImColor(236, 255, 0, 89);

    inline ImVec4 general_color122 = ImColor(255, 255, 255);

    inline ImVec4 text_active = ImColor(255, 255, 255, 255);

    inline ImVec4 general_color13 = ImColor(255, 255, 255);

    inline ImVec4 general_color14 = ImColor(255, 255, 255);

    inline ImVec4 general_color22 = ImColor(12, 12, 12, 0);

    inline ImVec4 backgroundcolar = ImColor(255, 245, 0);

    inline float rounding = 15.f;
}

namespace c2 {
    inline ImVec4 accent11 = ImColor(106, 106, 106);
    inline ImVec4 accent = ImColor(213, 0, 255);
    inline ImVec4 accent_text_color = ImColor(245, 245, 255); //2
    inline ImVec4 accent_text_low_color = ImColor(245, 245, 255, 255 / 2);

    inline ImVec4 accent_low_color = ImColor(250, 132, 86, 255 / 2);
    namespace bg
    {

        inline ImVec4 background = ImColor(0, 0, 0, 90);
        inline ImVec2 size = ImVec2(960, 610);
        inline float rounding = 25.f;

    }

    namespace child
    {

        inline ImVec4 background = ImColor(17, 17, 19, 100);
        inline ImVec4 outline = ImColor(18, 20, 18, 255);
        inline float rounding = 8.f;

    }

    namespace checkbox
    {
        inline ImVec4 background = ImColor(34, 34, 37, 255);
        inline ImVec4 circle_inactive = ImColor(46, 48, 55, 255);
        inline float rounding = 2.f;
    }

    namespace slider
    {
        inline ImVec4 background = ImColor(34, 34, 37, 255);
        inline ImVec4 circle_inactive = ImColor(46, 48, 55, 255);
        inline float rounding = 2.f;
        inline ImVec4 outline_background = ImColor(30, 32, 36, 255);
    }

    namespace tabs
    {
        inline ImVec4 background = ImColor(16, 17, 19, 255);

        inline ImVec4 outline = ImColor(22, 24, 26, 255);
        inline float rounding = 6.f;
    }

    namespace combo
    {
        inline ImVec4 background = ImColor(27, 29, 32, 255);
        inline ImVec4 outline_background = ImColor(30, 32, 36, 255);
        inline float rounding = 3;
    }

    namespace picker
    {
        inline ImVec4 background = ImColor(16, 17, 19, 255);
        inline ImVec4 outline = ImColor(22, 24, 26, 255);

        inline float rounding = 2.f;
    }

    namespace button
    {
        inline ImVec4 background_active = ImColor(26, 27, 29, 255);
        inline ImVec4 background_inactive = ImColor(16, 17, 19, 255);

        inline ImVec4 outline = ImColor(22, 24, 26, 255);

        inline float rounding = 2.f;
    }

    namespace keybind
    {
        inline ImVec4 background_active = ImColor(26, 27, 29, 255);
        inline ImVec4 background_inactive = ImColor(16, 17, 19, 255);

        inline ImVec4 outline = ImColor(22, 24, 26, 255);

        inline float rounding = 2.f;
    }

    namespace input
    {
        inline ImVec4 background_active = ImColor(26, 27, 29, 255);
        inline ImVec4 background_inactive = ImColor(16, 17, 19, 255);

        inline ImVec4 outline = ImColor(22, 24, 26, 255);
        inline ImVec4 icon = ImColor(26, 27, 31, 255);

        inline float rounding = 2.f;
    }

    namespace scroll
    {
        inline float rounding = 30.f;
    }

    namespace text
    {
        inline ImVec4 text_active = ImColor(255, 255, 255, 255);
        inline ImVec4 text_hov = ImColor(86, 88, 95, 255);
        inline ImVec4 text = ImColor(223, 223, 223);

        inline float glow_size = 8.f;
    }
}

inline ImVec2 center_text(ImVec2 min, ImVec2 max, const char* text)
{
    return min + (max - min) / 2 - ImGui::CalcTextSize(text) / 2;
}

inline ImFont* second_font;
inline ImFont* second_font1;
inline ImFont* inter_bold222;
inline ImFont* bold_font;
inline ImFont* bold_font1;
inline ImFont* bold_font2;
inline ImFont* semibold_font;
inline ImFont* semibold_font1;
inline ImFont* icon_font;

inline ImGuiWindow* main_window;
inline char search[64];

inline struct Notification
{
    std::string message, information;
    ImColor color;
    ImRect bb;

    ImVec2 offset = ImVec2(400, 0);
    ImVec2 target_offset = ImVec2(400, 0);
    float timer = 60;
}notif_state;

class NotificationSystem
{
public:
    inline void Notification(std::string message, std::string information, ImColor color)
    {
        notif_state.offset = ImVec2(400, 0);
        notif_state.target_offset = ImVec2(400, 0);
        notif_state.timer = 0;
        notif_state.color = color;
        notif_state.message = message;
        notif_state.information = information;
    }

    inline void DrawNotification()
    {
        if (notif_state.message.empty() && notif_state.information.empty())
            return;

        notif_state.timer += ImGui::GetIO().DeltaTime * 10.f;

        float fade_in_time = 6.0f;
        float visible_time = 20.0f;
        float fade_out_time = 6.0f;
        float alpha = 1.0f;

        if (notif_state.timer < fade_in_time)
            alpha = notif_state.timer / fade_in_time;
        else if (notif_state.timer > visible_time)
            alpha = 1.0f - ((notif_state.timer - visible_time) / fade_out_time);

        alpha = ImClamp(alpha, 0.0f, 1.0f);

        ImVec2 message_size = ImGui::CalcTextSize(notif_state.message.c_str());
        ImVec2 info_size = ImGui::CalcTextSize(notif_state.information.c_str());

        float padding = 15.0f;
        float width = std::max<float>(message_size.x, info_size.x) + padding * 2;
        float height = message_size.y + info_size.y + padding * 2 + 5.0f;

        notif_state.bb = ImRect(ImGui::GetWindowPos() + ImGui::GetWindowSize() - ImVec2(width + 20, height + 20), ImGui::GetWindowPos() + ImGui::GetWindowSize() - ImVec2(20, 20));

        ImColor bg_color = ImColor(15, 15, 15, static_cast<int>(200 * alpha));
        ImColor border_color = ImColor(150, 150, 150, static_cast<int>(20 * alpha));

        ImGui::GetForegroundDrawList()->AddRectFilled(notif_state.bb.Min, notif_state.bb.Max, bg_color, 5);

        ImGui::GetForegroundDrawList()->AddRect(notif_state.bb.Min, notif_state.bb.Max, border_color, 5, 0, 1.f);

        ImVec2 text_pos_main = notif_state.bb.Min + ImVec2((width - message_size.x) / 2, padding);
        ImVec2 text_pos_info = notif_state.bb.Min + ImVec2((width - info_size.x) / 2, height - padding - info_size.y);

        ImColor text_color_main = ImColor(notif_state.color.Value.x, notif_state.color.Value.y, notif_state.color.Value.z, alpha);
        ImColor text_color_info = ImColor(text_color[1].Value.x, text_color[1].Value.y, text_color[1].Value.z, alpha);

        ImGui::PushFont(inter_bold222);
        ImGui::GetForegroundDrawList()->AddText(text_pos_main, text_color_main, notif_state.message.c_str());
        ImGui::PopFont();

        ImGui::PushFont(second_font);
        ImGui::GetForegroundDrawList()->AddText(text_pos_info, text_color_info, notif_state.information.c_str());
        ImGui::PopFont();

        float time_ratio = ImClamp((visible_time - (notif_state.timer - fade_in_time)) / visible_time, 0.0f, 1.0f);
        float bar_width = (notif_state.bb.Max.x - notif_state.bb.Min.x) * time_ratio;

        ImRect bar_rect = ImRect(ImVec2(notif_state.bb.Min.x, notif_state.bb.Min.y), ImVec2(notif_state.bb.Min.x + bar_width, notif_state.bb.Min.y + 2));

        ImColor bar_color = ImColor(notif_state.color.Value.x, notif_state.color.Value.y, notif_state.color.Value.z, alpha);
        ImColor shadow_color = ImColor(notif_state.color.Value.x, notif_state.color.Value.y, notif_state.color.Value.z, alpha);

        ImGui::GetForegroundDrawList()->AddRectFilled(bar_rect.Min, bar_rect.Max, bar_color, 5);

        float shadow_thickness = 30.0f;
        ImVec2 shadow_offset = ImVec2(0, 0);

        ImGui::GetForegroundDrawList()->AddShadowRect(bar_rect.Min, bar_rect.Max, shadow_color, shadow_thickness, shadow_offset, 0, 5);
    }

private:
    struct
    {
        ImVec2 offset;
        ImVec2 target_offset;
        float timer = 0.f;
        ImColor color;
        std::string message;
        std::string information;
        ImRect bb;
    } notif_state;
};

inline NotificationSystem notificationSystem;
