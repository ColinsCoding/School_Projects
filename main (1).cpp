//GeneticAlgorithm.cpp
//Colin Casey
//May 19 2021

#include <iostream>
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

//map codes (inside entiy)
//-1 > n < 9 wall
//-1 error 
// 0 empty RNG
// 1 battery RNG
// 2 = physical robot

//sensor codes (inside DNA) (ALL RNG)
// 9 battery detected
// 8 wall detected
// 7 no object detected
// 6 dont care if anything is there  

//Number Generation functions
int generateStats( int, int, int); //accepts 3 parameters upper, lower, and seed. Seed multiplies time(0) so as long as seed is nonrepeating, the random numbers are non repeating 

int generateStats( int upper = 0, int lower = 0,  int seed = 0) 
{
    int  number;
    upper = (upper +  1) - lower;
    
    
    srand(seed * time(0));
    number = ((rand()) % (upper) + lower); //rand(is psuedo random) divided by the remainder of upper + lower 

  return number;
};




//class declarations
class entity; //object that can be empty or battery 
class robot; //robot class contains all methods related the robot


class entity {
  public:
      entity(); //overidden constructure 
      int determineMe(int); //in 
      int typeCode; // -1 = wall, 0 = emtpy, 1 = battery, 
      static int  counter; //static variable used a measure so all 40 batteries don't end it the same spot 
      

      //debugging varaibles and methods 
      static int totalBatteries; //
        //void whatAmI(const entity *map) {}; //anounces what type of entity this is Display function 

};


//entity functions start
//static variable intialization
int entity::counter = 0; 
int entity::totalBatteries = 0;

//copy constructor 
entity::entity() 
  {
    typeCode = 1; //intializes every entity to empty, code: 0
    determineMe(40);
  }

//function assigns 40% of the map to battery (its more like 45-55%, it needs fixing)
int entity::determineMe(int limit = 40) {
  
  srand(time(0) * counter);
  int number = -1; 
  int upper = 2; 
  int lower = 0; 
 
  number = ((rand()) % (upper) + lower);
  //cout << "number: " << number << endl;

  counter++;
  // cout << "count: " << counter << endl;

  do 
    {
      totalBatteries++; 
      return number;
    }
  while (totalBatteries <= limit );

  return 0;

}

//entity functions end 

//robot class prototype
class robot {
    public:
  //constructors 
          robot() {};

  //functions        
          int randomStart(); //generates a number 0-99
          bool isBatteryObject(); //return 9
          bool isWallObject(); //return 8
          bool isSquareEmtpy(); //return 7
          bool isObjectInSquare(); //return 6
          void detectEntity(); //umbrella functions for the previous four "is" functions
          void determineCoordinalData( const robot &r); //calculates and formats what is up, down, left and right
          
          bool isRobotDead(int x, const robot &r); //boolean function for ending the game loop
          int getPosition(const robot &r); //accepts entity objects since the map is an array of 100 entity objects
          void generateSensorDNA(); //randomly generates the first 15 DNA for a robot then assigns the default 16 to a developer set intrustrion 
          //generates a mode code (N = -10 S = +10 L = -1 R = +1 )
          
  //variable declarations
                static int nonrepeatingSeed; 
                static const int mapcode = 2; 
                int position = 0; //specific position for a single robot
                int energy; //if energy reaches 0 then robot dies 
                int turns; //truns survived used to track overall fitness 
                int down, up, left, right; //coordinal directions relative to the location of the current robot 


    //Struct declaration for DNA - the instructions the robot follows 
    //the robot searches through the first 15 arrays of "sensorCode" and if there is no mathch
    //robot follows the last direction (#16)
                        struct moveData 
                        {
                        int sesnorCode[4]; //array of the four sensor values 
                        int moveCode[1]; // N = -10 S = +10 L = -1 R = +1 
                        };

                        moveData DNA[16]; //16 lines of of sesnorcode 

};

int robot::nonrepeatingSeed = 0;

int robot::randomStart() {
  nonrepeatingSeed++;

  return generateStats(99,0,nonrepeatingSeed);
}

