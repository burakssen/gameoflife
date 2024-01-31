#include "Grid.h"

#include <iostream>

Grid::Grid()
{
}

Grid::~Grid()
{
    this->DestroyGrid();
}

Grid &Grid::GetInstance()
{
    static Grid instance;
    return instance;
}

void Grid::InitGrid()
{
    for (int i = 0; i < this->m_numOfCellsX; i++)
    {
        for (int j = 0; j < this->m_numOfCellsY; j++)
        {
            std::shared_ptr<Cell> cell = std::make_shared<Cell>(i * this->m_cellSize, j * this->m_cellSize, this->m_cellSize);
            this->m_cells.emplace_back(cell);
        }
    }
}

void Grid::DestroyGrid()
{
    this->m_cells.clear();
}

void Grid::DrawGrid()
{
    for (int i = 0; i < this->m_numOfCellsY * this->m_numOfCellsX; i++)
    {
        this->m_cells[i]->Draw();
    }
}

void Grid::UpdateGrid()
{
    std::vector<int> newCells;
    newCells.reserve(this->m_numOfCellsX * this->m_numOfCellsY);

    for (int i = 0; i < this->m_numOfCellsY; i++)
    {
        for (int j = 0; j < this->m_numOfCellsX; j++)
        {
            int neighbors = 0;
            if (i > 0 && j > 0)
            {
                neighbors += this->m_cells[(j - 1) * this->m_numOfCellsY + (i - 1)]->IsAlive();
            }
            if (j > 0)
            {
                neighbors += this->m_cells[(j - 1) * this->m_numOfCellsY + i]->IsAlive();
            }
            if (i < this->m_numOfCellsX - 1 && j > 0)
            {
                neighbors += this->m_cells[(j - 1) * this->m_numOfCellsY + (i + 1)]->IsAlive();
            }
            if (i > 0)
            {
                neighbors += this->m_cells[j * this->m_numOfCellsY + (i - 1)]->IsAlive();
            }
            if (i < this->m_numOfCellsY - 1)
            {
                neighbors += this->m_cells[j * this->m_numOfCellsY + (i + 1)]->IsAlive();
            }
            if (i > 0 && j < this->m_numOfCellsX - 1)
            {
                neighbors += this->m_cells[(j + 1) * this->m_numOfCellsY + (i - 1)]->IsAlive();
            }
            if (j < this->m_numOfCellsX - 1)
            {
                neighbors += this->m_cells[(j + 1) * this->m_numOfCellsY + i]->IsAlive();
            }
            if (i < this->m_numOfCellsY - 1 && j < this->m_numOfCellsX - 1)
            {
                neighbors += this->m_cells[(j + 1) * this->m_numOfCellsY + (i + 1)]->IsAlive();
            }

            if (this->m_cells[j * this->m_numOfCellsY + i]->IsAlive() == 1)
            {
                if (neighbors < 2)
                {
                    newCells[j * this->m_numOfCellsY + i] = 0;
                }
                else if (neighbors == 2 || neighbors == 3)
                {
                    newCells[j * this->m_numOfCellsY + i] = 1;
                }
                else if (neighbors > 3)
                {
                    newCells[j * this->m_numOfCellsY + i] = 0;
                }
            }
            else
            {
                if (neighbors == 3)
                {
                    newCells[j * this->m_numOfCellsY + i] = 1;
                }
                else
                {
                    newCells[j * this->m_numOfCellsY + i] = 0;
                }
            }
        }
    }

    for (int i = 0; i < this->m_numOfCellsX * this->m_numOfCellsY; i++)
    {
        this->m_cells[i]->SetAlive(newCells[i]);
    }
}

void Grid::HandleInputs(Camera2D &camera)
{
    for (int i = 0; i < this->m_numOfCellsX * this->m_numOfCellsY; i++)
    {
        this->m_cells[i]->HandleInputs(camera);
    }
}

void Grid::SetNumOfCellsX(int numOfCellsX)
{
    this->m_numOfCellsX = numOfCellsX;
}

void Grid::SetNumOfCellsY(int numOfCellsY)
{
    this->m_numOfCellsY = numOfCellsY;
}

void Grid::SetCellSize(int cellSize)
{
    this->m_cellSize = cellSize;
}
