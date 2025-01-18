#pragma once

#include <vector>
#include <glad/glad.h>

class Grid
{
private:
    const int GRID_WIDTH = 10;
    const int GRID_HEIGHT = 10;

    GLuint gd_VAO, gd_VBO;
public:
    Grid(){}
    ~Grid();
    std::vector<float> gridVertices;
    std::vector<float> generateGridVertices();
    
    void createBufferObjects();
    void drawGrid();
};
