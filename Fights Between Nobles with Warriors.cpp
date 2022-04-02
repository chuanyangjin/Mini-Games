/*
  Fights Between Nobles with Warriors
  Author: Chuanyang Jin
 */

#include <iostream>   
#include <string>
#include <vector>
#include <fstream>    
using namespace std;

const double EPS = 0.00001;
class Noble;

// Warrior class
class Warrior {
    friend ostream& operator<<(ostream& os, const Warrior& rhs);

public:
    Warrior(const string& Name, double Strength);
    const string& getName() const;
    double getStrength() const;
    bool isHired() const;
    void setStrength(double theStrength);
    void setEmployed(bool theEmployed);
    void setNoble(Noble& theNoble);
    void removeNoble();
    bool runaway();

private:
    string name;
    double strength;
    Noble* noble;
    bool employed;
};

// Noble class
class Noble {
    friend ostream& operator<<(ostream& os, const Noble& rhs);

public:
    Noble(const string& theName);
    const string& getName() const;
    double getStrength() const;
    void setStrength(double proportion);
    void die();
    bool hire(Warrior& warrior);
    bool fire(Warrior& warrior);
    void battle(Noble& another);
    bool removeWarrior(Warrior& warrior);

private:
    string name;
    vector<Warrior*> warriors;
    bool alive;
};

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
        << lance << endl
        << jim << endl
        << linus << endl
        << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
        << lance << endl
        << jim << endl
        << linus << endl
        << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha
        << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha
        << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}

// Warrior methods
// output operator
ostream& operator<<(ostream& os, const Warrior& rhs) {
    os << "          " << rhs.name << ": " << rhs.strength << endl;
    return os;
}

// constructor
Warrior::Warrior(const string& Name, double Strength)
    : name(Name), strength(Strength), employed(false), noble(nullptr) {}

// getters of Warrior
const string& Warrior::getName() const { return name; }
double Warrior::getStrength() const { return strength; }
bool Warrior::isHired() const { return employed; }

// setters of Warrior
void Warrior::setStrength(double theStrength) { strength = theStrength; }
void Warrior::setEmployed(bool theEmployed) { employed = theEmployed; }
void Warrior::setNoble(Noble& theNoble) { noble = &theNoble; }
void Warrior::removeNoble() { noble = nullptr; }

// when warrior runs away
bool Warrior::runaway() {
    if (!employed) {
        cout << "I am not hired!" << endl;
        return false;
    }
    else {
        cout << name << " flees in terror, abandoning his lord, " << noble->getName() << endl;
        noble->removeWarrior(*this);
        noble = nullptr;
        employed = false;
        return true;
    }
}



// Noble methods
// output operator
ostream& operator<<(ostream& os, const Noble& rhs) {
    os << rhs.name << " has an army of " << rhs.warriors.size() << endl;
    for (Warrior* ptr : rhs.warriors) {
        os << *ptr;
    }
    return os;
}

// constructor
Noble::Noble(const string& theName) : name(theName), alive(true) {}

// getters of Noble
const string& Noble::getName() const { return name; }
// return a double that represents the strength of the noble
double Noble::getStrength() const {
    double strength = 0;
    for (int i = 0; i < warriors.size(); i++) {
        strength += warriors[i]->getStrength();
    }
    return strength;
}

// setters of Noble
// set the noble's strength to a proportion during battle
void Noble::setStrength(double proportion) {
    for (int i = 0; i < warriors.size(); i++) {
        warriors[i]->setStrength(warriors[i]->getStrength() * proportion);
    }
}
// set the noble to death
void Noble::die() {
    // set the warriors of the noble to death
    for (int i = 0; i < warriors.size(); i++) {
        warriors[i]->setStrength(0);
    }
    alive = false;
}

// hire a warrior
bool Noble::hire(Warrior& warrior) {
    // dead nobles cannot fire a warriors, warriors who are already employed cannot be hired
    if (!alive) {
        cout << "Dead nobles cannot hire a warriors!" << endl;
        return false;
    }
    else if (warrior.isHired()) {
        cout << "Warriors who are already employed cannot be hired!" << endl;
        return false;
    }
    else {
        warriors.push_back(&warrior);
        warrior.setEmployed(true);
        warrior.setNoble(*this);
        return true;
    }
}
// fire a warrior
bool Noble::fire(Warrior& warrior) {
    // dead nobles cannot fire a warriors
    if (!alive) {
        cout << "Dead nobles cannot fire a warriors!" << endl;
        return false;
    }
    int i = 0;
    while (i < warriors.size()) {
        if (warriors[i]->getName() == warrior.getName()) {
            warriors[i]->setEmployed(false);
            warriors[i]->removeNoble();
            while (i < warriors.size() - 1) {
                warriors[i] = warriors[i + 1];
                i++;
            }
            warriors.pop_back();
            cout << "You don't work for me anymore " << warrior.getName()
                << "! -- " << name << "." << endl;
            return true;
        }
        i++;
    }
    cout << "The warrior is not in my army!" << endl;
    return false;
}
// battle between nobles
void Noble::battle(Noble& another) {
    cout << name << " battles " << another.name << endl;
    // both are dead
    if (!alive && !another.alive) {
        cout << "Oh, NO! They're both dead! Yuck!\n";
    }
    // the original warrior is dead
    else if (!alive) {
        cout << "He's dead, " << another.name << endl;
    }
    // another warrior is dead
    else if (!another.alive) {
        cout << "He's dead, " << name << endl;
    }
    // neither is dead
    else {
        // get the nobles' total strength
        double strength1 = getStrength();
        double strength2 = another.getStrength();

        // compare the armies' strength, get and display the result, and update the strengths and status
        if (abs(strength1 - strength2) < EPS) {
            die();
            another.die();
            cout << "Mutual Annihilation: " << name << " and " << another.name << " die at each other's hands\n";
        }
        else if ((strength1 - strength2) > EPS) {
            setStrength(1 - strength2 / strength1);
            another.die();
            cout << name << " defeats " << another.name << endl;
        }
        else if ((strength1 - strength2) < EPS) {
            double proportion = 1 - strength1 / strength2;
            another.setStrength(1 - strength1 / strength2);
            cout << another.name << " defeats " << name << endl;
        }
    }
}
// when warrior runs away
bool Noble::removeWarrior(Warrior& warrior) {
    int i = 0;
    while (i < warriors.size()) {
        if (warriors[i]->getName() == warrior.getName()) {
            while (i < warriors.size() - 1) {
                warriors[i] = warriors[i + 1];
                i++;
            }
            warriors.pop_back();
            return true;
        }
        i++;
    }
    return false;
}