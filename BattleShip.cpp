//battleship.cpp
//Colin Casey
//19 May 2021 

//coding goals 
//use smart pointers where u can
//save memory 
//clean code 
//polymorphism

// Specification B1 - Secret Option
// Specification B3 - Random Start
// Specification A2 - MultiFire Game
// Specification A4 - Replay Finished Game

#include <iostream>
using namespace std;

class map;//holds the ship 
class player; //human player and ai player prototype
class ship;//parent class to to the rest of the types of ships 
//child classes (they inherit the default ship class)
class Carrier;
class Battleship;
class Cruiser;
class Submarine;
class Destroyer;

class ship {
  private:
    bool destroyed; //sunk or not sunk 
    bool hittingwall; //ship size is conflicting with a wall
    bool hittingothership; //bool determines if one ship is conflicting with another ship
    int orientation; //
    string name = "unnamed";
    int position; 
    
    static const int width = 1;
    int length = 0;
    int shipcode = -1;

  public: 
    virtual int getLength() {return length;}
    virtual string getString() {return name;};
    virtual int getShipCode() {return shipcode;}
    virtual int getPosition() {return position;}
    virtual void componentTest() {}; //Need to implement
    // ship(); //constructor sets bare minimum basic values 
    // ship(ship &s) {}; //copy constructor for late use
    // ~ship();
    // int getHealth(); 
    // bool isDestroyed();
    // bool isHittingWall();
    // bool isHittingOtherShip();
    // int getOrientation();
    // int getLength();

// Specification C4 - Overload «
    friend ostream &operator << (ostream &out, ship &sh) 
      {
        out << "Ship Type [" << sh.getString() << "]" << endl; 
        out << "Destroyed [" << sh.destroyed << "]" << endl;
        out << "Orientation [" << sh.orientation << "]"  << endl; 
        out << "Length [" << sh.getLength() << "]" << endl;

        return out;
      }
};


class player {
  private:
    
    int totalShots = 0;
    int x;
    int y;


  public:
  //both askLetterCord and askNumberCord are used to place and shoot ships
    int askLetterCord(); 
    int askNumberCord();
    int shoot(); //contains the two functions above and spits out a value ready for the 1D array
    bool human; //true = humanplayer, false = ai 
    bool getPlayerType() {return human;} 
    int getTotalShots () {return totalShots;}
// Specification C2 - Prohibit AI wasted shots
// Specification C3 - Validate Input
// Specification B2 - Adv Input Validation
    bool validateShots(player &P, map *m); //function validates the shots of which ever 

//Specification B4 - Overload »
        friend istream &operator >> (istream &in, player &p) 
      {
        in >> p.x;
        in >> p.y;

        return in;
      }
};


class map {
  private: 
    
  public:
    map();
    int typecode; //0 = empty 

    //carrier code 5 
    //battleship code 4 
    // cruiser code 3 
    //submarine code 2 
    //destroyer code 1 

    //empty 0 
    //hit 1 
    //sunk 9 


};


/************************
* Derived Child Classes *
************************/
// Specification A3 - Child Classes
class Carrier : public ship {
  private:
    string name = "Carrier";
    int shipcode = 5;
    const int length = 5;
    int position = 0;
  public:
    
    string getString() {return name;}
    int getLength() {return length;}
    int getShipCode() {return shipcode;}
    

};

class Battleship : public ship {
  private:
    int position = 0;
    const int length = 4; 
    string name = "Battleship";
    int shipcode = 4;

  public:
    
    string getString() {return name;}
    int getLength() {return length;}
    int getShipCode() {return shipcode;}
};

class Cruiser : public ship {
  private:
    int position = 0;
    string name = "Cruiser";
    int shipcode = 3;
    const int length = 3;
  public:
    
    
    string getString() {return name;}
    int getLength() {return length;}
    int getShipCode() {return shipcode;}
};

class Submarine : public ship {
  private:
    string name = "Submarine";
    int shipcode = 2;
    const int length = 3;
  public:
    
    
    string getString() {return name;}
    int getLength() {return length;}
    int getShipCode() {return shipcode;}
};

class Destroyer : public ship {
  private:
    string name = "Destroyer";
    int shipcode = 1;
    const int length = 2;
  public:
    string getString() {return name;}
    int getLength() {return length;}
    int getShipCode() {return shipcode;}
};

