#include "level.h"


//Constructors
level::level() {
	currentworkingdirectory = get_current_dir_name();
}

level::level(int number_in, float width, float height, float stretch) {

  currentworkingdirectory = get_current_dir_name();

  number = number_in;

	//input file containing the trajectory initial values
  std::ifstream input(currentworkingdirectory + "/Levels/Level_" + std::to_string(number) + ".txt");

  //check if the inputfile was opened correctly. If not exit with error code 1
  if (!input) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }

	//to read in player, central body and station names and physics data we need to temporarily save them
	std::string aux_string;
	double aux_x;
	double aux_y;
	double aux_vx;
	double aux_vy;

	//read in the world bounds
	A = convert_to_double(input);
	B = convert_to_double(input);
	C = convert_to_double(input);
	D = height*(B-A)/width + C;

	//read in the central body parameters and calculate the horizon
	M = convert_to_double(input);
	a = convert_to_double(input);



	////read in the player name and physics data
	input >> aux_string;
	aux_x = convert_to_double(input);
	aux_y = convert_to_double(input);
	aux_vx = convert_to_double(input);
	aux_vy = convert_to_double(input);

	//initialize the player with the next some doubles from the file
	player.initialize(aux_string,aux_x,aux_y,aux_vx,aux_vy,M,a,width,height,stretch,A,B,C,D,true);



	//read in central body name
	input >> aux_string;

	//initialize the central body with all the data we now have
	horizon = M + sqrt(M*M - a*a);
	screen_horizon = player.screen_x(A+horizon,A,B,C,D);
	//load png
	central_body_tex.loadFromFile(currentworkingdirectory + "/Textures/T_" + aux_string + ".png");
	//make it look smooth
	central_body_tex.setSmooth(true);
	//assign the texture
	central_body.setTexture(central_body_tex);
	//change the sprite origin to the center
	central_body.setOrigin(central_body_tex.getSize().x/2, central_body_tex.getSize().y/2);
	//set the position (borrowing the screen_x,y from the player particle, so that we don't need to redefine them here)
	central_body.setPosition(player.screen_x(0,A,B,C,D),player.screen_y(0,A,B,C,D));
	//set scale according to the window size
	central_body.setScale(screen_horizon/(central_body_tex.getSize().x/2),screen_horizon/(central_body_tex.getSize().y/2));



	//now we do all the stations.
	amount_stations = convert_to_double(input);

	//the array size of stations is hardcoded to 10
	if (amount_stations > 10) {
		std::cout << "Warning, tried to load more than 10 stations. Excess stations will not be loaded." << std::endl;

		amount_stations = 10;
	}

	for (int i = 0; i < amount_stations; i++) {
		input >> aux_string;
		aux_x = convert_to_double(input);
		aux_y = convert_to_double(input);
		aux_vx = convert_to_double(input);
		aux_vy = convert_to_double(input);

		stations[i].initialize(aux_string,aux_x,aux_y,aux_vx,aux_vy,M,a,width,height,stretch,A,B,C,D,false);

	}



}

//Memberfunctions

//this does the same as the constructor: it loads all the data from the file specified by the level number.
void level::change_level(int number_in, float width, float height, float stretch) {
	number = number_in;

	//input file containing the trajectory initial values
  std::ifstream input(currentworkingdirectory + "/Levels/Level_" + std::to_string(number) + ".txt");

  //check if the inputfile was opened correctly. If not exit with error code 1
  if (!input) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }

	//to read in player, central body and station names and physics data we need to temporarily save them
	std::string aux_string;
	double aux_x;
	double aux_y;
	double aux_vx;
	double aux_vy;

	//read in the world bounds
	A = convert_to_double(input);
	B = convert_to_double(input);
	C = convert_to_double(input);
	D = height*(B-A)/width + C;

	//read in the central body parameters and calculate the horizon
	M = convert_to_double(input);
	a = convert_to_double(input);



	////read in the player name and physics data
	input >> aux_string;
	aux_x = convert_to_double(input);
	aux_y = convert_to_double(input);
	aux_vx = convert_to_double(input);
	aux_vy = convert_to_double(input);

	//initialize the player with the next some doubles from the file
	player.initialize(aux_string,aux_x,aux_y,aux_vx,aux_vy,M,a,width,height,stretch,A,B,C,D,true);



	//read in central body name
	input >> aux_string;

	//initialize the central body with all the data we now have
	horizon = M + sqrt(M*M - a*a);
	screen_horizon = player.screen_x(A+horizon,A,B,C,D);
	//load png
	central_body_tex.loadFromFile(currentworkingdirectory + "/Textures/T_" + aux_string + ".png");
	//make it look smooth
	central_body_tex.setSmooth(true);
	//assign the texture
	central_body.setTexture(central_body_tex,true);
	//change the sprite origin to the center
	central_body.setOrigin(central_body_tex.getSize().x/2, central_body_tex.getSize().y/2);
	//set the position (borrowing the screen_x,y from the player particle, so that we don't need to redefine them here)
	central_body.setPosition(player.screen_x(0,A,B,C,D),player.screen_y(0,A,B,C,D));
	//set scale according to the window size
	central_body.setScale(5.0/2*screen_horizon/(central_body_tex.getSize().x/2),5.0/2*screen_horizon/(central_body_tex.getSize().y/2));



	//now we do all the stations.
	amount_stations = convert_to_double(input);

	//the array size of stations is hardcoded to 10
	if (amount_stations > 10) {
		std::cout << "Warning, tried to load more than 10 stations. Excess stations will not be loaded." << std::endl;

		amount_stations = 10;
	}

	for (int i = 0; i < amount_stations; i++) {
		input >> aux_string;
		aux_x = convert_to_double(input);
		aux_y = convert_to_double(input);
		aux_vx = convert_to_double(input);
		aux_vy = convert_to_double(input);

		//initialize the player with the next some doubles from the file
		stations[i].initialize(aux_string,aux_x,aux_y,aux_vx,aux_vy,M,a,width,height,stretch,A,B,C,D,false);
	}
}

particle& level::getPlayer() {
	return player;
}

sf::Sprite& level::getCentralBody() {
	return central_body;
}

particle& level::getStation(int i) {
	return stations[i];
}

int level::getAmountStations() {
	return amount_stations;
}

//dt will already have the time factor in it. we just need to pass it again for the rotation of the central body
void level::simulate(double dt, double time_factor, bool launched, bool reached_goal) {

	//rotate the central body
	central_body.setRotation(central_body.getRotation() - a*delta_rotation*time_factor);

	//simulate the player
	if (launched) {
		player.evolve(dt,A,B,C,D,true);
	}

	//simulate all stations
	for (int i = 0; i < amount_stations; i++) {
		//if we have not reached the goal yet, or i is not the goal station, simulate it
		if (!reached_goal || i != goal_station) {
			stations[i].evolve(dt,A,B,C,D,false);
		}
	}

}

//return if the player is colliding with the goal station.
bool level::player_hit_goal() {
	if (player.checkCollision(stations[goal_station])) {
		return true;
	}
	else {
		return false;
	}
}

//return if the player is colliding with a non goal station, if so explode the player and make the other station invsible
bool level::player_hit_obstacle() {
	//loop through all stations
	for (int i = 0; i < amount_stations; i++) {

		//do not check against the goal station
		if (i != goal_station) {

			//check if we hit the current station
			if (player.checkCollision(stations[i])) {
				player.explode(A,B,C,D);

				stations[i].make_invisible();

				return true;
			}

		}

	} //end loop

	//if non was hit, return false
	return false;
}
