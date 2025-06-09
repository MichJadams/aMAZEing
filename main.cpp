#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <random>

struct SimpleString {
    SimpleString(size_t max_size) : max_size{ max_size }, length{} {
        if (max_size == 0) {
            throw std::runtime_error{ "Max size must be at least 1." };
        }
        buffer = new char[max_size];
        buffer[0] = 0;
    }
    ~SimpleString() {
        delete[] buffer;
    }

    void print() {
        printf("%s", buffer);
    }

    // for appending a single character 
    bool append(const char* x) {
        const auto x_len = strlen(x);

        if (x_len + length + 2 > max_size) return false;

        std::strncpy(buffer + length, x, max_size - length);

        length += x_len;
        buffer[length] = 0;

        return true;
    }

    // for appending a whole line 
    bool append_line(const char* x) {
        const auto x_len = strlen(x);

        if (x_len + length + 2 > max_size) return false;

        // strncpy will copy up to num bytes from source into destination. once finished it will
        // return the "destination", which is not used here.
        // this is the signature
        // char * std::strncpy(char* destination, const char* source, std::size_t num)
        std::strncpy(buffer + length, x, max_size - length);

        length += x_len;
        buffer[length++] = '\n';
        buffer[length] = 0;
        return true;
    }

private:
    size_t max_size;
    char* buffer;
    size_t length;

};

enum Direction {
    North,
    South,
    East,
    West
};
struct Coordinate {
	Coordinate() : row{ 0 }, col{ 0 } {}
    Coordinate(int row, int col) : row{ row }, col{ col } {}
    int row;
    int col;
};

struct Cell {
    Cell() : location{0,0} {}
   

    int right_wall{ 0 };
    int bottom{ 0 };
    Coordinate location;
};

struct Grid {

    Grid(Cell** cells, int rows, int cols) :
        cells{ cells }, rows{ rows }, cols{ cols }
    {

    }

    Cell** cells;
    int rows;
    int cols;

    void draw() {
        SimpleString maze{ 1100 };

	//maze.append("   ");
        for (int col = 0; col < rows; col += 1) {

            maze.append("+--");

        }

        maze.append_line("+");

        for (int row = 0; row < rows; row += 1) {
	  
	  maze.append("|");
            for (int col = 0; col < cols; col += 1) {

                Cell cell = cells[row][col];

                if (cell.right_wall == 0) {
                    maze.append("  |");
                }
                else {
                    maze.append("   ");
                }
            }

	    maze.append_line("");

            for (int col = 0; col < cols; col += 1) {
                Cell cell = cells[row][col];

                if (cell.bottom == 0) {
                    maze.append("+--");
                }
                else {
                    maze.append("+  ");
                }
            }
            maze.append_line("+");
        }

        maze.print();
    }
};

Cell** generate_cells(int rows, int cols)
{
    Cell** cells = new Cell*[rows];
    
    for (int row = 0; row < rows; row ++)
    {
        cells[row] = new Cell[cols];
    }
    return cells;
}

void generate_binary_tree_maze(Cell** cells, int row, int col)
{
  std::default_random_engine generator{};
  std::uniform_int_distribution<int> distribution(0,1);
  for (int r = 0; r < row; r++)
    {
      for(int c = 0; c < col; c++)
	{
	 
       	     int dice_roll = distribution(generator);

	     if (r == row-1 && c == col-1)
	       {}
	     else if(r == row-1)
	       {
		  cells[r][c].right_wall = dice_roll;
	       }
	     else if(c == col-1)
	       {
		  cells[r][c].bottom = dice_roll;
	       }
	     else
	       {
		    if(dice_roll == 1)
		      {
			cells[r][c].right_wall = 1;
		      }
		    else
		      {
			cells[r][c].bottom = 1; 
		      }
	       } 
	    
	}
    }
}



int main() {
  int rows = 10;
  int cols = 10; 
    Cell** cells = generate_cells(rows, cols);
    Grid grid(cells, rows, cols);
    generate_binary_tree_maze(cells, rows, cols); 


    grid.draw();

}

