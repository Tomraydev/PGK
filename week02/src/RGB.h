#pragma once
#include "Circle.h"

class RGB : public Circle{
    public:
        explicit RGB(int r) : Circle(r){
            init();
            top_label_.setString("RGB");
            bottom_label_.setString("B = " + std::to_string( (int)(slider_value*255) ) ); 
        }

        sf::Color calculate_color(double alfa, double len)const{
            double r,g,b;
            r = (len/radius_) * 255.0;
            g = (alfa/(2.0*M_PI)) * 255.0;
            b = slider_value * 255.0;
            return sf::Color( r, g, b);
        }

        void update_circle(double new_value){
            if(fabs(slider_value - new_value) > 0.01){
                slider_value = new_value;
                bottom_label_.setString("B = " + std::to_string( (int)(slider_value*255)) );

                generate_bitmap();
                texture_->update(colors_);
            }
        }
};