#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#include <cmath>
#include "flyingObject.h"
#include "uiDraw.h"

// Put your Bullet class here
class Bullet : public FlyingObject
{
   protected:
      float angle;
      int lifetime;
      Velocity initialVelocity;

   public:
      //Constructor
      Bullet();

      //Getters
      float getAngle() const {return angle;}
      int getLifeTime() const {return lifetime;}
      Velocity getInitialVelocity() const {return initialVelocity;}

      //Setters
      void setAngle(float angle);
      void setLifeTime(int lifetime);
      void setInitialVelocity(Velocity &initialVelocity);

      //Member
      void fire(Point point, float angle, Velocity velocity);
         
      virtual void advance()
      {
         velocity.setDx(initialVelocity.getDx() + (BULLET_SPEED * (cos(M_PI / 180.0 * angle))));
         velocity.setDy(initialVelocity.getDy() + (BULLET_SPEED * (sin(M_PI / 180.0 * angle))));

         velocity.advancePoint(point);

         wrapAroundScreen();
      }

      virtual void draw()
      {
         drawDot(point);
         
      }
};

#endif /* bullet_h */
