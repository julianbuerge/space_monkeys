#ifndef star_system_H
#define star_system_H

//default cpp libraries
#include <unistd.h> //to get the current working directory
#include <cmath>
#include <iostream>
#include <string>
//simple and fast multimedia library
#include <SFML/Graphics.hpp>
//my own classes


class star_system
{
private:

  //Membervariables
  std::string currentworkingdirectory;

  //the star system represents a game-level. here is its id. this means that the associated file is Level_id.txt.
  int level_id;

  //identifier of the star system. used as the text displayed.
  std::string name;
  //identifier of the star image. used to load the correct picture from files.
  std::string texture_name;

  sf::Sprite sprite;

  sf::Texture texture;

  sf::Font font;
  sf::Text text;

  //physical initial coordinates and velocities.
  double x;
  double y;
  double vx;
  double vy;

  //if we have been swallowed by the blackhole or not
  bool swallowed;

  //pi
  double pi = 3.14159265358979;

  //propertime
  double tau;

  //Lorentzfactor
  double Lorentzfactor;

  //central body influencing the star_system parameters
  double M;
  double a;

  //window parameters
  float width;
  float height;
  float stretch;





  //Memberfunctions

  //convert radians to degrees
  double radtodeg(double alpha);

  //Equation of motion ODE operators dv^i/dt = f_vi(x,y,vx,vy)
  double f_vx(double x, double y, double vx, double vy);
  double f_vy(double x, double y, double vx, double vy);


public:

  //Constructors
  star_system();

  star_system(int level_id_in, std::string name_in, std::string texture_name_in, double x_in, double y_in, double vx_in, double vy_in, double M_in, double a_in, float width_in, float height_in, float stretch_in, float A, float B, float C, float D);

  //Membervariables


  //Memberfunctions

  //in case you have already allocated an instance but want to initialize like with the constructor, use this
  void initialize(int level_id_in, std::string name_in, std::string texture_name_in, double x_in, double y_in, double vx_in, double vy_in, double M_in, double a_in, float width_in, float height_in, float stretch_in, float A, float B, float C, float D);


  //transform world coordinates x,y to screen coordinates.
  //the world is [A,B]x[C,D] and the screen is [0,width*stretch]x[0,height*stretch] with origin top left corner.
  float screen_x(double x,float A,float B,float C,float D);
  float screen_y(double y,float A,float B,float C,float D);

  //retrieve the sprite for rendering
  sf::Sprite& getSprite();

  //retrieve the text for rendering
  sf::Text& getText();

  //get the current Lorentzfactor
  double getLorentzfactor();

  //get if we were swallowed
  bool getSwallowed();

  //spacetime metric (independent of t and vt = 1)
  double g(double x, double y, double vx, double vy);

  //get the spatial speed. From g(v,v) < 0 with v = (1,vx,vy) we get g_ijv^iv^j / -g_00 < 1. The spatical speed is sqrt(g_ijv^iv^j / -g_00).
  double spatial_speed(double vx, double vy);
  double spatial_speed();

  //manually set vx,vy by an angle and modulus
  void set_chart_velocity(double modulus, double angle);

  //evolve the trajectory by time dt and update the propertime. optionally always rotate the sprite in direction of travel.
  void evolve(double dt, float A, float B, float C, float D);

  //check if we are colliding with another star_system
  bool checkCollision(star_system& other_star_system);

  //make the star_system invisible in order to do as if it stopped existing
  void make_invisible();

  //return the level id if the star system was clicked (in the level menu)
  int pressed(float x, float y);

};

#endif //star_system_H
