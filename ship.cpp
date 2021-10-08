#include "ship.h"

// Put your ship methods here

//CONSTRUCTOR
Ship :: Ship()
{
   generate();
   setHealth(8);
   setRadius(SHIP_SIZE);
   setRotation(270);
   point.setX(0);
   point.setY(0);
   

   //Input event based variables.
   setMotionAngle(0);
   setThrust(false);
}

//SETTERS
void Ship :: setMotionAngle(float motionAngle)
{
   this->motionAngle = motionAngle;
}

void Ship :: setRadius(float radius)
{
   this->radius = radius;
}

void Ship :: setRotation(int rotation)
{
   this->rotation = rotation;
}

void Ship :: setSpeedFactor(float speedFactor)
{
   this->speedFactor = speedFactor;
}

void Ship :: setThrust(bool thrust)
{
   this->thrust = thrust;
}

void Ship :: setHealth(int health)
{
   this->health = health;
}

//Movement
void Ship :: rotateRight()
{
   setRotation(getRotation() - ROTATE_AMOUNT);
}

void Ship :: rotateLeft()
{
   setRotation(getRotation() + ROTATE_AMOUNT);
}

void Ship :: accelerate()
{
   setMotionAngle(getRotation());
   setThrust(true);
}

void Ship :: inverseVelocity(string rockType, Velocity rockVelocity)
{
   if (velocity.getDx() == 0 && velocity.getDy() == 0)
   {
      velocity.setDx(rockVelocity.getDx() * 2);
      velocity.setDy(rockVelocity.getDy() * 2);
   }
   else
   {
      velocity.setDx(velocity.getDx() * -1);
      velocity.setDy(velocity.getDy() * -1);

      //If collision with big Rock, give 80% velocity
      if (rockType == "big")
      {
         if (velocity.getDx() > rockVelocity.getDx()
            && velocity.getDy() > rockVelocity.getDy())
         {
            velocity.setDx(velocity.getDx() * .80);
            velocity.setDy(velocity.getDy() * .80);
         }
         else
         {
            velocity.setDx(rockVelocity.getDx() * 2);
            velocity.setDy(rockVelocity.getDy() * 2);
         }
      }

      //if collision with medium rock, give 60% velocity
      if (rockType == "medium")
      {
         if (velocity.getDx() > rockVelocity.getDx()
            && velocity.getDy() > rockVelocity.getDy())
         {
            velocity.setDx(velocity.getDx() * .60);
            velocity.setDy(velocity.getDy() * .60);
         }
         else
         {
            velocity.setDx(rockVelocity.getDx() * 2);
            velocity.setDy(rockVelocity.getDy() * 2);
         }
         
      }

      //if small rock, give 40% velocity
      if (rockType == "small")
      {
         if (velocity.getDx() > rockVelocity.getDx()
            && velocity.getDy() > rockVelocity.getDy())
         {
            velocity.setDx(velocity.getDx() * .40);
            velocity.setDy(velocity.getDy() * .40);
         }
         else
         {
            velocity.setDx(rockVelocity.getDx() * 2);
            velocity.setDy(rockVelocity.getDy() * 2);
         }
         
      } 
   }
   
   
}



