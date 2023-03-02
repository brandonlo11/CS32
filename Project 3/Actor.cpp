#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* world) : GraphObject(imageID, startX, startY, startDirection, depth, size), m_world(world), isAlive(true){
};

void Actor::doSomething(){
}

void Actor::bonk(){
}

bool Actor::getShare(){
    return true;
}

bool Actor::getDamageable(){
    return false;
}

void Actor::damage(){
    getWorld()->increaseScore(100);
    makeDead();
}

bool Actor::checkOverlap(int x, int y){
    if (x <= getX()+SPRITE_WIDTH-1 && x >= getX() && y <= getY()+SPRITE_HEIGHT-1 && y >= getY()){
        return true;
    }
    else if (y <= getY()+SPRITE_HEIGHT-1 && y >= getY() && x+SPRITE_WIDTH-1 <= (getX()+SPRITE_WIDTH-1) && x+SPRITE_WIDTH-1 >= getX()){
        return true;
    }
    else if(x <= getX()+SPRITE_WIDTH-1 && x >= getX() && y+SPRITE_HEIGHT-1 <= getY()+SPRITE_HEIGHT-1 && y+SPRITE_HEIGHT-1 >= getY()){
        return true;
    }
    else if(y+SPRITE_HEIGHT-1 <= getY()+SPRITE_HEIGHT-1 && y+SPRITE_HEIGHT-1 >= getY() && x+SPRITE_WIDTH-1 <= (getX()+SPRITE_WIDTH-1) && x+SPRITE_WIDTH-1 >= getX()){
        return true;
    }
    else{
        return false;
    }
}

bool Actor::checkInLine(int y){
    if (getY() <= y+ 1.5*SPRITE_HEIGHT && getY() >= y - 1.5*SPRITE_HEIGHT){
        return true;
    }
    return false;
}

bool Actor::checkInVicinity(int x){
    if (getX() < x + 8*SPRITE_WIDTH && getX() > x - 8*SPRITE_WIDTH){
        return true;
    }
    return false;
}

bool Actor::relation(int x, int y){
    if (x > getX()){
        //peach is to the left of piranha
        return true;
    }else{
        return false;
    }
}
void Actor::makeDead(){
    isAlive = false;
}

Inanimate::Inanimate(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* world): Actor (imageID, startX, startY, startDirection, depth, size, world){
}

bool Inanimate::getShare(){
    return false;
}

Enemy::Enemy(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* world): Actor(imageID, startX, startY, startDirection, depth, size, world){
}
bool Enemy::getDamageable(){
    return true;
}

void Enemy::doSomething(){
    if (checkAlive() == false){
        return;
    }
    if (getWorld()->overlapsPeach(getX(), getY())){
        getWorld()->damagePeach();
        return;
    }
    //check if there is a blocking object, if so turn around
    if (getDirection() == 0){
        if (getWorld()->isBlockingObjectAt(getX() + 1, getY()) || !(getWorld()->isBlockingObjectAt(getX() + SPRITE_WIDTH, getY() - 1))){
            setDirection(180);
        }
    }
    if (getDirection() == 180){
        if (getWorld()->isBlockingObjectAt(getX() - 1, getY()) || !(getWorld()->isBlockingObjectAt(getX() - SPRITE_WIDTH, getY() - 1))){
            setDirection(0);
        }
    }
    //move in the direction its facing
    if (getDirection() == 0){
        if (getWorld()->isBlockingObjectAt(getX() + 1, getY())){
            return;
        }
        moveTo(getX() + 1, getY());
    }
    if (getDirection() == 180){
            if (getWorld()->isBlockingObjectAt(getX() - 1, getY())){
                return;
            }
        moveTo(getX() - 1, getY());
    }
}

void Enemy::bonk(){
    touchedByPeach();
}

bool Enemy::touchedByPeach(){
    if (getWorld()->overlapsPeach(getX(), getY())){
        if (getWorld()->getInvincibilityLeft()){
            getWorld()->playSound(SOUND_PLAYER_KICK);
            getWorld()->increaseScore(100);
            makeDead();
            return true;
        }
    }
    return false;
}

