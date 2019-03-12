#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Shapes_container {
	private:
		vector<sf::Drawable *> s_vec;
		sf::RenderWindow * s_window;
		sf::Texture t_;
	public:
		Shapes_container(sf::RenderWindow * win): s_window(win){};
		~Shapes_container(){
			for(int i = 0; i < s_vec.size(); i++){
				delete s_vec[i];
			}
			s_vec.clear();
		};

		void add(sf::Drawable *obj){
			s_vec.push_back(obj);
			return;
		}

		void draw(){
			for(int i = 0; i < s_vec.size(); i++){
				s_window->draw(*(s_vec[i]));
			}
			return;
		}
		void set_texture(sf::Texture &tex){
			t_ = tex;
		}
		sf::Texture* get_texture(void){
			return &t_;
		}
        void undo(void){
            if(s_vec.size()) s_vec.pop_back();
            return;
        }
};