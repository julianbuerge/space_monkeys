#include "star_cluster.h"


//Constructors
star_cluster::star_cluster() {
	currentworkingdirectory = get_current_dir_name();
}

star_cluster::star_cluster(std::string name_in, float width, float height, float stretch) {
	currentworkingdirectory = get_current_dir_name();

  name = name_in;

	//input file containing the trajectory initial values
  std::ifstream input(currentworkingdirectory + "/Levels/Star_Cluster_" + name + ".txt");

  //check if the inputfile was opened correctly. If not exit with error code 1
  if (!input) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }

	//to read in central body and star names & physics data we need to temporarily save them
	std::string aux_name;
	std::string aux_texture_name;
	double aux_id;
	double aux_x;
	double aux_y;
	double aux_modulus;
	double aux_angle;

	//read in the world bounds
	A = convert_to_double(input);
	B = convert_to_double(input);
	C = convert_to_double(input);
	D = height*(B-A)/width + C;

	//read in the central body parameters and calculate the horizon
	M = convert_to_double(input);
	a = convert_to_double(input);

	//read in central body name
	input >> aux_texture_name;

	//in order to get its sreen_x,y functions initialize stars[0] with dummy data
	stars[0].initialize(-1,"Dummy_System","Default_Star",-1,-1,0,0,0,0,width,height,stretch,A,B,C,D);

	//initialize the central body with all the data we now have
	horizon = M + sqrt(M*M - a*a);
	screen_horizon = stars[0].screen_x(A+horizon,A,B,C,D);
	//load png
	central_body_tex.loadFromFile(currentworkingdirectory + "/Textures/T_" + aux_texture_name + ".png");
	//make it look smooth
	central_body_tex.setSmooth(true);
	//assign the texture
	central_body.setTexture(central_body_tex);
	//change the sprite origin to the center
	central_body.setOrigin(central_body_tex.getSize().x/2, central_body_tex.getSize().y/2);
	//set the position (borrowing the screen_x,y from the player star_system, so that we don't need to redefine them here)
	central_body.setPosition(stars[0].screen_x(0,A,B,C,D),stars[0].screen_y(0,A,B,C,D));
	//set scale according to the window size
	central_body.setScale(screen_horizon/(central_body_tex.getSize().x/2),screen_horizon/(central_body_tex.getSize().y/2));



	//now we do all the stars.
	amount_stars = convert_to_double(input);

	//the array size of stars is hardcoded to 100
	if (amount_stars > 100) {
		std::cout << "Warning, tried to load more than 100 stars. Excess stars will not be loaded." << std::endl;

		amount_stars = 100;
	}


	for (int i = 0; i < amount_stars; i++) {

		aux_id = convert_to_double(input);

		input >> aux_name;

		aux_x = convert_to_double(input);
		aux_y = convert_to_double(input);
		aux_modulus = convert_to_double(input);
		aux_angle = convert_to_double(input);

		input >> aux_texture_name;

		stars[i].initialize(aux_id, aux_name, aux_texture_name,aux_x,aux_y,0,0,M,a,width,height,stretch,A,B,C,D);

		stars[i].set_chart_velocity(aux_modulus,aux_angle);

	}
}

//Memberfunctions

//this does the same as the constructor: it loads all the data from the file specified by the level number.
void star_cluster::change_star_cluster(std::string name_in, float width, float height, float stretch) {
	currentworkingdirectory = get_current_dir_name();

  name = name_in;

	//input file containing the trajectory initial values
  std::ifstream input(currentworkingdirectory + "/Levels/Star_Cluster_" + name + ".txt");

  //check if the inputfile was opened correctly. If not exit with error code 1
  if (!input) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }

	//to read in central body and star names & physics data we need to temporarily save them
	std::string aux_name;
	std::string aux_texture_name;
	double aux_id;
	double aux_x;
	double aux_y;
	double aux_modulus;
	double aux_angle;

	//read in the world bounds
	A = convert_to_double(input);
	B = convert_to_double(input);
	C = convert_to_double(input);
	D = height*(B-A)/width + C;

	//read in the central body parameters and calculate the horizon
	M = convert_to_double(input);
	a = convert_to_double(input);

	//read in central body name
	input >> aux_texture_name;

	//in order to get its sreen_x,y functions initialize stars[0] with dummy data
	stars[0].initialize(-1,"Dummy_System","Default_Star",-1,-1,0,0,0,0,width,height,stretch,A,B,C,D);

	//initialize the central body with all the data we now have
	horizon = M + sqrt(M*M - a*a);
	screen_horizon = stars[0].screen_x(A+horizon,A,B,C,D);
	//load png
	central_body_tex.loadFromFile(currentworkingdirectory + "/Textures/T_" + aux_texture_name + ".png");
	//make it look smooth
	central_body_tex.setSmooth(true);
	//assign the texture
	central_body.setTexture(central_body_tex);
	//change the sprite origin to the center
	central_body.setOrigin(central_body_tex.getSize().x/2, central_body_tex.getSize().y/2);
	//set the position (borrowing the screen_x,y from the player star_system, so that we don't need to redefine them here)
	central_body.setPosition(stars[0].screen_x(0,A,B,C,D),stars[0].screen_y(0,A,B,C,D));
	//set scale according to the window size
	central_body.setScale(screen_horizon/(central_body_tex.getSize().x/2),screen_horizon/(central_body_tex.getSize().y/2));



	//now we do all the stars.
	amount_stars = convert_to_double(input);

	//the array size of stars is hardcoded to 100
	if (amount_stars > 100) {
		std::cout << "Warning, tried to load more than 100 stars. Excess stars will not be loaded." << std::endl;

		amount_stars = 100;
	}


	for (int i = 0; i < amount_stars; i++) {

		aux_id = convert_to_double(input);

		input >> aux_name;

		aux_x = convert_to_double(input);
		aux_y = convert_to_double(input);
		aux_modulus = convert_to_double(input);
		aux_angle = convert_to_double(input);

		input >> aux_texture_name;

		stars[i].initialize(aux_id, aux_name, aux_texture_name,aux_x,aux_y,0,0,M,a,width,height,stretch,A,B,C,D);

		stars[i].set_chart_velocity(aux_modulus, aux_angle);

	}
}

sf::Sprite& star_cluster::getCentralBody() {
	return central_body;
}

star_system& star_cluster::getStar(int i) {
	return stars[i];
}

int star_cluster::getAmountStars() {
	return amount_stars;
}

//dt will not have the time factor in it.
void star_cluster::simulate(double dt, double time_factor) {

	//rotate the central body
	central_body.setRotation(central_body.getRotation() - a*delta_rotation*time_factor);

	//simulate all stars
	for (int i = 0; i < amount_stars; i++) {
			stars[i].evolve(dt*time_factor,A,B,C,D);
	}

}
