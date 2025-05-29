#include <cstdio>
#include <cstring>
#include <stdexcept>

struct SimpleString {
  SimpleString(size_t max_size) : max_size {max_size}, length{} {
    if(max_size ==0){
      throw std::runtime_error{"Max size must be at least 1."};
    }
    buffer = new char[max_size];
    buffer[0] = 0; 
  }
  ~SimpleString(){
    delete[] buffer;
  }

  void print() {
    printf("%s",  buffer);
  }

  // for appending a single character 
  bool append(const char* x){
    const auto x_len = strlen(x);

    if(x_len + length + 2 > max_size) return false;

    std::strncpy(buffer + length, x, max_size - length);

    length += x_len;
    buffer[length] = 0;

    return true;
  }

  // for appending a whole line 
  bool append_line(const char* x) {
    const auto x_len = strlen(x);

    if(x_len + length + 2 > max_size) return false;

    // strncpy will copy up to num bytes from source into destination. once finished it will
    // return the "destination", which is not used here.
    // this is the signature
    // char * std::strncpy(char* destination, const char* source, std::size_t num)
    std::strncpy(buffer+length, x, max_size - length);

    length += x_len;
    buffer[length++] = '\n';
    buffer[length] = 0;
    return true;
  }

private:
  size_t max_size;
  char * buffer;
  size_t length;
  
};

struct Cell{
  int nothing{0};
};
struct Grid{

  Cell cells[25] = {};
    
  void draw(){
    SimpleString maze{500};

    maze.append_line("+--+--+--+--+--+");
    for(int row = 0; row < 25; row += 5){

      for(int col  = 0; col < 5; col += 1){
        // holding the cells in a single demensional array
        // makes some things easier, but also some things harder
        // like thinking 
        Cell cell = cells[row + col]; // this is really tripping my brain up

        if(cell.nothing == 0){
          maze.append("|  ");
        }
      }
      maze.append_line("|");
      for(int col =0; col < 5; col +=1){
        Cell cell = cells[row + col];

        if(cell.nothing == 0){
          maze.append("+--");
        }
      }
      maze.append_line("+");
    }

    maze.print();
  }
};
  
int main(){
  Grid grid;

  grid.draw();

}

