#include "particle.h"

//PARTICLE CLASS

//private Memberfunctions

//Equation of motion ODE operators dv^i/dt = f_vi(x,y,vx,vy)

double particle::f_vx(double dt, double x_new, double y_new, double vx_new, double vy_new) {
  //approximate the propertime interval to the new point
  double dtau = dt*0.5*(sqrt(-g(x,y,vx,vy)) + sqrt(-g(x_new,y_new,vx_new,vy_new)));

  //approximate the Lorentzfactor at the new point
  double ut = dt/dtau;

  double fx_new = -(x_new+10)*0.1/pow(sqrt((pow((x_new+10),2)+pow(y_new+10,2))),3);
  double fy_new = -(y_new+10)*0.1/pow(sqrt((pow((x_new+10),2)+pow(y_new+10,2))),3);

  //find the force accelaration part of the equations of motion (I am not sure if how to do this correctly, so now it is done very naively. If M=0,a=0 then the particle will do a Kepler motion)
  double Fx = 0; //fx_new; //fx_new-fx_new*vx_new-fy_new*vy_new;

  return Fx + (M*(2*pow(a,5)*(-2*vx_new*vy_new*x_new*(pow(x_new,2) - 3*pow(y_new,2)) + pow(vy_new,2)*y_new*(-3*pow(x_new,2) + pow(y_new,2)) + pow(vx_new,2)*(3*pow(x_new,2)*y_new - pow(y_new,3))) + 2*pow(a,4)*(-(pow(vy_new,2)*x_new*(pow(x_new,2) - 3*pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + M*((vx_new - vy_new)*(vx_new + vy_new)*pow(x_new,3) + 6*vx_new*vy_new*pow(x_new,2)*y_new - 3*(vx_new - vy_new)*(vx_new + vy_new)*x_new*pow(y_new,2) - 2*vx_new*vy_new*pow(y_new,3)) + pow(vx_new,3)*(pow(x_new,4) - pow(y_new,4)) + pow(vx_new,2)*x_new*(4*vy_new*y_new*(pow(x_new,2) + pow(y_new,2)) + (pow(x_new,2) - 3*pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + vx_new*vy_new*(-2*y_new*(-3*pow(x_new,2) + pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + vy_new*(-pow(x_new,4) + pow(y_new,4)))) - pow(a,2)*(pow(x_new,2) + pow(y_new,2))*(-3*pow(vy_new,2)*x_new*(pow(x_new,2) - 3*pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + 4*pow(vx_new,3)*(pow(x_new,4) - pow(y_new,4)) + pow(vx_new,2)*x_new*(16*vy_new*y_new*(pow(x_new,2) + pow(y_new,2)) + 3*(pow(x_new,2) - 3*pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + 2*vx_new*vy_new*(-3*y_new*(-3*pow(x_new,2) + pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + 2*vy_new*(-pow(x_new,4) + pow(y_new,4))) + 2*M*((1 + 4*pow(vx_new,2) - pow(vy_new,2))*pow(x_new,3) + vx_new*(-2 - pow(vx_new,2) + pow(vy_new,2))*pow(y_new,2)*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + x_new*y_new*((1 - pow(vx_new,2) + 4*pow(vy_new,2))*y_new + 4*(1 + pow(vx_new,2))*vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + vx_new*pow(x_new,2)*(10*vy_new*y_new + (2 + pow(vx_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) - pow(vy_new,2)*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))))) + pow(pow(x_new,2) + pow(y_new,2),2)*(-(x_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))*((1 + 2*pow(vy_new,2))*pow(x_new,2) - (-1 + pow(vy_new,2))*pow(y_new,2))) + 2*pow(vx_new,3)*(pow(x_new,4) - pow(y_new,4)) + pow(vx_new,2)*(8*vy_new*x_new*y_new*(pow(x_new,2) + pow(y_new,2)) + 3*pow(x_new,3)*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + 2*vx_new*vy_new*(y_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))*(4*pow(x_new,2) + pow(y_new,2)) + vy_new*(-pow(x_new,4) + pow(y_new,4))) + 2*M*((1 + 3*pow(vx_new,2))*pow(x_new,3) + vx_new*pow(x_new,2)*(4*vy_new*y_new + (3 + pow(vx_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + x_new*y_new*((1 + 2*pow(vx_new,2) + pow(vy_new,2))*y_new + 2*(1 + pow(vx_new,2))*vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + vx_new*pow(y_new,2)*(2*vy_new*y_new + sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + pow(vy_new,2)*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))))) + 2*pow(a,3)*(M*(vx_new*y_new*(-2*(2 + pow(vx_new,2))*pow(x_new,3) - 2*(2 + pow(vx_new,2))*x_new*pow(y_new,2) - 3*vx_new*pow(x_new,2)*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + vx_new*pow(y_new,2)*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + pow(vy_new,2)*y_new*(2*vx_new*x_new*(pow(x_new,2) + pow(y_new,2)) + (3*pow(x_new,2) - pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + 2*vy_new*(vx_new*pow(x_new,3)*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) - 3*vx_new*x_new*pow(y_new,2)*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + (1 + pow(vx_new,2))*(pow(x_new,4) - pow(y_new,4)))) + 2*(pow(x_new,2) + pow(y_new,2))*(-(pow(vy_new,2)*y_new*(-3*pow(x_new,2) + pow(y_new,2))) - pow(vx_new,3)*x_new*y_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + vx_new*vy_new*x_new*(2*pow(x_new,2) + y_new*(-6*y_new + vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)))) + pow(vx_new,2)*(pow(y_new,2)*(y_new - vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + pow(x_new,2)*(-3*y_new + vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)))))) - 2*a*(pow(x_new,2) + pow(y_new,2))*(M*(pow(vy_new,2)*y_new*(2*vx_new*x_new*(pow(x_new,2) + pow(y_new,2)) + (2*pow(x_new,2) - pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) - y_new*(4*vx_new*x_new*(pow(x_new,2) + pow(y_new,2)) + 2*pow(vx_new,3)*x_new*(pow(x_new,2) + pow(y_new,2)) + (pow(x_new,2) + pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + pow(vx_new,2)*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))*(5*pow(x_new,2) + 2*pow(y_new,2))) + 2*vy_new*(2*vx_new*pow(x_new,3)*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) - vx_new*x_new*pow(y_new,2)*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + (1 + pow(vx_new,2))*(pow(x_new,4) - pow(y_new,4)))) + (pow(x_new,2) + pow(y_new,2))*(-3*pow(vx_new,3)*x_new*y_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + vy_new*(-((pow(x_new,2) + pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + vy_new*(3*pow(x_new,2)*y_new - pow(y_new,3))) + pow(vx_new,2)*(pow(y_new,2)*(y_new - 3*vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) - 3*pow(x_new,2)*(y_new - vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)))) + vx_new*vy_new*x_new*(2*pow(x_new,2) + 3*y_new*(-2*y_new + vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))))))))/(pow(pow(x_new,2) + pow(y_new,2),3)*pow(-pow(a,2) + pow(x_new,2) + pow(y_new,2),2));
}

double particle::f_vy(double dt, double x_new, double y_new, double vx_new, double vy_new) {
  //approxmate the propertime interval to the new point
  double dtau = dt*0.5*(sqrt(-g(x,y,vx,vy)) + sqrt(-g(x_new,y_new,vx_new,vy_new)));

  //approximate the Lorentzfactor at the new point
  double ut = dt/dtau;

  double fx_new = -(x_new+10)*0.1/pow(sqrt((pow((x_new+10),2)+pow(y_new+10,2))),3);
  double fy_new = -(y_new+10)*0.1/pow(sqrt((pow((x_new+10),2)+pow(y_new+10,2))),3);

  //find the force accelaration part of the equations of motion (I am not sure if how to do this correctly, so now it is done very naively. If M=0,a=0 then the particle will do a Kepler motion)
  double Fy = 0; //fy_new; //1/ut*fy_new-fx_new*vx_new-fy_new*vy_new;

  return Fy + (M*(-2*pow(a,5)*(-(pow(vy_new,2)*x_new*(pow(x_new,2) - 3*pow(y_new,2))) - 2*vx_new*vy_new*y_new*(-3*pow(x_new,2) + pow(y_new,2)) + pow(vx_new,2)*(pow(x_new,3) - 3*x_new*pow(y_new,2))) - 2*pow(a,4)*(M*(2*vx_new*vy_new*pow(x_new,3) - 3*(vx_new - vy_new)*(vx_new + vy_new)*pow(x_new,2)*y_new - 6*vx_new*vy_new*x_new*pow(y_new,2) + (vx_new - vy_new)*(vx_new + vy_new)*pow(y_new,3)) - 2*vx_new*vy_new*x_new*(2*vy_new*y_new*(pow(x_new,2) + pow(y_new,2)) - (pow(x_new,2) - 3*pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + pow(vy_new,2)*(-(y_new*(-3*pow(x_new,2) + pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + vy_new*(pow(x_new,4) - pow(y_new,4))) + pow(vx_new,2)*(y_new*(-3*pow(x_new,2) + pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + vy_new*(-pow(x_new,4) + pow(y_new,4)))) - pow(a,2)*(pow(x_new,2) + pow(y_new,2))*(2*M*y_new*(pow(x_new,2) + pow(y_new,2)) + 4*M*vy_new*(-pow(x_new,2) + pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) - 2*pow(vy_new,3)*(x_new - y_new)*(x_new + y_new)*(2*pow(x_new,2) + 2*pow(y_new,2) + M*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + pow(vy_new,2)*(3*y_new*(-3*pow(x_new,2) + pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + M*(-2*pow(x_new,2)*y_new + 8*pow(y_new,3))) + 2*vx_new*x_new*(10*M*vy_new*pow(y_new,2) + 4*M*y_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) - 3*vy_new*(pow(x_new,2) - 3*pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + 4*pow(vy_new,2)*y_new*(2*pow(x_new,2) + 2*pow(y_new,2) + M*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)))) + pow(vx_new,2)*(-2*M*y_new*(-4*pow(x_new,2) + pow(y_new,2)) - 3*y_new*(-3*pow(x_new,2) + pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + 2*vy_new*(x_new - y_new)*(x_new + y_new)*(2*pow(x_new,2) + 2*pow(y_new,2) + M*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))))) + pow(pow(x_new,2) + pow(y_new,2),2)*(-2*pow(vy_new,3)*pow(x_new,4) + 2*pow(vy_new,3)*pow(y_new,4) - pow(x_new,2)*y_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) - pow(y_new,3)*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + 3*pow(vy_new,2)*pow(y_new,3)*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + 2*vx_new*vy_new*x_new*(4*vy_new*y_new*(pow(x_new,2) + pow(y_new,2)) + sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))*(pow(x_new,2) + 4*pow(y_new,2))) + pow(vx_new,2)*(y_new*(pow(x_new,2) - 2*pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + 2*vy_new*(pow(x_new,4) - pow(y_new,4))) + 2*M*(pow(vx_new,2)*pow(x_new,2)*(y_new + vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + pow(x_new,2)*(y_new + 2*pow(vy_new,2)*y_new + vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + pow(y_new,2)*(y_new + 3*pow(vy_new,2)*y_new + vy_new*(3 + pow(vy_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + 2*vx_new*x_new*(y_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + pow(vy_new,2)*y_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + vy_new*(pow(x_new,2) + 2*pow(y_new,2))))) - 2*a*(pow(x_new,2) + pow(y_new,2))*(M*(pow(vx_new,2)*x_new*(-2*vy_new*y_new*(pow(x_new,2) + pow(y_new,2)) + (pow(x_new,2) - 2*pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + x_new*(4*vy_new*y_new*(pow(x_new,2) + pow(y_new,2)) + 2*pow(vy_new,3)*y_new*(pow(x_new,2) + pow(y_new,2)) + (pow(x_new,2) + pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + pow(vy_new,2)*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))*(2*pow(x_new,2) + 5*pow(y_new,2))) + 2*vx_new*(vy_new*pow(x_new,2)*y_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) - 2*vy_new*pow(y_new,3)*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + (1 + pow(vy_new,2))*(pow(x_new,4) - pow(y_new,4)))) + (pow(x_new,2) + pow(y_new,2))*(vx_new*(3*pow(vy_new,2)*(x_new - y_new)*(x_new + y_new)*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + (pow(x_new,2) + pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + vy_new*(6*pow(x_new,2)*y_new - 2*pow(y_new,3))) + pow(vx_new,2)*x_new*(pow(x_new,2) - 3*y_new*(y_new + vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)))) + pow(vy_new,2)*x_new*(-pow(x_new,2) + 3*y_new*(y_new + vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)))))) + 2*pow(a,3)*(2*(pow(x_new,2) + pow(y_new,2))*(pow(vx_new,2)*x_new*(pow(x_new,2) - y_new*(3*y_new + vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)))) + pow(vy_new,2)*x_new*(-pow(x_new,2) + y_new*(3*y_new + vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)))) + vx_new*vy_new*(-(pow(y_new,2)*(2*y_new + vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)))) + pow(x_new,2)*(6*y_new + vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))))) + M*(pow(vx_new,2)*x_new*(-2*vy_new*y_new*(pow(x_new,2) + pow(y_new,2)) + (pow(x_new,2) - 3*pow(y_new,2))*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + 2*vx_new*(3*vy_new*pow(x_new,2)*y_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) - vy_new*pow(y_new,3)*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2)) + (1 + pow(vy_new,2))*(pow(x_new,4) - pow(y_new,4))) + vy_new*x_new*(pow(x_new,2)*(2*(2 + pow(vy_new,2))*y_new - vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))) + pow(y_new,2)*(2*(2 + pow(vy_new,2))*y_new + 3*vy_new*sqrt(-pow(a,2) + pow(x_new,2) + pow(y_new,2))))))))/(pow(pow(x_new,2) + pow(y_new,2),3)*pow(-pow(a,2) + pow(x_new,2) + pow(y_new,2),2));
}


