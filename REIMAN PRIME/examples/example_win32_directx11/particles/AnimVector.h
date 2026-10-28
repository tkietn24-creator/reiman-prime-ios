#include "Vector.hpp"
#include <vector>
#include <random>
#include <math.h>
#include <sysinfoapi.h>
#include <WinUser.h>
#include <windef.h>
#include "imgui.h"


std::vector<ImVec2> circles_pos;
std::vector<ImVec2> circles_dir;
std::vector<int> circles_radius;
static float vector_speed = 0.0f;
static float glass_opticaly = 100.0f;
static int particle_size = 100;

class dot
{
public:
    dot(SourceEngine::Vector p, SourceEngine::Vector v) {
        m_vel = v;
        m_pos = p;
    }

    void update();
    void draw();

    SourceEngine::Vector m_pos, m_vel;
};

std::vector<dot*> dots = { };

void dot::update() {
    auto opacity = 255.0f / 255.0f;

    //  m_pos += m_vel * (opacity);
    m_pos += m_vel * (opacity * 2);
}

void dot::draw()
{
    int opacity = 1155.0f * (1155.0f / 1155.0f);
    ImGui::GetWindowDrawList()->AddRectFilled({ m_pos.x - 2.5f, m_pos.y - 2.5f }, { m_pos.x + 2.5f, m_pos.y + 2.5f }, ImColor(255,255,255), 400);
    ImGui::GetWindowDrawList()->AddShadowCircle({ m_pos.x - 2.5f, m_pos.y - 2.5f }, 1.f, ImColor(255, 255, 255), 5 * 15, ImVec2(0, 0), 0, 1);

    auto t = std::find(dots.begin(), dots.end(), this);
    if (t == dots.end()) {
        return;
    }

    for (auto i = t; i != dots.end(); i++) {
        if ((*i) == this) continue;

        auto dist = (m_pos - (*i)->m_pos).Length2D();

        if (dist < glass_opticaly) {
            int alpha = opacity * (dist / glass_opticaly);

            ImGui::GetWindowDrawList()->AddLine({ m_pos.x - 2, m_pos.y - 3 }, { (*i)->m_pos.x - 2, (*i)->m_pos.y - 3 }, ImColor(255,255,255,0));
        }
    }
}

void dot_draw()
{

    struct screen_size
    {
        int x, y;
    };
    screen_size sc;

    if (!vector_speed)
        vector_speed = GetTickCount();

    if (GetTickCount() > vector_speed + (-10 * 8))
    {
        RECT screen_rect;
        GetWindowRect(GetDesktopWindow(), &screen_rect);

        sc.x = GetSystemMetrics(SM_CXSCREEN / 2);
        sc.y = GetSystemMetrics(SM_CYSCREEN / 2);

        int s = rand() % 600 / particle_size;

        if (s == 0)
        {
            dots.push_back(new dot(SourceEngine::Vector(rand() % (int)sc.x, -16, 0), SourceEngine::Vector((rand() % 15) - 7, rand() % 5 + 3, 0)));
        }
        else if (s == 1) {
            dots.push_back(new dot(SourceEngine::Vector(rand() % (int)sc.x, (int)sc.y + 16, 0), SourceEngine::Vector((rand() % 15) - 7, -1 * (rand() % 5 + 3), 0)));
        }
        else if (s == 2) {
            dots.push_back(new dot(SourceEngine::Vector(-16, rand() % (int)sc.y, 0), SourceEngine::Vector(rand() % 3 + 1, (rand() % 15) - 7, 0)));
        }
        else if (s == 3) {
            dots.push_back(new dot(SourceEngine::Vector((int)sc.x + 16, rand() % (int)sc.y, 0), SourceEngine::Vector(-1 * (rand() % 15 + 1), (rand() % 15) - 3, 0)));
        }

        auto alph = 255.0f * (255.0f / 255.0f);
        auto a_int = (int)(alph);

        ImGui::GetWindowDrawList()->AddRectFilled({ 0, 0 }, { (float)sc.x, (float)sc.y }, ImColor(a_int, 0, 0, 0));

        for (auto i = dots.begin(); i < dots.end();) {
            if ((*i)->m_pos.y <= -10 || (*i)->m_pos.y > sc.y + 10 || (*i)->m_pos.x < -20 || (*i)->m_pos.x > sc.x + 20) {
                delete (*i);
                i = dots.erase(i);
            }
            else {
                (*i)->update();
                i++;
            }
        }
        vector_speed = 0;
    }
    for (auto i = dots.begin(); i < dots.end(); i++) {
        (*i)->draw();
    }
}

void dot_destroy() {
    for (auto i = dots.begin(); i < dots.end(); i++) {
        delete (*i);
    }

    dots.clear();
}
