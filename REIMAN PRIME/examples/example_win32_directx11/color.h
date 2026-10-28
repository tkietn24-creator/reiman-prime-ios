#include "imgui.h"

// WIDGET COLORS

namespace c {



    inline ImVec4 accent = ImColor(main_color);

    inline ImVec4 accent_color0 = ImColor(230, 14, 80);
    inline ImVec4 accent_color1 = ImColor(124, 22, 53);

    inline ImVec4 accent_color = ImColor(255, 255, 255, 255);
    //maudo
    inline ImVec4 logo_color = ImColor(255, 255, 255);


    inline ImVec4 accent_low_color = ImColor(82, 207, 218, 255 / 2);
    inline ImVec4 accent_low = ImColor(50, 210, 220, 255 / 2);

    inline ImVec4 accent_text_color = ImColor(245, 245, 255);

    inline ImVec4 accent_text_low_color = ImColor(245, 245, 255, 255 / 2);

    inline ImVec4 notify = ImColor(43, 48, 54);
    inline ImVec4 general_color = ImColor(50, 191, 255, 255);

    namespace bg
    {
        inline ImVec4 background = ImColor(20, 20, 20, 200);
        inline ImVec4 outline_background = ImColor(21, 22, 23, 255);
        inline ImVec2 size = ImVec2(750, 640);
        inline float rounding = 18;
    }
    namespace tabs
    {
        inline ImVec4 background = ImColor(16, 17, 19, 255);

        inline ImVec4 outline = ImColor(22, 24, 26, 255);
        inline float rounding = 6.f;
    }
    namespace child
    {
        inline ImVec4 background = ImColor(22, 23, 26, 245);
        inline ImVec4 outline_background = ImColor(27, 29, 32, 255);
        inline float rounding = 6;
        inline ImVec4 outline = ImColor(18, 20, 18, 255);
    }

    namespace checkbox
    {
        inline ImVec4 circle_inactive = ImColor(43, 48, 54, 255);

        inline ImVec4 background = ImColor(27, 29, 32, 255);
        inline ImVec4 outline_background = ImColor(30, 32, 36, 255);
        inline float rounding = 30;
    }

    namespace slider
    {
        inline ImVec4 circle_inactive = ImColor(43, 48, 54, 255);

        inline ImVec4 background = ImColor(27, 29, 32, 255);
        inline ImVec4 outline_background = ImColor(30, 32, 36, 255);
        inline float rounding = 30;
    }

    namespace combo
    {
        inline ImVec4 background = ImColor(27, 29, 32, 255);
        inline ImVec4 outline_background = ImColor(30, 32, 36, 255);
        inline float rounding = 3;
    }

    namespace picker
    {
        inline ImVec4 background = ImColor(27, 29, 32, 255);
        inline ImVec4 outline_background = ImColor(30, 32, 36, 255);
        inline float rounding = 8;
    }

    namespace button
    {
        inline ImVec4 background = ImColor(main_color);
        inline ImVec4 outline_background = ImColor(main_color);
        inline float rounding = 8;
    }

    namespace input
    {
        inline ImVec4 background = ImColor(32, 32, 31, 255);
        inline ImVec4 background_active = ImColor(26, 27, 29, 255);
        inline ImVec4 background_hov = ImColor(255, 255, 255); //al poner el cursol encima de la linea del login aparecera el color elegido

        inline ImVec4 icon = ImColor(30, 30, 30, 255);
        inline ImVec4 outline = ImColor(40, 40, 40, 255);

        inline ImVec4 outline_background = ImColor(255, 255, 255, 255);
        inline float rounding = 3;
        inline ImVec4 background_inactive = ImColor(15, 15, 15, 255);
        inline ImVec4 text_selected = ImColor(56, 56, 56, 70);

    }