//convert radians to degrees
double particle::radtodeg(double alpha) {
  return alpha*180/pi;
}

//rotate the sprite to the travel direction (vx,vy). this is just graphics, no physics.
void particle::rotate_to_velocity() {

	//angle to rotate to. in degrees. it's supposed to be in negative direction, starting at the north pole of the unit circle, from 0 to 360.
	float angle = 0;

	//caputre the bad case
	if (vx == 0 && vy == 0) {
    //set the sprite rotation to face the black hole as this is the direction we will fall at a speed of zero
    if (x < 0 && y == 0) {
      sprite.setRotation(90);
    }
    else if (x > 0 && y == 0) {
      sprite.setRotation(270);
    }
    else if (x == 0 && y > 0) {
      sprite.setRotation(180);
    }
    else {
      sprite.setRotation(0);
    }

	}
	else {
		//find the angle in radians. This is w.r.t. the normal unit circle and in [-pi,pi].
		angle = atan2(vy,vx);

		//transform it to the negative unit circle starting in the norhpole. this was determined by drawing [-pi,pi] has to be mapped to this negative unit circle.
		if (angle < pi/2) {
			angle = pi/2 - angle;
		}
		else {
			angle = 2.5*pi - angle;
		}

    //set the sprite rotation to the calculated angle
  	sprite.setRotation(radtodeg(angle));

	}

}

//Constructors
particle::particle():trail(sf::LineStrip, trail_points) {
	currentworkingdirectory = get_current_dir_name();

	//propertime
	tau = 0;

  //make the whole trail white
  for (int i = 0; i < trail.getVertexCount(); i++) {
    trail[i].color = sf::Color::White;
  }

	//Lorentzfactor
	Lorentzfactor = 1;
}


particle::particle(std::string name_in, double x_in, double y_in, double vx_in, double vy_in, double M_in, double a_in, float width_in, float height_in, float stretch_in,float A, float B, float C, float D, bool face_forward = false):trail(sf::LineStrip, trail_points) {

  currentworkingdirectory = get_current_dir_name();

  name = name_in;

	//physical initial coordinates and velocities.
	x = x_in;
	y = y_in;
	vx = vx_in;
	vy = vy_in;

  //check if we are in the black hole
  if (sqrt(x*x + y*y - a*a) <= M + sqrt(M*M-a*a)) {
    swallowed = true;
  }
  else {
    swallowed = false;
  }

	//propertime
	tau = 0;

	//Lorentzfactor
	Lorentzfactor = 1;

	//central body parameters
	M = M_in;
	a = a_in;

	//window parameters
	width = width_in;
	height = height_in;
	stretch = stretch_in;



	//load png
	texture.loadFromFile(currentworkingdirectory + "/Textures/T_" + name+".png");
	//make it look smooth
	texture.setSmooth(true);
	//assign the texture
	sprite.setTexture(texture);
	//change the sprite origin to the center
	sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
	//set the position
	sprite.setPosition(screen_x(x,A,B,C,D),screen_y(y,A,B,C,D));
	//set scale according to the window size and according to the world size. A scale of 1 corresponds to a 2560x1440 window and a world of [-10,10]x[-5,6.25].
	sprite.setScale(20/(B-A)*stretch, 11.25/(D-C)*stretch);

	//if so desired, rotate the sprite to face the direction of travel
	if (face_forward) {
		rotate_to_velocity();
	}

  //make the whole trail white
  for (int i = 0; i < trail.getVertexCount(); i++) {
    trail[i].color = sf::Color::White;
  }

  //set the whole trail to the particle position
  for (int i = 0; i < trail.getVertexCount(); i++) {
    trail[i].position = sprite.getPosition();
  }

}

//Memberfunctions

//in case you have already allocated an instance but want to initialize like with the constructor, use this
void particle::initialize(std::string name_in, double x_in, double y_in, double vx_in, double vy_in, double M_in, double a_in, float width_in, float height_in, float stretch_in, float A, float B, float C, float D, bool face_forward = false) {
	name = name_in;

	//physical initial coordinates and velocities.
	x = x_in;
	y = y_in;
	vx = vx_in;
	vy = vy_in;

  //check if we are in the black hole
  if (sqrt(x*x + y*y - a*a) <= M + sqrt(M*M-a*a)) {
    swallowed = true;
  }
  else {
    swallowed = false;
  }

	//propertime
	tau = 0;

	//Lorentzfactor
	Lorentzfactor = 1;

	//central body parameters
	M = M_in;
	a = a_in;

	//window parameters
	width = width_in;
	height = height_in;
	stretch = stretch_in;



	//load png
	texture.loadFromFile(currentworkingdirectory + "/Textures/T_" + name+".png");
	//make it look smooth
	texture.setSmooth(true);
	//assign the texture
	sprite.setTexture(texture, true);
	//change the sprite origin to the center
	sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
	//set the position
	sprite.setPosition(screen_x(x,A,B,C,D),screen_y(y,A,B,C,D));
  //set scale according to the window size and according to the world size. A scale of 1 corresponds to a 2560x1440 window and a world of [-10,10]x[-5,6.25].
	sprite.setScale(20/(B-A)*stretch, 11.25/(D-C)*stretch);

	//if so desired, rotate the sprite to face the direction of travel
	if (face_forward) {
		rotate_to_velocity();
	}

  //make the whole trail white
  for (int i = 0; i < trail.getVertexCount(); i++) {
    trail[i].color = sf::Color::White;
  }

  //set the whole trail to the particle position
  for (int i = 0; i < trail.getVertexCount(); i++) {
    trail[i].position = sprite.getPosition();
  }

}

