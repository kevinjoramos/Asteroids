/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;

#define OFF_SCREEN_BORDER_AMOUNT 5

/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game(Point tl, Point br)
 : topLeft(tl), bottomRight(br)
{
   // Set up the initial conditions of the game
   score = 0;

   // TODO: Set your object pointers to a good initial value (e.g., NULL)
   for (int i = 0; i < 5; i++)
   {
      rocks.push_back(NULL);
   }
}

/****************************************
 * GAME DESTRUCTOR
 ****************************************/
Game :: ~Game()
{
   // TODO: Check to see if there is currently a bird allocated
   //       and if so, delete it.

}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   //Advance all the in game objects
   advanceBullets();
   advanceRocks();
   advanceShip();

   //Handle events
   handleCollisions();

   //clear memory
   cleanUpZombies();
}

/***************************************
 * GAME :: ADVANCE BULLETS
 * Go through each bullet and advance it.
 ***************************************/
void Game :: advanceBullets()
{
   
   for (int i = 0; i < bullets.size(); i++)
   {
      // Move each of the bullets forward if it is alive
      if (bullets[i].IsAlive())
      {
         // this bullet is alive, so tell it to move forward
         bullets[i].advance();

         if (!isOnScreen(bullets[i].getPoint()))
         {
            // the bullet has left the screen
            bullets[i].kill();
         } 
      }
   }
}

//We need to build advance functions for each in game object that moves.
//This advance bird can be useful template.
/**************************************************************************
 * GAME :: ADVANCE BIRD
 *
 * 1. If there is no bird, create one with some probability
 * 2. If there is a bird, and it's alive, advance it
 * 3. Check if the bird has gone of the screen, and if so, "kill" it
 **************************************************************************/
void Game :: advanceRocks()
{  
   for (vector <Rock*> :: iterator it = rocks.begin(); it != rocks.end(); ++it)
   {
      if (*it == NULL)
      {  
         *it = createRock(); 
      }
      else
      {
         // we have a bird, make sure it's alive
         if ((*it)->IsAlive())
         {
            // move it forward
            (*it)->advance(); 
         }
      }
   }
}

/**************************************************************************
 * GAME :: CREATE ROCK
 * Create a rock of a random type according to the rules of the game.
 **************************************************************************/
Rock* Game :: createRock()
{
   return new BigRock();
}

Rock* Game :: createMediumRock(Point &motherPoint, Velocity &motherVelocity)
{
   return new MediumRock(motherPoint, motherVelocity);
}

Rock* Game :: createSmallRock(Point &motherPoint, Velocity &motherVelocity)
{
   return new SmallRock(motherPoint, motherVelocity);
}

void Game :: advanceShip()
{
   if (ship.IsAlive() == true)
      ship.advance();

}

/**************************************************************************
 * GAME :: CREATE BIRD
 * Create a bird of a random type according to the rules of the game.
 **************************************************************************
Bird* Game :: createBird()
{
   int birdSelector = random(0, 3);

   if (birdSelector == 0)
   {
      bird = new Bird();
   }
   else if (birdSelector == 1)
   {
      bird = new ToughBird();
   }
   else if (birdSelector == 2)
   {
      bird = new SacredBird();
   }

   // TODO: Fill this in
   
   return bird;
}
*/

/**************************************************************************
 * GAME :: IS ON SCREEN
 * Determines if a given point is on the screen.
 **************************************************************************/
