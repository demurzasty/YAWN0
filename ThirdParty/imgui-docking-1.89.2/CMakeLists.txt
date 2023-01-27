cmake_minimum_required (VERSION 3.8.2)

add_library (ImGUI STATIC
    "imgui.cpp"
    "imgui_demo.cpp"
    "imgui_draw.cpp"
    "imgui_tables.cpp"
    "imgui_widgets.cpp"
)
target_include_directories (ImGUI PUBLIC ".")