//transform world coordinates x,y to screen coordinates
//the world is [A,B]x[C,D] and the screen is [0,width*stretch]x[0,height*stretch] with origin top left corner.
float particle::screen_x(double x, float A, float B, float C, float D) {
	return (x-A)/(B-A)*width;
}

float particle::screen_y(double y, float A, float B, float C, float D) {
	return (D-y)/(D-C)*height;
}

//retrieve the sprite for rendering
sf::Sprite& particle::getSprite() {
	return sprite;
}

//retrieve the trail for rendering
sf::VertexArray& particle::getTrail() {
  return trail;
}

//return the Lorentzfactor
double particle::getLorentzfactor() {
	return Lorentzfactor;
}

//can be used while stationary. this finds dt/dtau seeing what evolving by one dt would yield
double particle::calcgetLorentzfactor(double dt)  {
  //Dormand-Prince fifth order integration (with non adaptive step size), to find where we would land if the did one time step
  double k1_x = dt*vx;
  double k1_y = dt*vy;
  double k1_vx = dt*f_vx(dt,x,y,vx,vy);
  double k1_vy = dt*f_vy(dt,x,y,vx,vy);

  double k2_x = dt*(vx+1.0/5*k1_vx);
  double k2_y = dt*(vy+1.0/5*k1_vy);
  double k2_vx = dt*f_vx(dt,x+1.0/5*k1_x,y+1.0/5*k1_y,vx+1.0/5*k1_vx,vy+1.0/5*k1_vy);
  double k2_vy = dt*f_vy(dt,x+1.0/5*k1_x,y+1.0/5*k1_y,vx+1.0/5*k1_vx,vy+1.0/5*k1_vy);

  double k3_x = dt*(vx+3.0/40*k1_vx+9.0/40*k2_vx);
  double k3_y = dt*(vy+3.0/40*k1_vy+9.0/40*k2_vy);
  double k3_vx = dt*f_vx(dt,x+3.0/40*k1_x+9.0/40*k2_x,y+3.0/40*k1_y+9.0/40*k2_y,vx+3.0/40*k1_vx+9.0/40*k2_vx,vy+3.0/40*k1_vy+9.0/40*k2_vy);
  double k3_vy = dt*f_vy(dt,x+3.0/40*k1_x+9.0/40*k2_x,y+3.0/40*k1_y+9.0/40*k2_y,vx+3.0/40*k1_vx+9.0/40*k2_vx,vy+3.0/40*k1_vy+9.0/40*k2_vy);

  double k4_x = dt*(vx+44.0/45*k1_vx-56.0/15*k2_vx+32.0/9*k3_vx);
  double k4_y = dt*(vy+44.0/45*k1_vy-56.0/15*k2_vy+32.0/9*k3_vy);
  double k4_vx = dt*f_vx(dt,x+44.0/45*k1_x-56.0/15*k2_x+32.0/9*k3_x,y+44.0/45*k1_y-56.0/15*k2_y+32.0/9*k3_y,vx+44.0/45*k1_vx-56.0/15*k2_vx+32.0/9*k3_vx,vy+44.0/45*k1_vy-56.0/15*k2_vy+32.0/9*k3_vy);
  double k4_vy = dt*f_vy(dt,x+44.0/45*k1_x-56.0/15*k2_x+32.0/9*k3_x,y+44.0/45*k1_y-56.0/15*k2_y+32.0/9*k3_y,vx+44.0/45*k1_vx-56.0/15*k2_vx+32.0/9*k3_vx,vy+44.0/45*k1_vy-56.0/15*k2_vy+32.0/9*k3_vy);

  double k5_x = dt*(vx+19372.0/6561*k1_vx-25360.0/2187*k2_vx+64448.0/6561*k3_vx-212.0/729*k4_vx);
  double k5_y = dt*(vy+19372.0/6561*k1_vy-25360.0/2187*k2_vy+64448.0/6561*k3_vy-212.0/729*k4_vy);
  double k5_vx = dt*f_vx(dt,x+19372.0/6561*k1_x-25360.0/2187*k2_x+64448.0/6561*k3_x-212.0/729*k4_x,y+19372.0/6561*k1_y-25360.0/2187*k2_y+64448.0/6561*k3_y-212.0/729*k4_y,vx+19372.0/6561*k1_vx-25360.0/2187*k2_vx+64448.0/6561*k3_vx-212.0/729*k4_vx,vy+19372.0/6561*k1_vy-25360.0/2187*k2_vy+64448.0/6561*k3_vy-212.0/729*k4_vy);
  double k5_vy = dt*f_vy(dt,x+19372.0/6561*k1_x-25360.0/2187*k2_x+64448.0/6561*k3_x-212.0/729*k4_x,y+19372.0/6561*k1_y-25360.0/2187*k2_y+64448.0/6561*k3_y-212.0/729*k4_y,vx+19372.0/6561*k1_vx-25360.0/2187*k2_vx+64448.0/6561*k3_vx-212.0/729*k4_vx,vy+19372.0/6561*k1_vy-25360.0/2187*k2_vy+64448.0/6561*k3_vy-212.0/729*k4_vy);

  double k6_x = dt*(vx+9017.0/3168*k1_vx-355.0/33*k2_vx+46732.0/5247*k3_vx+49.0/176*k4_vx-5103.0/18656*k5_vx);
  double k6_y = dt*(vy+9017.0/3168*k1_vy-355.0/33*k2_vy+46732.0/5247*k3_vy+49.0/176*k4_vy-5103.0/18656*k5_vy);
  double k6_vx = dt*f_vx(dt,x+9017.0/3168*k1_x-355.0/33*k2_x+46732.0/5247*k3_x+49.0/176*k4_x-5103.0/18656*k5_x,y+9017.0/3168*k1_y-355.0/33*k2_y+46732.0/5247*k3_y+49.0/176*k4_y-5103.0/18656*k5_y,vx+9017.0/3168*k1_vx-355.0/33*k2_vx+46732.0/5247*k3_vx+49.0/176*k4_vx-5103.0/18656*k5_vx,vy+9017.0/3168*k1_vy-355.0/33*k2_vy+46732.0/5247*k3_vy+49.0/176*k4_vy-5103.0/18656*k5_vy);
  double k6_vy = dt*f_vy(dt,x+9017.0/3168*k1_x-355.0/33*k2_x+46732.0/5247*k3_x+49.0/176*k4_x-5103.0/18656*k5_x,y+9017.0/3168*k1_y-355.0/33*k2_y+46732.0/5247*k3_y+49.0/176*k4_y-5103.0/18656*k5_y,vx+9017.0/3168*k1_vx-355.0/33*k2_vx+46732.0/5247*k3_vx+49.0/176*k4_vx-5103.0/18656*k5_vx,vy+9017.0/3168*k1_vy-355.0/33*k2_vy+46732.0/5247*k3_vy+49.0/176*k4_vy-5103.0/18656*k5_vy);

  double x_new = x + (35.0/384*k1_x + 500.0/1113*k3_x + 125.0/192*k4_x - 2187.0/6784*k5_x + 11.0/84*k6_x);
  double y_new = y + (35.0/384*k1_y + 500.0/1113*k3_y + 125.0/192*k4_y - 2187.0/6784*k5_y + 11.0/84*k6_y);
  double vx_new = vx + (35.0/384*k1_vx + 500.0/1113*k3_vx + 125.0/192*k4_vx - 2187.0/6784*k5_vx + 11.0/84*k6_vx);
  double vy_new = vy + (35.0/384*k1_vy + 500.0/1113*k3_vy + 125.0/192*k4_vy - 2187.0/6784*k5_vy + 11.0/84*k6_vy);

  //check if we had entered the black hole
  if (sqrt(x_new*x_new + y_new*y_new - a*a) <= M + sqrt(M*M-a*a)) {
    return -1;
  }
  else {
    //update the propertime by approximating the arclength integral
    double dtau = dt*0.5*(sqrt(-g(x,y,vx,vy)) + sqrt(-g(x_new,y_new,vx_new,vy_new)));

    //the would-be Lorentzfactor
    return dt/dtau;
  }

}

//get if we were swallowed
bool particle::getSwallowed() {
  return swallowed;
}

//get the spatial speed. From g(v,v) < 0 with v = (1,vx,vy) we get g_ijv^iv^j / -g_00 - g_0kv^k - g_k0v^k < 1. The spatical speed is sqrt(g_ijv^iv^j / -g_00 - g_0kv^k - g_k0v^k).
double particle::spatial_speed(double vx, double vy) {
	return sqrt((4*a*M*(-(vy*x) + vx*y)*(vx*x + vy*y)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) - 2*pow(a,2)*M*(vy*(-x + y) + vx*(x + y))*(vx*(x - y) + vy*(x + y)) + (pow(x,2) + pow(y,2))*(2*M*pow(vx*x + vy*y,2) + (pow(vx,2) + pow(vy,2))*(pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))))/((pow(x,2) + pow(y,2))*(4*a*M*(vy*x - vx*y) + (pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) - 2*M*(pow(x,2) + pow(y,2) + 2*vx*x*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + 2*vy*y*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))))));
}

double particle::spatial_speed() {
  return sqrt((4*a*M*(-(vy*x) + vx*y)*(vx*x + vy*y)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) - 2*pow(a,2)*M*(vy*(-x + y) + vx*(x + y))*(vx*(x - y) + vy*(x + y)) + (pow(x,2) + pow(y,2))*(2*M*pow(vx*x + vy*y,2) + (pow(vx,2) + pow(vy,2))*(pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))))/((pow(x,2) + pow(y,2))*(4*a*M*(vy*x - vx*y) + (pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) - 2*M*(pow(x,2) + pow(y,2) + 2*vx*x*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + 2*vy*y*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))))));
}

