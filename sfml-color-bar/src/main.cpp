#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Color_bar{
    public:
        Color_bar(int x, int y): size_x(x), size_y(y){
            colors_pixels = new sf::Uint8[size_x * size_y * 4];

            colors_texture = new sf::Texture();
            colors_texture->create(size_x, size_y);

            colors_sprite = new sf::Sprite();
        }
        ~Color_bar(){
            delete colors_pixels;
            delete colors_texture;
            delete colors_sprite;
        };

        inline void set_pixel(unsigned int x, unsigned int y,unsigned char r, unsigned char g, unsigned char b){
		colors_pixels[4 * (y * size_x + x) + 0] = r;
		colors_pixels[4 * (y * size_x + x) + 1] = g;
		colors_pixels[4 * (y * size_x + x) + 2] = b;
		colors_pixels[4 * (y * size_x + x) + 3] = 255;
	    }

        sf::Uint8 *colors_pixels;
	    sf::Texture *colors_texture;
        sf::Sprite *colors_sprite;

    private:
        int size_x;
        int size_y;
};

int main(void){

    Color_bar cb(1536,30);
    for(unsigned int x = 0; x < 256; x++){
        for(unsigned int y = 0; y < 30; y++){
            cb.set_pixel(x + 0*256, y, 255, x, 0);
            cb.set_pixel(x + 1*256, y, 255-x, 255, 0);
            cb.set_pixel(x + 2*256, y, 0, 255, x);
            cb.set_pixel(x + 3*256, y, 0, 255-x, 255);
            cb.set_pixel(x + 4*256, y, x, 0, 255);
            cb.set_pixel(x + 5*256, y, 255, 0, 255-x);
        }
    }

		
		cb.colors_texture->update(cb.colors_pixels);		
		cb.colors_sprite->setTexture(*cb.colors_texture);
		cb.colors_sprite->setPosition(1, 1);

    sf::Event event;
    sf::RenderWindow window(
		sf::VideoMode(1536, 600),
		"GFK Lab 02 - Tomasz Rajchel",
		sf::Style::Titlebar | sf::Style::Close
	);

    window.setFramerateLimit(60);

    while (window.isOpen()){
		window.clear(sf::Color::Black);

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
                    }
                }
            }



        };
        window.draw(*cb.colors_sprite);
        window.display();
    }


    return 0;
}