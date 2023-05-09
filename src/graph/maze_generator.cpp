#include "graph/maze_generator.h"

void MazeGenerator::generate(Grid &grid, Grid::Location start,
                             Grid::Location end,
                             std::vector<Grid::Location> &path) {
    for (int i = 0; i < grid.height; i++) {
        std::fill(grid.grid[i].begin(), grid.grid[i].end(),
                  Grid::CellType::WALL);
    }

    std::random_device rd;
    std::mt19937::result_type seed =
        rd() ^
        ((std::mt19937::result_type)
             std::chrono::duration_cast<std::chrono::seconds>(
                 std::chrono::system_clock::now().time_since_epoch())
                 .count() +
         (std::mt19937::result_type)
             std::chrono::duration_cast<std::chrono::microseconds>(
                 std::chrono::high_resolution_clock::now().time_since_epoch())
                 .count());

    std::mt19937 gen(seed);
    std::stack<Grid::Location> cells;

    cells.push(start);

    // set start and top positions
    grid.grid[start.y][start.x] = Grid::CellType::EMPTY;
    grid.grid[end.y][end.x] = Grid::CellType::EMPTY;

    path.push_back(start);
    path.push_back(end);

    while (!cells.empty()) {
        Grid::Location current = cells.top();
        cells.pop();

        std::vector<Grid::Location> neighbors =
            grid.neighbors(current, 1, false);

        if (neighbors.empty()) {
            continue;
        }

        std::uniform_int_distribution<int> dist(0, neighbors.size() - 1);
        Grid::Location random_neighbor = neighbors[dist(gen)];

        cells.push(current);
        cells.push(random_neighbor);

        grid.grid[(random_neighbor.y + current.y) / 2]
                 [(random_neighbor.x + current.x) / 2] = Grid::CellType::EMPTY;
        grid.grid[random_neighbor.y][random_neighbor.x] = Grid::CellType::EMPTY;

        path.push_back(Grid::Location{(random_neighbor.x + current.x) / 2,
                                      (random_neighbor.y + current.y) / 2});
        path.push_back(Grid::Location{random_neighbor.x, random_neighbor.y});
    }
}