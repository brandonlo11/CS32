//
//  History.cpp
//  Project 1
//
//  Created by Brandon Lo on 1/10/22.
//

#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) : m_rows(nRows), m_cols(nCols) {
    // Fill the grid with dots
    for (int r = 0; r < m_rows; r++)
        for (int c = 0; c < m_cols; c++)
            m_grid[r][c] = '.';
}

bool History::record (int r, int c){
    if (r > m_rows || c > m_cols || m_rows < 1 || m_cols <1){
        return false;
    }
    else if (m_grid[r-1][c-1] == 'Z'){
        return true;
    }
    else if (m_grid[r-1][c-1] != '.'){
        m_grid[r-1][c-1] += 1;
        return true;
    }
    else{
        m_grid[r-1][c-1] = 'A';
        return true;
    }
}

void History::display() const{
    clearScreen();

    int r,c;
    for (r = 0; r < m_rows; r++)
    {
        for (c = 0; c < m_cols; c++){
            cout << m_grid[r][c];
        }
        cout << endl;
    }
    cout << endl;
}