    namespace keybind
    {
        inline ImVec4 background = ImColor(27, 29, 32, 255);
        inline ImVec4 outline_background = ImColor(30, 32, 36, 255);
        inline float rounding = 3;
    }
    ///////////////////////////////////////////// TABS

    inline ImVec4 tab_text_active = ImColor(70, 7, 117);
    inline ImVec4 tab_text_hov = ImColor(70, 7, 117, 230);
    inline ImVec4 tab_text = ImColor(88, 92, 112, 255);

    inline ImVec4 tab_active = ImColor(70, 7, 117);
    inline ImVec4 glow_active = ImColor(70, 7, 117, 230);

    ///////////////////////////////////////////// TEXT
    inline ImVec4 text = ImColor(66, 65, 70, 255);
    namespace Text {
        inline ImVec4 text_active = ImColor(255, 255, 255, 255);
        inline ImVec4 text_hov = ImColor(70, 7, 117);
        inline ImVec4 text = ImColor(66, 65, 70, 255);
        inline float glow_size = 8.f;
    }
    ///////////////////////////////////////////// CHILD

    inline ImVec4 child_background = ImColor(22, 21, 26, 255);
    inline ImVec4 border_child = ImColor(28, 27, 32, 255);
    inline ImVec4 child_gradient = ImColor(70, 7, 117);

    inline ImVec4 border_child_default = ImColor(22, 21, 26, 255);
    inline ImVec4 child_name = ImColor(62, 61, 65, 255);

    ///////////////////////////////////////////// GRADIENT

    inline ImVec4 checkbox_gradient_start = ImColor(70, 7, 117);
    inline ImVec4 checkbox_gradient_end = ImColor(70, 7, 117);

    ///////////////////////////////////////////// CHECKBOXES

    inline ImVec4 checkbox_bg = ImColor(17, 16, 21, 255);
    inline ImVec4 checkbox_mark = ImColor(255, 255, 255, 255);

    ///////////////////////////////////////////// SLIDERS

    inline ImVec4 slider_background = ImColor(209, 44, 44);
    inline ImVec4 circle_push_gradient = ImColor(209, 44, 44);
    inline ImVec4 circle_pop_gradient = ImColor(209, 44, 44);

    ///////////////////////////////////////////// INPUTTEXT

    inline ImVec4 input_push_gradient = ImColor(27, 26, 31, 255);
    inline ImVec4 input_pop_gradient = ImColor(17, 16, 21, 255);


    ///////////////////////////////////////////// SCROLLBAR

    inline ImVec4 scroll_background = ImColor(181, 26, 26);
    inline ImVec4 scroll_keep = ImColor(181, 26, 26);

    ///////////////////////////////////////////// COMBOBOX

    inline ImVec4 combo_background = ImColor(209, 44, 44);

    inline ImVec4 combo_push_gradient = ImColor(209, 44, 44);
    inline ImVec4 combo_pop_gradient = ImColor(209, 44, 44);

    ///////////////////////////////////////////// BUTTON

    inline ImVec4 button_push_gradient_active = ImColor(27, 26, 31, 255);
    inline ImVec4 button_pop_gradient_active = ImColor(17, 16, 21, 255);

    inline ImVec4 button_push_gradient_hovered = ImColor(30, 29, 34, 255);
    inline ImVec4 button_pop_gradient_hovered = ImColor(19, 20, 24, 255);

    inline ImVec4 button_push_gradient = ImColor(27, 26, 31, 255);
    inline ImVec4 button_pop_gradient = ImColor(17, 16, 21, 255);

    ///////////////////////////////////////////// KEYBIND

    inline ImVec4 keybind_background = ImColor(18, 18, 20, 255);
    inline ImVec4 keybind_border = ImColor(16, 16, 18, 255);

    ///////////////////////////////////////////// TAB VISIBLE

    inline ImVec4 tab_push_gradient = ImColor(209, 44, 44);
    inline ImVec4 tab_pop_gradient = ImColor(209, 44, 44);

}

