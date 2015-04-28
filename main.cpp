/* To-Do:

- write rules for cells living/dying
- add checks for input size during setInitialState()
- add check for correct character values when initializing grid
- add function to randomly generate an initial state, given grid dimensions
- implement exceptions where marked
- learn ncurses to implement graphics
*/

#define ALIVE '#'
#define DEAD '.'

#include <iostream>
using std::cin; using std::cout; using std::endl;
#include <fstream>
using std::ifstream;
#include <string>
using std::string; using std::getline;


// create 2D array to use as the grid
bool** createGridArray(unsigned int grid_width, unsigned int grid_depth)
{
    bool** grid_array_pointer = new bool*[grid_depth];
    for (unsigned int i = 0; i < grid_depth; ++i) {
        grid_array_pointer[i] = new bool[grid_width];
    }
    return grid_array_pointer;
}


// set initial state of the grid
// ADD AN EXCEPTION HERE
void setInitialState(bool** grid, ifstream& init_file, unsigned int grid_width, unsigned int grid_depth)
{
    // get a line to represent each row and copy it into the grid
    string row;
    for (unsigned int y = 0; y < grid_depth; ++y) {
        getline(init_file,row);
        for (unsigned int x = 0; x < grid_width; ++x) {
            if (row[x] == ALIVE) {
                grid[y][x] = true;
            }
            else if (row[x] == DEAD) {
                grid[y][x] = false;
            }
            else {
                // raise not_implemented_error;
            }
        }
    }
}


// Sum the values of each neighboring cell in the grid and return it
// Since the grid is a bool array, should be equal to number of live cells
int countNeighbors(bool** grid, unsigned int grid_width, unsigned int grid_depth, int target_y; int target_x)
{
    unsigned int live_neighbors = 0;
    for (int y = target_y - 1; y <= target_y + 1; ++y) {
        for (int x = target_x - 1; x <= target_x + 1; ++x) {
            if (y == target_y && x == target_x) // ignore target itself
                continue
            // add length of row/column to offset effect of negative int in mod calculation
            live_neighbors += grid[(y + grid_depth) % grid_depth][(x + grid_width) % grid_width];
        }
    }
    return live_neighbors;
}


void writeNextFrame(bool** grid, unsigned int grid_width, unsigned int grid_depth)
{
    // call findNeighbors on each element in grid and change value based on Conway's rules
    // create a second grid object to read from so calculations aren't affected by new frame being drawn


}

void runGame(unsigned int turns, bool** grid)
{
    // main game loop
}


void displayGrid(bool** grid, unsigned int grid_width, unsigned int grid_depth)
{
    for (unsigned int i = 0; i < grid_depth; ++i) {
        for (unsigned int j = 0; j < grid_width; ++j) {
            if (grid[i][j]) {
                cout << ALIVE << " ";
            }
            else if (!grid[i][j]) {
                cout << DEAD << " ";
            }
        }
        cout << endl;
    }
}


int main()
{
    unsigned int grid_width, grid_depth, turns;
    string file_name;
    ifstream init_file;

    cout << "Enter name of initialization file:" << endl;
    cin >> file_name;
    init_file.open(file_name);

    // get dimensions of grid
    init_file >> grid_width >> grid_depth >> turns;

    // move buffer position to next line in file
    init_file.seekg(1, init_file.cur);

    // create grid and set initial state
    bool** life_grid = createGridArray(grid_width,grid_depth);
    setInitialState(life_grid, init_file, grid_width, grid_depth);
    displayGrid(life_grid, grid_width, grid_depth);

    init_file.close();

    return 0;
}