//spacetime metric (independent of t and vt = 1).
double particle::g(double x, double y, double vx, double vy) {
	return -1 + pow(vy,2) + (-2*pow(a,2)*M*(vy*(-x + y) + vx*(x + y))*(vx*(x - y) + vy*(x + y)) - 4*a*M*(vy*x - vx*y)*(pow(x,2) + vx*x*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + y*(y + vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)))) + (pow(x,2) + pow(y,2))*(pow(vx,2)*(pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + 2*M*((1 + pow(vx,2))*pow(x,2) + 2*vx*x*(vy*y + sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + y*(y + pow(vy,2)*y + 2*vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))))))/(pow(pow(x,2) + pow(y,2),2)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)));
}

//evolve the trajectory by time dt and update the propertime
void particle::evolve(double dt, float A, float B, float C, float D, bool face_forward = false) {

  //only if we have not been swallowed evolve the particle
  if (!swallowed) {

    //update x,y,vx,vy according to the central body and GR equations of motion.

    //Dormand-Prince fifth order integration (with non adaptive step size)
    double k1_x = dt*vx;
    double k1_y = dt*vy;
    double k1_vx = dt*f_vx(dt,x,y,vx,vy);
    double k1_vy = dt*f_vy(dt,x,y,vx,vy);

    double k2_x = dt*(vx+1.0/5*k1_vx);
    double k2_y = dt*(vy+1.0/5*k1_vy);
    double k2_vx = dt*f_vx(dt,x+1.0/5*k1_x,y+1.0/5*k1_y,vx+1.0/5*k1_vx,vy+1.0/5*k1_vy);
    double k2_vy = dt*f_vy(dt,x+1.0/5*k1_x,y+1.0/5*k1_y,vx+1.0/5*k1_vx,vy+1.0/5*k1_vy);

    double k3_x = dt*(vx+3.0/40*k1_vx+9.0/40*k2_vx);
    double k3_y = dt*(vy+3.0/40*k1_vy+9.0/40*k2_vy);
    double k3_vx = dt*f_vx(dt,x+3.0/40*k1_x+9.0/40*k2_x,y+3.0/40*k1_y+9.0/40*k2_y,vx+3.0/40*k1_vx+9.0/40*k2_vx,vy+3.0/40*k1_vy+9.0/40*k2_vy);
    double k3_vy = dt*f_vy(dt,x+3.0/40*k1_x+9.0/40*k2_x,y+3.0/40*k1_y+9.0/40*k2_y,vx+3.0/40*k1_vx+9.0/40*k2_vx,vy+3.0/40*k1_vy+9.0/40*k2_vy);

    double k4_x = dt*(vx+44.0/45*k1_vx-56.0/15*k2_vx+32.0/9*k3_vx);
    double k4_y = dt*(vy+44.0/45*k1_vy-56.0/15*k2_vy+32.0/9*k3_vy);
    double k4_vx = dt*f_vx(dt,x+44.0/45*k1_x-56.0/15*k2_x+32.0/9*k3_x,y+44.0/45*k1_y-56.0/15*k2_y+32.0/9*k3_y,vx+44.0/45*k1_vx-56.0/15*k2_vx+32.0/9*k3_vx,vy+44.0/45*k1_vy-56.0/15*k2_vy+32.0/9*k3_vy);
    double k4_vy = dt*f_vy(dt,x+44.0/45*k1_x-56.0/15*k2_x+32.0/9*k3_x,y+44.0/45*k1_y-56.0/15*k2_y+32.0/9*k3_y,vx+44.0/45*k1_vx-56.0/15*k2_vx+32.0/9*k3_vx,vy+44.0/45*k1_vy-56.0/15*k2_vy+32.0/9*k3_vy);

    double k5_x = dt*(vx+19372.0/6561*k1_vx-25360.0/2187*k2_vx+64448.0/6561*k3_vx-212.0/729*k4_vx);
    double k5_y = dt*(vy+19372.0/6561*k1_vy-25360.0/2187*k2_vy+64448.0/6561*k3_vy-212.0/729*k4_vy);
    double k5_vx = dt*f_vx(dt,x+19372.0/6561*k1_x-25360.0/2187*k2_x+64448.0/6561*k3_x-212.0/729*k4_x,y+19372.0/6561*k1_y-25360.0/2187*k2_y+64448.0/6561*k3_y-212.0/729*k4_y,vx+19372.0/6561*k1_vx-25360.0/2187*k2_vx+64448.0/6561*k3_vx-212.0/729*k4_vx,vy+19372.0/6561*k1_vy-25360.0/2187*k2_vy+64448.0/6561*k3_vy-212.0/729*k4_vy);
    double k5_vy = dt*f_vy(dt,x+19372.0/6561*k1_x-25360.0/2187*k2_x+64448.0/6561*k3_x-212.0/729*k4_x,y+19372.0/6561*k1_y-25360.0/2187*k2_y+64448.0/6561*k3_y-212.0/729*k4_y,vx+19372.0/6561*k1_vx-25360.0/2187*k2_vx+64448.0/6561*k3_vx-212.0/729*k4_vx,vy+19372.0/6561*k1_vy-25360.0/2187*k2_vy+64448.0/6561*k3_vy-212.0/729*k4_vy);

    double k6_x = dt*(vx+9017.0/3168*k1_vx-355.0/33*k2_vx+46732.0/5247*k3_vx+49.0/176*k4_vx-5103.0/18656*k5_vx);
    double k6_y = dt*(vy+9017.0/3168*k1_vy-355.0/33*k2_vy+46732.0/5247*k3_vy+49.0/176*k4_vy-5103.0/18656*k5_vy);
    double k6_vx = dt*f_vx(dt,x+9017.0/3168*k1_x-355.0/33*k2_x+46732.0/5247*k3_x+49.0/176*k4_x-5103.0/18656*k5_x,y+9017.0/3168*k1_y-355.0/33*k2_y+46732.0/5247*k3_y+49.0/176*k4_y-5103.0/18656*k5_y,vx+9017.0/3168*k1_vx-355.0/33*k2_vx+46732.0/5247*k3_vx+49.0/176*k4_vx-5103.0/18656*k5_vx,vy+9017.0/3168*k1_vy-355.0/33*k2_vy+46732.0/5247*k3_vy+49.0/176*k4_vy-5103.0/18656*k5_vy);
    double k6_vy = dt*f_vy(dt,x+9017.0/3168*k1_x-355.0/33*k2_x+46732.0/5247*k3_x+49.0/176*k4_x-5103.0/18656*k5_x,y+9017.0/3168*k1_y-355.0/33*k2_y+46732.0/5247*k3_y+49.0/176*k4_y-5103.0/18656*k5_y,vx+9017.0/3168*k1_vx-355.0/33*k2_vx+46732.0/5247*k3_vx+49.0/176*k4_vx-5103.0/18656*k5_vx,vy+9017.0/3168*k1_vy-355.0/33*k2_vy+46732.0/5247*k3_vy+49.0/176*k4_vy-5103.0/18656*k5_vy);

    double x_new = x + (35.0/384*k1_x + 500.0/1113*k3_x + 125.0/192*k4_x - 2187.0/6784*k5_x + 11.0/84*k6_x);
    double y_new = y + (35.0/384*k1_y + 500.0/1113*k3_y + 125.0/192*k4_y - 2187.0/6784*k5_y + 11.0/84*k6_y);
    double vx_new = vx + (35.0/384*k1_vx + 500.0/1113*k3_vx + 125.0/192*k4_vx - 2187.0/6784*k5_vx + 11.0/84*k6_vx);
    double vy_new = vy + (35.0/384*k1_vy + 500.0/1113*k3_vy + 125.0/192*k4_vy - 2187.0/6784*k5_vy + 11.0/84*k6_vy);



    //check if we have entered the black hole
    if (sqrt(x_new*x_new + y_new*y_new - a*a) <= M + sqrt(M*M-a*a)) {
      swallowed = true;

      make_invisible();
    }

    //if we are outsidethe black hole  update the proper time, Lorentzfactor, position of the sprite and the trail
    if (!swallowed) {
      //update the propertime by approximating the arclength integral
      double dtau = dt*0.5*(sqrt(-g(x,y,vx,vy)) + sqrt(-g(x_new,y_new,vx_new,vy_new)));

      tau = tau + dtau;

      Lorentzfactor = dt/dtau;

      //move to the new position in the physical cooridnates
      x = x_new;
      y = y_new;
      vx = vx_new;
      vy = vy_new;

      //actually move the sprite to the new position
      sprite.setPosition(screen_x(x,A,B,C,D),screen_y(y,A,B,C,D));

      //if so desired, rotate the sprite to face the direction of travel
      if (face_forward) {
        rotate_to_velocity();
      }

      //refresh the trailline
      for(int i = trail.getVertexCount()-1; i > 0; i--) {
        trail[i].position = trail[i-1].position;
      }
      trail[0].position = sprite.getPosition();
    }
  }


}


//check if we are colliding with another particle, but only if it has not been swallowed by the black hole
bool particle::checkCollision(particle& other_particle) {

  if (!swallowed && !other_particle.getSwallowed()) {
    sf::FloatRect box = sprite.getGlobalBounds();
  	sf::FloatRect other_box = other_particle.getSprite().getGlobalBounds();

  	if (box.intersects(other_box)) {
  		return true;
  	}
  	else {
  		return false;
  	}
  }
  else {
    return false;
  }

}

