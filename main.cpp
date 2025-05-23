#include <cstdef>
#include <unordered_map>
#include <unordered_map>

struct Cell {
  Cell(int row, int col){
    this.row = row;
    this.col = col;
    this.links = {};
  }
  void link(Cell cell, bool bidi){
    this.links[cell] = true;
    if(bidi){
      cell.link(this, false);
    }

  }

  void unlink(Cell cell, bool bidi){
    // not sure how to "delete" an element from a map in C++
    
  }
  
  std::unordered_map<Cell, bool> links;
  Cell north;
  Cell south;
  Cell east;
  Cell west;
private:
  int row;
  int col;
}
  
struct Grid {
  Grid(int row, int col){
    this.row = row;
    this.col = col;
  }
private:
  int row;
  int col;
}

int main(){}

