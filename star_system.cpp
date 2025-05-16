#include "star_system.h"


// CLASS

//private Memberfunctions

//Equation of motion ODE operators dv^i/dt = f_vi(x,y,vx,vy)

double star_system::f_vx(double x, double y, double vx, double vy) {
  return (M*(2*pow(a,5)*(-2*vx*vy*x*(pow(x,2) - 3*pow(y,2)) + pow(vy,2)*y*(-3*pow(x,2) + pow(y,2)) + pow(vx,2)*(3*pow(x,2)*y - pow(y,3))) + 2*pow(a,4)*(-(pow(vy,2)*x*(pow(x,2) - 3*pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + M*((vx - vy)*(vx + vy)*pow(x,3) + 6*vx*vy*pow(x,2)*y - 3*(vx - vy)*(vx + vy)*x*pow(y,2) - 2*vx*vy*pow(y,3)) + pow(vx,3)*(pow(x,4) - pow(y,4)) + pow(vx,2)*x*(4*vy*y*(pow(x,2) + pow(y,2)) + (pow(x,2) - 3*pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + vx*vy*(-2*y*(-3*pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + vy*(-pow(x,4) + pow(y,4)))) - pow(a,2)*(pow(x,2) + pow(y,2))*(-3*pow(vy,2)*x*(pow(x,2) - 3*pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + 4*pow(vx,3)*(pow(x,4) - pow(y,4)) + pow(vx,2)*x*(16*vy*y*(pow(x,2) + pow(y,2)) + 3*(pow(x,2) - 3*pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + 2*vx*vy*(-3*y*(-3*pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + 2*vy*(-pow(x,4) + pow(y,4))) + 2*M*((1 + 4*pow(vx,2) - pow(vy,2))*pow(x,3) + vx*(-2 - pow(vx,2) + pow(vy,2))*pow(y,2)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + x*y*((1 - pow(vx,2) + 4*pow(vy,2))*y + 4*(1 + pow(vx,2))*vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + vx*pow(x,2)*(10*vy*y + (2 + pow(vx,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) - pow(vy,2)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))))) + pow(pow(x,2) + pow(y,2),2)*(-(x*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))*((1 + 2*pow(vy,2))*pow(x,2) - (-1 + pow(vy,2))*pow(y,2))) + 2*pow(vx,3)*(pow(x,4) - pow(y,4)) + pow(vx,2)*(8*vy*x*y*(pow(x,2) + pow(y,2)) + 3*pow(x,3)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + 2*vx*vy*(y*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))*(4*pow(x,2) + pow(y,2)) + vy*(-pow(x,4) + pow(y,4))) + 2*M*((1 + 3*pow(vx,2))*pow(x,3) + vx*pow(x,2)*(4*vy*y + (3 + pow(vx,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + x*y*((1 + 2*pow(vx,2) + pow(vy,2))*y + 2*(1 + pow(vx,2))*vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + vx*pow(y,2)*(2*vy*y + sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + pow(vy,2)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))))) + 2*pow(a,3)*(M*(vx*y*(-2*(2 + pow(vx,2))*pow(x,3) - 2*(2 + pow(vx,2))*x*pow(y,2) - 3*vx*pow(x,2)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + vx*pow(y,2)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + pow(vy,2)*y*(2*vx*x*(pow(x,2) + pow(y,2)) + (3*pow(x,2) - pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + 2*vy*(vx*pow(x,3)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) - 3*vx*x*pow(y,2)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + (1 + pow(vx,2))*(pow(x,4) - pow(y,4)))) + 2*(pow(x,2) + pow(y,2))*(-(pow(vy,2)*y*(-3*pow(x,2) + pow(y,2))) - pow(vx,3)*x*y*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + vx*vy*x*(2*pow(x,2) + y*(-6*y + vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)))) + pow(vx,2)*(pow(y,2)*(y - vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + pow(x,2)*(-3*y + vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)))))) - 2*a*(pow(x,2) + pow(y,2))*(M*(pow(vy,2)*y*(2*vx*x*(pow(x,2) + pow(y,2)) + (2*pow(x,2) - pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) - y*(4*vx*x*(pow(x,2) + pow(y,2)) + 2*pow(vx,3)*x*(pow(x,2) + pow(y,2)) + (pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + pow(vx,2)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))*(5*pow(x,2) + 2*pow(y,2))) + 2*vy*(2*vx*pow(x,3)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) - vx*x*pow(y,2)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + (1 + pow(vx,2))*(pow(x,4) - pow(y,4)))) + (pow(x,2) + pow(y,2))*(-3*pow(vx,3)*x*y*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + vy*(-((pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + vy*(3*pow(x,2)*y - pow(y,3))) + pow(vx,2)*(pow(y,2)*(y - 3*vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) - 3*pow(x,2)*(y - vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)))) + vx*vy*x*(2*pow(x,2) + 3*y*(-2*y + vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))))))))/(pow(pow(x,2) + pow(y,2),3)*pow(-pow(a,2) + pow(x,2) + pow(y,2),2));
}

double star_system::f_vy(double x, double y, double vx, double vy) {
  return (M*(-2*pow(a,5)*(-(pow(vy,2)*x*(pow(x,2) - 3*pow(y,2))) - 2*vx*vy*y*(-3*pow(x,2) + pow(y,2)) + pow(vx,2)*(pow(x,3) - 3*x*pow(y,2))) - 2*pow(a,4)*(M*(2*vx*vy*pow(x,3) - 3*(vx - vy)*(vx + vy)*pow(x,2)*y - 6*vx*vy*x*pow(y,2) + (vx - vy)*(vx + vy)*pow(y,3)) - 2*vx*vy*x*(2*vy*y*(pow(x,2) + pow(y,2)) - (pow(x,2) - 3*pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + pow(vy,2)*(-(y*(-3*pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + vy*(pow(x,4) - pow(y,4))) + pow(vx,2)*(y*(-3*pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + vy*(-pow(x,4) + pow(y,4)))) - pow(a,2)*(pow(x,2) + pow(y,2))*(2*M*y*(pow(x,2) + pow(y,2)) + 4*M*vy*(-pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) - 2*pow(vy,3)*(x - y)*(x + y)*(2*pow(x,2) + 2*pow(y,2) + M*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + pow(vy,2)*(3*y*(-3*pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + M*(-2*pow(x,2)*y + 8*pow(y,3))) + 2*vx*x*(10*M*vy*pow(y,2) + 4*M*y*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) - 3*vy*(pow(x,2) - 3*pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + 4*pow(vy,2)*y*(2*pow(x,2) + 2*pow(y,2) + M*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)))) + pow(vx,2)*(-2*M*y*(-4*pow(x,2) + pow(y,2)) - 3*y*(-3*pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + 2*vy*(x - y)*(x + y)*(2*pow(x,2) + 2*pow(y,2) + M*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))))) + pow(pow(x,2) + pow(y,2),2)*(-2*pow(vy,3)*pow(x,4) + 2*pow(vy,3)*pow(y,4) - pow(x,2)*y*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) - pow(y,3)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + 3*pow(vy,2)*pow(y,3)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + 2*vx*vy*x*(4*vy*y*(pow(x,2) + pow(y,2)) + sqrt(-pow(a,2) + pow(x,2) + pow(y,2))*(pow(x,2) + 4*pow(y,2))) + pow(vx,2)*(y*(pow(x,2) - 2*pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + 2*vy*(pow(x,4) - pow(y,4))) + 2*M*(pow(vx,2)*pow(x,2)*(y + vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + pow(x,2)*(y + 2*pow(vy,2)*y + vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + pow(y,2)*(y + 3*pow(vy,2)*y + vy*(3 + pow(vy,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + 2*vx*x*(y*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + pow(vy,2)*y*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + vy*(pow(x,2) + 2*pow(y,2))))) - 2*a*(pow(x,2) + pow(y,2))*(M*(pow(vx,2)*x*(-2*vy*y*(pow(x,2) + pow(y,2)) + (pow(x,2) - 2*pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + x*(4*vy*y*(pow(x,2) + pow(y,2)) + 2*pow(vy,3)*y*(pow(x,2) + pow(y,2)) + (pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + pow(vy,2)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))*(2*pow(x,2) + 5*pow(y,2))) + 2*vx*(vy*pow(x,2)*y*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) - 2*vy*pow(y,3)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + (1 + pow(vy,2))*(pow(x,4) - pow(y,4)))) + (pow(x,2) + pow(y,2))*(vx*(3*pow(vy,2)*(x - y)*(x + y)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + (pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + vy*(6*pow(x,2)*y - 2*pow(y,3))) + pow(vx,2)*x*(pow(x,2) - 3*y*(y + vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)))) + pow(vy,2)*x*(-pow(x,2) + 3*y*(y + vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)))))) + 2*pow(a,3)*(2*(pow(x,2) + pow(y,2))*(pow(vx,2)*x*(pow(x,2) - y*(3*y + vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)))) + pow(vy,2)*x*(-pow(x,2) + y*(3*y + vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)))) + vx*vy*(-(pow(y,2)*(2*y + vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)))) + pow(x,2)*(6*y + vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))))) + M*(pow(vx,2)*x*(-2*vy*y*(pow(x,2) + pow(y,2)) + (pow(x,2) - 3*pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + 2*vx*(3*vy*pow(x,2)*y*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) - vy*pow(y,3)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + (1 + pow(vy,2))*(pow(x,4) - pow(y,4))) + vy*x*(pow(x,2)*(2*(2 + pow(vy,2))*y - vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + pow(y,2)*(2*(2 + pow(vy,2))*y + 3*vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))))))))/(pow(pow(x,2) + pow(y,2),3)*pow(-pow(a,2) + pow(x,2) + pow(y,2),2));
}

//convert radians to degrees
double star_system::radtodeg(double alpha) {
  return alpha*180/pi;
}


//Constructors
star_system::star_system() {
	currentworkingdirectory = get_current_dir_name();

  font.loadFromFile(currentworkingdirectory + "/Fonts/Capsule.ttf");

	//propertime
	tau = 0;

	//Lorentzfactor
	Lorentzfactor = 1;
}


star_system::star_system(int level_id_in, std::string name_in,  std::string texture_name_in, double x_in, double y_in, double vx_in, double vy_in, double M_in, double a_in, float width_in, float height_in, float stretch_in,float A, float B, float C, float D) {

  currentworkingdirectory = get_current_dir_name();

  font.loadFromFile(currentworkingdirectory + "/Fonts/Capsule.ttf");


  level_id = level_id_in;

  name = name_in;

  texture_name = texture_name_in;

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
	texture.loadFromFile(currentworkingdirectory + "/Textures/T_" + texture_name +".png");
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


  //setup the text, this is for displaying the name of the system

  //choose the font
  text.setFont(font);
  //set the character size
  text.setCharacterSize(30*stretch); // in pixels, not points!
  //set the color
  text.setFillColor(sf::Color(255,255,255));
  //set the position
  text.setPosition(screen_x(x,A,B,C,D)-0.5*text.getLocalBounds().width, screen_y(y,A,B,C,D)-1.6*text.getCharacterSize());
  //set the string
  text.setString(name);

}

//Memberfunctions

//in case you have already allocated an instance but want to initialize like with the constructor, use this
void star_system::initialize(int level_id_in, std::string name_in, std::string texture_name_in, double x_in, double y_in, double vx_in, double vy_in, double M_in, double a_in, float width_in, float height_in, float stretch_in, float A, float B, float C, float D) {
  level_id = level_id_in;

  name = name_in;

  texture_name = texture_name_in;

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
	texture.loadFromFile(currentworkingdirectory + "/Textures/T_" + texture_name+".png");
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


  //setup the text, this is for displaying the name of the system

  //choose the font
  text.setFont(font);
  //set the character size
  text.setCharacterSize(30*stretch); // in pixels, not points!
  //set the color
  text.setFillColor(sf::Color(255,255,255));
  //set the position
  text.setPosition(screen_x(x,A,B,C,D)-0.5*text.getLocalBounds().width, screen_y(y,A,B,C,D)-1.6*text.getCharacterSize());
  //set the string
  text.setString(name);

}

//transform world coordinates x,y to screen coordinates
//the world is [A,B]x[C,D] and the screen is [0,width*stretch]x[0,height*stretch] with origin top left corner.
float star_system::screen_x(double x, float A, float B, float C, float D) {
	return (x-A)/(B-A)*width;
}

float star_system::screen_y(double y, float A, float B, float C, float D) {
	return (D-y)/(D-C)*height;
}

//retrieve the sprite for rendering
sf::Sprite& star_system::getSprite() {
	return sprite;
}

//retrieve the text for rendering
sf::Text& star_system::getText() {
  return text;
}

//return the Lorentzfactor
double star_system::getLorentzfactor() {
	return Lorentzfactor;
}

//get if we were swallowed
bool star_system::getSwallowed() {
  return swallowed;
}

//spacetime metric (independent of t and vt = 1).
double star_system::g(double x, double y, double vx, double vy) {
	return -1 + pow(vy,2) + (-2*pow(a,2)*M*(vy*(-x + y) + vx*(x + y))*(vx*(x - y) + vy*(x + y)) - 4*a*M*(vy*x - vx*y)*(pow(x,2) + vx*x*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + y*(y + vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)))) + (pow(x,2) + pow(y,2))*(pow(vx,2)*(pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + 2*M*((1 + pow(vx,2))*pow(x,2) + 2*vx*x*(vy*y + sqrt(-pow(a,2) + pow(x,2) + pow(y,2))) + y*(y + pow(vy,2)*y + 2*vy*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))))))/(pow(pow(x,2) + pow(y,2),2)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)));
}