Endpoint::Endpoint(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* world): Actor(imageID, startX, startY, startDirection, depth, size, world){
}

bool Endpoint::helper(){
    if (checkAlive() && getWorld()->overlapsPeach(getX(), getY())){
        getWorld()->increaseScore(1000);
        makeDead();
        return true;
    }
    return false;
}

Goodie::Goodie(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* world): Actor(imageID, startX, startY, startDirection, depth, size, world){
}

void Goodie::moveOrChangeDir(){
    if(!(getWorld()->isBlockingObjectAt(getX(), getY()-2))){
        moveTo(getX(), getY()-2);
    }
    if (getDirection() == 0){
        if (getWorld()->isBlockingObjectAt(getX() + 2, getY())){
            setDirection(180);
            return;
        }
    }
    if (getDirection() == 180){
        if (getWorld()->isBlockingObjectAt(getX() - 2, getY())){
            setDirection(0);
            return;
        }
    }
    if (getDirection() == 0){
        moveTo(getX() + 2, getY());
    }
    if (getDirection() == 180){
        moveTo(getX() - 2, getY());
    }
}

Fire::Fire(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* world): Actor(imageID, startX, startY, startDirection, depth, size, world){
}

void Fire::moveOrDie(){
    if(!(getWorld()->isBlockingObjectAt(getX(), getY()-2))){
        moveTo(getX(), getY()-2);
    }
    //check if there is a blocking object, if so make dead
    if (getDirection() == 0){
        if (getWorld()->isBlockingObjectAt(getX() + 2, getY())){
            makeDead();
            return;
        }
    }
    if (getDirection() == 180){
        if (getWorld()->isBlockingObjectAt(getX() - 2, getY())){
            makeDead();
            return;
        }
    }
    //move in direction it is facing
    if (getDirection() == 0){
        moveTo(getX() + 2, getY());
    }
    if (getDirection() == 180){
        moveTo(getX() - 2, getY());
    }
}

Peach::Peach(int startX, int startY, StudentWorld* world) : Actor(IID_PEACH, startX, startY, 0, 0, 1.0, world), hitPoints(1), remaining_jump_distance(0), isJumping(false), hasJumpPower(false), hasShootPower(false), hasStarPower(false), time_to_recharge_before_next_fire(0), invincibilityLeft(0), tempInvincibilityLeft(0){
}

void Peach::falling(){
    if (isJumping){
        return;
    }
    //check if there is an abject below Peach
    if (getWorld() -> isBlockingObjectAt(getX(), getY()) || getWorld() -> isBlockingObjectAt(getX(), getY() - 1) || getWorld() -> isBlockingObjectAt(getX(), getY() - 2) || getWorld() -> isBlockingObjectAt(getX(), getY() - 3)){
        return;
    }
    moveTo(getX(), getY() - 4);
}

void Peach::jumping(){
    if (!isJumping || remaining_jump_distance <= 0){
        isJumping = false;
        return;
    }
    if (remaining_jump_distance == 0){
        isJumping = false;
        return;
    }
    if (getWorld()->isBlockingObjectAt(getX(), getY() + 4)){
        getWorld()->callBonk(getX(), getY() + 4);
        remaining_jump_distance = 0;
        return;
    }
    moveTo(getX(), getY() + 4);
    remaining_jump_distance -= 1;
}

void Peach::jumpPower(){
    hasJumpPower = true;
}

void Peach::starPower(){
    hasStarPower = true;
}

void Peach::shootPower(){
    hasShootPower = true;
}

void Peach::setInvincibilityLeft(int x){
    invincibilityLeft = x;
}

