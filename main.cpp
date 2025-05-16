//default cpp libraries
#include <unistd.h> //to get the current working directory
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
//simple and fast multimedia library
#include <SFML/Graphics.hpp>
//my own classes
#include "star_cluster.h"
#include "level.h"
#include "button.h"





//GLOBAL VARIABLES

//path of the current working directory
std::string currentworkingdirectory = get_current_dir_name();


//window size
float stretch = 0.9;

float width = 2560*stretch;
float height = 1440*stretch;

//math
double pi = 3.141592653589793;

//END OF GLOBAL VARIABLES





//AUXILIARY FUNCTIONS

//returns x as a string up to custom digits after the comma
std::string rounded(double x, int digits) {

  //take the part in front of the comma, if x = X2X1.x1x2x3 then only take X1X2 to the string for now
  std::string result = std::to_string((int)(x)) + ".";

  //cutoff the part in front of the comma, such that y = 0.x1x2x3 instead of X2X1.x1x2x3
  double y = x- (int)(x);

  for (int i = 1; i <= digits; i++) {

    //add the next digit after the comma. if y = 0.y1y2y3 this adds y1
    result = result + std::to_string((int)(10*y));

    //create y1.y2y3 and subtract y1.0 in order to be able to do the next iteration analogously
    y = 10*y - (int)(10*y);
  }

  return  result;
}

//setup a sprite based on a png. the given position is in screen coordinates in percent (values between 0 and 1).
//scaling works thus: : all textures are designed as if the window was 2560x1440. But it is stretch*2560 x stretch*1440.
void setup_sprite(sf::Sprite& sprite, sf::Texture& texture, std::string png, float x, float y, bool centered_origin = false, bool centered_bottom = false) {

  //load png
  texture.loadFromFile(currentworkingdirectory + "/Textures/T_" + png);
  //make it look smooth
  texture.setSmooth(true);
  //assign the texture
  sprite.setTexture(texture);

  if (centered_origin) {
    //change the sprite origin to the center
    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
  }

  if (centered_bottom) {
    //change the sprite origin to the center
    sprite.setOrigin(sprite.getOrigin().x, texture.getSize().y);
  }


  //set the position
  sprite.setPosition(x*width,y*height);
  //set scale according to the window size
  sprite.setScale(stretch, stretch);

}

void setup_text(sf::Text& text, sf::Font& font, int size, sf::Color color, float x, float y, bool center_origin = false) {
  //choose the font
  text.setFont(font);
  //set the character size
  text.setCharacterSize(size*stretch); // in pixels, not points!
  //set the color
  text.setFillColor(color);

  //center, if so desired
  if (center_origin) {
    text.setOrigin(text.getLocalBounds().width/2,text.getLocalBounds().height/2);
  }
  //set the position
  text.setPosition(x*width, y*height);

}

//END OF AUXILIARY FUNCTIONS





//MAIN PROGRAM

