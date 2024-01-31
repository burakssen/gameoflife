#pragma once

#include <raylib.h>

class Cell
{
public:
    Cell(int x, int y, int size);
    ~Cell();

    void Draw();
    void HandleInputs(Camera2D &camera);

    void SetAlive(bool alive);
    bool IsAlive() const;

private:
    int m_x = 0;
    int m_y = 0;
    int m_size = 0;

    bool m_alive = false;
};