#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), finishedLevel(false), finishedGame(false), jumpstr(""), shootstr(""), starstr("")
{
}

bool StudentWorld::isBlockingObjectAt(int x, int y){
    for (list<Actor*>::iterator i = m_actors.begin(); i != m_actors.end();) {
        if ((*i)->checkOverlap(x, y) && !((*i)->getShare())){
            return true;
        }
        i++;
    }
    return false;
}

void StudentWorld::callBonk(int x, int y){
    for (list<Actor*>::iterator i = m_actors.begin(); i != m_actors.end();) {
        if ((*i)->checkOverlap(x, y)){
            (*i)->bonk();
        }
        i++;
    }
}

bool StudentWorld::Damageable(int x, int y){
    for (list<Actor*>::iterator i = m_actors.begin(); i != m_actors.end(); i++) {
        if ((*i)->checkOverlap(x, y)){
            if ((*i)->checkAlive()){
                if ((*i)->getDamageable()){
                    (*i)->damage();
                    return true;
                }
            }
        }
    }
    return false;
}

void StudentWorld::damagePeach(){
    m_peach->damage();
}

bool StudentWorld::overlapsPeach(int x, int y){
    if(m_peach->checkOverlap(x, y)){
        return true;
    }
    return false;
}

bool StudentWorld::inLinePeach(int y){
    if(m_peach->checkInLine(y)){
        return true;
    }
    return false;
}

bool StudentWorld::inVicinityPeach(int x){
    if (m_peach->checkInVicinity(x)){
        return true;
    }
    return false;
}

bool StudentWorld::isLeft(int x, int y){
    if (m_peach->relation(x, y)){
        return true;
    }
    return false;
}

bool StudentWorld::getInvincibilityLeft(){
    return m_peach->getInvincibility();
}

int StudentWorld::init()
{
    Level lev(assetPath());
    // string stream for the level string
    ostringstream oss;
    oss << "level" << setw(2) << setfill('0') << getLevel() << ".txt";
    string level_file = oss.str();
    cerr<< level_file << endl;
    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found){
        cerr << "File not found" << endl;
        return  GWSTATUS_LEVEL_ERROR;
    }
    if (result == Level::load_fail_bad_format){
        cerr << "Bad format" << endl;
        return  GWSTATUS_LEVEL_ERROR;
    }
    if (result == Level::load_success){
        cerr << "Success" << endl;
        for (int i = 0; i < GRID_HEIGHT; i++){
            for (int j = 0; j < GRID_WIDTH; j++){
                Level::GridEntry ge = lev.getContentsOf(i, j);
                Actor* actor;
                //Goes through grid and creates correct actors at each point
                switch (ge){
                    case Level::empty:
                        break;
                    case Level::peach:
                        m_peach = new Peach (i*SPRITE_WIDTH,j*SPRITE_HEIGHT, this);
                        break;
                    case Level::koopa:
                        actor = new Koopa(i*SPRITE_WIDTH,j*SPRITE_HEIGHT, randomDir(), this);
                        m_actors.push_back(actor);
                        break;
                    case Level::goomba:
                        actor = new Goomba(i*SPRITE_WIDTH,j*SPRITE_HEIGHT, randomDir(), this);
                        m_actors.push_back(actor);
                        break;
                    case Level::piranha:
                        actor = new Piranha(i*SPRITE_WIDTH,j*SPRITE_HEIGHT, randomDir(), this);
                        m_actors.push_back(actor);
                        break;
                    case Level::block:
                        actor = new Block(i*SPRITE_WIDTH,j*SPRITE_HEIGHT, this, 'n');
                        m_actors.push_back(actor);
                        break;
                    case Level::star_goodie_block:
                        actor = new Block(i*SPRITE_WIDTH,j*SPRITE_HEIGHT, this, 's');
                        m_actors.push_back(actor);
                        break;
                    case Level::mushroom_goodie_block:
                        actor = new Block(i*SPRITE_WIDTH,j*SPRITE_HEIGHT, this, 'm');
                        m_actors.push_back(actor);
                        break;
                    case Level::flower_goodie_block:
                        actor = new Block(i*SPRITE_WIDTH,j*SPRITE_HEIGHT, this, 'f');
                        m_actors.push_back(actor);
                        break;
                    case Level::pipe:
                        actor = new Pipe(i*SPRITE_WIDTH,j*SPRITE_HEIGHT, this);
                        m_actors.push_back(actor);
                        break;
                    case Level::flag:
                        actor = new Flag(i*SPRITE_WIDTH,j*SPRITE_HEIGHT, this);
                        m_actors.push_back(actor);
                        break;
                    case Level::mario:
                        actor = new Mario(i*SPRITE_WIDTH,j*SPRITE_HEIGHT, this);
                        m_actors.push_back(actor);
                        break;
                }
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    m_peach->doSomething();
    list<Actor*>::iterator q = m_actors.begin();
    //calls doSomething for all actors
    for (int i = 0; i < m_actors.size(); i++) {
        (*q)->doSomething();
        q++;
    }
    if(!(m_peach->checkAlive())){
        decLives();
        playSound(SOUND_PLAYER_DIE);
        return GWSTATUS_PLAYER_DIED;
    }
    if (finishedLevel){
        playSound(SOUND_FINISHED_LEVEL);
        finishedLevel = false;
        return GWSTATUS_FINISHED_LEVEL;
    }
    if (finishedGame){
        playSound(SOUND_GAME_OVER);
        finishedGame = false;
        return GWSTATUS_PLAYER_WON;
    }
    //removes dead actors
    for (list<Actor*>::iterator h = m_actors.begin(); h != m_actors.end();) {
        if(!((*h)->checkAlive())){
            delete *h;
            auto remove = h;
            h++;
            m_actors.erase(remove);
        } else {
            h++;
        }
    }
    //string stream to display top text
    ostringstream temp;
    temp << "Lives: " << getLives() << "  Level: " << getLevel() << "  Points: " << setw(6) << setfill('0') << getScore() << starstr << shootstr << jumpstr;
    string topText = temp.str();
    setGameStatText(topText);
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_peach;
    for (list<Actor*>::iterator i = m_actors.begin(); i != m_actors.end();) {
        delete *i;
        auto remove = i;
        i++;
        m_actors.erase(remove);
    }
}

void StudentWorld::powerUpJump(){
    m_peach->jumpPower();
    jumpstr = " JumpPower!";
}

void StudentWorld::powerUpStar(){
    m_peach->starPower();
    starstr = " StarPower!";
    m_peach->setInvincibilityLeft(150);
}

void StudentWorld::powerUpShoot(){
    m_peach->shootPower();
    shootstr = " ShootPower!";
}

void StudentWorld::setHitpoints(int x){
    m_peach->hitpoints(x);
}

void StudentWorld::endLevel(){
    finishedLevel = true;
}

void StudentWorld::endGame(){
    finishedGame = true;
}

StudentWorld::~StudentWorld(){
    cleanUp();
}

void StudentWorld::addActor(Actor* actor){
    m_actors.push_back(actor);
}

void StudentWorld::setEmpty(std::string str){
    if (str == "star"){
        starstr = "";
    }
    if (str == "shoot"){
        shootstr = "";
    }
    if (str == "jump"){
        jumpstr = "";
    }
}

int StudentWorld::randomDir(){
    int r = rand() % 2 + 1;
    if (r == 1) {
        return 0;
    }else{
        return 180;
    }
}