void Peach::doSomething(){
    if (!(checkAlive())){
        return;
    }
    if(hasStarPower){
        invincibilityLeft--;
        if (invincibilityLeft == 0){
            hasStarPower = false;
            getWorld()->setEmpty("star");
        }
    }
    if(tempInvincibilityLeft > 0){
        tempInvincibilityLeft--;
    }
    if(time_to_recharge_before_next_fire > 0){
        time_to_recharge_before_next_fire--;
    }
    getWorld()->callBonk(getX(), getY());
    int ch;
    if (getWorld()->getKey(ch)){
        switch (ch){
            case KEY_PRESS_LEFT:
                setDirection(180);
                if (getWorld()->isBlockingObjectAt(getX() - 4, getY())){
                    getWorld()->callBonk(getX() - 4, getY());
                    break;
                }
                moveTo(getX() - 4, getY());
                break;
            case KEY_PRESS_RIGHT:
                setDirection(0);
                if (getWorld()->isBlockingObjectAt(getX() + 4, getY())){
                    getWorld()->callBonk(getX() + 4, getY());
                    break;
                }
                moveTo(getX() + 4, getY());
                break;
            case KEY_PRESS_UP:
                if (isJumping){
                    break;
                }
                if (!(getWorld()->isBlockingObjectAt(getX(), getY() - 1))){
                    break;
                }
                isJumping = true;
                if (!hasJumpPower){
                    remaining_jump_distance = 8;
                } else {
                    remaining_jump_distance = 12;
                }
                getWorld()->playSound(SOUND_PLAYER_JUMP);
                break;
            case KEY_PRESS_SPACE:
                if (hasShootPower == false || time_to_recharge_before_next_fire > 0){
                    break;
                }
                getWorld()->playSound(SOUND_PLAYER_FIRE);
                time_to_recharge_before_next_fire = 8;
                if (getDirection() == 0){
                    Actor* actor = new PeachFire(getX() + 4, getY(), getDirection(), getWorld());
                    getWorld()->addActor(actor);
                } else {
                    Actor* actor = new PeachFire(getX() - 4, getY(), getDirection(), getWorld());
                    getWorld()->addActor(actor);
                }
        }
    }
    jumping();
    falling();
}

void Peach::hitpoints(int x){
    hitPoints = x;
}
bool Peach::getInvincibility(){
    return hasStarPower;
}

void Peach::bonk(){
    if (tempInvincibilityLeft > 0 || invincibilityLeft > 0){
        return;
    }
    hitPoints--;
    tempInvincibilityLeft = 10;
    if (hasShootPower){
        hasShootPower = false;
        getWorld()->setEmpty("shoot");
    }
    if (hasJumpPower){
        hasJumpPower = false;
        getWorld()->setEmpty("jump");
    }
    if (hitPoints >= 1){
        getWorld()->playSound(SOUND_PLAYER_HURT);
    }
    if (hitPoints < 1){
        makeDead();
    }
}

void Peach::damage(){
    bonk();
}

Goomba::Goomba(int startX, int startY, int startDirection, StudentWorld* world):Enemy(IID_GOOMBA, startX, startY, startDirection, 0, 1.0, world){
}

Koopa::Koopa(int startX, int startY, int startDirection, StudentWorld* world):Enemy(IID_KOOPA, startX, startY, startDirection, 0, 1.0, world){
}

void Koopa::bonk(){
    if (touchedByPeach()){
        makeShell();
    }
}

void Koopa::damage(){
    getWorld()->increaseScore(100);
    makeDead();
    makeShell();
}

void Koopa::makeShell(){
    Actor* actor = new Shell(getX(), getY(), getDirection(), getWorld());
    getWorld()->addActor(actor);
}

Piranha::Piranha(int startX, int startY, int startDirection, StudentWorld* world): Enemy(IID_PIRANHA, startX, startY, startDirection, 0, 1.0, world), firing_delay(0){
}

void Piranha::doSomething(){
    if (checkAlive() == false){
        return;
    }
    increaseAnimationNumber();
    if (getWorld()->overlapsPeach(getX(), getY())){
        getWorld()->damagePeach();
        return;
    }
    if (!getWorld()->inLinePeach(getY())){
        return;
    }
    if (getWorld()->isLeft(getX(), getY())){
        setDirection(180);
    }else{
        setDirection(0);
    }
    if (firing_delay > 0){
        firing_delay--;
    }
    if (firing_delay == 0){
        if (getWorld()->inVicinityPeach(getX())){
            Actor* actor = new PiranhaFire(getX(), getY(), getDirection(), getWorld());
            getWorld()->addActor(actor);
            getWorld()->playSound(SOUND_PIRANHA_FIRE);
            firing_delay = 40;
        }
    }
}

