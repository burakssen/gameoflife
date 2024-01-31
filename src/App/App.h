#pragma once

#include <string>

#include <raylib.h>

#include "Grid/Grid.h"

class App
{
private:
    App();
    void Destroy();
    void HandleInputs();
    void Draw();
    void Update();

public:
    static App &GetInstance();
    ~App();

    void Init();
    void Run();

private:
    int m_width = 1024;
    int m_height = 768;

    std::string m_title = "Game Of Life Simulation";

    Grid &m_grid = Grid::GetInstance();

    bool m_paused = true;
    float m_speed = 10.0f;
    float m_timer = 0.0f;

    std::vector<int> m_commonDivisors;
    int m_currentDivisor = 4;
    int m_stepNumber = 0;
    bool m_started = false;

    Camera2D m_camera = {0};
};
