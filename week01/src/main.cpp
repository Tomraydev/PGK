#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "font.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "Menu.h"
#include "Shapes_container.h"

using namespace std;

struct User_state {
	public:
	sf::Vector2f mouse_position;
	sf::Vector2f click_position;
	sf::Keyboard::Key pressed_key;
	bool is_clicked_in_draw_area = false;
	bool is_clicked_in_color_picker = false;
	bool is_mouse_released = false;
	bool is_key_pressed = false;

};

int main(){
	sf::RenderWindow window(
		sf::VideoMode(800, 650),
		"GFK Lab 01 - Tomasz Rajchel",
		sf::Style::Titlebar | sf::Style::Close
	);
	sf::Event event;
	Menu menu;				
	User_state us;
	Shapes_container sc(&window);


	window.setFramerateLimit(60);
	window.setPosition(sf::Vector2i(500,20));

	while (window.isOpen()){
		window.clear(sf::Color::Black);
		sc.draw();
		
		while (window.pollEvent(event)){

			switch (event.type){

				case sf::Event::Closed:{
					window.close();
					break;
				}

				case sf::Event::KeyPressed:{
					if(event.key.code == sf::Keyboard::Escape){
						window.close();
						break;

					}else if (event.key.code == sf::Keyboard::W){
						string filename = "output.bmp";
						//cout << "working" << endl;
						sf::Texture tex;
						tex.create(window.getSize().x, window.getSize().y);
						tex.update(window);

						sf::Image img;
						img.create(796, 536, sf::Color::Black);
						img.copy(tex.copyToImage(), 0,0, sf::IntRect(2, 62, 796, 536) );
						img.saveToFile(filename);

						break;

					}else if (event.key.code == sf::Keyboard::O){
						string filename = "output.bmp";

						sf::Texture tex;
						if (!tex.loadFromFile(filename)){
							break;
						}
						sc.set_texture(tex);
						cout << "load successfull" << endl;
						
						sf::Sprite *spr = new sf::Sprite(*sc.get_texture());		
						spr->setPosition(sf::Vector2f(2,62));
						sc.add(spr);

						break;
					}else if (event.key.code == sf::Keyboard::Z){
						sc.undo();
						break;
					}
					
					else {
						us.is_key_pressed = true;
						us.is_mouse_released = false;
						us.pressed_key = event.key.code;
						menu.set_current_key(event.key.code);
					}

					break;
					//cout << event.key.code << endl;
				}

				case sf::Event::MouseButtonPressed:{
					//cout << "Pressed\t" << event.mouseButton.x << "\t" << event.mouseButton.y << endl;
					us.click_position = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
					us.is_clicked_in_draw_area = menu.is_in_drawing_area(us.click_position);
					us.is_clicked_in_color_picker = menu.is_in_color_picker(us.click_position);
					break;
				}

				case sf::Event::MouseButtonReleased:{
					//cout << "Released\t" << event.mouseButton.x << "\t" << event.mouseButton.y << endl;
					us.is_mouse_released = true;
					break;
				}

				case sf::Event::MouseMoved:{
					//cout << "Moved\t" << event.mouseMove.x << "\t" << event.mouseMove.y << endl;
					if(menu.is_in_drawing_area(sf::Vector2f(event.mouseMove.x, event.mouseMove.y) ) ){
						us.mouse_position = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
					}
					//cout << us.mouse_position.x << "\t" << us.mouse_position.y << endl;
					break;
				}

				default: break;
			}
		}

		if(us.is_clicked_in_draw_area){
			switch(us.pressed_key){
				case sf::Keyboard::Key::L: {
					sf::VertexArray *line = new sf::VertexArray(sf::LinesStrip, 2);
					(*line)[0].position = us.click_position;
					(*line)[1].position = us.mouse_position;
					(*line)[0].color = menu.get_draw_color();
					(*line)[1].color = menu.get_fill_color();

					window.draw(*line);

					if(us.is_mouse_released){
						sc.add(line);
					}else {
						delete line;
					}

					break;
				}

				case sf::Keyboard::Key::R: {
					sf::RectangleShape *rec = new sf::RectangleShape(sf::Vector2f(us.mouse_position - us.click_position));
					rec->setOutlineColor(menu.get_draw_color() );
					rec->setFillColor(sf::Color::Transparent);
					rec->setPosition(us.click_position);
					rec->setOutlineThickness(1.0);

					window.draw(*rec);

					if(us.is_mouse_released){
						sc.add(rec);
					}else {
						delete rec;
					}
					break;
				}

				case sf::Keyboard::Key::A: {
					sf::RectangleShape *rec = new sf::RectangleShape(sf::Vector2f(us.mouse_position - us.click_position));
					rec->setOutlineColor(menu.get_draw_color() );
					rec->setFillColor(menu.get_fill_color());
					rec->setPosition(us.click_position);
					rec->setOutlineThickness(1.0);

					window.draw(*rec);

					if(us.is_mouse_released){
						sc.add(rec);
					}else {
						delete rec;
					}
					break;
				}

				case sf::Keyboard::Key::C: {
					sf::CircleShape *circle = new sf::CircleShape();
					circle->setOutlineColor(menu.get_draw_color() );
					circle->setFillColor(sf::Color::Transparent);
					circle->setOutlineThickness(1.0);
					circle->setPosition(us.click_position);


					double x = us.mouse_position.x - us.click_position.x;
					double y = us.mouse_position.y - us.click_position.y;
					double r = sqrt(x*x + y*y)/2;
					double angle = atan2(y,x) * (180/M_PI) - 45; // in degrees

					circle->setRadius(r);
					circle->rotate(angle);
					circle->move(sf::Vector2f(
						-(r*sqrt(2)-r) * cos((angle + 45) * M_PI / 180),
						-(r*sqrt(2)-r) * sin((angle + 45) * M_PI / 180)
					));
					//cout << "x = " << x << "\t" << "y = " << y << "\t" << "angle = " << angle << endl;


					window.draw(*circle);

					if(us.is_mouse_released){
						sc.add(circle);
					}else {
						delete circle;
					}
					break;
				}

				default: break;
			}
			if(us.is_mouse_released){
				us.is_clicked_in_draw_area = false;
				us.is_mouse_released = false;
			}
		}

		if(us.is_clicked_in_color_picker){
			switch(us.pressed_key){
				case sf::Keyboard::Key::F:{
					menu.set_draw_color(menu.pick_color(us.click_position));
					break;
				}
				case sf::Keyboard::Key::B:{
					menu.set_fill_color(menu.pick_color(us.click_position));
					break;
				}
				default: break;
			}
			us.is_clicked_in_color_picker = false;
		}

		window.draw(menu);
		window.display();
	}
	return 0;
}