int main()
{

    //RENDERING BUISNESS

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //create the render window
    sf::RenderWindow window(sf::VideoMode(width, height), "Space Monkeys", sf::Style::Default, settings);

    //the game view, this is the game world. this view should be used per default
    sf::View gameview(sf::FloatRect(0.f, 0.f, width, height));

    //gui view, this is the user interface world and never moves or scales. gui elements should only be drawn when this view is active
    sf::View guiview(sf::FloatRect(0.f, 0.f, width, height));

    //font for all sorts of texts
    sf::Font font;
    font.loadFromFile(currentworkingdirectory + "/Fonts/Capsule.ttf");

    //END OF RENDERING BUISNESS





    //GUI ELEMENTS

      //TITLEPAGE
      sf::Sprite gui_titlepage;
      sf::Texture gui_titlepage_tex;

      setup_sprite(gui_titlepage,gui_titlepage_tex,"Titlepage.png",0,0);

      button button_play(0,"Play",0.05,0.95,width,height,stretch,false);

      button button_show_controls(1, "Controls",0.25,0.95,width,height,stretch,false);

      sf::Text text_title;
      setup_text(text_title, font, 200, sf::Color::White, 0.05, 0.05);
      text_title.setString("Space\nMonkeys");
      text_title.setStyle(sf::Text::Bold);

      sf::Text text_tutorial;
      setup_text(text_tutorial, font, 35, sf::Color::White, 0.6, 0.4);
      text_tutorial.setString("Space ship controls:\n\nLaunch                         Spacebar\nRotate launch velocity     A and D\nScale launch velocity      W and S\nFine Adjustments            Hold Shift\n\n\n\n\nLevel Controls:\n\nReset Level               R\nChange play rate        Q and E\n\nZoom                        Scroll\nReset Zoom               Middle Mouse\n\nGo to menu                Escape");


      //END OF TITLEPAGE



      //LEVEL MENU

      //not used
      sf::Sprite objective;
      sf::Texture objective_tex;
      setup_sprite(objective, objective_tex, "Objective.png", 0.05, 0.5);

      //END OF LEVEL MENU



      //HUD

      //general
      sf::Sprite hud;
      sf::Texture hud_tex;
      setup_sprite(hud,hud_tex,"HUD.png",0,0);

      sf::Text text_time_factor;
      setup_text(text_time_factor, font, 47, sf::Color(255,255,255), 0.055, 0.017);

      //physical stats
      sf::Text text_time_dilation;
      setup_text(text_time_dilation, font, 47, sf::Color(255,255,255), 0.58, 0.898);

      sf::Text text_speed;
      setup_text(text_speed, font, 47, sf::Color(255,255,255), 0.32, 0.898);

      //maximal dilation indicator
      sf::RectangleShape box_max_dilation(sf::Vector2f(180.f*stretch, 300.f*stretch));
      box_max_dilation.setOrigin(0,box_max_dilation.getSize().y);
      box_max_dilation.setPosition(0.9*width,0.96*height);
      box_max_dilation.setFillColor(sf::Color(2.4*44,2.4*100,2.4*14));

      sf::Text text_maximal_time_dilation;
      setup_text(text_maximal_time_dilation, font, 47, sf::Color(2.4*44,2.4*100,2.4*14), 0.9, 0.96);

      //velocity arrow
      sf::Sprite velocity_arrow;
      sf::Texture velocity_arrow_tex;

      setup_sprite(velocity_arrow,velocity_arrow_tex,"Arrow.png",0,0);
      velocity_arrow.setOrigin(velocity_arrow_tex.getSize().x/2, velocity_arrow_tex.getSize().y);

      //goal reached screen
      sf::Text text_banana_delivered;
      sf::Text text_max_dilation_delivered;
      setup_text(text_banana_delivered, font, 60, sf::Color::White, 0.5, 0.05);
      setup_text(text_max_dilation_delivered, font, 35, sf::Color(2.4*44,2.4*100,2.4*14), 0.5, 0.1);

      text_banana_delivered.setString("Bananas delivered");
      text_banana_delivered.setPosition(text_banana_delivered.getPosition().x-text_banana_delivered.getLocalBounds().width/2,text_banana_delivered.getPosition().y);

      text_max_dilation_delivered.setPosition(text_banana_delivered.getPosition().x,text_max_dilation_delivered.getPosition().y);

      //END OF HUD

    //END OF GUI ELEMENTS




    //ADMIN VARIABLES

    std::string active_star_cluster_name = "Alphani";

    star_cluster active_star_cluster(active_star_cluster_name, width, height, stretch);

    int amount_levels = active_star_cluster.getAmountStars();


    level active_level;

    int active_level_number = 1;

    bool on_titlepage = true;
    bool in_level_menu = false;
    bool in_level = false;

    bool show_controls = false;

    //END OF ADMIN VARIABLES




    //GAMEPLAY VARIABLES

    //world time
    double t = 0;
    //world delta time, later it will be determined by the frametime to guarante that the simulation runs in real time
    double dt = 0;

    //clocks

    //start a clock to measure the time that passed in the last frame
    sf::Clock clock;

    //a clock to measure the time between reaching the goal or crashing and automatic restaring of the level
    sf::Clock clock_time_since_end;

    //the current zoom factor. can be adjusted by player input and automatically if the player ship leaves the view.
    float zoom = 1;

    //to adjust how fast the simulation goes, and what the default should be
    double default_time_factor = 24;
    double time_factor = default_time_factor;

    //current and biggest achieved time dilation
    double Lorentzfactor = 1;
    double maximal_Lorentzfactor = 1;

    //booleans
    bool launched = false;

    bool reached_goal = false;

    bool crashed = false;

    //END OF GAMEPLAY VARIABLES




    //INPUT VARIABLES

    //deltas to adjust initial speed
    double delta_modulus = 0.0005;
    double delta_angle = 0.002;

    //chosen angles. these are used to restart with the same settings you launched it.
    double modulus;
    double angle;

    //END OF INPUT VARIABLES



    //set the default star_cluster active
    active_star_cluster.change_star_cluster(active_star_cluster_name, width, height, stretch);

    //for safety, set level 1 as active.
    active_level.change_level(active_level_number, width, height, stretch);

    //GAME LOOP
    while (window.isOpen())
    {
        //measure the time that passed in the last loopiteration and use it here as dt (so we are one behind). the timefactor is used to run the time at a higher rate, say at 5x
        dt = clock.restart().asSeconds();


        //EVENT POLLING
        sf::Event event;
        while (window.pollEvent(event)) {

          //SWITCH BETWEEN DIFFERENT EVENT TYPES
          switch (event.type)  {
            // window closed
            case sf::Event::Closed:
              window.close();
              break;

            //All keyboard events
            case sf::Event::KeyPressed:

              //close the game
              if (event.key.code == sf::Keyboard::Escape) {
                if (on_titlepage) {
                  window.close();
                }
                else if (in_level_menu) {
                  show_controls = false;

                  on_titlepage = true;
                  in_level_menu = false;
                }
                else if (in_level) {
                  in_level_menu = true;
                  in_level = false;

                  //reset the zoom
                  gameview.zoom(1/zoom);

                  zoom = 1;

                }

              }

              //launching the player
              if (event.key.code == sf::Keyboard::Space) {
                if (in_level && !launched && !reached_goal && !crashed) {
                  launched = true;

                  modulus = active_level.getPlayer().get_chart_velocity_modulus();
                  angle = active_level.getPlayer().get_chart_velocity_angle();
                }
              }

              //reset the level
              if (event.key.code == sf::Keyboard::R) {
                if (in_level) {
                  //reset the gameplay variables to default
                  launched = false;
                  reached_goal = false;
                  crashed = false;

                  Lorentzfactor = 1;
                  maximal_Lorentzfactor = 1;

                  t = 0;

                  //reset the level by forcing it to reload its data from the input file (we change the level to itself).
                  active_level.change_level(active_level_number, width, height, stretch);

                  //set initial speed to what we had previously
                  active_level.getPlayer().set_chart_velocity(modulus, angle, true);
                }
              }

              //increase and decrease the time factor
              if (in_level && event.key.code == sf::Keyboard::Q) {
                if (time_factor == 12) {
                  time_factor = 1;
                }
                else if (time_factor == 24) {
                  time_factor = 12;
                }
                else if (time_factor > 24) {
                  time_factor = time_factor / 4;
                }
              }
              if (in_level && event.key.code == sf::Keyboard::E) {
                if (time_factor == 1) {
                  time_factor = 12;
                }
                else if (time_factor == 12) {
                  time_factor = 24;
                }
                else if (time_factor < 384) {
                  time_factor = time_factor * 4;
                }
              }

              //for people who dont have a mouse: zooming with keyboard
              if (event.key.code == sf::Keyboard::Up && in_level) {
                //apply the zoom
                gameview.zoom(1/1.05);
                //update what zoom factor we have
                zoom = zoom/1.05;
              }
              if (event.key.code == sf::Keyboard::Down && in_level) {
                //apply the zoom
                gameview.zoom(1.05);
                //update what zoom factor we have
                zoom = zoom*1.05;
              }
              if (event.key.code == sf::Keyboard::Z && in_level) {
                //reset the zoom
                gameview.zoom(1/zoom);

                zoom = 1;
              }

              break; //end of keyboard events

            //mouse click events
            case sf::Event::MouseButtonPressed:
              if (event.mouseButton.button == sf::Mouse::Left)  {

                    //on the title page, check if we pressed the play button
                    if (on_titlepage) {
                      if (button_play.pressed(event.mouseButton.x, event.mouseButton.y) == 0) {
                          //set the game in the correct state
                          on_titlepage = false;
                          in_level_menu = true;

                      }

                      if (button_show_controls.pressed(event.mouseButton.x, event.mouseButton.y) == 1) {
                        if (show_controls) {
                          show_controls = false;
                        }
                        else {
                          show_controls = true;
                        }
                      }
                    }
                    //in the level menu, loop through all level buttons and see if any was clicked. if so make this the active level
                    else if (in_level_menu) {

                      for (int i = 0; i < amount_levels; i++) {

                        //take into account the zoom of the gameview by converting to world coordinates (where the world is the gameview).
                        float x_mouse = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), gameview).x;
                        float y_mouse = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), gameview).y;

                        //check if the i-th star sytem was pressed (by returning not -1) and if so set it's id as the active_level_number
                        int id_clicked = active_star_cluster.getStar(i).pressed(x_mouse,y_mouse);

                        if (id_clicked != -1) {

                          //select the clicked level id as the active one
                          active_level_number = id_clicked;

                          //set correct game state
                          in_level_menu = false;
                          in_level = true;

                          //reset the zoom
                          gameview.zoom(1/zoom);

                          zoom = 1;

                          //reset the timefactor
                          time_factor = default_time_factor;

                          //reset gameplay variables to default
                          launched = false;
                          reached_goal = false;
                          crashed = false;

                          Lorentzfactor = 1;
                          maximal_Lorentzfactor = 1;

                          t = 0;

                          //actually change to the desired level
                          active_level.change_level(active_level_number, width, height, stretch);

                          modulus = active_level.getPlayer().get_chart_velocity_modulus();
                          angle = active_level.getPlayer().get_chart_velocity_angle();

                        } //endif
                      } //end loop

                    } //end of left click
              }

              if (event.mouseButton.button == sf::Mouse::Middle && (in_level || in_level_menu)) {
                //reset the zoom
                gameview.zoom(1/zoom);

                zoom = 1;
              }
            break; //end of mouse click events


            //mouse scroll events
            case sf::Event::MouseWheelScrolled:
              //only catch the normal scrolling (not sideways), and only if we are actually in the level
              if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel && (in_level || in_level_menu)) {

                //scroll up = zoom in
                if (event.mouseWheelScroll.delta == -1) {
                  //apply the zoom
                  gameview.zoom(1.05);
                  //update what zoom factor we have
                  zoom = zoom*1.05;
                }
                //scroll down = zoom out
                else if (event.mouseWheelScroll.delta == 1) {
                  //apply the zoom
                  gameview.zoom(1/1.05);
                  //update what zoom factor we have
                  zoom = zoom/1.05;
                }

              }

            break; //end of mouse scroll events

            // we don't process other types of events
            default:
            break;

          } //END OF SWITCH OF EVENT TYPES

        }//END OF EVENT POLLING





        //GLOBAL INPUTS

        //increase the initial speed before launch
        if (in_level && !launched && !reached_goal && !crashed && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            active_level.getPlayer().stretch_chart_velocity(delta_modulus/10,true);
          }
          else {
            active_level.getPlayer().stretch_chart_velocity(delta_modulus,true);
          }

          modulus = active_level.getPlayer().get_chart_velocity_modulus();
          angle = active_level.getPlayer().get_chart_velocity_angle();
        }

        if (in_level && !launched && !reached_goal && !crashed && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            active_level.getPlayer().stretch_chart_velocity(-delta_modulus/10,true);
          }
          else {
            active_level.getPlayer().stretch_chart_velocity(-delta_modulus,true);
          }

          modulus = active_level.getPlayer().get_chart_velocity_modulus();
          angle = active_level.getPlayer().get_chart_velocity_angle();
        }

        //turn the initial velocity before launch
        if (in_level && !launched && !reached_goal && !crashed && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            active_level.getPlayer().rotate_chart_velocity(delta_angle/10, true);
          }
          else {
            active_level.getPlayer().rotate_chart_velocity(delta_angle, true);
          }

          modulus = active_level.getPlayer().get_chart_velocity_modulus();
          angle = active_level.getPlayer().get_chart_velocity_angle();
        }
        if (in_level && !launched && !reached_goal && !crashed && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            active_level.getPlayer().rotate_chart_velocity(-delta_angle/10, true);
          }
          else {
            active_level.getPlayer().rotate_chart_velocity(-delta_angle, true);
          }

          modulus = active_level.getPlayer().get_chart_velocity_modulus();
          angle = active_level.getPlayer().get_chart_velocity_angle();
        }

        //END OF GLOBAL INPUTS






        //LEVEL MENU SIMULATION PART

        //do this in titlepage, level menu and level on purpose, for immersion the cluster should always run
        active_star_cluster.simulate(dt,4);

        //END OF LEVEL MENU SIMULATION PART



        //GAMEPLAY

            //IN LEVEL: main purpose is to simulate the player within the active_level
            if (in_level) {

              if (!launched && !crashed && !reached_goal) {
                //put the velocity arrow to the player
                velocity_arrow.setPosition(active_level.getPlayer().getSprite().getPosition());
                velocity_arrow.setRotation(active_level.getPlayer().getSprite().getRotation());
                velocity_arrow.setScale(1,1+2*active_level.getPlayer().get_chart_velocity_modulus());

              }



              //do the physics simulation
              active_level.simulate(time_factor*dt, time_factor, launched, reached_goal);


              if (launched) {
                //retrieve the current time dilation
                Lorentzfactor = active_level.getPlayer().getLorentzfactor();
              }


              //if the current time dilation exceeds the biggest one so far, replace that one
              if (!launched && !reached_goal && !crashed) {

                //to update ui with initial Lorentzfactor
                Lorentzfactor = active_level.getPlayer().calcgetLorentzfactor(dt);
                //to scale the box correctly
                maximal_Lorentzfactor = active_level.getPlayer().calcgetLorentzfactor(dt);
              }
              else if (Lorentzfactor > maximal_Lorentzfactor) {
                maximal_Lorentzfactor = Lorentzfactor;
              }




              //update the gui texts
              text_time_dilation.setString(rounded(Lorentzfactor,3));

              text_maximal_time_dilation.setString(rounded(maximal_Lorentzfactor,3));

              text_speed.setString(rounded(active_level.getPlayer().spatial_speed(),3) + "c");

              text_time_factor.setString(std::to_string((int)(time_factor)));

              text_max_dilation_delivered.setString("with top dilation "+rounded(maximal_Lorentzfactor,3));

              //stretch the box of the maximal time dilation
              box_max_dilation.setScale(1,1+2/pi*atan(0.1*(maximal_Lorentzfactor-1))*3);
              text_maximal_time_dilation.setPosition(box_max_dilation.getPosition().x,box_max_dilation.getPosition().y-(1+2/pi*atan(0.1*(maximal_Lorentzfactor-1))*3)*box_max_dilation.getSize().y-1.2*text_maximal_time_dilation.getCharacterSize());




              //check for collision with the goal, but only if we are not currently in a state of having hit the goal and waiting for the next thing to happen.
              if (active_level.player_hit_goal() && !reached_goal && !crashed) {
                launched = false;
                reached_goal = true;

                clock_time_since_end.restart();

              }

              //check for collision with another station but only if we are not currently crashed already. if it hits, the checker function automatically explodes the player and make the other station invisible
              if (active_level.player_hit_obstacle() && !crashed) {
                launched = false;
                crashed = true;

                clock_time_since_end.restart();

              }

              //check if the player has been swallowed by the blackhole
              if (active_level.getPlayer().getSwallowed() && !crashed) {
                launched = false;
                crashed = true;

                clock_time_since_end.restart();

              }

              /*
              //if we have reached the end by reaching the goal, automatically load the next level after 5 seconds
              if (reached_goal && clock_time_since_end.getElapsedTime().asSeconds() > 5 && active_level_number < amount_levels) {

                //reset gameplay variables to default
                launched = false;
                reached_goal = false;
                crashed = false;

                Lorentzfactor = 1;
                maximal_Lorentzfactor = 1;

                t = 0;

                //make the next level the current level
                active_level_number += 1;

                //reload the level
                active_level.change_level(active_level_number, width, height, stretch);

              }
              */
              //if we have reached the end by reaching the goal, automatically go back to the level menu after 5 seconds
              if (reached_goal && clock_time_since_end.getElapsedTime().asSeconds() > 5) {

                //reset gameplay variables to default
                launched = false;
                reached_goal = false;
                crashed = false;

                in_level_menu = true;
                in_level = false;

                //reset the zoom
                gameview.zoom(1/zoom);

                zoom = 1;

              }

              //if we have reached the end by crashing, automatically restart after 2.5 seconds
              if (crashed && clock_time_since_end.getElapsedTime().asSeconds() > 2.5) {

                //reset gameplay variables to default
                launched = false;
                reached_goal = false;
                crashed = false;

                Lorentzfactor = 1;
                maximal_Lorentzfactor = 1;

                t = 0;

                //reload the level
                active_level.change_level(active_level_number, width, height, stretch);

                //set initial speed to what we had previously
                active_level.getPlayer().set_chart_velocity(modulus, angle, true);
              }

            }
            //END OF IN LEVEL



        //END OF GAMEPLAY




        //DRAWING: first use the the game view to draw game elements, then switch to the gui view and draw the gui elements
        window.clear();

        //GAME VIEW
        window.setView(gameview);

        if (in_level_menu) {
          window.draw(active_star_cluster.getCentralBody());

          for (int i = 0; i < active_star_cluster.getAmountStars(); i++) {
            window.draw(active_star_cluster.getStar(i).getSprite());
            window.draw(active_star_cluster.getStar(i).getText());
          }
        }

        if (in_level) {
          window.draw(active_level.getCentralBody());

          for (int i = 0; i < active_level.getAmountStations(); i++) {
            window.draw(active_level.getStation(i).getTrail());
            window.draw(active_level.getStation(i).getSprite());
          }

          if (!launched && !crashed && !reached_goal && active_level.getPlayer().spatial_speed() > 0) {
            window.draw(velocity_arrow);
          }

          window.draw(active_level.getPlayer().getTrail());
          window.draw(active_level.getPlayer().getSprite());

        }

        //GUI VIEW
        window.setView(guiview);

        if (on_titlepage) {
          window.draw(gui_titlepage);

          window.draw(button_play.getSprite());
          window.draw(button_play.getText());
          window.draw(button_show_controls.getSprite());
          window.draw(button_show_controls.getText());

          window.draw(text_title);

          if (show_controls) {
            window.draw(text_tutorial);
          }

        }

        else if (in_level_menu) {

        }

        else if (in_level) {
          window.draw(hud);

          window.draw(text_time_dilation);
          window.draw(box_max_dilation);
          window.draw(text_maximal_time_dilation);
          window.draw(text_speed);
          window.draw(text_time_factor);

          if (reached_goal) {
            window.draw(text_banana_delivered);
            window.draw(text_max_dilation_delivered);
          }
        }

        //display everything
        window.display();

        //END OF DRAWING





    }

    //END OF GAME LOOP





    return 0;
}

//END OF MAIN PROGRAM
