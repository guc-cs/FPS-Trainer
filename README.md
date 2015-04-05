FPS-Trainer
===========

In the 5th Semester - Winter Fall 2010, a team who was fascinated by video games in general and FPS games in specific proposed to implement a First Person Shooter target practice game. This idea was inpsired by the infamous Virtua Cop game [https://youtu.be/5GVl7t9GYkc](https://youtu.be/5GVl7t9GYkc). The project was implemented using C++ and Vanilla OpenGL.

Introduction
------------
The game is a simple First-Person Shooter, and consists mainly of one level featured in most games of this genre, which is a practice range. Targets will pop-up in various locations as the player navigates through the level, and the player is required to hit some or all of them. The player only has a fixed number ammount of ammunition and is required to reload when the gun runs low on Ammo. The score is a function of how many targets the user hits in a fixed time interval using the minimum ammount of bullets.

![Screenshot of the game](http://i.imgur.com/og7SNfr.png)


Features
--------
* First-Person Camera implementation
* Simple Physics including gravity calculations
* Md2 Model parser for target characters taken from Counter strike 1.6
* Detecting whether or not a bullet has hit a target in the 3D map.
* Using Textures and height maps to draw the map environment.
* Using Textures to draw the targets and the weapon.
* Adequate random placement of the targets with respect to the map boundaries.
* Collision Detection between the player and the map as well as targets
* A simple game menu state machine, hit marker and Ammo hud display
* Reacting to Keyboard and mouse events to navigate through the map and shoot

How To
------
1. Install the necessary dependencies

  ```bash
  sudo apt-get install build-essential freeglut3 freeglut3-dev
  ```
  
2. Make it

  ```bash
  make
  ```
  
3. Play it!

  ```bash
  ./FPSTrainer
  ```

Controls
--------
* Jump - `Space`
* Duck/Stand up - `C`
* Move Forward - `W`
* Move Backward - `S`
* Move Left - `A`
* Move Right - `D`
* Reload - `R`
* Toggle Menu `ESC`
* Fire weapon `Left mouse click`
* Look around `Mouse`


Bugs
----
Everything here is just student code and a proof of concept. Currently, there are a few bugs with the collision detection system so, you can actually get stuck in the map in some cases. Moreover, there is a stack smashing bug (See gcc flags in the Makefile). In addition, if you resize the window, all the event handlers' calculations become faulty.
 

Contributors
------------
* Mohab El-karef
* Ahmed Mohsen
* Amr Tj. Wallas
* Magued George


License
-------
MIT. See [LICENSE](/LICENSE) file for more infomration
