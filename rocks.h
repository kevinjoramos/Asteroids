#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "flyingObject.h"
#include "uiDraw.h"
#include <cmath>
#include <string>

// Define the following classes here:
//   Rock
class Rock : public FlyingObject
{
   protected:
      float motionAngle;
      float radius;
      int rotation;
      float speedFactor;
      std::string typeRock;

   public:
      //Getters
      float getMotionAngle() const {return motionAngle;}
      float getRadius() const {return radius;}
      int getRotation() const {return rotation;}
      float getSpeedFactor() const {return speedFactor;}
      std::string getTypeRock() const {return typeRock;}

      //Setters
      void setMotionAngle(float motionAngle);
      void setRadius(float radius);
      void setRotation(int rotation);
      void setSpeedFactor(float speedFactor);
      void setTypeRock(std::string typeRock);

      //Member <- I left blank but compiler might need me to fill.
};

//   BigRock
class BigRock : public Rock
{
   public:
      //Constructor
      BigRock();

      //Member
      virtual void advance()
      {
         setRotation(getRotation() + BIG_ROCK_SPIN);
         velocity.setDx(getSpeedFactor() * (-cos(M_PI / 180.0 * getMotionAngle())));
         velocity.setDy(getSpeedFactor() * (sin(M_PI / 180.0 * getMotionAngle())));

         velocity.advancePoint(point);

         wrapAroundScreen();
      }

      virtual void draw()
      {
         drawLargeAsteroid(getPoint(), getRotation());
      }
};

//   MediumRock
class MediumRock : public Rock
{
   protected:
      Velocity motherVelocity;

   public:
      //Constructor
      MediumRock(Point &point, Velocity &velocity);

      Velocity getMotherVelocity() const {return motherVelocity;}

      void setMotherVelocity(Velocity &motherVelocity);

      //Member
      virtual void advance()
      {
         setRotation(getRotation() + MEDIUM_ROCK_SPIN);
      
         velocity.setDx(getSpeedFactor() * (cos(M_PI / 180.0 * getMotionAngle()  )));
         velocity.setDx(velocity.getDx() + motherVelocity.getDx());

         velocity.setDy(getSpeedFactor() * (sin(M_PI / 180.0 * getMotionAngle()  )));
         velocity.setDy(velocity.getDy() + motherVelocity.getDy());

         velocity.advancePoint(point);

         wrapAroundScreen();
      }

      virtual void draw()
      {
         drawMediumAsteroid(getPoint(), getRotation());
      }
   

};

//   SmallRock
class SmallRock : public Rock
{
   protected:
      Velocity motherVelocity;

   public:
      //Constructor
      SmallRock(Point &point, Velocity &velocity);

      Velocity getMotherVelocity() const {return motherVelocity;}

      void setMotherVelocity(Velocity &motherVelocity);

      //Member
      virtual void advance()
      {
         setRotation(getRotation() + SMALL_ROCK_SPIN);
         velocity.setDx(getSpeedFactor() * (cos(M_PI / 180.0 * getMotionAngle())));
         velocity.setDx(velocity.getDx() + motherVelocity.getDx());

         velocity.setDy(getSpeedFactor() * (sin(M_PI / 180.0 * getMotionAngle())));
         velocity.setDy(velocity.getDy() + motherVelocity.getDy());

         velocity.advancePoint(point);

         wrapAroundScreen();
      }

      virtual void draw()
      {
         drawSmallAsteroid(getPoint(), getRotation());
      }


};



#endif /* rocks_h */