//get the spatial speed. From g(v,v) < 0 with v = (1,vx,vy) we get g_ijv^iv^j / -g_00 - g_0kv^k - g_k0v^k < 1. The spatical speed is sqrt(g_ijv^iv^j / -g_00 - g_0kv^k - g_k0v^k).
double star_system::spatial_speed(double vx, double vy) {
	return sqrt((4*a*M*(-(vy*x) + vx*y)*(vx*x + vy*y)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) - 2*pow(a,2)*M*(vy*(-x + y) + vx*(x + y))*(vx*(x - y) + vy*(x + y)) + (pow(x,2) + pow(y,2))*(2*M*pow(vx*x + vy*y,2) + (pow(vx,2) + pow(vy,2))*(pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))))/((pow(x,2) + pow(y,2))*(4*a*M*(vy*x - vx*y) + (pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) - 2*M*(pow(x,2) + pow(y,2) + 2*vx*x*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + 2*vy*y*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))))));
}

double star_system::spatial_speed() {
  return sqrt((4*a*M*(-(vy*x) + vx*y)*(vx*x + vy*y)*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) - 2*pow(a,2)*M*(vy*(-x + y) + vx*(x + y))*(vx*(x - y) + vy*(x + y)) + (pow(x,2) + pow(y,2))*(2*M*pow(vx*x + vy*y,2) + (pow(vx,2) + pow(vy,2))*(pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))))/((pow(x,2) + pow(y,2))*(4*a*M*(vy*x - vx*y) + (pow(x,2) + pow(y,2))*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) - 2*M*(pow(x,2) + pow(y,2) + 2*vx*x*sqrt(-pow(a,2) + pow(x,2) + pow(y,2)) + 2*vy*y*sqrt(-pow(a,2) + pow(x,2) + pow(y,2))))));
}

