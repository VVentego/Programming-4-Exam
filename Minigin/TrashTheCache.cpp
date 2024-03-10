#include "TrashTheCache.h"
#include <SDL_ttf.h>

namespace dae
{
    TrashTheCache::TrashTheCache(GameObject* pOwner, SDL_Window* parentWindow, int width, int height, const char* title) : dae::Component::Component(pOwner),
        parentWindow(parentWindow), width(width), height(height), title(title)
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();

        // Setup Dear ImGui platform/renderer bindings
        ImGui_ImplSDL2_InitForOpenGL(parentWindow, SDL_GL_GetCurrentContext());
        //const char* glsl_version = "#version 330";
        ImGui_ImplOpenGL2_Init();
    }

    TrashTheCache::~TrashTheCache()
    {
        // Cleanup
        ImGui_ImplOpenGL2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void TrashTheCache::PlotFunction(float (*func)(float), float xMin, float xMax, int numPoints)
    {
        data.clear();
        float step = (xMax - xMin) / numPoints;
        for (float x = xMin; x <= xMax; x += step) {
            float y = func(x);
            data.push_back({ x, y });
        }
    }

    void TrashTheCache::Render()
    {
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Create dialog box
        ImGui::SetNextWindowSize(ImVec2(static_cast<float>(width), static_cast<float>(height)));
        ImGui::Begin(title, nullptr, ImGuiWindowFlags_NoResize);

        // Create child window for the graph
        ImGui::BeginChild("Graph", ImVec2(static_cast<float>(width), static_cast<float>(height)), true);

        // Plot the graph
        ImGui::PlotLines("Function Plot", [](void* data, int idx) {
            std::vector<ImVec2>* plotData = (std::vector<ImVec2>*)data;
            return plotData->at(idx).y;
            }, (void*)&data, static_cast<int>(data.size()), 0, NULL, FLT_MAX, FLT_MAX, ImVec2(static_cast<float>(0), static_cast<float>(200)));

        ImGui::EndChild();
        ImGui::End(); // End dialog box

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    }
}