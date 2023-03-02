#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    bool isBlockingObjectAt(int x, int y); //checks if there is an actor blocking movement at the point passed in
    bool Damageable(int x, int y); //checks if there is a damageable actor at the point passed in
    void damagePeach(); //hurts peach
    void callBonk(int x, int y); //calls the bonk function of an actor
    bool overlapsPeach(int x, int y); //determines if an actor overlaps with peach
    bool inLinePeach(int y); //checks if peach is within row of the Piranha
    bool inVicinityPeach(int x); //checks if peach is close enough to the piranha so piranha can shoot fire
    bool isLeft(int x, int y); //checks if peach is to the left of the point passed in
    bool getInvincibilityLeft(); //sees if peach is invincible
    int randomDir(); //creates a random start direction
    void endLevel(); //ends the level
    void endGame(); //ends the game
    void powerUpJump(); //activates Peach's jump power
    void powerUpStar(); //activates Peach's star power
    void powerUpShoot(); //activates Peach's shoot power
    void addActor(Actor* actor); //adds a new actor to the list
    void setHitpoints(int x); //sets Peach's hitpoint to the parameter
    void setEmpty(std::string str); //sets a string (for the top text) to empty
    ~StudentWorld();
    
private:
    std::list<Actor*> m_actors; //list of actor pointers
    Peach* m_peach; //pointer to peach
    bool finishedLevel;
    bool finishedGame;
    std::string jumpstr; //corresponds to a section of the top text
    std::string starstr;
    std::string shootstr;
};

#endif // STUDENTWORLD_H_