int randomNumber(int lower, int upper, int seed); //
void greetingMenu(); //explains the rules of battleship
void gameplayMenu(); //during the game where the player selects fire and shoot
map* assignMap(ship &s, map *m); //accepts a ship argument and the specific map the ship is assigned to 
int displayMap(map* m); //accepts a point to map objects, function formats and display map the contents inside the map
int convertLetterToNumber(char x); //accepts char variable as parameter 
bool verifyWallBounds(ship &s, map *m); //accpets two parameters, a ship and the map 

void greetingMenu() {
  cout << "Battleship" << endl;
  cout << "==========" << endl;
  cout << "<P>lay"  << endl;
  cout << "<R>ules" << endl;
  cout << "<T>urn on Advanced Firing" << endl;
  cout << "<Q>uit"  << endl;
  cout << endl;
       
}

void gameplayMenu() {
  cout << "<F>ire " << endl;
  cout << endl;
}

bool verifyWallBounds (ship &s, map *m) {
  int up, down, left, right;

  up = s.getPosition() - 10;
  down = s.getPosition() + 10;
  left = s.getPosition() - 1;
  right = s.getPosition() + 1;

  if ((s.getPosition() - 10 < 0)) {cout << "WALL to top: invalid placement or shot" << endl; return false;}
  if ((s.getPosition() + 10 < 99)) {cout << "WALL to bottom: invalid placement or shot" << endl; return false;}
  if ((s.getPosition()) % 10 == 0 ) {cout << "WALL to left: invalid placement or shot" << endl; return false;}
  if ((s.getPosition() - 9) % 10 == 0) {cout << "WALL to right: invalid placement or shot" << endl; return false;}

  return true;
}



int displayMap(map* m ) {

  const string letters = "ABCDEFGHIJ"; //const string of letters A - J for displaying map purposes
  int ticker = 0;

  cout << "  ";

  for (int x = 0; x < 10; x++) 
  {
    cout << letters.at(x) << " ";
    
  }

  cout << endl;

  //display index 0 - 99 from a map object 
  for (int i = 1; i < 101; i++) 
  {
    if (i % 10 == 1) {cout << ticker + 1 << " ";}
    cout << m[i - 1].typecode << " " ;

  //this line formats the code so if i divided by 10 has a remainder of 0 start the next line 
  //simple way to 
    if (i % 10 == 0 ) {cout << "\n"; ticker++;}
  }
  
  return -1; 
}

map::map() {
  typecode = 0;
}

map* assignMap(ship &s, map *m) {

  int number = -1;
  int actualIndex = -1;
  char letter = 'x';


  cout << endl;
  cout << "Place " << s.getString() << endl;; 

  cout << "Enter Letter Coordinate: ";
  cin >> letter;  

  cout << "Enter Number Coordinate: "; 
  cin >> number;


  letter = convertLetterToNumber(letter);

  for (int e = 0; e < s.getLength(); e++ ) 
  {
    actualIndex = letter + ((number - 1) * 10) + e;
    m[actualIndex].typecode = s.getShipCode();
  }

  return m; // if assignMap function returns -1 something went wrong 
}


int convertLetterToNumber(char x) {
  x = toupper(x); // in case the user enters a lower case letter, this converts to uppercase 
  int numberFROMletter = -1; //negative is a default error code 

  if (x == 'A') {numberFROMletter = 0;} 
  else if (x == 'B') {numberFROMletter = 1;}
  else if (x == 'C') {numberFROMletter = 2;}
  else if (x == 'D') {numberFROMletter = 3;}
  else if (x == 'E') {numberFROMletter = 4;}
  else if (x == 'F') {numberFROMletter = 5;}
  else if (x == 'G') {numberFROMletter = 6;}
  else if (x == 'H') {numberFROMletter = 7;} 
  else if (x == 'I') {numberFROMletter = 8;}
  else if (x == 'J') {numberFROMletter = 9;}

  return numberFROMletter;
}






/****************
* Main Function *
****************/

