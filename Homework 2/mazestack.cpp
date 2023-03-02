//
//  main.cpp
//  Homework 2
//
//  Created by Brandon Lo on 1/29/22.
//

#include <iostream>
#include <stack>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    stack<Coord> coordStack;
    coordStack.push(Coord(sr, sc));
    maze[sr][sc] = '@';
    while (!coordStack.empty()){
        Coord current = coordStack.top();
        coordStack.pop();
        if (current.r() == er && current.c() == ec){
            return true;
        }
        if (maze[current.r()][current.c()-1] == '.'){ //check west
            coordStack.push(Coord(current.r(), current.c()-1));
            maze[current.r()][current.c()-1] = '@';
        }
        if (maze[current.r()+1][current.c()] == '.'){ //check south
            coordStack.push(Coord(current.r()+1, current.c()));
            maze[current.r()+1][current.c()] = '@';
        }
        if (maze[current.r()][current.c()+1] == '.'){ //check east
            coordStack.push(Coord(current.r(), current.c()+1));
            maze[current.r()][current.c()+1] = '@';
        }
        if (maze[current.r()-1][current.c()] == '.'){ //check north
            coordStack.push(Coord(current.r()-1, current.c()));
            maze[current.r()-1][current.c()] = '@';
        }
//        print(maze, nRows);
    }
    return false;
}
