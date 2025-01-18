#include <renderer/GridDrawer.h>

int grid[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

std::vector<float> GridDrawer::generateGridVertices() {
    std::vector<float> vertices;

    float cellSize = 0.1f; // Size of each grid cell
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x] == 1) { // Only add vertices for walls
                float xPos = x * cellSize;
                float yPos = y * cellSize;

                // Add vertices for a quad
                vertices.push_back(xPos);               // Bottom-left
                vertices.push_back(yPos);

                vertices.push_back(xPos + cellSize);    // Bottom-right
                vertices.push_back(yPos);

                vertices.push_back(xPos + cellSize);    // Top-right
                vertices.push_back(yPos + cellSize);

                vertices.push_back(xPos);               // Top-left
                vertices.push_back(yPos + cellSize);
            }
        }
    }

    return vertices;
}

void GridDrawer::createBufferObjects(){
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

void GridDrawer::drawGrid(){
    glBindVertexArray(gd_VAO);
    glDrawArrays(GL_QUADS, 0, gridVertices.size() / 2);
    glBindVertexArray(0);
}


