#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "font.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Menu : public sf::Drawable{
private:
	sf::Font font;
	sf::Text *text;
	sf::RectangleShape *rectangle;

	sf::Texture *colors_texture;
	sf::Sprite *colors_sprite;
	sf::Uint8 *colors_pixels;
	const unsigned int colors_size_x = 765;
	const unsigned int colors_size_y = 60;
	inline void draw_to_color_pixels(unsigned int x, unsigned int y,unsigned char r, unsigned char g, unsigned char b){
		colors_pixels[4 * (y * colors_size_x + x) + 0] = r;
		colors_pixels[4 * (y * colors_size_x + x) + 1] = g;
		colors_pixels[4 * (y * colors_size_x + x) + 2] = b;
		colors_pixels[4 * (y * colors_size_x + x) + 3] = 255;
	}

	string current_key = "";
	sf::Color draw_color = sf::Color::Red;
	sf::Color fill_color = sf::Color::White;
	sf::RectangleShape *f_rec;
	sf::RectangleShape *b_rec;

public:
	Menu(){
		font.loadFromMemory(font_data, font_data_size);
		text = new sf::Text;
		text->setFont(font);
		text->setCharacterSize(12);
		text->setFillColor(sf::Color::White);

		rectangle = new sf::RectangleShape(sf::Vector2f(796, 536));
		rectangle->setFillColor(sf::Color::Transparent);
		rectangle->setOutlineColor(sf::Color::White);
		rectangle->setOutlineThickness(1.0f);
		rectangle->setPosition(2, 62);

		f_rec = new sf::RectangleShape(sf::Vector2f(29, 29));
		f_rec->setFillColor(draw_color);
		f_rec->setPosition(765 + 4, 1);

		b_rec = new sf::RectangleShape(sf::Vector2f(29, 29));
		b_rec->setFillColor(fill_color);
		b_rec->setPosition(765 + 4, 31);

		unsigned int x, y;
		colors_pixels = new sf::Uint8[colors_size_x * colors_size_y * 4];
		for (x = 0; x<255; x++){
			for (y = 0; y < 30; y++){
				draw_to_color_pixels(x, y, x, 255, 0);
				draw_to_color_pixels(x+255, y, 255, 255-x, 0);
				draw_to_color_pixels(x + 510, y, 255, 0, x);
				draw_to_color_pixels(254 - x, y+30, 0, 255, 255-x);
				draw_to_color_pixels(509 - x, y + 30, 0, x, 255 );
				draw_to_color_pixels(764 - x, y + 30, 255-x, 0, 255);
			}
		}

		colors_texture = new sf::Texture();
		colors_texture->create(colors_size_x, colors_size_y);
		colors_texture->update(colors_pixels);

		colors_sprite = new sf::Sprite();
		colors_sprite->setTexture(*colors_texture);
		colors_sprite->setPosition(1, 1);
	}
	~Menu(){
		delete text;
		delete rectangle;
		delete colors_pixels;
		delete colors_texture;
		delete colors_sprite;
		delete f_rec;
		delete b_rec;
	}

	void outtextxy(sf::RenderTarget& target, float x, float y, string str)const{
		text->setPosition(x, y); 
		text->setString(str); 
		target.draw(*text);
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const{
		outtextxy(target,5, 600, "f - wybor koloru rysowania");
		outtextxy(target, 5, 615, "b - wybor koloru wypelniania");
		outtextxy(target, 5, 630, "l - rysowanie linii");

		outtextxy(target, 200, 600, "r - rysowanie prostokata");
		outtextxy(target, 200, 615, "a - rysowanie wypelnionego prostokata");
		outtextxy(target, 200, 630, "c - rysowanie okregu");

		outtextxy(target, 470, 600, "w - zapis do pliku");
		outtextxy(target, 470, 615, "o - odczyt z pliku");
		outtextxy(target, 470, 630, "esc - wyjscie");

		outtextxy(target, 650, 615, "Aktualne:");

		outtextxy(target, 705, 615, current_key);

		target.draw(*rectangle);
		target.draw(*colors_sprite);

		f_rec->setFillColor(draw_color);
		b_rec->setFillColor(fill_color);
		target.draw(*f_rec);
		target.draw(*b_rec);
	}

	sf::Color get_draw_color(void){
		return draw_color;
	}
	sf::Color get_fill_color(void){
		return fill_color;
	}
	void set_draw_color(const sf::Color &c){
		draw_color = c;
	}
	void set_fill_color(const sf::Color &c){
		fill_color = c;
	}

	sf::Color pick_color(const sf::Vector2f &mouse){
		int x = mouse.x;
		int y = mouse.y;
		sf::Color c = sf::Color(colors_pixels[4 * (y * colors_size_x + x) + 0],
								colors_pixels[4 * (y * colors_size_x + x) + 1],
								colors_pixels[4 * (y * colors_size_x + x) + 2]);
		return c;
	}

	bool is_in_drawing_area(const sf::Vector2f &mouse )const{
		if(mouse.x < 2 || mouse.x > 798){
			return false;
		}else if (mouse.y < 62 || mouse.y > 598){
			return false;
		}else {
			return true;
		}
	}

	bool is_in_color_picker(const sf::Vector2f &mouse )const{
		if(mouse.x < 2 || mouse.x > 765){
			return false;
		}else if (mouse.y < 0 || mouse.y > 60){
			return false;
		}else {
			return true;
		}
	}

	void set_current_key(sf::Keyboard::Key k){
		switch(k){
			case sf::Keyboard::Key::L:{
				current_key = "l";
				break;
			}
			case sf::Keyboard::Key::F:{
				current_key = "f";
				break;
			}
			case sf::Keyboard::Key::B:{
				current_key = "b";
				break;
			}
			case sf::Keyboard::Key::R:{
				current_key = "r";
				break;
			}
			case sf::Keyboard::Key::A:{
				current_key = "a";
				break;
			}
			case sf::Keyboard::Key::C:{
				current_key = "c";
				break;
			}
			default:{
				current_key = "";
				break;
			}
		}
	}
};