//
//  Mesa.hpp
//  Project 1
//
//  Created by Brandon Lo on 1/9/22.
//

#ifndef Mesa_hpp
#define Mesa_hpp

#include "Player.h"
#include "globals.h"
#include "Gark.h"
#include "History.h"

class Gark;
class Mesa
{
  public:
        // Constructor/destructor
    Mesa(int nRows, int nCols);
    ~Mesa();

        // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     garkCount() const;
    int     numGarksAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;

        // Mutators
    bool   addGark(int r, int c);
    bool   addPlayer(int r, int c);
    bool   attackGarkAt(int r, int c, int dir);
    bool   moveGarks();
    History& history();

  private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Gark*   m_garks[MAXGARKS];
    int     m_nGarks;
    History m_history;
};

#endif /* Mesa_hpp */
