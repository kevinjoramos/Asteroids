/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <list>

#include "rocks.h"
#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "bullet.h"
#include "ship.h"



// TODO: include your bullet and bird classes


#define CLOSE_ENOUGH 15


/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
   /*********************************************
    * Constructor
    * Initializes the game
    *********************************************/
   Game(Point tl, Point br);
   ~Game();
   
   /*********************************************
    * Function: handleInput
    * Description: Takes actions according to whatever
    *  keys the user has pressed.
    *********************************************/
   void handleInput(const Interface & ui);
   
   /*********************************************
    * Function: advance
    * Description: Move everything forward one
    *  step in time.
    *********************************************/
   void advance();
   
   /*********************************************
    * Function: draw
    * Description: draws everything for the game.
    *********************************************/
   void draw(const Interface & ui);
   
private:
   // The coordinates of the screen
   Point topLeft;
   Point bottomRight;
   
   int score;
   
   std::vector<Bullet> bullets;
   std::vector<Rock*> rocks;
   Ship ship;
   
   


   /*************************************************
    * Private methods to help with the game logic.
    *************************************************/
   bool isOnScreen(const Point & point);
   void advanceBullets();
   void advanceRocks();
   void advanceShip();
   Rock* createRock();
   Rock* createMediumRock(Point &motherPoint, Velocity &motherVelocity);
   Rock* createSmallRock(Point &motherPoint, Velocity &motherVelocity);
   
   void handleCollisions();
   float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const;
   void splitRock(Rock &rock, int rockIndex);
   void cleanUpZombies();
};


#endif /* GAME_H */
