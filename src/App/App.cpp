#include "App.h"

#include <iostream>

App::App()
{
}

App::~App()
{
    this->Destroy();
}

App &App::GetInstance()
{
    static App instance;
    return instance;
}

void App::Init()
{
    InitWindow(this->m_width, this->m_height, this->m_title.c_str());
    SetTargetFPS(60);

    for (int i = 1; i <= this->m_width && i <= this->m_height; i++)
    {
        if (this->m_width % i == 0 && this->m_height % i == 0)
        {
            this->m_commonDivisors.emplace_back(i);
        }
    }

    int cellSize = this->m_commonDivisors[this->m_currentDivisor];
    int numOfCellsX = this->m_width / cellSize;
    int numOfCellsY = this->m_height / cellSize;

    std::cout << "Num Of Cells X: " << numOfCellsX << std::endl;
    std::cout << "Num Of Cells Y: " << numOfCellsY << std::endl;
    std::cout << "Cell Size: " << cellSize << std::endl;

    this->m_grid.SetNumOfCellsX(numOfCellsX);
    this->m_grid.SetNumOfCellsY(numOfCellsY);
    this->m_grid.SetCellSize(cellSize);

    this->m_grid.InitGrid();

    this->m_camera.target = {0.0f, 0.0f};
    this->m_camera.offset = {0.0f, 0.0f};
    this->m_camera.rotation = 0.0f;
    this->m_camera.zoom = 1.0f;
}

void App::Run()
{
    while (!WindowShouldClose())
    {
        this->HandleInputs();
        this->Update();
        this->Draw();
    }
}

void App::HandleInputs()
{
    if (IsKeyPressed(KEY_UP))
    {
        this->m_speed += 1.0f;
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
        this->m_speed -= 1.0f;
    }

    if (IsKeyPressed(KEY_U))
    {
        int cellSize = this->m_commonDivisors[--this->m_currentDivisor];
        int numOfCellsX = this->m_width / cellSize;
        int numOfCellsY = this->m_height / cellSize;

        this->m_grid.DestroyGrid();
        this->m_grid.SetNumOfCellsX(numOfCellsX);
        this->m_grid.SetNumOfCellsY(numOfCellsY);
        this->m_grid.SetCellSize(cellSize);
        this->m_grid.InitGrid();
    }

    if (IsKeyPressed(KEY_D))
    {
        int cellSize = this->m_commonDivisors[++this->m_currentDivisor];
        int numOfCellsX = this->m_width / cellSize;
        int numOfCellsY = this->m_height / cellSize;

        this->m_grid.DestroyGrid();
        this->m_grid.SetNumOfCellsX(numOfCellsX);
        this->m_grid.SetNumOfCellsY(numOfCellsY);
        this->m_grid.SetCellSize(cellSize);
        this->m_grid.InitGrid();
    }

    if (int wm = GetMouseWheelMove(); wm != 0)
    {
        this->m_camera.zoom += wm * 0.05f;

        if (this->m_camera.zoom < 1.0f)
        {
            this->m_camera.zoom = 1.0f;
        }
        else if (this->m_camera.zoom > 3.0f)
        {
            this->m_camera.zoom = 3.0f;
        }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
    {
        // while button down move camera with mouse
        this->m_camera.target.x -= GetMouseX() * 0.5f;
        this->m_camera.target.y -= GetMouseY() * 0.5f;

        // clamp camera position to screen bounds
        if (this->m_camera.target.x < 0.0f)
        {
            this->m_camera.target.x = 0.0f;
        }
        else if (this->m_camera.target.x > this->m_width)
        {
            this->m_camera.target.x = this->m_width;
        }

        if (this->m_camera.target.y < 0.0f)
        {
            this->m_camera.target.y = 0.0f;
        }
        else if (this->m_camera.target.y > this->m_height)
        {
            this->m_camera.target.y = this->m_height;
        }

        // update camera offset
        this->m_camera.offset.x = -this->m_camera.target.x + this->m_width / 2;
        this->m_camera.offset.y = -this->m_camera.target.y + this->m_height / 2;

        // clamp camera offset to screen bounds
        if (this->m_camera.offset.x > 0.0f)
        {
            this->m_camera.offset.x = 0.0f;
        }
        else if (this->m_camera.offset.x < -this->m_width)
        {
            this->m_camera.offset.x = -this->m_width;
        }

        if (this->m_camera.offset.y > 0.0f)
        {
            this->m_camera.offset.y = 0.0f;
        }
        else if (this->m_camera.offset.y < -this->m_height)
        {
            this->m_camera.offset.y = -this->m_height;
        }

        // update camera
        this->m_camera.target.x += this->m_camera.offset.x;
        this->m_camera.target.y += this->m_camera.offset.y;

        this->m_camera.offset = {0.0f, 0.0f};
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        this->m_paused = !this->m_paused;
        this->m_started = true;
    }

    this->m_grid.HandleInputs(this->m_camera);
}

void App::Draw()
{
    BeginDrawing();
    BeginMode2D(this->m_camera);
    ClearBackground(RAYWHITE);
    this->m_grid.DrawGrid();

    Color color = {0, 0, 0, 100};
    DrawRectangle(0, 0, 250, 100, color);
    DrawRectangleLines(0, 0, 250, 100, BLACK);
    if (!this->m_started)
    {
        DrawText("Press Space To Start", 10, 10, 20, BLACK);
    }
    else if (this->m_paused)
    {
        DrawText("Paused", 10, 10, 20, BLACK);
    }
    else
    {
        DrawText("Running", 10, 10, 20, BLACK);
        DrawText(("Speed: " + std::to_string(this->m_speed)).c_str(), 10, 30, 20, BLACK);
        DrawText(("Step Number: " + std::to_string(this->m_stepNumber)).c_str(), 10, 50, 20, BLACK);
    }
    EndMode2D();
    EndDrawing();
}

void App::Update()
{
    if (!this->m_paused)
    {
        this->m_timer += GetFrameTime() * this->m_speed;
        if (this->m_timer >= 1.0f)
        {
            this->m_timer = 0.0f;
            this->m_grid.UpdateGrid();
            this->m_stepNumber++;
        }
    }
}

void App::Destroy()
{
    CloseWindow();
}