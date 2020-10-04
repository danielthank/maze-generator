#include <vector>

using namespace std;

class Node {
public:
  Node();
  void open(int);
  bool up();
  bool down();
  bool left();
  bool right();
private:
  int wall;
};

class Maze {
public:
  Maze();
  Maze(int, int);
  vector<Node> &operator[](int i);
  void wilson();
private:
  constexpr static int go[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  int n, m;
  vector<vector<Node>> grids;

  bool check(int x, int y);
  pair<int, int> random_walk(int x, int y);
  void open_wall(int x, int y, int xx, int yy);
};