//let the particle explode, but only if it has not been swallowed by the black hole
void particle::explode(float A, float B, float C, float D) {

  if (!swallowed) {
    //load png
  	texture.loadFromFile(currentworkingdirectory + "/Textures/T_Explosion_1.png");
  	//make it look smooth
  	texture.setSmooth(true);
  	//assign the texture
  	sprite.setTexture(texture, true);
  	//change the sprite origin to the center
  	sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
  	//set scale according to the window size
  	sprite.setScale(stretch, stretch);
    //set scale according to the window size and according to the world size. A scale of 1 corresponds to a 2560x1440 window and a world of [-10,10]x[-5,6.25].
  	sprite.setScale(20/(B-A)*stretch, 11.25/(D-C)*stretch);
  }

}

//make the particle invisible in order to do as if it stopped existing
void particle::make_invisible() {
	//load png
	texture.loadFromFile(currentworkingdirectory + "/Textures/T_Invisible.png");
	//assign the texture
	sprite.setTexture(texture, true);

  for (int i = 0; i < trail.getVertexCount(); i++) {
    trail[i].color = sf::Color::Transparent;
  }
}


void particle::set_chart_velocity(double modulus, double angle, bool face_forward = false) {

	//prevent a negative modulus
	if (modulus >= 0) {

		double vx_new = modulus*cos(angle);
		double vy_new = modulus*sin(angle);

		//prevent a superluminal speed
		if (spatial_speed(vx_new, vy_new) < 0.95) {
			vx = vx_new;
			vy = vy_new;
		}
	}

	//if so desired, rotate the sprite to face the direction of travel
	if (face_forward) {
		rotate_to_velocity();
	}

}

