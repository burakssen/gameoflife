#pragma once

#include <memory>
#include <vector>

#include <raylib.h>

#include "Cell.h"

class Grid
{
private:
    Grid();

public:
    static Grid &GetInstance();
    ~Grid();

    void DrawGrid();
    void UpdateGrid();
    void HandleInputs(Camera2D &camera);

    void SetNumOfCellsX(int numOfCellsX);
    void SetNumOfCellsY(int numOfCellsY);
    void SetCellSize(int cellSize);
    void InitGrid();
    void DestroyGrid();

private:
    int m_numOfCellsX = 0;
    int m_numOfCellsY = 0;
    int m_cellSize = 0;

    std::vector<std::shared_ptr<Cell>> m_cells;
};