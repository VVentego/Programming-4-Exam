#pragma once
#include "Component.h"
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl2.h>
#include <vector>

namespace dae
{
    class TrashTheCache :
        public Component
    {
    public:
        TrashTheCache(GameObject* pOwner, SDL_Window* parentWindow, int width, int height, const char* title);
        ~TrashTheCache();

        void PlotFunction(float(*func)(float), float xMin, float xMax, int numPoints);

        void Render();

    private:
        SDL_Window* parentWindow;
        int width, height;
        const char* title;
        std::vector<ImVec2> data;
    };
}