//change the components vx,vy leaving spatial speed constant
void particle::rotate_chart_velocity(double delta_angle, bool face_forward) {
  //only allow rotating if we are not on zero velocity
  if (vx != 0 || vy != 0) {
    //get current angle
    double angle = get_chart_velocity_angle();

    double newangle = angle + delta_angle;

    //find the modulus lambda such that lambda*cos(new angle), lambda*sin(new angle) fits the old spatial velocity
    double lambda = (-16*pow(a,3)*pow(M,2)*vx*vy*pow(x,3)*cos(newangle)+4*pow(a,2)*M*pow(vx,2)*pow(x,5)*cos(newangle)+16*a*pow(M,2)*vx*vy*pow(x,5)*cos(newangle)+4*pow(a,2)*M*pow(vy,2)*pow(x,5)*cos(newangle)-4*M*pow(vx,2)*pow(x,7)*cos(newangle)-4*M*pow(vy,2)*pow(x,7)*cos(newangle)+24*pow(a,3)*pow(M,2)*pow(vx,2)*pow(x,2)*y*cos(newangle)-24*pow(a,3)*pow(M,2)*pow(vy,2)*pow(x,2)*y*cos(newangle)-24*a*pow(M,2)*pow(vx,2)*pow(x,4)*y*cos(newangle)+16*a*pow(M,2)*pow(vy,2)*pow(x,4)*y*cos(newangle)+48*pow(a,3)*pow(M,2)*vx*vy*x*pow(y,2)*cos(newangle)+8*pow(a,2)*M*pow(vx,2)*pow(x,3)*pow(y,2)*cos(newangle)-16*a*pow(M,2)*vx*vy*pow(x,3)*pow(y,2)*cos(newangle)+8*pow(a,2)*M*pow(vy,2)*pow(x,3)*pow(y,2)*cos(newangle)-12*M*pow(vx,2)*pow(x,5)*pow(y,2)*cos(newangle)-12*M*pow(vy,2)*pow(x,5)*pow(y,2)*cos(newangle)-8*pow(a,3)*pow(M,2)*pow(vx,2)*pow(y,3)*cos(newangle)+8*pow(a,3)*pow(M,2)*pow(vy,2)*pow(y,3)*cos(newangle)-24*a*pow(M,2)*pow(vx,2)*pow(x,2)*pow(y,3)*cos(newangle)+8*a*pow(M,2)*pow(vy,2)*pow(x,2)*pow(y,3)*cos(newangle)+4*pow(a,2)*M*pow(vx,2)*x*pow(y,4)*cos(newangle)-32*a*pow(M,2)*vx*vy*x*pow(y,4)*cos(newangle)+4*pow(a,2)*M*pow(vy,2)*x*pow(y,4)*cos(newangle)-12*M*pow(vx,2)*pow(x,3)*pow(y,4)*cos(newangle)-12*M*pow(vy,2)*pow(x,3)*pow(y,4)*cos(newangle)-8*a*pow(M,2)*pow(vy,2)*pow(y,5)*cos(newangle)-4*M*pow(vx,2)*x*pow(y,6)*cos(newangle)-4*M*pow(vy,2)*x*pow(y,6)*cos(newangle)+8*pow(a,2)*pow(M,2)*pow(vx,2)*pow(x,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-8*pow(a,2)*pow(M,2)*pow(vy,2)*pow(x,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-8*pow(M,2)*pow(vx,2)*pow(x,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+48*pow(a,2)*pow(M,2)*vx*vy*pow(x,2)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-4*a*M*pow(vx,2)*pow(x,4)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-16*pow(M,2)*vx*vy*pow(x,4)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-4*a*M*pow(vy,2)*pow(x,4)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-24*pow(a,2)*pow(M,2)*pow(vx,2)*x*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+24*pow(a,2)*pow(M,2)*pow(vy,2)*x*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-8*pow(M,2)*pow(vx,2)*pow(x,3)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-8*pow(M,2)*pow(vy,2)*pow(x,3)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-16*pow(a,2)*pow(M,2)*vx*vy*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-8*a*M*pow(vx,2)*pow(x,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-16*pow(M,2)*vx*vy*pow(x,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-8*a*M*pow(vy,2)*pow(x,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-8*pow(M,2)*pow(vy,2)*x*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-4*a*M*pow(vx,2)*pow(y,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-4*a*M*pow(vy,2)*pow(y,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-8*pow(a,3)*pow(M,2)*pow(vx,2)*pow(x,3)*sin(newangle)+8*pow(a,3)*pow(M,2)*pow(vy,2)*pow(x,3)*sin(newangle)+8*a*pow(M,2)*pow(vx,2)*pow(x,5)*sin(newangle)-48*pow(a,3)*pow(M,2)*vx*vy*pow(x,2)*y*sin(newangle)+4*pow(a,2)*M*pow(vx,2)*pow(x,4)*y*sin(newangle)+32*a*pow(M,2)*vx*vy*pow(x,4)*y*sin(newangle)+4*pow(a,2)*M*pow(vy,2)*pow(x,4)*y*sin(newangle)-4*M*pow(vx,2)*pow(x,6)*y*sin(newangle)-4*M*pow(vy,2)*pow(x,6)*y*sin(newangle)+24*pow(a,3)*pow(M,2)*pow(vx,2)*x*pow(y,2)*sin(newangle)-24*pow(a,3)*pow(M,2)*pow(vy,2)*x*pow(y,2)*sin(newangle)-8*a*pow(M,2)*pow(vx,2)*pow(x,3)*pow(y,2)*sin(newangle)+24*a*pow(M,2)*pow(vy,2)*pow(x,3)*pow(y,2)*sin(newangle)+16*pow(a,3)*pow(M,2)*vx*vy*pow(y,3)*sin(newangle)+8*pow(a,2)*M*pow(vx,2)*pow(x,2)*pow(y,3)*sin(newangle)+16*a*pow(M,2)*vx*vy*pow(x,2)*pow(y,3)*sin(newangle)+8*pow(a,2)*M*pow(vy,2)*pow(x,2)*pow(y,3)*sin(newangle)-12*M*pow(vx,2)*pow(x,4)*pow(y,3)*sin(newangle)-12*M*pow(vy,2)*pow(x,4)*pow(y,3)*sin(newangle)-16*a*pow(M,2)*pow(vx,2)*x*pow(y,4)*sin(newangle)+24*a*pow(M,2)*pow(vy,2)*x*pow(y,4)*sin(newangle)+4*pow(a,2)*M*pow(vx,2)*pow(y,5)*sin(newangle)-16*a*pow(M,2)*vx*vy*pow(y,5)*sin(newangle)+4*pow(a,2)*M*pow(vy,2)*pow(y,5)*sin(newangle)-12*M*pow(vx,2)*pow(x,2)*pow(y,5)*sin(newangle)-12*M*pow(vy,2)*pow(x,2)*pow(y,5)*sin(newangle)-4*M*pow(vx,2)*pow(y,7)*sin(newangle)-4*M*pow(vy,2)*pow(y,7)*sin(newangle)-16*pow(a,2)*pow(M,2)*vx*vy*pow(x,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+4*a*M*pow(vx,2)*pow(x,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+4*a*M*pow(vy,2)*pow(x,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+24*pow(a,2)*pow(M,2)*pow(vx,2)*pow(x,2)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)-24*pow(a,2)*pow(M,2)*pow(vy,2)*pow(x,2)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)-8*pow(M,2)*pow(vx,2)*pow(x,4)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+48*pow(a,2)*pow(M,2)*vx*vy*x*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+8*a*M*pow(vx,2)*pow(x,3)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)-16*pow(M,2)*vx*vy*pow(x,3)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+8*a*M*pow(vy,2)*pow(x,3)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)-8*pow(a,2)*pow(M,2)*pow(vx,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+8*pow(a,2)*pow(M,2)*pow(vy,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)-8*pow(M,2)*pow(vx,2)*pow(x,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)-8*pow(M,2)*pow(vy,2)*pow(x,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+4*a*M*pow(vx,2)*x*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)-16*pow(M,2)*vx*vy*x*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+4*a*M*pow(vy,2)*x*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)-8*pow(M,2)*pow(vy,2)*pow(y,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+sqrt(pow(16*pow(a,3)*pow(M,2)*vx*vy*pow(x,3)*cos(newangle)-4*pow(a,2)*M*pow(vx,2)*pow(x,5)*cos(newangle)-16*a*pow(M,2)*vx*vy*pow(x,5)*cos(newangle)-4*pow(a,2)*M*pow(vy,2)*pow(x,5)*cos(newangle)+4*M*pow(vx,2)*pow(x,7)*cos(newangle)+4*M*pow(vy,2)*pow(x,7)*cos(newangle)-24*pow(a,3)*pow(M,2)*pow(vx,2)*pow(x,2)*y*cos(newangle)+24*pow(a,3)*pow(M,2)*pow(vy,2)*pow(x,2)*y*cos(newangle)+24*a*pow(M,2)*pow(vx,2)*pow(x,4)*y*cos(newangle)-16*a*pow(M,2)*pow(vy,2)*pow(x,4)*y*cos(newangle)-48*pow(a,3)*pow(M,2)*vx*vy*x*pow(y,2)*cos(newangle)-8*pow(a,2)*M*pow(vx,2)*pow(x,3)*pow(y,2)*cos(newangle)+16*a*pow(M,2)*vx*vy*pow(x,3)*pow(y,2)*cos(newangle)-8*pow(a,2)*M*pow(vy,2)*pow(x,3)*pow(y,2)*cos(newangle)+12*M*pow(vx,2)*pow(x,5)*pow(y,2)*cos(newangle)+12*M*pow(vy,2)*pow(x,5)*pow(y,2)*cos(newangle)+8*pow(a,3)*pow(M,2)*pow(vx,2)*pow(y,3)*cos(newangle)-8*pow(a,3)*pow(M,2)*pow(vy,2)*pow(y,3)*cos(newangle)+24*a*pow(M,2)*pow(vx,2)*pow(x,2)*pow(y,3)*cos(newangle)-8*a*pow(M,2)*pow(vy,2)*pow(x,2)*pow(y,3)*cos(newangle)-4*pow(a,2)*M*pow(vx,2)*x*pow(y,4)*cos(newangle)+32*a*pow(M,2)*vx*vy*x*pow(y,4)*cos(newangle)-4*pow(a,2)*M*pow(vy,2)*x*pow(y,4)*cos(newangle)+12*M*pow(vx,2)*pow(x,3)*pow(y,4)*cos(newangle)+12*M*pow(vy,2)*pow(x,3)*pow(y,4)*cos(newangle)+8*a*pow(M,2)*pow(vy,2)*pow(y,5)*cos(newangle)+4*M*pow(vx,2)*x*pow(y,6)*cos(newangle)+4*M*pow(vy,2)*x*pow(y,6)*cos(newangle)-8*pow(a,2)*pow(M,2)*pow(vx,2)*pow(x,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+8*pow(a,2)*pow(M,2)*pow(vy,2)*pow(x,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+8*pow(M,2)*pow(vx,2)*pow(x,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-48*pow(a,2)*pow(M,2)*vx*vy*pow(x,2)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+4*a*M*pow(vx,2)*pow(x,4)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+16*pow(M,2)*vx*vy*pow(x,4)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+4*a*M*pow(vy,2)*pow(x,4)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+24*pow(a,2)*pow(M,2)*pow(vx,2)*x*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)-24*pow(a,2)*pow(M,2)*pow(vy,2)*x*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+8*pow(M,2)*pow(vx,2)*pow(x,3)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+8*pow(M,2)*pow(vy,2)*pow(x,3)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+16*pow(a,2)*pow(M,2)*vx*vy*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+8*a*M*pow(vx,2)*pow(x,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+16*pow(M,2)*vx*vy*pow(x,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+8*a*M*pow(vy,2)*pow(x,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+8*pow(M,2)*pow(vy,2)*x*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+4*a*M*pow(vx,2)*pow(y,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+4*a*M*pow(vy,2)*pow(y,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(newangle)+8*pow(a,3)*pow(M,2)*pow(vx,2)*pow(x,3)*sin(newangle)-8*pow(a,3)*pow(M,2)*pow(vy,2)*pow(x,3)*sin(newangle)-8*a*pow(M,2)*pow(vx,2)*pow(x,5)*sin(newangle)+48*pow(a,3)*pow(M,2)*vx*vy*pow(x,2)*y*sin(newangle)-4*pow(a,2)*M*pow(vx,2)*pow(x,4)*y*sin(newangle)-32*a*pow(M,2)*vx*vy*pow(x,4)*y*sin(newangle)-4*pow(a,2)*M*pow(vy,2)*pow(x,4)*y*sin(newangle)+4*M*pow(vx,2)*pow(x,6)*y*sin(newangle)+4*M*pow(vy,2)*pow(x,6)*y*sin(newangle)-24*pow(a,3)*pow(M,2)*pow(vx,2)*x*pow(y,2)*sin(newangle)+24*pow(a,3)*pow(M,2)*pow(vy,2)*x*pow(y,2)*sin(newangle)+8*a*pow(M,2)*pow(vx,2)*pow(x,3)*pow(y,2)*sin(newangle)-24*a*pow(M,2)*pow(vy,2)*pow(x,3)*pow(y,2)*sin(newangle)-16*pow(a,3)*pow(M,2)*vx*vy*pow(y,3)*sin(newangle)-8*pow(a,2)*M*pow(vx,2)*pow(x,2)*pow(y,3)*sin(newangle)-16*a*pow(M,2)*vx*vy*pow(x,2)*pow(y,3)*sin(newangle)-8*pow(a,2)*M*pow(vy,2)*pow(x,2)*pow(y,3)*sin(newangle)+12*M*pow(vx,2)*pow(x,4)*pow(y,3)*sin(newangle)+12*M*pow(vy,2)*pow(x,4)*pow(y,3)*sin(newangle)+16*a*pow(M,2)*pow(vx,2)*x*pow(y,4)*sin(newangle)-24*a*pow(M,2)*pow(vy,2)*x*pow(y,4)*sin(newangle)-4*pow(a,2)*M*pow(vx,2)*pow(y,5)*sin(newangle)+16*a*pow(M,2)*vx*vy*pow(y,5)*sin(newangle)-4*pow(a,2)*M*pow(vy,2)*pow(y,5)*sin(newangle)+12*M*pow(vx,2)*pow(x,2)*pow(y,5)*sin(newangle)+12*M*pow(vy,2)*pow(x,2)*pow(y,5)*sin(newangle)+4*M*pow(vx,2)*pow(y,7)*sin(newangle)+4*M*pow(vy,2)*pow(y,7)*sin(newangle)+16*pow(a,2)*pow(M,2)*vx*vy*pow(x,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)-4*a*M*pow(vx,2)*pow(x,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)-4*a*M*pow(vy,2)*pow(x,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)-24*pow(a,2)*pow(M,2)*pow(vx,2)*pow(x,2)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+24*pow(a,2)*pow(M,2)*pow(vy,2)*pow(x,2)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+8*pow(M,2)*pow(vx,2)*pow(x,4)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)-48*pow(a,2)*pow(M,2)*vx*vy*x*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)-8*a*M*pow(vx,2)*pow(x,3)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+16*pow(M,2)*vx*vy*pow(x,3)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)-8*a*M*pow(vy,2)*pow(x,3)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+8*pow(a,2)*pow(M,2)*pow(vx,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)-8*pow(a,2)*pow(M,2)*pow(vy,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+8*pow(M,2)*pow(vx,2)*pow(x,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+8*pow(M,2)*pow(vy,2)*pow(x,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)-4*a*M*pow(vx,2)*x*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+16*pow(M,2)*vx*vy*x*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)-4*a*M*pow(vy,2)*x*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle)+8*pow(M,2)*pow(vy,2)*pow(y,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(newangle),2)-4*(-4*pow(a,2)*pow(M,2)*pow(vx,2)*pow(x,4)-4*pow(a,3)*M*vx*vy*pow(x,4)+4*pow(a,2)*pow(M,2)*pow(vy,2)*pow(x,4)+pow(a,2)*pow(vx,2)*pow(x,6)+4*pow(M,2)*pow(vx,2)*pow(x,6)+4*a*M*vx*vy*pow(x,6)+pow(a,2)*pow(vy,2)*pow(x,6)-pow(vx,2)*pow(x,8)-pow(vy,2)*pow(x,8)+4*pow(a,3)*M*pow(vx,2)*pow(x,3)*y-16*pow(a,2)*pow(M,2)*vx*vy*pow(x,3)*y-4*pow(a,3)*M*pow(vy,2)*pow(x,3)*y-4*a*M*pow(vx,2)*pow(x,5)*y+8*pow(M,2)*vx*vy*pow(x,5)*y+4*a*M*pow(vy,2)*pow(x,5)*y+3*pow(a,2)*pow(vx,2)*pow(x,4)*pow(y,2)+8*pow(M,2)*pow(vx,2)*pow(x,4)*pow(y,2)+4*a*M*vx*vy*pow(x,4)*pow(y,2)+3*pow(a,2)*pow(vy,2)*pow(x,4)*pow(y,2)+4*pow(M,2)*pow(vy,2)*pow(x,4)*pow(y,2)-4*pow(vx,2)*pow(x,6)*pow(y,2)-4*pow(vy,2)*pow(x,6)*pow(y,2)+4*pow(a,3)*M*pow(vx,2)*x*pow(y,3)-16*pow(a,2)*pow(M,2)*vx*vy*x*pow(y,3)-4*pow(a,3)*M*pow(vy,2)*x*pow(y,3)-8*a*M*pow(vx,2)*pow(x,3)*pow(y,3)+16*pow(M,2)*vx*vy*pow(x,3)*pow(y,3)+8*a*M*pow(vy,2)*pow(x,3)*pow(y,3)+4*pow(a,2)*pow(M,2)*pow(vx,2)*pow(y,4)+4*pow(a,3)*M*vx*vy*pow(y,4)-4*pow(a,2)*pow(M,2)*pow(vy,2)*pow(y,4)+3*pow(a,2)*pow(vx,2)*pow(x,2)*pow(y,4)+4*pow(M,2)*pow(vx,2)*pow(x,2)*pow(y,4)-4*a*M*vx*vy*pow(x,2)*pow(y,4)+3*pow(a,2)*pow(vy,2)*pow(x,2)*pow(y,4)+8*pow(M,2)*pow(vy,2)*pow(x,2)*pow(y,4)-6*pow(vx,2)*pow(x,4)*pow(y,4)-6*pow(vy,2)*pow(x,4)*pow(y,4)-4*a*M*pow(vx,2)*x*pow(y,5)+8*pow(M,2)*vx*vy*x*pow(y,5)+4*a*M*pow(vy,2)*x*pow(y,5)+pow(a,2)*pow(vx,2)*pow(y,6)-4*a*M*vx*vy*pow(y,6)+pow(a,2)*pow(vy,2)*pow(y,6)+4*pow(M,2)*pow(vy,2)*pow(y,6)-4*pow(vx,2)*pow(x,2)*pow(y,6)-4*pow(vy,2)*pow(x,2)*pow(y,6)-pow(vx,2)*pow(y,8)-pow(vy,2)*pow(y,8)+2*pow(a,2)*M*pow(vx,2)*pow(x,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-8*a*pow(M,2)*vx*vy*pow(x,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-2*pow(a,2)*M*pow(vy,2)*pow(x,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+2*M*pow(vy,2)*pow(x,6)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+8*a*pow(M,2)*pow(vx,2)*pow(x,3)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+8*pow(a,2)*M*vx*vy*pow(x,3)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-8*a*pow(M,2)*pow(vy,2)*pow(x,3)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-4*M*vx*vy*pow(x,5)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+2*M*pow(vx,2)*pow(x,4)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+4*M*pow(vy,2)*pow(x,4)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+8*a*pow(M,2)*pow(vx,2)*x*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+8*pow(a,2)*M*vx*vy*x*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-8*a*pow(M,2)*pow(vy,2)*x*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-8*M*vx*vy*pow(x,3)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-2*pow(a,2)*M*pow(vx,2)*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+8*a*pow(M,2)*vx*vy*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+2*pow(a,2)*M*pow(vy,2)*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+4*M*pow(vx,2)*pow(x,2)*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+2*M*pow(vy,2)*pow(x,2)*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-4*M*vx*vy*x*pow(y,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+2*M*pow(vx,2)*pow(y,6)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2)))*(4*pow(a,2)*M*vx*pow(x,5)+4*a*pow(M,2)*vy*pow(x,5)-pow(a,2)*pow(x,6)-2*pow(M,2)*pow(x,6)-4*M*vx*pow(x,7)+pow(x,8)-4*a*pow(M,2)*vx*pow(x,4)*y+4*pow(a,2)*M*vy*pow(x,4)*y-4*M*vy*pow(x,6)*y+8*pow(a,2)*M*vx*pow(x,3)*pow(y,2)+8*a*pow(M,2)*vy*pow(x,3)*pow(y,2)-3*pow(a,2)*pow(x,4)*pow(y,2)-6*pow(M,2)*pow(x,4)*pow(y,2)-12*M*vx*pow(x,5)*pow(y,2)+4*pow(x,6)*pow(y,2)-8*a*pow(M,2)*vx*pow(x,2)*pow(y,3)+8*pow(a,2)*M*vy*pow(x,2)*pow(y,3)-12*M*vy*pow(x,4)*pow(y,3)+4*pow(a,2)*M*vx*x*pow(y,4)+4*a*pow(M,2)*vy*x*pow(y,4)-3*pow(a,2)*pow(x,2)*pow(y,4)-6*pow(M,2)*pow(x,2)*pow(y,4)-12*M*vx*pow(x,3)*pow(y,4)+6*pow(x,4)*pow(y,4)-4*a*pow(M,2)*vx*pow(y,5)+4*pow(a,2)*M*vy*pow(y,5)-12*M*vy*pow(x,2)*pow(y,5)-pow(a,2)*pow(y,6)-2*pow(M,2)*pow(y,6)-4*M*vx*x*pow(y,6)+4*pow(x,2)*pow(y,6)-4*M*vy*pow(y,7)+pow(y,8)-4*pow(M,2)*vx*pow(x,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+4*a*M*vy*pow(x,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-M*pow(x,6)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-4*a*M*vx*pow(x,4)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-4*pow(M,2)*vy*pow(x,4)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-8*pow(M,2)*vx*pow(x,3)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+8*a*M*vy*pow(x,3)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-3*M*pow(x,4)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-8*a*M*vx*pow(x,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-8*pow(M,2)*vy*pow(x,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-4*pow(M,2)*vx*x*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+4*a*M*vy*x*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-3*M*pow(x,2)*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-4*a*M*vx*pow(y,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-4*pow(M,2)*vy*pow(y,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-M*pow(y,6)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-8*pow(a,3)*pow(M,2)*vy*pow(x,3)*cos(2*newangle)+4*pow(a,2)*pow(M,2)*pow(x,4)*cos(2*newangle)+4*a*pow(M,2)*vy*pow(x,5)*cos(2*newangle)-2*pow(M,2)*pow(x,6)*cos(2*newangle)+24*pow(a,3)*pow(M,2)*vx*pow(x,2)*y*cos(2*newangle)-4*pow(a,3)*M*pow(x,3)*y*cos(2*newangle)-20*a*pow(M,2)*vx*pow(x,4)*y*cos(2*newangle)+4*a*M*pow(x,5)*y*cos(2*newangle)+24*pow(a,3)*pow(M,2)*vy*x*pow(y,2)*cos(2*newangle)-16*a*pow(M,2)*vy*pow(x,3)*pow(y,2)*cos(2*newangle)-2*pow(M,2)*pow(x,4)*pow(y,2)*cos(2*newangle)-8*pow(a,3)*pow(M,2)*vx*pow(y,3)*cos(2*newangle)-4*pow(a,3)*M*x*pow(y,3)*cos(2*newangle)-16*a*pow(M,2)*vx*pow(x,2)*pow(y,3)*cos(2*newangle)+8*a*M*pow(x,3)*pow(y,3)*cos(2*newangle)-4*pow(a,2)*pow(M,2)*pow(y,4)*cos(2*newangle)-20*a*pow(M,2)*vy*x*pow(y,4)*cos(2*newangle)+2*pow(M,2)*pow(x,2)*pow(y,4)*cos(2*newangle)+4*a*pow(M,2)*vx*pow(y,5)*cos(2*newangle)+4*a*M*x*pow(y,5)*cos(2*newangle)+2*pow(M,2)*pow(y,6)*cos(2*newangle)+8*pow(a,2)*pow(M,2)*vx*pow(x,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-2*pow(a,2)*M*pow(x,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-4*pow(M,2)*vx*pow(x,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)+M*pow(x,6)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)+24*pow(a,2)*pow(M,2)*vy*pow(x,2)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-8*a*pow(M,2)*pow(x,3)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-4*pow(M,2)*vy*pow(x,4)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-24*pow(a,2)*pow(M,2)*vx*x*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)+M*pow(x,4)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-8*pow(a,2)*pow(M,2)*vy*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-8*a*pow(M,2)*x*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)+2*pow(a,2)*M*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)+4*pow(M,2)*vx*x*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-M*pow(x,2)*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)+4*pow(M,2)*vy*pow(y,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-M*pow(y,6)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-8*pow(a,3)*pow(M,2)*vx*pow(x,3)*sin(2*newangle)+2*pow(a,3)*M*pow(x,4)*sin(2*newangle)+8*a*pow(M,2)*vx*pow(x,5)*sin(2*newangle)-2*a*M*pow(x,6)*sin(2*newangle)-24*pow(a,3)*pow(M,2)*vy*pow(x,2)*y*sin(2*newangle)+8*pow(a,2)*pow(M,2)*pow(x,3)*y*sin(2*newangle)+16*a*pow(M,2)*vy*pow(x,4)*y*sin(2*newangle)-4*pow(M,2)*pow(x,5)*y*sin(2*newangle)+24*pow(a,3)*pow(M,2)*vx*x*pow(y,2)*sin(2*newangle)-8*a*pow(M,2)*vx*pow(x,3)*pow(y,2)*sin(2*newangle)-2*a*M*pow(x,4)*pow(y,2)*sin(2*newangle)+8*pow(a,3)*pow(M,2)*vy*pow(y,3)*sin(2*newangle)+8*pow(a,2)*pow(M,2)*x*pow(y,3)*sin(2*newangle)+8*a*pow(M,2)*vy*pow(x,2)*pow(y,3)*sin(2*newangle)-8*pow(M,2)*pow(x,3)*pow(y,3)*sin(2*newangle)-2*pow(a,3)*M*pow(y,4)*sin(2*newangle)-16*a*pow(M,2)*vx*x*pow(y,4)*sin(2*newangle)+2*a*M*pow(x,2)*pow(y,4)*sin(2*newangle)-8*a*pow(M,2)*vy*pow(y,5)*sin(2*newangle)-4*pow(M,2)*x*pow(y,5)*sin(2*newangle)+2*a*M*pow(y,6)*sin(2*newangle)-8*pow(a,2)*pow(M,2)*vy*pow(x,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)+4*a*pow(M,2)*pow(x,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)+24*pow(a,2)*pow(M,2)*vx*pow(x,2)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)-4*pow(a,2)*M*pow(x,3)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)-8*pow(M,2)*vx*pow(x,4)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)+2*M*pow(x,5)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)+24*pow(a,2)*pow(M,2)*vy*x*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)-8*pow(M,2)*vy*pow(x,3)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)-8*pow(a,2)*pow(M,2)*vx*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)-4*pow(a,2)*M*x*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)-8*pow(M,2)*vx*pow(x,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)+4*M*pow(x,3)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)-4*a*pow(M,2)*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)-8*pow(M,2)*vy*x*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)+2*M*x*pow(y,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle))))/(2.*(4*pow(a,2)*M*vx*pow(x,5)+4*a*pow(M,2)*vy*pow(x,5)-pow(a,2)*pow(x,6)-2*pow(M,2)*pow(x,6)-4*M*vx*pow(x,7)+pow(x,8)-4*a*pow(M,2)*vx*pow(x,4)*y+4*pow(a,2)*M*vy*pow(x,4)*y-4*M*vy*pow(x,6)*y+8*pow(a,2)*M*vx*pow(x,3)*pow(y,2)+8*a*pow(M,2)*vy*pow(x,3)*pow(y,2)-3*pow(a,2)*pow(x,4)*pow(y,2)-6*pow(M,2)*pow(x,4)*pow(y,2)-12*M*vx*pow(x,5)*pow(y,2)+4*pow(x,6)*pow(y,2)-8*a*pow(M,2)*vx*pow(x,2)*pow(y,3)+8*pow(a,2)*M*vy*pow(x,2)*pow(y,3)-12*M*vy*pow(x,4)*pow(y,3)+4*pow(a,2)*M*vx*x*pow(y,4)+4*a*pow(M,2)*vy*x*pow(y,4)-3*pow(a,2)*pow(x,2)*pow(y,4)-6*pow(M,2)*pow(x,2)*pow(y,4)-12*M*vx*pow(x,3)*pow(y,4)+6*pow(x,4)*pow(y,4)-4*a*pow(M,2)*vx*pow(y,5)+4*pow(a,2)*M*vy*pow(y,5)-12*M*vy*pow(x,2)*pow(y,5)-pow(a,2)*pow(y,6)-2*pow(M,2)*pow(y,6)-4*M*vx*x*pow(y,6)+4*pow(x,2)*pow(y,6)-4*M*vy*pow(y,7)+pow(y,8)-4*pow(M,2)*vx*pow(x,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+4*a*M*vy*pow(x,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-M*pow(x,6)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-4*a*M*vx*pow(x,4)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-4*pow(M,2)*vy*pow(x,4)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-8*pow(M,2)*vx*pow(x,3)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+8*a*M*vy*pow(x,3)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-3*M*pow(x,4)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-8*a*M*vx*pow(x,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-8*pow(M,2)*vy*pow(x,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-4*pow(M,2)*vx*x*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))+4*a*M*vy*x*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-3*M*pow(x,2)*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-4*a*M*vx*pow(y,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-4*pow(M,2)*vy*pow(y,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-M*pow(y,6)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))-8*pow(a,3)*pow(M,2)*vy*pow(x,3)*cos(2*newangle)+4*pow(a,2)*pow(M,2)*pow(x,4)*cos(2*newangle)+4*a*pow(M,2)*vy*pow(x,5)*cos(2*newangle)-2*pow(M,2)*pow(x,6)*cos(2*newangle)+24*pow(a,3)*pow(M,2)*vx*pow(x,2)*y*cos(2*newangle)-4*pow(a,3)*M*pow(x,3)*y*cos(2*newangle)-20*a*pow(M,2)*vx*pow(x,4)*y*cos(2*newangle)+4*a*M*pow(x,5)*y*cos(2*newangle)+24*pow(a,3)*pow(M,2)*vy*x*pow(y,2)*cos(2*newangle)-16*a*pow(M,2)*vy*pow(x,3)*pow(y,2)*cos(2*newangle)-2*pow(M,2)*pow(x,4)*pow(y,2)*cos(2*newangle)-8*pow(a,3)*pow(M,2)*vx*pow(y,3)*cos(2*newangle)-4*pow(a,3)*M*x*pow(y,3)*cos(2*newangle)-16*a*pow(M,2)*vx*pow(x,2)*pow(y,3)*cos(2*newangle)+8*a*M*pow(x,3)*pow(y,3)*cos(2*newangle)-4*pow(a,2)*pow(M,2)*pow(y,4)*cos(2*newangle)-20*a*pow(M,2)*vy*x*pow(y,4)*cos(2*newangle)+2*pow(M,2)*pow(x,2)*pow(y,4)*cos(2*newangle)+4*a*pow(M,2)*vx*pow(y,5)*cos(2*newangle)+4*a*M*x*pow(y,5)*cos(2*newangle)+2*pow(M,2)*pow(y,6)*cos(2*newangle)+8*pow(a,2)*pow(M,2)*vx*pow(x,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-2*pow(a,2)*M*pow(x,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-4*pow(M,2)*vx*pow(x,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)+M*pow(x,6)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)+24*pow(a,2)*pow(M,2)*vy*pow(x,2)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-8*a*pow(M,2)*pow(x,3)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-4*pow(M,2)*vy*pow(x,4)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-24*pow(a,2)*pow(M,2)*vx*x*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)+M*pow(x,4)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-8*pow(a,2)*pow(M,2)*vy*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-8*a*pow(M,2)*x*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)+2*pow(a,2)*M*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)+4*pow(M,2)*vx*x*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-M*pow(x,2)*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)+4*pow(M,2)*vy*pow(y,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-M*pow(y,6)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*cos(2*newangle)-8*pow(a,3)*pow(M,2)*vx*pow(x,3)*sin(2*newangle)+2*pow(a,3)*M*pow(x,4)*sin(2*newangle)+8*a*pow(M,2)*vx*pow(x,5)*sin(2*newangle)-2*a*M*pow(x,6)*sin(2*newangle)-24*pow(a,3)*pow(M,2)*vy*pow(x,2)*y*sin(2*newangle)+8*pow(a,2)*pow(M,2)*pow(x,3)*y*sin(2*newangle)+16*a*pow(M,2)*vy*pow(x,4)*y*sin(2*newangle)-4*pow(M,2)*pow(x,5)*y*sin(2*newangle)+24*pow(a,3)*pow(M,2)*vx*x*pow(y,2)*sin(2*newangle)-8*a*pow(M,2)*vx*pow(x,3)*pow(y,2)*sin(2*newangle)-2*a*M*pow(x,4)*pow(y,2)*sin(2*newangle)+8*pow(a,3)*pow(M,2)*vy*pow(y,3)*sin(2*newangle)+8*pow(a,2)*pow(M,2)*x*pow(y,3)*sin(2*newangle)+8*a*pow(M,2)*vy*pow(x,2)*pow(y,3)*sin(2*newangle)-8*pow(M,2)*pow(x,3)*pow(y,3)*sin(2*newangle)-2*pow(a,3)*M*pow(y,4)*sin(2*newangle)-16*a*pow(M,2)*vx*x*pow(y,4)*sin(2*newangle)+2*a*M*pow(x,2)*pow(y,4)*sin(2*newangle)-8*a*pow(M,2)*vy*pow(y,5)*sin(2*newangle)-4*pow(M,2)*x*pow(y,5)*sin(2*newangle)+2*a*M*pow(y,6)*sin(2*newangle)-8*pow(a,2)*pow(M,2)*vy*pow(x,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)+4*a*pow(M,2)*pow(x,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)+24*pow(a,2)*pow(M,2)*vx*pow(x,2)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)-4*pow(a,2)*M*pow(x,3)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)-8*pow(M,2)*vx*pow(x,4)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)+2*M*pow(x,5)*y*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)+24*pow(a,2)*pow(M,2)*vy*x*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)-8*pow(M,2)*vy*pow(x,3)*pow(y,2)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)-8*pow(a,2)*pow(M,2)*vx*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)-4*pow(a,2)*M*x*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)-8*pow(M,2)*vx*pow(x,2)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)+4*M*pow(x,3)*pow(y,3)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)-4*a*pow(M,2)*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)-8*pow(M,2)*vy*x*pow(y,4)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)+2*M*x*pow(y,5)*sqrt(-pow(a,2)+pow(x,2)+pow(y,2))*sin(2*newangle)));

    double vx_new = lambda*cos(newangle);
    double vy_new = lambda*sin(newangle);

    //double check that we do not exceed the maximal speed
    if (spatial_speed(vx_new,vy_new) < 0.95) {
      vx = vx_new;
      vy = vy_new;
    }

    //if so desired, rotate the sprite to face the direction of travel
	 if (face_forward) {
		  rotate_to_velocity();
	 }

  }

}

