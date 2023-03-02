class Sport{
public:
    Sport (string str);
    virtual string name() const;
    virtual bool isOutdoor() const;
    virtual string icon() const = 0;
    virtual ~Sport();
private:
    string event;
};

class Snowboarding: public Sport{
public:
    Snowboarding(string str);
    virtual string icon() const;
    virtual ~Snowboarding();
};

class Biathlon: public Sport{
public:
    Biathlon(string str, double d);
    virtual string icon() const;
    virtual ~Biathlon();
private:
    double distance;
};

class FigureSkating: public Sport{
public:
    FigureSkating(string str);
    virtual bool isOutdoor() const;
    virtual string icon() const;
    virtual ~FigureSkating();
};

Sport::Sport(string str){
    event = str;
}

Biathlon::Biathlon(string str, double d):Sport(str){
    distance = d;
}

Snowboarding::Snowboarding(string str):Sport(str){
}

FigureSkating::FigureSkating(string str):Sport(str){
}

string Sport::name() const{
    return event;
}

bool Sport::isOutdoor() const{
    return true;
}

bool FigureSkating::isOutdoor() const{
    return false;
}

string Snowboarding::icon() const{
    return "a descending snowboarder";
}

string Biathlon::icon() const{
    return "a skier with a rifle";
}

string FigureSkating::icon() const{
    return "a skater in the Biellmann position";
}

Sport::~Sport(){
}

Snowboarding::~Snowboarding(){
    cout << "Destroying the Snowboarding object named " << name() << "." <<endl;
}

Biathlon::~Biathlon(){
    cout << "Destroying the Biathlon object named " << name() << ", distance " << distance << " km." << endl;
}

FigureSkating::~FigureSkating(){
    cout << "Destroying the FigureSkating object named " << name() << "." << endl;
}
