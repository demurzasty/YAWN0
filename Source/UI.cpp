#include <YAWN/UI.hpp>

#include <imgui.h>
#include <imgui_internal.h>

using namespace YAWN;

static_assert(sizeof(Vertex2D) == sizeof(ImDrawVert));
static_assert(offsetof(Vertex2D, Position) == offsetof(ImDrawVert, pos));
static_assert(offsetof(Vertex2D, UV) == offsetof(ImDrawVert, uv));
static_assert(offsetof(Vertex2D, Color) == offsetof(ImDrawVert, col));

Managed<UI> UI::Instance() {
    static Managed<UI> instance = new UI();

    return instance;
}

UI::UI() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    io.BackendPlatformName = "YAWN";
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)
    // io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;    // We can create multi-viewports on the Platform side (optional)
    

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Build texture atlas
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    _fontTexture = new Texture();
    _fontTexture->SetData(width, height, pixels);

    io.Fonts->SetTexID(_fontTexture.Get());
}

UI::~UI() {
    for (auto&& [index, id] : _canvasBuffers) {
        _graphicsDevice->DestroyCanvasBuffer(id);
    }

    _fontTexture.Reset();

    ImGui::DestroyContext();
}

void UI::ShowDemo() {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(1280, 720);
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

    ImGui::NewFrame();

    static bool show_demo_window = true;
    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    ImGui::Render();

    ImDrawData* drawData = ImGui::GetDrawData();
    for (int n = 0; n < drawData->CmdListsCount; n++) {
        const ImDrawList* cmdList = drawData->CmdLists[n];
        const usize vtx_buffer_size = cmdList->VtxBuffer.Size * sizeof(ImDrawVert);
        const usize idx_buffer_size = cmdList->IdxBuffer.Size * sizeof(ImDrawIdx);

        ArrayView<const Vertex2D> vertices((const Vertex2D*)cmdList->VtxBuffer.Data, cmdList->VtxBuffer.Size);
        ArrayView<const uint32> indices(cmdList->IdxBuffer.Data, cmdList->IdxBuffer.Size);

        Id canvasBuffer = GetCanvasBuffer(n);

        _graphicsDevice->SetCanvasBufferPrimitives(canvasBuffer, vertices, indices);

        for (int i = 0; i < cmdList->CmdBuffer.Size; i++) {
            const ImDrawCmd* command = &cmdList->CmdBuffer[i];

            if (command->UserCallback) {

            } else {
                //ArrayView<const Vertex2D> vertices((const Vertex2D*)cmdList->VtxBuffer.Data, cmdList->VtxBuffer.Size);
                //ArrayView<const uint32> indices(cmdList->IdxBuffer.Data, cmdList->IdxBuffer.Size);

                ArrayView<const Vertex2D> commandVertices(vertices.Data() + command->VtxOffset, vertices.Size() - command->VtxOffset);
                ArrayView<const uint32> commandIndices(indices.Data() + command->IdxOffset, command->ElemCount);

                _graphicsDevice->PushCanvasDraw2D(canvasBuffer, 
                    _fontTexture->Id(),
                    command->IdxOffset,
                    command->ElemCount,
                    command->VtxOffset);

                //_graphicsDevice->PushPrimitives2D(_fontTexture->Id(), commandVertices, commandIndices);
            }
        }


    }

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        // GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        // glfwMakeContextCurrent(backup_current_context);
    }
}

Id UI::GetCanvasBuffer(int index) {
    if (_canvasBuffers.Contains(index)) {
        return _canvasBuffers[index];
    }

    return _canvasBuffers[index] = _graphicsDevice->CreateCanvasBuffer();
}