void star_system::set_chart_velocity(double modulus, double angle) {

	//prevent a negative modulus
	if (modulus >= 0) {

		double vx_new = modulus*cos(angle);
		double vy_new = modulus*sin(angle);

		//prevent a superluminal speed
		if (spatial_speed(vx_new, vy_new) < 1) {
			vx = vx_new;
			vy = vy_new;
		}
	}

}

//evolve the trajectory by time dt and update the propertime
void star_system::evolve(double dt, float A, float B, float C, float D) {

  //only if we have not been swallowed evolve the star_system
  if (!swallowed) {

    //update x,y,vx,vy according to the central body and GR equations of motion.

    //Dormand-Prince fifth order integration (with non adaptive step size)
    double k1_x = dt*vx;
    double k1_y = dt*vy;
    double k1_vx = dt*f_vx(x,y,vx,vy);
    double k1_vy = dt*f_vy(x,y,vx,vy);

    double k2_x = dt*(vx+1.0/5*k1_vx);
    double k2_y = dt*(vy+1.0/5*k1_vy);
    double k2_vx = dt*f_vx(x+1.0/5*k1_x,y+1.0/5*k1_y,vx+1.0/5*k1_vx,vy+1.0/5*k1_vy);
    double k2_vy = dt*f_vy(x+1.0/5*k1_x,y+1.0/5*k1_y,vx+1.0/5*k1_vx,vy+1.0/5*k1_vy);

    double k3_x = dt*(vx+3.0/40*k1_vx+9.0/40*k2_vx);
    double k3_y = dt*(vy+3.0/40*k1_vy+9.0/40*k2_vy);
    double k3_vx = dt*f_vx(x+3.0/40*k1_x+9.0/40*k2_x,y+3.0/40*k1_y+9.0/40*k2_y,vx+3.0/40*k1_vx+9.0/40*k2_vx,vy+3.0/40*k1_vy+9.0/40*k2_vy);
    double k3_vy = dt*f_vy(x+3.0/40*k1_x+9.0/40*k2_x,y+3.0/40*k1_y+9.0/40*k2_y,vx+3.0/40*k1_vx+9.0/40*k2_vx,vy+3.0/40*k1_vy+9.0/40*k2_vy);

    double k4_x = dt*(vx+44.0/45*k1_vx-56.0/15*k2_vx+32.0/9*k3_vx);
    double k4_y = dt*(vy+44.0/45*k1_vy-56.0/15*k2_vy+32.0/9*k3_vy);
    double k4_vx = dt*f_vx(x+44.0/45*k1_x-56.0/15*k2_x+32.0/9*k3_x,y+44.0/45*k1_y-56.0/15*k2_y+32.0/9*k3_y,vx+44.0/45*k1_vx-56.0/15*k2_vx+32.0/9*k3_vx,vy+44.0/45*k1_vy-56.0/15*k2_vy+32.0/9*k3_vy);
    double k4_vy = dt*f_vy(x+44.0/45*k1_x-56.0/15*k2_x+32.0/9*k3_x,y+44.0/45*k1_y-56.0/15*k2_y+32.0/9*k3_y,vx+44.0/45*k1_vx-56.0/15*k2_vx+32.0/9*k3_vx,vy+44.0/45*k1_vy-56.0/15*k2_vy+32.0/9*k3_vy);

    double k5_x = dt*(vx+19372.0/6561*k1_vx-25360.0/2187*k2_vx+64448.0/6561*k3_vx-212.0/729*k4_vx);
    double k5_y = dt*(vy+19372.0/6561*k1_vy-25360.0/2187*k2_vy+64448.0/6561*k3_vy-212.0/729*k4_vy);
    double k5_vx = dt*f_vx(x+19372.0/6561*k1_x-25360.0/2187*k2_x+64448.0/6561*k3_x-212.0/729*k4_x,y+19372.0/6561*k1_y-25360.0/2187*k2_y+64448.0/6561*k3_y-212.0/729*k4_y,vx+19372.0/6561*k1_vx-25360.0/2187*k2_vx+64448.0/6561*k3_vx-212.0/729*k4_vx,vy+19372.0/6561*k1_vy-25360.0/2187*k2_vy+64448.0/6561*k3_vy-212.0/729*k4_vy);
    double k5_vy = dt*f_vy(x+19372.0/6561*k1_x-25360.0/2187*k2_x+64448.0/6561*k3_x-212.0/729*k4_x,y+19372.0/6561*k1_y-25360.0/2187*k2_y+64448.0/6561*k3_y-212.0/729*k4_y,vx+19372.0/6561*k1_vx-25360.0/2187*k2_vx+64448.0/6561*k3_vx-212.0/729*k4_vx,vy+19372.0/6561*k1_vy-25360.0/2187*k2_vy+64448.0/6561*k3_vy-212.0/729*k4_vy);

    double k6_x = dt*(vx+9017.0/3168*k1_vx-355.0/33*k2_vx+46732.0/5247*k3_vx+49.0/176*k4_vx-5103.0/18656*k5_vx);
    double k6_y = dt*(vy+9017.0/3168*k1_vy-355.0/33*k2_vy+46732.0/5247*k3_vy+49.0/176*k4_vy-5103.0/18656*k5_vy);
    double k6_vx = dt*f_vx(x+9017.0/3168*k1_x-355.0/33*k2_x+46732.0/5247*k3_x+49.0/176*k4_x-5103.0/18656*k5_x,y+9017.0/3168*k1_y-355.0/33*k2_y+46732.0/5247*k3_y+49.0/176*k4_y-5103.0/18656*k5_y,vx+9017.0/3168*k1_vx-355.0/33*k2_vx+46732.0/5247*k3_vx+49.0/176*k4_vx-5103.0/18656*k5_vx,vy+9017.0/3168*k1_vy-355.0/33*k2_vy+46732.0/5247*k3_vy+49.0/176*k4_vy-5103.0/18656*k5_vy);
    double k6_vy = dt*f_vy(x+9017.0/3168*k1_x-355.0/33*k2_x+46732.0/5247*k3_x+49.0/176*k4_x-5103.0/18656*k5_x,y+9017.0/3168*k1_y-355.0/33*k2_y+46732.0/5247*k3_y+49.0/176*k4_y-5103.0/18656*k5_y,vx+9017.0/3168*k1_vx-355.0/33*k2_vx+46732.0/5247*k3_vx+49.0/176*k4_vx-5103.0/18656*k5_vx,vy+9017.0/3168*k1_vy-355.0/33*k2_vy+46732.0/5247*k3_vy+49.0/176*k4_vy-5103.0/18656*k5_vy);

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

      //update the text position
      text.setPosition(screen_x(x,A,B,C,D)-0.5*text.getLocalBounds().width, screen_y(y,A,B,C,D)-1.6*text.getCharacterSize());

    }
  }


}


//check if we are colliding with another star_system, but only if it has not been swallowed by the black hole
bool star_system::checkCollision(star_system& other_star_system) {

  if (!swallowed && !other_star_system.getSwallowed()) {
    sf::FloatRect box = sprite.getGlobalBounds();
  	sf::FloatRect other_box = other_star_system.getSprite().getGlobalBounds();

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

//make the star_system invisible in order to do as if it stopped existing
void star_system::make_invisible() {
	//load png
	texture.loadFromFile(currentworkingdirectory + "/Textures/T_Invisible.png");
	//assign the texture
	sprite.setTexture(texture, true);
}

//return the level id if the star system was clicked (in the level menu)
int star_system::pressed(float x, float y) {

  //get the sprite bounding box
  sf::FloatRect bounding_box = sprite.getGlobalBounds();

  sf::Vector2f clicked_point(x,y);

  if (bounding_box.contains(clicked_point)) {
    return level_id;
  }
  else {
    return -1;
  }

}
