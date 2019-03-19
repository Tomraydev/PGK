#pragma once
#include "Circle.h"

class CMY : public Circle{
    public:
        explicit CMY(int r) : Circle(r){
            init();
            top_label_.setString("CMY");
            bottom_label_.setString("Y = " + std::to_string( (int)(slider_value*100) ) + "%" );
        }

        sf::Color calculate_color(double alfa, double len)const{
            double c = len/radius_;
            double m = alfa/(2*M_PI);
            double y = slider_value;

            double r,g,b;
            r = (1-c)*255.0;
            g = (1-m)*255.0;
            b = (1-y)*255.0;

            return sf::Color( r, g, b);
        }

        void update_circle(double new_value){
            if(fabs(slider_value - new_value) > 0.01){
                slider_value = new_value;
                bottom_label_.setString("Y = " + std::to_string( (int)(slider_value*100) ) + "%" );

                generate_bitmap();
                texture_->update(colors_);
            }
        }
};