bool Game :: isOnScreen(const Point & point)
{
   return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
      && point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
      && point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
      && point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/**************************************************************************
 * GAME :: HANDLE COLLISIONS
 * Check for a collision between a bird and a bullet.
 **************************************************************************/
void Game :: handleCollisions()
{  
   
   // now check for a hit (if it is close enough to any live bullets)
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].IsAlive())
      {
         // this bullet is alive, see if its too close

         // check if the bird is at this point (in case it was hit)
         for (int j = 0; j < rocks.size(); j++)
         {

            if (rocks[j] != NULL && rocks[j]->IsAlive())
            {
               // BTW, this logic could be more sophisiticated, but this will
               // get the job done for now...
               if (rocks[j]->getRadius() >= getClosestDistance(bullets[i], *rocks[j]))
               {
                  //we have a hit!
                  splitRock(*rocks[j], j);
                  rocks[j]->kill();
                  // the bullet is dead as well
                  bullets[i].kill();
               }
            }
         }
      } // if bullet is alive
      
   } // for bullets

   for (int i = 0; i < rocks.size(); i++)
   {
      if (rocks[i] != NULL && rocks[i]->IsAlive())
      {
         if (ship.IsAlive())
         {
            // BTW, this logic could be more sophisiticated, but this will
            // get the job done for now...
            if (rocks[i]->getRadius() + ship.getRadius() >= getClosestDistance(ship, *rocks[i]))
            {
               //We have a hit.
               if (ship.getHealth() > 1)
               {
                  //reverse velocities. velocities.

                  ship.inverseVelocity(rocks[i]->getTypeRock(), rocks[i]->getVelocity());
                  splitRock(*rocks[i], i);
                  rocks[i]->kill();
                  

                  ship.setHealth(ship.getHealth() - 1);
               }
               else
               {
                  splitRock(*rocks[i], i);
                  rocks[i]->kill();
                  // the bullet is dead as well
                  ship.kill();
               }
            }
         }
      }
   }
}

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) + (yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

/**************************************************************************
 * GAME :: SPLIT ROCK
 * Splits rock that was shot or hit with the ship into two pieces.
 **************************************************************************/
void Game :: splitRock(Rock &rock, int rockIndex)
{
   //delete rocks[rockIndex];
   
   if (rocks[rockIndex]->getTypeRock() == "big")
   {
      Point motherPoint = rocks[rockIndex]->getPoint();
      Velocity motherVelocity = rocks[rockIndex]->getVelocity();
      
      rocks.push_back(createMediumRock(motherPoint, motherVelocity));
      rockIndex = rocks.size() - 1;
      rocks[rockIndex]->setMotionAngle(90);
      rocks[rockIndex]->setSpeedFactor(1);

      rocks.push_back(createMediumRock(motherPoint, motherVelocity));
      rockIndex = rocks.size() - 1;
      rocks[rockIndex]->setMotionAngle(270);
      rocks[rockIndex]->setSpeedFactor(1);

      rocks.push_back(createSmallRock(motherPoint, motherVelocity));
      rockIndex = rocks.size() - 1;
      rocks[rockIndex]->setMotionAngle(0);
      rocks[rockIndex]->setSpeedFactor(2);

   }

   if (rocks[rockIndex]->getTypeRock() == "medium")
   {
      Point motherPoint = rocks[rockIndex]->getPoint();
      Velocity motherVelocity = rocks[rockIndex]->getVelocity();
      
      rocks.push_back(createSmallRock(motherPoint, motherVelocity));
      rockIndex = rocks.size() - 1;
      rocks[rockIndex]->setMotionAngle(0);
      rocks[rockIndex]->setSpeedFactor(3);

      rocks.push_back(createSmallRock(motherPoint, motherVelocity));
      rockIndex = rocks.size() - 1;
      rocks[rockIndex]->setMotionAngle(180);
      rocks[rockIndex]->setSpeedFactor(3);
   }


}

/**************************************************************************
 * GAME :: CLEAN UP ZOMBIES
 * Remove any dead objects (take bullets out of the list, deallocate bird)
 **************************************************************************/
void Game :: cleanUpZombies()
{
   // Look for dead bullets
   vector<Bullet>::iterator bulletIt = bullets.begin();
   while (bulletIt != bullets.end())
   {
      Bullet bullet = *bulletIt;
      // Asteroids Hint:
      // If we had a list of pointers, we would need this line instead:
      //Bullet* pBullet = *bulletIt;
      
      if (!bullet.IsAlive())
      {
         // If we had a list of pointers, we would need to delete the memory here...
         
         
         // remove from list and advance
         bulletIt = bullets.erase(bulletIt);
      }
      else
      {
         bulletIt++; // advance
      }
   }

   vector<Rock*>::iterator rockIt = rocks.begin();
   while (rockIt != rocks.end())
   {
      Rock* pRock = *rockIt;

      if (!pRock->IsAlive())
      {
         delete pRock;
         pRock = NULL;

         rockIt = rocks.erase(rockIt);
      }
      else
      {
        rockIt++;
      }
      
   }
   
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui)
{
   
   if (ui.isLeft())
   {
      ship.rotateLeft();
   }
   
   if (ui.isRight())
   {
      ship.rotateRight();
   }

   if (ui.isUp())
   {
      ship.accelerate();
   }
   
   if (ui.isSpace())
   {
      Bullet newBullet;
      newBullet.fire(ship.getPoint(), ship.getRotation(), ship.getVelocity());

      bullets.push_back(newBullet);
   }
   /*
   // Check for "Spacebar"
   if (ui.isSpace())
   {
      Bullet newBullet;
      newBullet.fire(rifle.getPoint(), rifle.getAngle());
      
      bullets.push_back(newBullet);
   }initialVelocity.getDx()
   */
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{

   if (ship.IsAlive())
   {
      ship.draw();
   }

   // draw the Rocks
   for (vector <Rock*> :: iterator it = rocks.begin(); it != rocks.end(); ++it)
   {
      if ((*it)->IsAlive())
         (*it)->draw();
   }

   
   
   // draw the bullets, if they are alive
   for (int i = 0; i < bullets.size(); i++)
   {
      //kills the bullet if it is older than 40 frames.
      if (bullets[i].getLifeTime() > 40)
      {
         bullets[i].kill();
      }

      if (bullets[i].IsAlive())
      {
         bullets[i].draw();
         bullets[i].setLifeTime(bullets[i].getLifeTime() + 1);

      }
   }
   
   // Put the score on the screen
   /*
   Point scoreLocation;
   scoreLocation.setX(topLeft.getX() + 5);
   scoreLocation.setY(topLeft.getY() - 5);
   
   drawNumber(scoreLocation, score);
   */
}

