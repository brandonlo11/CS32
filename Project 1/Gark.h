//
//  Gark.hpp
//  Project 1
//
//  Created by Brandon Lo on 1/9/22.
//

#ifndef Gark_hpp
#define Gark_hpp

class Mesa;

class Gark
{
  public:
        // Constructor
    Gark(Mesa* mp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;

        // Mutators
    void move();
    bool getAttacked(int dir);

  private:
    Mesa* m_mesa;
    int   m_row;
    int   m_col;
    int   m_health;
};


#endif /* Gark_hpp */
