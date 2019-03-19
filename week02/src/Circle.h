#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>



class Circle: public sf::Drawable, public sf::Transformable {
    protected:
        int radius_;
        std::unique_ptr<sf::Texture> texture_;
        std::unique_ptr<sf::Sprite> sprite_;
        sf::Font font_;
        sf::Text top_label_;
        sf::Text bottom_label_;
        sf::Uint8 *colors_;
        double slider_value = 0.5;

    public:
        explicit Circle(int radius):
            radius_(radius),
            texture_(new sf::Texture),
            sprite_(new sf::Sprite),
            colors_(new sf::Uint8[16 * radius_ * radius_]){
        };

        virtual ~Circle(){
            delete[] colors_;
        }

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const{
            states.transform *= getTransform();
            target.draw(*sprite_, states);
            target.draw(top_label_, states);
            target.draw(bottom_label_, states);
            return;
        }

        virtual sf::Color calculate_color(double alfa, double len)const = 0;

        void init(void){
            if (!font_.loadFromFile("Roboto-Regular.ttf")){
                std::cout << "Error: cannot load the font" << std::endl;
            }
            top_label_.setFont(font_);
            top_label_.setCharacterSize(12);
            top_label_.setFillColor(sf::Color::Black);
            top_label_.setPosition(0,0);

            bottom_label_.setFont(font_);
            bottom_label_.setCharacterSize(12);
            bottom_label_.setFillColor(sf::Color::Black);
            bottom_label_.setPosition(2*radius_ - 50, 2*radius_);

            texture_->create(2*radius_, 2*radius_);
            generate_bitmap();
            texture_->update(colors_);
            sprite_->setTexture(*texture_);
        }

        void generate_bitmap(void){
            #pragma omp parallel for
            for(int i = 0; i < 2*radius_; i++){
                for(int j = 0; j < 2*radius_; j++){
                    double x = i - radius_;
                    double y = radius_ - j;

                    double angle = atan2(y,x);
                    if(angle < 0){
                        angle = angle + 2*M_PI;
                    }
                    double r = sqrt(x*x + y*y);
                    sf::Color color = calculate_color(angle, r);

                    if(r <= radius_){
                        colors_[ 4*(j*2*radius_ + i) + 0] = color.r;
                        colors_[ 4*(j*2*radius_ + i) + 1] = color.g;
                        colors_[ 4*(j*2*radius_ + i) + 2] = color.b;
                        colors_[ 4*(j*2*radius_ + i) + 3] = 255;
                    }else {
                        colors_[ 4*(j*2*radius_ + i) + 0] = 0;
                        colors_[ 4*(j*2*radius_ + i) + 1] = 0;
                        colors_[ 4*(j*2*radius_ + i) + 2] = 0;
                        colors_[ 4*(j*2*radius_ + i) + 3] = 0;
                    }
                }
            }
            return;
        }
};