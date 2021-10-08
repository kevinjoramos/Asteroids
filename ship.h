#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#include "flyingObject.h"
#include "uiDraw.h"
#include "cmath"

// Put your Ship class here
class Ship : public FlyingObject
{
   protected:
      float motionAngle;
      float radius;
      int rotation;
      float speedFactor;
      bool thrust;
      int health;

   public:
      //Constructor
      Ship();

      //Getters
      float getMotionAngle() const {return motionAngle;}
      float getRadius() const {return radius;}
      int getRotation() const {return rotation;}
      float getSpeedFactor() const {return speedFactor;}
      bool getThrust() const {return thrust;}
      int getHealth() const {return health;}

      //Setters
      void setMotionAngle(float motionAngle);
      void setRadius(float radius);
      void setRotation(int rotation);
      void setSpeedFactor(float speedFactor);
      void setThrust(bool thrust);
      void setHealth(int health);

      //Member
      void rotateRight();
      void rotateLeft();
      void accelerate();
      void inverseVelocity(string rockType, Velocity rockVelocity);

      virtual void advance()
      {
         if (thrust == true)
         {
            velocity.setDx(velocity.getDx() + (THRUST_AMOUNT * (cos(M_PI / 180.0 * getMotionAngle() - 80))));
            velocity.setDy(velocity.getDy() + (THRUST_AMOUNT * (sin(M_PI / 180.0 * getMotionAngle() - 80))));

            velocity.advancePoint(point);

            setThrust(false);

         }
         else
         {
            velocity.setDx(velocity.getDx());
            velocity.setDy(velocity.getDy());

            velocity.advancePoint(point);
         }

         wrapAroundScreen();
      }

      virtual void draw()
      {
         drawShip(point, rotation, thrust);
      }
};

#endif /* ship_h */
