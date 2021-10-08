#include "flyingObject.h"

// Put your FlyingObject method bodies here

//Constructor
FlyingObject :: FlyingObject()
{
   
}

//Setters
void FlyingObject :: setPoint(Point &point)
{
   this->point = point;
}

void FlyingObject :: setVelocity(Velocity &velocity)
{
   this->velocity = velocity;
}

void FlyingObject :: setScoredPoints(int scoredPoints)
{
   this->scoredPoints = scoredPoints;
}

void FlyingObject :: generate()
{
   isAlive = true;
}

bool FlyingObject :: kill()
{
   isAlive = false;
}

void FlyingObject :: wrapAroundScreen()
{
   if (point.getX() > 200 || point.getX() < -200)
      point.setX(point.getX() * -1);

   if (point.getY() > 200 || point.getY() < -200)
      point.setY(point.getY() * -1); 
}