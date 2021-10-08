#include "bullet.h"

// Put your bullet methods here

//Constructor
Bullet :: Bullet()
{
   generate();
   setLifeTime(0);

}

//Getters

//Setters
void Bullet :: setAngle(float angle)
{
   this->angle = angle;
}

void Bullet :: setLifeTime(int lifetime)
{
   this->lifetime = lifetime;
}

void Bullet :: setInitialVelocity(Velocity &initialVelocity)
{
   this->initialVelocity = initialVelocity;

}

//Member
void Bullet :: fire(Point point, float angle, Velocity velocity)
{
   setInitialVelocity(velocity);
   setPoint(point);
   setAngle(angle + 90);
   draw();
}