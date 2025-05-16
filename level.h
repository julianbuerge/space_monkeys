#ifndef LEVEL_H
#define LEVEL_H

//default cpp libraries
#include <unistd.h> //to get the current working directory
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
//simple and fast multimedia library
#include <SFML/Graphics.hpp>
//my own classes
#include "particle.h"
//my utility
#include "auxiliary_functions.h"

class level {
    private:

    //Membervariables
    std::string currentworkingdirectory;

    //identifier of the level. used to load the correct data from files.
    int number;

    //player particle.
    particle player;

    //central body sprite
    sf::Sprite central_body;
    sf::Texture central_body_tex;

    //array of all other particles.
    particle stations[10];
    //amount of actual stations (may be less than or at most 10)
    int amount_stations;
    //index of the station which is the goal. currently hardcoded to be the first.
    int goal_station = 0;

    //central body parameters: mass M and rotation a.
    double M;
    double a;

    double horizon;
    double screen_horizon;

    //rotation animation delta: each frame the central body will rotate by a*delta_rotation degrees.
    double delta_rotation = 0.005;

    //world bounds
		float A;
		float B;
		float C;
		float D;

    public:

    //Memberfunctions



    //Constructors
    level();
    level(int number_in, float width, float height, float stretch);


    //Membervariables


    //Memberfunctions

    //this does the same as the constructor: it loads all the data from the file specified by the level number.
    void change_level(int number_in, float width, float height, float stretch);

    particle& getPlayer();
    sf::Sprite& getCentralBody();
    particle& getStation(int i);
    int getAmountStations();

    //dt will already have the time factor in it. we just need to pass it again for the rotation of the central body
    void simulate(double dt, double time_factor, bool launched, bool reached_goal);

    //return if the player is colliding with the goal station.
    bool player_hit_goal();

    //return if the player is colliding with a non goal station, if so explode the player and make the other station invsible
    bool player_hit_obstacle();

    //return if station i hit another station. NOT IMPLEMENTED
    bool station_hit_station(int i);

};

#endif
