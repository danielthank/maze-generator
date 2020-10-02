#include <iostream>
#include <vector>
#include <stack>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "./maze.hpp"

using namespace std;

enum State {
            UNVISITED = 0,
            VISITING = 1,
            VISITED = 2,
};

Node::Node() : wall(0) {}

void Node::open(int index) { wall |= (1 << index); }

bool Node::top() { return wall & (1 << 0); }

bool Node::down() { return wall & (1 << 1); }

bool Node::left() { return wall & (1 << 2); }

bool Node::right() { return wall & (1 << 3); }

Maze::Maze() : n(0), m(0) {}

Maze::Maze(int n, int m) : n(n), m(m) {
  grids.resize(n);
  for (int i=0; i<n; i++) {
    grids[i] = vector<Node>(m);
  }
}

vector<Node> &Maze::operator[](int i) {
  return grids[i];
}

void Maze::wilson() {
  vector<vector<State>> states;
  states.resize(n);
  for (int i=0; i<n; i++) {
    states[i] = vector<State>(m, UNVISITED);
  }
  states[0][0] = VISITED;
  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
      if (states[i][j] == VISITED) continue;
      stack<pair<int, int>> visiting;
      auto now = make_pair(i, j);
      bool success = false;
      while (true) {
        int x = now.first, y = now.second;
        switch (states[x][y]) {
        case UNVISITED:
          states[x][y] = VISITING;
          visiting.push(make_pair(x, y));
          break;
        case VISITING:
          while (visiting.top() != now) {
            states[visiting.top().first][visiting.top().second] = UNVISITED;
            visiting.pop();
          }
          break;
        case VISITED:
          int nowx = x, nowy = y;
          while (!visiting.empty()) {
            int nextx = visiting.top().first, nexty = visiting.top().second;
            open_wall(nowx, nowy, nextx, nexty);
            states[nextx][nexty] = VISITED;
            visiting.pop();
            nowx = nextx, nowy = nexty;
          }
          success = true;
          break;
        }
        if (success) break;
        now = random_walk(x, y);
      }
    }
  }
}


bool Maze::check(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < m;
}

pair<int, int> Maze::random_walk(int x, int y) {
  while (1) {
    int t = emscripten_random() * 4;
    int xx = x + go[t][0];
    int yy = y + go[t][1];
    if (!check(xx, yy)) continue;
    return make_pair(xx, yy);
  }
}

void Maze::open_wall(int x, int y, int xx, int yy) {
  for (int i=0; i<4; i++) {
    if (x + go[i][0] == xx && y + go[i][1] == yy) {
      grids[x][y].open(i);
      grids[xx][yy].open(i ^ 1);
      break;
    }
  }
}
