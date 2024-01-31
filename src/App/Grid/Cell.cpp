#include "Cell.h"

#include <iostream>

Cell::Cell(int x, int y, int size)
{
    this->m_x = x;
    this->m_y = y;
    this->m_size = size;
}

Cell::~Cell()
{
}

void Cell::Draw()
{
    DrawRectangleLines(this->m_x, this->m_y, this->m_size, this->m_size, LIGHTGRAY);
    if (this->m_alive)
    {
        DrawRectangle(this->m_x, this->m_y, this->m_size, this->m_size, BLACK);
    }
}

void Cell::HandleInputs(Camera2D &camera)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        int m_posX = this->m_x * camera.zoom - camera.target.x;
        int m_posY = this->m_y * camera.zoom - camera.target.y;

        if (GetMouseX() >= m_posX && GetMouseX() <= m_posX + this->m_size * camera.zoom &&
            GetMouseY() >= m_posY && GetMouseY() <= m_posY + this->m_size * camera.zoom)
        {
            this->m_alive = !this->m_alive;
        }
    }
}

void Cell::SetAlive(bool alive)
{
    this->m_alive = alive;
}

bool Cell::IsAlive() const
{
    return this->m_alive;
}