void robot::determineCoordinalData(const robot &r) {
  up = r.position - 10;
  down = r.position + 10;
  left = r.position - 1;
  right = r.position + 1;
}

bool robot::isBatteryObject() {
  if (up || down || left || right == 1) 
    {return true;}

  return false;
}

bool robot::isWallObject() {
  if (up < 0) {return true;}
  else if (down > 99) {return true;}
  else if (left % 10 == 0) {return true;}
  else if ((right - 9) % 10 == 0) {return true;}

  return false; 

}

bool robot::isSquareEmtpy() {
  
  if (up || down || left || right == 0) {return true;}
    return false;
}

bool robot::isObjectInSquare() {
  
  if (isWallObject() == true || isBatteryObject() == true )
    {return true;}

      return false;
}

void robot::detectEntity() {
  
}

bool robot::isRobotDead(int x, const robot &r) {
  if (r.energy == 0)
    {return true;}
    
    return false;
}

int robot::getPosition(const robot &r) {return r.position;}

//place these in robot  constructor 
void robot::generateSensorDNA() {
  for (int j = 0; j < 15; j++) 
    {
      for (int x = 0; x < 4; x++)
        { 
          nonrepeatingSeed++;
          DNA[j].sesnorCode[x] = generateStats(3, 6, nonrepeatingSeed);
          nonrepeatingSeed++;
          DNA[j].moveCode[x] = generateStats(4, 1, nonrepeatingSeed);
        }
      
    }

    DNA[15].sesnorCode[0] = 6;
    DNA[15].sesnorCode[1] = 6;
    DNA[15].sesnorCode[2] = 6;
    DNA[15].sesnorCode[3] = 6;
    
    DNA[15].moveCode[0] = -10; //-10 means north
}


//general functions start
void starMenu(); //sets up the vairables and siaplys system time 
entity* assignEntity(robot &r, entity *m, int locationON1d);
robot breed(robot &r) {return r;};
entity* moveRobot(robot &r, entity *m, int location);
int displayMap(entity* e); //accepts a map reference, formats the data, and displays an accurate 10x10 gride 


entity* moveRobot(robot &r, entity *m, int location)
{
  for (int x = 0; x < 15; x++) 
    {
      if (r.DNA[x].sesnorCode[0] == (m->typeCode - 10) 
      && 
      r.DNA[x].sesnorCode[1] == (m->typeCode + 10) 
      && 
      r.DNA[x].sesnorCode[2] == (m->typeCode -1) 
      && 
      r.DNA[x].sesnorCode[3] == (m->typeCode + 1)
      )
          {r.DNA[x].moveCode[0] = 1; };
    }
  



  return m;
}

int displayMap(entity* e) {
  
  for (int x = 0; x < 100; x++) 
    {
      cout << e->typeCode << " ";
      if ((x +2) % 10 == 1) {cout << endl;}
    }

  return -1;
}

entity* assignEntity(robot &r, entity *e, int locationON1d) {
  
  locationON1d = 0;
  int number = -1;

      e[locationON1d].typeCode = r.mapcode;
  
        return e; 
}


//general functions end

//Main Function START 
int main() {

    //variable declaration and intialization
      int lifetimes = 5; //variable determines how many robots will endure the test of life. 200 lifetimes = 200 robots on randomly generated maps 
      bool isgameover = false; //ends the program if a key [ ] is pressed
      int currentPosition= -1;



          //object declaration and intialization
            robot Robot[lifetimes]; //intializing 200 robot objects on the stack

            entity *map = new entity[100];
            


cout << "START" << endl;


                //lifetimes for loop 
                  for (int i = 0; i < lifetimes; i++)
                    {
                      //individual robot do/while loop 
                        do 
                        {
                          map = assignEntity(Robot[i], map, Robot[i].randomStart());

                          displayMap(map);
                          
                        } while ( isgameover == false || Robot[i].isRobotDead(0, Robot[i]) == false ); //loop ends if admin sets gameover to be true or the current robot dyes 
                    }

cout << "END" << endl;

  
}
//Main Function END
