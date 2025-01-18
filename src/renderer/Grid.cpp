#include <renderer/Grid.h>

#define GRID_WIDTH 10
#define GRID_HEIGHT 10

int grid[GRID_WIDTH][GRID_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

std::vector<float> Grid::generateGridVertices() {
    std::vector<float> vertices;
    float cellSize = 0.2f;

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x] == 1) {
                float xPos = -1.0f + x * cellSize;         // Map x to NDC
                float yPos = -1.0f + y * cellSize;         // Map y to NDC
                
                // First triangle
                vertices.push_back(xPos);                // Bottom-left
                vertices.push_back(yPos);

                vertices.push_back(xPos + cellSize);     // Bottom-right
                vertices.push_back(yPos);

                vertices.push_back(xPos);                // Top-left
                vertices.push_back(yPos + cellSize);

                // Second triangle
                vertices.push_back(xPos);                // Top-left
                vertices.push_back(yPos + cellSize);

                vertices.push_back(xPos + cellSize);     // Bottom-right
                vertices.push_back(yPos);

                vertices.push_back(xPos + cellSize);     // Top-right
                vertices.push_back(yPos + cellSize);
            }
        }
    }

    return vertices;
}

void Grid::createBufferObjects(){
    gridVertices = generateGridVertices();

    glGenVertexArrays(1, &gd_VAO);
    glGenBuffers(1, &gd_VBO);

    glBindVertexArray(gd_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, gd_VBO);
    glBufferData(GL_ARRAY_BUFFER, gridVertices.size() * sizeof(float), gridVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Grid::drawGrid(){
    glBindVertexArray(gd_VAO);
    glDrawArrays(GL_TRIANGLES, 0, gridVertices.size() / 2);
    glBindVertexArray(0);
}

Grid::~Grid(){
    glDeleteVertexArrays(1, &gd_VAO);
    glDeleteBuffers(1, &gd_VBO);
}
