#ifndef PARTICLE_H
#define PARTICLE_H

//default cpp libraries
#include <unistd.h> //to get the current working directory
#include <cmath>
#include <iostream>
#include <string>
//simple and fast multimedia library
#include <SFML/Graphics.hpp>
//my own classes


class particle
{
private:

  //Membervariables
  std::string currentworkingdirectory;

  //identifier of the spaceship. used to load the correct data from files.
  std::string name;

  sf::Sprite sprite;

  sf::Texture texture;

  //trail line
  int trail_points = 10000;

  sf::VertexArray trail;

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

  //central body influencing the particle parameters
  double M;
  double a;

  //window parameters
  float width;
  float height;
  float stretch;





  //Memberfunctions

  //convert radians to degrees
  double radtodeg(double alpha);

  //rotate the sprite to the travel direction (vx,vy). this is just graphics, no physics.
  void rotate_to_velocity();

  //Equation of motion ODE operators dv^i/dt = f_vi(x,y,vx,vy)
  double f_vx(double dt, double x_new, double y_new, double vx_new, double vy_new);
  double f_vy(double dt, double x_new, double y_new, double vx_new, double vy_new);


public:

  //Constructors
  particle();

  particle(std::string name_in, double x_in, double y_in, double vx_in, double vy_in, double M_in, double a_in, float width_in, float height_in, float stretch_in, float A, float B, float C, float D, bool face_forward);

  //Membervariables


  //Memberfunctions

  //in case you have already allocated an instance but want to initialize like with the constructor, use this
  void initialize(std::string name_in, double x_in, double y_in, double vx_in, double vy_in, double M_in, double a_in, float width_in, float height_in, float stretch_in, float A, float B, float C, float D, bool face_forward);


  //transform world coordinates x,y to screen coordinates.
  //the world is [A,B]x[C,D] and the screen is [0,width*stretch]x[0,height*stretch] with origin top left corner.
  float screen_x(double x,float A,float B,float C,float D);
  float screen_y(double y,float A,float B,float C,float D);

  //retrieve the sprite for rendering
  sf::Sprite& getSprite();

  //retrieve the trail for rendering
  sf::VertexArray& getTrail();

  //get the current Lorentzfactor
  double getLorentzfactor();

  //can be used while stationary. this finds dt/dtau seeing what evolving by one dt would yield
  double calcgetLorentzfactor(double dt);

  //get if we were swallowed
  bool getSwallowed();

  //spacetime metric (independent of t and vt = 1)
  double g(double x, double y, double vx, double vy);

  //get the spatial speed. From g(v,v) < 0 with v = (1,vx,vy) we get g_ijv^iv^j / -g_00 < 1. The spatical speed is sqrt(g_ijv^iv^j / -g_00).
  double spatial_speed(double vx, double vy);
  double spatial_speed();

  //evolve the trajectory by time dt and update the propertime. optionally always rotate the sprite in direction of travel.
  void evolve(double dt, float A, float B, float C, float D, bool face_forward);

  //check if we are colliding with another particle
  bool checkCollision(particle& other_particle);

  //let the particle explode.
  void explode(float A, float B, float C, float D);

  //make the particle invisible in order to do as if it stopped existing
  void make_invisible();

  //manually set vx,vy by an angle and modulus
  void set_chart_velocity(double modulus, double angle, bool face_forward);

  //change the components vx,vy leaving either their polar angle or spatial speed constant
  void rotate_chart_velocity(double delta_angle, bool face_forward);
  void stretch_chart_velocity(double delta_modulus, bool face_forward);

  //retrieve modulus and angle of (vx,vy) in the chart (not the physical length)
  double get_chart_velocity_modulus();
  double get_chart_velocity_angle();

};

#endif //PARTICLE_H
