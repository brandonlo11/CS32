//
//  Game.hpp
//  Project 1
//
//  Created by Brandon Lo on 1/9/22.
//

#ifndef Game_hpp
#define Game_hpp

class Mesa;

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nGarks);
    ~Game();

        // Mutators
    void play();

  private:
    Mesa* m_mesa;
};

#endif /* Game_hpp */