int main() {

//game functionaly variable Declarations 
  bool isgameover = false; //gameloop bool value if true the game loop ends 
  bool isstartmenuover = false; //bool value handles the the start menu
  int turncounter = 1; 
  char userInput;
  char secretResign;

      // Specification C1 - OOP
      //ship objects
        ship x;
        Carrier *c = new Carrier;
        Carrier carrier;
        Battleship battleship;
        Cruiser cruiser;
        Submarine submarine;
        Destroyer destroyer;

          //map objects 
            map *playerShips = new map[100]; //playerships points to array of 100 map object on the heap (only ships)
            map *playerHitOrMiss = new map[100]; //map pointer 
            map *aiShips = new map[100];
            map *aiHitOrMiss= new map[100];

              //player objects
                player human;
                player ai;
                human.human = true; //sets human player to true
                ai.human = false; //sets ai player object to false

  
  greetingMenu();


  cout << "Enter:";
  cin >> userInput; 
  userInput = toupper(userInput); //converts in put to uppercase

    do 
      {
        switch(userInput) {
          case 'P': 
            cout << "playing..." << endl;
            isstartmenuover = true;

                //Displays map so the user knows what the board looks like 
                  displayMap(playerShips); //displays player ships

                    //5 function calls designed to prompt the user to enter the location 
                      playerShips = assignMap(carrier,playerShips);
                      playerShips = assignMap(battleship, playerShips);
                      playerShips = assignMap(cruiser, playerShips);
                      playerShips = assignMap(submarine, playerShips);
                      playerShips = assignMap(destroyer, playerShips);

                          displayMap(playerShips);
                          cout << "Do you accept your ship placement?" << endl;
                          cin >> userInput;

                              //GAME LOOP
                                do 
                                {
                                  turncounter++;
                                  //whos turn is it 
                                  if (turncounter % 2 == 0) //if the turncounter's remainder is 0 then the human goes first 
                                    {
                                      // Specification A1 - Resign Game
                                      cin >> secretResign;
                                      if (secretResign == 'x') {isgameover = true;}
                                      cout << "Human turn" << endl;

                                      human.shoot(); 
                                    } 
                                  else if (turncounter % 2 == 1 ) //if the turncounter's remainder is 1 then the human goes first 
                                    {
                                      cout << "Robot turn" << endl;
                                    }


                                } while (isgameover == false);
     
            break;
          case 'R':
            cout << "rules..." << endl;
            break;

          case 'T':
            cout << "advanced firing..." << endl;
            break;

          case 'Q': 
            cout << "Quiting..." << endl;
            break;

        }

      } while (isstartmenuover == false);

  




}

/**********************
* END of Main Function*
**********************/

int player::askNumberCord()
{
    
    int n;
    bool valid = false;
          do 
          {
            cout << "Enter Number Coordinate:" << endl;
            cin >> n; 
            cout << endl;


            if (n < 1 || n > 10) //if the number input is outside the 1-10 range then  the program will reprompt the user to enter the data until the base condition is met. 
              {
                cout << "Reenter a number 1-10" << endl;
                cin >> n; 
                cout << endl;
              }
            else if (n >= 1 || n <= 10) //if the input is between 1 and 10, the do/while loop ends
              {
                valid = true; 
              }

          } while (valid == false);

          

  return n;
}

int player::askLetterCord() 
{

    bool valid = false;
    char x;

            do 
          {
            cout << "Enter Letter Coordinate:" << endl;
            cin >> x; 
            cout << endl;

            x = toupper(x); //capitalizes all input

            if (x < 65 || x > 74) //if the number input is outside the ASCII range from A-J (65-74) range then  the program will reprompt the user to enter the data until the base condition is met. 
              {
                cout << "Reenter a Letter A-J" << endl;
                cin >> x; 
                cout << endl;
              }
            else if (x >= 65 || x <= 74) //if the input is between A and J, the do/while loop ends
              {
                valid = true; 
              }

          } while (valid == false);

  return convertLetterToNumber(x);

}

int player::shoot() {
  int shotLocation = -1;
  cout << "Enter Your Shot's Coordinates: " << endl;

  shotLocation = askLetterCord() + ((askNumberCord() - 1) * 10);

  if (shotLocation > 99 || shotLocation < 0) 
    {
      cout << "Shot calculation messed up" << endl;
    }
  return shotLocation;
}

bool player::validateShots(player &P, map *M) {

   if (M[P.shoot()].typecode == 1)
    {
      cout << "You can't shoot the same square twice" << endl;
      return false;
    } 

  return true;

}


