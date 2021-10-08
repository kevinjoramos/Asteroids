###############################################################
# Program:
#     Project 13, Asteroids
#     Brother Alvey, CS165
# Author:
#     Kevin Ramos
# Summary:
#     This program is a homage to old "astroids" game for the
#     atari. It involves flying a spacship without external
#     forces to change your velocity, manuvering around the
#     astroids, and shooting them into smaller pieces.
#     
#     11-24-20
#     I was able to prepare all the files for the project by
#     refrencing my files from the skeet project. the rock files are
#     not finished yet because I still need to flesh out the classes
#     for the other two sizes. Most of the game.cpp file is
#     commented out, but this is because there are functions
#     that have good reference material for the functions I still
#     need to make.
#
#	  12-06-20 
#     I finished programing the ship and its movements and flight,
#     I also completed the bullets, and their movement. After
#     each bullet is fired, it dies after 40 frames.
#
#     I also wrapped the screen around the edges. And added rock
#     rotating each frame. (I forgot this in the previous.)
#
#     What took so long was getting the trigonometry correct for 
#     making the ship accelerate in the direction that ship was pointing
#     when thrusting.
#
#	  12-09-20
#     I finished building the classes for the different size
#     asteroids. I programmed their collision and splitting.
#     I also programmed their removal and freeing of memory.
#     The hardest part was figuring out how each "child"
#     asteroid would inheret the parent velocity and point. 
#
#    
# Above and Beyond
#     I gave my ship "shields" with a strength of 7. The Ship
#     can withstand 7 collisions without being destroyed, and
#     on the eigth collsion, the ship will crash.
#     
#     On each of the preceeding collsions, the ship will "bump"
#     with the asteroids, breaking it into pieces, sending the
#     player hurling away with an inverted velocity with a slight
#     percentage drop depending on the size of the asteroid. 
#     If the ship's velocity is slower than the asteroid, then
#     the ship will gain twice the velocity of the asteroid.
#     
#     This changes the game in two interesting ways. You can
#     actually use these bounces to help position your ship
#     in the way you want, but on the other hand, you have to be
#     careful, if there are too many asteroids on the field, you
#     can quickly find your ship being "pin-balled" to death if 
#     you dont react fast enough.
#     The functionality for this can be found in the ship.cpp file
#     and in the game.cpp collision function.
###############################################################


LFLAGS = -lglut -lGLU -lGL

###############################################################
# Build the main game
###############################################################
a.out: driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o rocks.o
	g++ driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o rocks.o $(LFLAGS)
	tar -j -cf asteroids.tar makefile *.h *.cpp

###############################################################
# Individual files
#    uiDraw.o       Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o   Handles input events
#    point.o        The position on the screen
#    game.o         Handles the game interaction
#    velocity.o     Velocity (speed and direction)
#    flyingObject.o Base class for all flying objects
#    ship.o         The player's ship
#    bullet.o       The bullets fired from the ship
#    rocks.o        Contains all of the Rock classes
###############################################################
uiDraw.o: uiDraw.cpp uiDraw.h
	g++ -c uiDraw.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
	g++ -c uiInteract.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

driver.o: driver.cpp game.h
	g++ -c driver.cpp

game.o: game.cpp game.h uiDraw.h uiInteract.h point.h velocity.h flyingObject.h bullet.h rocks.h ship.h
	g++ -c game.cpp

velocity.o: velocity.cpp velocity.h point.h
	g++ -c velocity.cpp

flyingObject.o: flyingObject.cpp flyingObject.h point.h velocity.h uiDraw.h
	g++ -c flyingObject.cpp

ship.o: ship.cpp ship.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c ship.cpp

bullet.o: bullet.cpp bullet.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c bullet.cpp

rocks.o: rocks.cpp rocks.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c rocks.cpp


###############################################################
# General rules
###############################################################
clean:
	rm a.out asteroids.tar *.o
