#include <cstdio>
#include <cstring>
#include <cstdlib>

struct Coordinate
{
  int x;
  int y;
};

enum class Direction
  {
    North,
    South,
    East,
    West
  };

enum class ConnectionType
  {
    Wall,
    Hall,
    Perimiter,
  };
struct Connection
{
  ConnectionType type = ConnectionType::Wall;
};
struct Cell {
   Coordinate location{};
  // next step is to initilize these to something like ConnectionType::Perimiter
  // and get rid of the null pointers 
  Connection* North = 0;
  Connection* South = 0;
  Connection* East = 0;
  Connection* West = 0;
  
  void link(Direction dire, ConnectionType type)
  {
    switch(dire)
      {
      case(Direction::North):
	{
	  this->North->type = type; 
	}break;
      case(Direction::South):
	{
	  this->South->type = type;
	}
	break;
      case(Direction::East):
	{
	  this->East->type = type;
	}
	break;
      case (Direction::West):
	{
	  this->West->type = type;
	}
	break; 
      };
  }

  void print_links()
  {
    printf("North {%p} | South {%p} | East {%p}| West {%p}\n", North, South, East, West);
  }
};
struct SimpleString
{
  SimpleString(int max_size): max_size{max_size}{
    output = new char[max_size];
    output[0] = 0; 
  }

  void append(const char* x){

    int x_len = strlen(x);
    strncpy(output + length, x, max_size - length);
    length += x_len;
    
    output[length] = 0; 
  }
  void append_line(const char* x){
    int x_len = strlen(x);
    strncpy(output + length, x, max_size-length);
    length += x_len;
    output[length++] = '\n';
    output[length] = 0;  
  }
  void print() const
  {
    printf("%s", output); 
  }

  char* output;
  int max_size{};
  size_t length{};
};

void draw_grid(Cell** cells, int rows, int cols)
{
  SimpleString maze{1000};

  
  
  for(int r{}; r <rows; r++)
    {
      for(int c{}; c < cols; c++)
      {
	if(cells[r][c].North == nullptr)
	  {
	    maze.append("+--");
	    continue;
	  }

	if(cells[r][c].North->type == ConnectionType::Wall)
	  {
	   
	    maze.append("+--");
	    continue;
	    
	  }
	maze.append("+  ");
        
      }
      maze.append_line("+");
      maze.append("|");
      for(int c{}; c < cols; c++)
	{
	  if(cells[r][c].East == nullptr)
	    {
	      maze.append("  |");
	      continue;
	    }
	  if( cells[r][c].East->type == ConnectionType::Wall)
	    {
	      maze.append("  |");
	      continue;
	    }
	  maze.append("   ");
	}

      maze.append_line("");
    }

  for(int c{}; c< cols; c++)
    {
      if(cells[rows -1][c].South == nullptr)
	{
	  maze.append("+--");
	}
    }
  maze.append_line("+");
  
  maze.print();
}

Cell** create_grid(int rows, int cols)
{
  Cell** cells = new Cell*[rows];
  
  for(int r = 0; r < rows; r++)
    {
      cells[r] = new Cell[cols];
    }

  // now link the cells. 
  for(int r = 0; r < rows; r++)
    {
      for(int c = 0; c < cols; c++)
	{
	  if(r != 0)
	    {
	      Connection* conn = new Connection{ConnectionType::Wall};
	      cells[r][c].North = conn;
	      cells[r-1][c].South = conn;
	    }
	  if(c != cols-1)
	    {
	      Connection* conn = new Connection{ConnectionType::Wall};
	      cells[r][c].East = conn;
	      cells[r][c+1].West = conn;
	    }
	}
    }
  return cells;
}

void make_binary_maze(Cell** cells, int rows, int cols)
{
  for(int r{}; r < rows; r++)
    {
      for(int c{}; c< cols; c++)
	{
       	  Cell cell = cells[r][c];
	  if(cell.North == nullptr && cell.East == nullptr) continue;
	  if(cell.North == nullptr)
	    {
	       cell.link(Direction::East, ConnectionType::Hall);
	       continue;
	    }
	  if(cell.East == nullptr)
	    {
	      cell.link(Direction::North, ConnectionType::Hall);
	      continue;
	    }
	  int choice = rand() % 2;
	  if(choice == 1)
	    {
	      cell.link(Direction::North, ConnectionType::Hall);
	    }
	  if(choice == 0)
	    {
	      cell.link(Direction::East, ConnectionType::Hall);
	    }
	}
    }
}

int main()
{
  Cell** cells = create_grid(10,10);

  make_binary_maze(cells, 10, 10);
  // create entrance and exit
  cells[0][0].North = new Connection{ConnectionType::Hall};
  cells[9][9].South = new Connection{ConnectionType::Hall};
  draw_grid(cells, 10, 10); 
 }

