#include <YAWN/YAWN.hpp>

#include <stdio.h>

using namespace YAWN;

int Application::Run() {
    Managed<Platform> platform = Platform::Instance();
    Managed<GraphicsDevice> graphicsDevice = GraphicsDevice::Instance();
    Managed<Scene> scene = Scene::Instance();
    Managed<UI> ui = new UI();

    Vertex2D vertices[] = {
        Vertex2D(Vector2(-1.0f, 1.0f), Vector2(0.0f, 0.0f), Color::White()),
        Vertex2D(Vector2(-1.0f, -1.0f), Vector2(0.0f, 1.0f), Color::White()),
        Vertex2D(Vector2(1.0f, -1.0f), Vector2(1.0f, 1.0f), Color::White()),
        Vertex2D(Vector2(1.0f, 1.0f), Vector2(1.0f, 0.0f), Color::White())
    };

    uint32 indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    //Managed<Texture> texture = new Texture();

    //texture->Load("Data/Textures/4.png");

    double lastTime = platform->CurrentTime();
    while (platform->IsWindowOpen()) {
        platform->PollEvents();

        double currentTime = platform->CurrentTime();
        float timeStep = float(currentTime - lastTime);
        lastTime = currentTime;

        scene->Update(timeStep);

        //graphicsDevice->PushPrimitives2D(texture->Id(), vertices, indices);

        ui->ShowDemo();

        graphicsDevice->Present();
    }
    return 0;
}
