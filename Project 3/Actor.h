#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

class Actor: public GraphObject{
public:
    Actor(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* m_world);
    virtual void doSomething();
    virtual void bonk();
    bool checkAlive(); //returns whether an actor is alive or not
    void makeDead(); //sets boolean of an actor to dead
    StudentWorld* getWorld(); //returns a pointer to the world
    bool checkOverlap(int x, int y); //Checks if one actor overlaps with another
    bool checkInLine(int y); //Checks if peach is within row of the Piranha
    bool checkInVicinity(int x); //Checks if peach is close enough to the piranha so piranha can shoot fire
    bool relation(int x, int y); //Checks the direction of peach in relation to the piranha
    virtual bool getShare(); //Checks if an actor can share the space with another
    virtual bool getDamageable(); //Checks if an actor can be damaged
    virtual void damage(); //Hurts an object
private:
    StudentWorld* m_world;
    bool isAlive;
};

//For blocks and pipes
class Inanimate: public Actor{
public:
    Inanimate(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* world);
    virtual bool getShare();
};


//For Koopas, Goombas, and Piranhas
class Enemy: public Actor{
public:
    Enemy(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* world);
    virtual void doSomething();
    virtual void bonk();
    bool touchedByPeach(); //called when enemy overlaps with peach
    virtual bool getDamageable();
};

//For Flags and Mario
class Endpoint: public Actor{
public:
    Endpoint(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* world);
    bool helper(); //ends the level
};


//For power ups
class Goodie: public Actor{
public:
    Goodie(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* world);
    void moveOrChangeDir(); //moves the goodies
};

//For firballs and shells
class Fire: public Actor{
public:
    Fire(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* world);
    void moveOrDie(); //moves the fires
};

class Peach: public Actor{
public:
    Peach(int startX, int startY, StudentWorld* world);
    virtual void doSomething();
    virtual void bonk();
    virtual void damage();
    void falling(); //checks if peach is falling
    void jumping(); //checks if peach is jumping
    void jumpPower(); //activates jump power
    void shootPower(); //activates shoot power
    void starPower(); //activates star power
    void setInvincibilityLeft(int x); //sets invincibility left to parameter
    bool getInvincibility(); //returns whether peach is invincible
    void hitpoints(int x); //sets hitpoints to the parameter
private:
    int hitPoints;
    int remaining_jump_distance;
    bool isJumping;
    bool hasJumpPower;
    bool hasShootPower;
    bool hasStarPower;
    int invincibilityLeft;
    int tempInvincibilityLeft;
    int time_to_recharge_before_next_fire;
};

class Goomba: public Enemy{
public:
    Goomba(int startX, int startY, int startDirection, StudentWorld* world);
};

class Koopa: public Enemy{
public:
    Koopa(int startX, int startY, int startDirection, StudentWorld* world);
    virtual void bonk();
    virtual void damage();
    void makeShell(); //creates a shell
};

class Piranha: public Enemy{
public:
    Piranha(int startX, int startY, int startDirection, StudentWorld* world);
    virtual void doSomething();
private:
    int firing_delay; //keeps track of how long until it can fire again
};

class Shell: public Fire{
public:
    Shell(int startX, int startY, int startDirection, StudentWorld* world);
    virtual void doSomething();
};

class Star: public Goodie{
public:
    Star(int startX, int startY, StudentWorld* world);
    virtual void doSomething();
};

class Flower: public Goodie{
public:
    Flower(int startX, int startY, StudentWorld* world);
    virtual void doSomething();
};

class Mushroom: public Goodie{
public:
    Mushroom(int startX, int startY, StudentWorld* world);
    virtual void doSomething();
};

class PiranhaFire: public Fire{
public:
    PiranhaFire(int startX, int startY, int startDirection, StudentWorld* world);
    virtual void doSomething();
};

class PeachFire: public Fire{
public:
    PeachFire(int startX, int startY, int startDirection, StudentWorld* world);
    virtual void doSomething();
};

class Block: public Inanimate{
public:
    Block (int startX, int startY, StudentWorld* world, char t);
    virtual void bonk();
private:
    char type; //n for normal, f for flower, s for star, m for mushroom
    bool beenBonked;
};

class Pipe: public Inanimate{
public:
    Pipe (int startX, int startY, StudentWorld* world);
};

class Flag: public Endpoint{
public:
    Flag (int startX, int startY, StudentWorld* world);
    virtual void doSomething();
};

class Mario: public Endpoint{
public:
    Mario (int startX, int startY, StudentWorld* world);
    virtual void doSomething();
};

#endif // ACTOR_H_