//change the components vx,vy leaving their polar angle constant
void particle::stretch_chart_velocity(double delta_modulus,bool face_forward) {
  //get current modulus
  double modulus = get_chart_velocity_modulus();
  //get current angle
  double angle = get_chart_velocity_angle();

  double newmodulus = modulus + delta_modulus;

  if (newmodulus < 0) {
    newmodulus = 0;
  }

  double vx_new = newmodulus*cos(angle);
  double vy_new = newmodulus*sin(angle);

  //double check that we do not exceed the maximal speed
  if (spatial_speed(vx_new,vy_new) < 0.95) {
    vx = vx_new;
    vy = vy_new;
  }

  //if so desired, rotate the sprite to face the direction of travel
	if (face_forward) {
		rotate_to_velocity();
	}

}

//retrieve modulus and angle of (vx,vy) in the chart (not the physical length)
double particle::get_chart_velocity_modulus() {
	return sqrt(vx*vx+vy*vy);
}
double particle::get_chart_velocity_angle() {
  if (vx != 0 || vy != 0) {
    return atan2(vy,vx);
  }
  else {
    if (x < 0 && y == 0) {
      return 0;
    }
    else if (x > 0 && y == 0) {
      return pi;
    }
    else if (x == 0 && y > 0) {
      return -pi/2;
    }
    else {
      return pi/2;
    }
  }

}
