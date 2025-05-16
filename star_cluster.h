#ifndef star_cluster_H
#define star_cluster_H

//default cpp libraries
#include <unistd.h> //to get the current working directory
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
//simple and fast multimedia library
#include <SFML/Graphics.hpp>
//my own classes
#include "star_system.h"
//my utility
#include "auxiliary_functions.h"

class star_cluster {
    private:

    //Membervariables
    std::string currentworkingdirectory;

    //identifier of the star_cluster. used to load the correct data from files.
    std::string name;


    //central body sprite
    sf::Sprite central_body;
    sf::Texture central_body_tex;

    //array of all other star_systems.
    star_system stars[100];
    //amount of actual stars (may be less than or at most 100)
    int amount_stars;

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



    //Memberfunctions

    public:

    //Constructors
    star_cluster();
    star_cluster(std::string name_in, float width, float height, float stretch);


    //Membervariables


    //Memberfunctions

    //this does the same as the constructor: it loads all the data from the file specified by the star_cluster name.
    void change_star_cluster(std::string name_in, float width, float height, float stretch);

    sf::Sprite& getCentralBody();
    star_system& getStar(int i);
    int getAmountStars();

    //dt will not have the time factor in it.
    void simulate(double dt, double time_factor);

};

#endif
