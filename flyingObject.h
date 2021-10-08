#ifndef flyingObject_h
#define flyingObject_h

#include "point.h"
#include "velocity.h"

// Put your FlyingObject class here
class FlyingObject
{
   protected:
      Point point;
      Velocity velocity;
      bool isAlive;
      int scoredPoints;

   public:
      //Constructor
      FlyingObject();

      //Getters
      Point getPoint() const {return point;}
      Velocity getVelocity() const {return velocity;}
      bool IsAlive() const {return isAlive;}
      int getScoredPoints() const {return scoredPoints;}
      
      //Setters
      void setPoint(Point &point);
      void setVelocity(Velocity &velocity);
      void setScoredPoints(int scoredPoints);
      void generate();
      bool kill();

      //member
      virtual void advance() = 0;
      virtual void draw() = 0;
      void wrapAroundScreen();
      
};

#endif /* flyingObject_h */