Block:: Block(int startX, int startY, StudentWorld* world, char t) : Inanimate(IID_BLOCK, startX, startY, 0, 2, 1.0, world), type(t), beenBonked(false){
}

void Block::bonk(){
    if (type == 'n' || beenBonked == true){
        getWorld()->playSound(SOUND_PLAYER_BONK);
        return;
    }
    if (type == 'f'){
        Actor* actor = new Flower(getX(), getY() + 8, getWorld());
        getWorld()->addActor(actor);

    }
    if (type == 'm'){
        Actor* actor = new Mushroom(getX(), getY() + 8, getWorld());
        getWorld()->addActor(actor);

    }
    if (type == 's'){
        Actor* actor = new Star(getX(), getY() + 8, getWorld());
        getWorld()->addActor(actor);
    }
    getWorld()->playSound(SOUND_POWERUP_APPEARS);
    beenBonked = true;
}

Pipe::Pipe(int startX, int startY, StudentWorld* world) : Inanimate(IID_PIPE, startX, startY, 0, 2, 1.0, world){
}

Shell::Shell(int startX, int startY, int startDirection, StudentWorld* world): Fire(IID_SHELL, startX, startY, startDirection, 1, 1, world){
}

void Shell::doSomething(){
    if (getWorld()->Damageable(getX(), getY())){
        makeDead();
        return;
    }
    moveOrDie();
}

Star::Star(int startX, int startY, StudentWorld* world): Goodie(IID_STAR, startX, startY, 0, 1, 1.0, world){
}

void Star::doSomething(){
    if(getWorld()->overlapsPeach(getX(), getY())){
        getWorld()->increaseScore(100);
        getWorld()->powerUpStar();
        makeDead();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    moveOrChangeDir();
}

Flower::Flower(int startX, int startY, StudentWorld* world): Goodie(IID_FLOWER, startX, startY, 0, 1, 1.0, world){
}

void Flower::doSomething(){
    if(getWorld()->overlapsPeach(getX(), getY())){
        getWorld()->increaseScore(50);
        getWorld()->powerUpShoot();
        getWorld()->setHitpoints(2);
        makeDead();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    moveOrChangeDir();
}

Mushroom::Mushroom(int startX, int startY, StudentWorld* world): Goodie(IID_MUSHROOM, startX, startY, 0, 1, 1.0, world){
}

void Mushroom::doSomething(){
    if(getWorld()->overlapsPeach(getX(), getY())){
        getWorld()->increaseScore(75);
        getWorld()->powerUpJump();
        getWorld()->setHitpoints(2);
        makeDead();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    moveOrChangeDir();
}

PiranhaFire::PiranhaFire(int startX, int startY, int startDirection, StudentWorld* world): Fire(IID_PIRANHA_FIRE, startX, startY, startDirection, 1, 1.0, world){
}

void PiranhaFire::doSomething(){
    if (getWorld()->overlapsPeach(getX(), getY())){
        getWorld()->damagePeach();
        makeDead();
        return;
    }
        moveOrDie();
}

PeachFire::PeachFire(int startX, int startY, int startDirection, StudentWorld* world): Fire(IID_PEACH_FIRE, startX, startY, startDirection, 1, 1.0, world){
}

void PeachFire::doSomething(){
    if (getWorld()->Damageable(getX(), getY())){
        makeDead();
        return;
    }
    moveOrDie();
}

Flag::Flag(int startX, int startY, StudentWorld* world): Endpoint(IID_FLAG, startX, startY, 0, 1, 1.0, world){
}

void Flag::doSomething(){
    if(helper()){
        getWorld()->endLevel();
    }
}

Mario::Mario(int startX, int startY, StudentWorld* world): Endpoint(IID_MARIO, startX, startY, 0, 1, 1.0, world){
}

void Mario::doSomething(){
    if(helper()){
        getWorld()->endGame();
    }
}

StudentWorld* Actor::getWorld(){
    return m_world;
};

bool Actor::checkAlive(){
    return isAlive;
}
