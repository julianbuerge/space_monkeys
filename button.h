#ifndef BUTTON_H
#define BUTTON_H

//default cpp libraries
#include <unistd.h> //to get the current working directory
#include <iostream>
#include <fstream>
#include <string>
//simple and fast multimedia library
#include <SFML/Graphics.hpp>

class button {
  private:

  //Membervariables
  std::string currentworkingdirectory;

  int id;

  sf::Sprite sprite;
  sf::Texture texture;

  sf::Font font;
  sf::Text text;

  //Memberfunctions

  public:

  //Constructors
  button();

  //x,y are values between 0 and 1 giving the button position on the screen.
  button(int i, std::string name, float x, float y, float width, float height, float stretch, bool center_origin);

  //Memberfunctions

  //same as constructor
  void initialize(int i, std::string name, float x, float y, float width, float height, float stretch, bool center_origin);

  //return the sprite for rendering
  sf::Sprite& getSprite();

  //return the text for rendering
  sf::Text& getText();

  //return the button number id if it was pressed (check if x,y are within the sprite)
  int pressed(float x, float y);

};

#endif
