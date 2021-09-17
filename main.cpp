//Colin Casey
//Hokkeeman.cpp 
//4/21/2021

#include <iostream>
using namespace std;


auto validateInput(char i); //hopefully the function can be designed to handle ints and strings 
void displayMenu(); //void function displaying the alpha menu using cout statements 
void unitTest();
class Snail;
class Creature;
class Feline;


// Specification C2 - Creature class
class Creature {
  public:
    Creature(); //constructor inmtializes hunger and boredom between values of 0 and 5 
    Creature(const Creature &c); //copy constructor. it is designed to use the overloaded = operator to copy the values 
    virtual void sprite(); //
    string askName(string n); //method prompts the user to overide a creatures default name 
    int generateStats(int seed, int upper, int lower);
    void listen(); //creatures displays current hunger and bordom states 
    void play(); //reduce boredom by a random number between 4-8 
    void feed(); //reduces hunger by a random number between 3-6 
    void displayStats();
    int isHokeemonDead();
    void creatureCompTest();

  
    bool alive = true; //bool value determines if creature is alive or not based on hunger
    bool catatonic = false; //if boredom reaches 0 then snail becomes catatonic (dead) unplayable  
    int boredom = -1; //play functio increases boredom, if boredom reaches 0 the creature goes catotonic 
    int hunger = -1; //if hunger reachs zero creature dies 
    string name = ""; //user can overide default name 
  
  // Specification C1 - PassTime()
  //passtime() is designed to increment by one once every game loop 
  void passTime() {
    boredom--;
    hunger--;
  }

  friend ostream &operator << (ostream& out, const Creature d) {
        out << d.alive << endl;
        out << d.boredom << endl;
        out << d.hunger << endl;
        out << d.name << endl;
    return out;
  }

//Specification B3 - Overload Assignment Operator
  Creature operator = (const Creature &c) {
    Creature tempcreature;
    tempcreature.alive = c.alive;
    tempcreature.boredom = c.boredom;
    tempcreature.hunger = c.hunger;
    tempcreature.name = c.name;

    return tempcreature;
  }

//Specification B4 - Overload + Operator
  Creature operator + (const Creature &c) {
    Creature tempcreature;
    tempcreature.boredom = tempcreature.boredom + c.boredom;
    tempcreature.hunger = tempcreature.hunger + c.hunger;

    return tempcreature;
  }
};




Creature::Creature() {
  alive = true; 
  boredom = generateStats(1, 5, 1);
  hunger = generateStats(2, 5, 1);
  name = "unnamed";
}

// Specification A2 - Copy Constructor
Creature::Creature(const Creature &c) {
  Creature d;
  d = c;
}

void Creature::sprite() {cout << "Error loading sprite:" << endl;}

// Specification A1 - Critter Name
string Creature::askName(string n) {
  name = n;
  cout << "Enter Name: ";
  cin >> name;
  return name;
}

int Creature::generateStats(int seed = 0, int upper = 0, int lower = 0) 
{
    int  number;
    int  i;
    srand(seed * time(0));

    number = (rand() % upper) + lower;

    return number;
}

void Creature::listen() {
    cout << "Hunger [" << hunger << "]" << endl;
    cout << "Boredom [" << boredom << "]" << endl;
}

void Creature::play() {boredom += generateStats(time(0), 5, 4);}
void Creature::feed() {hunger += generateStats(time(0), 4, 3);}

int Creature::isHokeemonDead() 
{
  if (hunger < 0) 
    {
      alive = false;
      return -1;
    } 

  if (boredom < 0) 
    {
      catatonic = true;
      return -1;
    }
  
  if (boredom || hunger > 0) {return 1;}
  return 0;
}

void Creature::displayStats() {
  cout << "Hunger: " << hunger << endl;
  cout << "Boredom: " << boredom << endl;
}


// Specification B2 - Virtual Class Creature
// Specification B1 - Child Class
class Snail : public virtual Creature {
  public:
  Snail(); //constructor intializes snail specific characteristics 
  int determineEyeColor();
  void sprite(); //displays snail graphic 

  private:
    int eyeColor; //0-9 = white, 10-15 = green, 16-19 = blue, 20 = red 
};

Snail::Snail() {};

 void Snail::sprite() {

  cout << "         __,._            "<< endl;
  cout << "        /  _   \\         "<< endl;
  cout << "       |  6 \\   \\oo     "<< endl;
  cout << "       \\___/ .|__||_     "<< endl;
  cout << " __,..=^  . ,      ~\\    "<< endl;
  cout << "<.__________________/     "<< endl;
};

// int Snail::determineShellColor() {
//   return 0;
// }

// Snail::Snail(){
//   shellColor = determineShellColor();

// }

// Specification A3 - Second Child Class
class Feline : public virtual Creature {

  public:
    Feline();
    void sprite();
    void componentTest();
    
