#include "rocks.h"

// Put your Rock methods here

// ROCK BASE CLASS SETTERS
void Rock :: setMotionAngle(float motionAngle)
{
   this->motionAngle = motionAngle;
}

void Rock :: setRadius(float radius)
{
   this->radius = radius;
}

void Rock :: setRotation(int rotation)
{
   this->rotation = rotation;
}

void Rock :: setSpeedFactor(float speedFactor)
{
   this->speedFactor = speedFactor;
}

void Rock :: setTypeRock(std::string typeRock)
{
   this->typeRock = typeRock;
}

void MediumRock :: setMotherVelocity(Velocity &motherVelocity)
{
   this->motherVelocity = motherVelocity;
}

void SmallRock :: setMotherVelocity(Velocity &motherVelocity)
{
   this->motherVelocity = motherVelocity;
}


//CONSTRUCTORS
BigRock :: BigRock()
{
   setMotionAngle(random(0, 359)); //<-Assuming that angle is in degrees.
   setRadius(BIG_ROCK_SIZE);
   setRotation(BIG_ROCK_SPIN);
   setSpeedFactor(1.0);
   setTypeRock("big");
   generate();

   point.setX(random(-199, 199));
   point.setY(random(-199, 199));
}

MediumRock :: MediumRock(Point &point, Velocity &velocity)
{
   generate();
   setTypeRock("medium");
   setRadius(MEDIUM_ROCK_SIZE);
   setRotation(MEDIUM_ROCK_SPIN);

   setPoint(point);
   setMotherVelocity(velocity);
}

SmallRock :: SmallRock(Point &point, Velocity &velocity)
{
   generate();
   setTypeRock("small");
   setRadius(SMALL_ROCK_SIZE);
   setRotation(SMALL_ROCK_SPIN);
   
   //setSpeedFactor(1.0);

   setPoint(point);
   setMotherVelocity(velocity);
}

