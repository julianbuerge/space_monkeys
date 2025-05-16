#include "button.h"

//Constructors
button::button() {
  currentworkingdirectory = get_current_dir_name();

  id = -1;
}

button::button(int i, std::string name, float x, float y, float width, float height, float stretch, bool center_origin = false) {
  currentworkingdirectory = get_current_dir_name();

  font.loadFromFile(currentworkingdirectory + "/Fonts/Capsule.ttf");

  id = i;

  //load png
	texture.loadFromFile(currentworkingdirectory + "/Textures/T_Button.png");
	//make it look smooth
	texture.setSmooth(true);
	//assign the texture
	sprite.setTexture(texture);
	//change the sprite origin to the center
  if (center_origin) {
      sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
  }
	//set the position
	sprite.setPosition(x*width,y*height);
	//set scale according to the window size
	sprite.setScale(stretch, stretch);


  //setup the text

  //choose the font
  text.setFont(font);
  //set the character size
  text.setCharacterSize(80*stretch); // in pixels, not points!
  //set the color
  text.setFillColor(sf::Color::White);
  //set the position
  text.setPosition(x*width+stretch*texture.getSize().x/14, y*height-stretch*texture.getSize().y-1.1*text.getCharacterSize());
  //set the string
  text.setString(name);

}


//Memberfunctions

//same as constructor
void button::initialize(int i, std::string name, float x, float y, float width, float height, float stretch, bool center_origin) {
  currentworkingdirectory = get_current_dir_name();

  font.loadFromFile(currentworkingdirectory + "/Fonts/Capsule.ttf");

  id = i;

  //load png
	texture.loadFromFile(currentworkingdirectory + "/Textures/T_Button.png");
	//make it look smooth
	texture.setSmooth(true);
	//assign the texture
	sprite.setTexture(texture);
	//change the sprite origin to the center
  if (center_origin) {
      sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
  }
	//set the position
	sprite.setPosition(x*width,y*height);
	//set scale according to the window size
	sprite.setScale(stretch, stretch);

  //choose the font
  text.setFont(font);
  //set the character size
  text.setCharacterSize(80*stretch); // in pixels, not points!
  //set the color
  text.setFillColor(sf::Color::White);
  //set the position
  text.setPosition(x*width+stretch*texture.getSize().x/14, y*height-stretch*texture.getSize().y-1.1*text.getCharacterSize());
  //set the string
  text.setString(name);

}

//return the sprite for rendering
sf::Sprite& button::getSprite() {
  return sprite;
}

sf::Text& button::getText() {
  return text;
}

//return the button id if pressed
int button::pressed(float x, float y) {

  //get the sprite bounding box
  sf::FloatRect bounding_box_sprite = sprite.getGlobalBounds();
  sf::FloatRect bounding_box_text = text.getGlobalBounds();

  sf::Vector2f clicked_point(x,y);

  if (bounding_box_sprite.contains(clicked_point) || bounding_box_text.contains(clicked_point)) {
    return id;
  }
  else {
    return -1;
  }

}