  private:
    int ppm; //purs per minute 
    int furColor; //can have 0-5 tails 

// Specification C4 - Overload «
  friend ostream &operator << (ostream& out, const Feline f) {
        out << f.alive << endl;
        out << f.boredom << endl;
        out << f.hunger << endl;
        out << f.name << endl;      
        out << f.ppm << endl;
        out << f.furColor << endl;
    return out;
  }
};

//default constructor sets dummy values for feline 
Feline::Feline() 
{
  ppm = 10;
  furColor = 0; 
}


void Feline::sprite() {
  cout << "    /\\_____/\\ " << endl;
  cout << "   /  o   o  \\ " << endl;
  cout << "  ( ==  ^  == )" << endl;
  cout << "   )         (" << endl;
  cout << "  (           )" << endl;
  cout << " ( (  )   (  ) )" << endl;
  cout << "(__(__)___(__)__)" << endl;
}

void displayMenu() {
  cout << "<L>isten " << endl;
  cout << "<P>lay " << endl;
  cout << "<F>eed " << endl;
  cout << "<Q>uit " << endl;
}

// Specification C3 - Validate Input
//validate input function accepts one char value as parameter and returns boolean 
auto validateInput(char i) 
{  
  bool isinputvalid;

  i = toupper(i); //if user enter a lower case letter tuupper function converts it to an uppercase 

  if (i == 'L' || i == 'P' || i == 'F' || i == 'Q')
    {isinputvalid = true;}
      else 
        {isinputvalid = false;}
  
  return isinputvalid; 
}

void Creature::creatureCompTest() 
{
  string f = "Failed";
  string p = "Passed";
  Creature test, temp;
  Snail snailtest;
  Feline felinetest;

  test.hunger = -1;
  test.boredom = -1;
  test.alive = false;
  test.name = "rocky";

  snailtest.hunger = -1;
  snailtest.boredom = -1;
  snailtest.alive = false;
  snailtest.name = "ballin";

  test = temp; //tests overloaded assignment operator 
  temp = snailtest; //tests child to parent assignment 
  snailtest + felinetest; //tests overloaded + operator 

  if (test.hunger == -1) {cout << "Hunger manual assignment: " << p << endl;} else {cout << "Hunger manual assignment: " << f << endl;}
  if (test.boredom == -1) {cout << "Boredom manual assignment: " << p << endl;} else {cout << "Boredom manual assignment: " << f << endl;}
  if (test.alive == false) {cout << "Alive manual assignment:" << p << endl;} else {cout << "Alive manual assignment" << f << endl;}
  if (test.name == "rocky") {cout << "Name manual assignment:" << p << endl;} else {cout << "Name manual assignment" << f << endl;}

  if (temp.hunger == -1 && temp.boredom == -1) {cout << "Overload Assignment: " << p << endl; } else {cout << "Overload Assignment: " << f << endl;}

}



int main() {

  unitTest();//unit test declared before anything eles 

  bool isgameover = false;//bool determines when the game do/while loop is over 
  char menuInput; //char variable to hold user input 
  char hokeChoice; //hokeChoice char variable determines which hokeeman species the player chooses
  Creature * playerHokeemon; //pointer varaibele holds the address 
  Feline feline1; //child1 of parent creature class
  Snail snail1; //child 2 of parent creature class

  //asks user which hokeemon they want to play with 
  cout << "Snail or Feline? Choose your Hokeeman!" << endl;
  cin >> hokeChoice; 
  hokeChoice = toupper(hokeChoice);
  if (hokeChoice == 'S') {playerHokeemon = &snail1;}
  else if (hokeChoice == 'F') {playerHokeemon =  &feline1;}

  playerHokeemon->askName("error"); //set default to error if a user doesn't enter a name 
     
 
  //game loop start 
  do 
    {
      displayMenu(); //display alpha menu <L>isten, <P>lay, <F>eed, <Q>uit 
      //menu verification loop start 
        do 
          {
            cin >> menuInput; //consoles prompts user to enter menu choice 
            if (validateInput(menuInput) == false)
            cout << "Error: Invalid Input - Reenter: ";

          }while (validateInput(menuInput) == false);
      
      switch (menuInput) {
        case 'L':
          cout << "Listening to " << playerHokeemon->name << endl;
              playerHokeemon->listen();
            break;
        case 'P':
          cout << "Playing... with " << playerHokeemon->name << endl;
              playerHokeemon->play();
            break;
        case 'F':
          cout << "Feeding... " << playerHokeemon->name << endl;
              playerHokeemon->feed();
            break;
        case 'Q':
          cout << "Abandoning..." << playerHokeemon->name << endl;
          isgameover = true;
            break;
      }


      playerHokeemon->passTime();

    } while (isgameover == false); //game loop exit condition 
  //game loop end

cout << "Game over" << endl;
}

//component test function
void unitTest() {
  Snail componentOBJ; //creates snail to test creature class function
  componentOBJ.creatureCompTest();
  // Specification A4 - Write a Lambda
  auto lamb = [](int a, int b) { return a + b; };
  if (lamb(1, -1) == 0) {cout << "Lambda works" << endl;}

  cout << "\n\n";
}
