#pragma once
#include "Circle.h"

class HSV : public Circle{
    public:
        explicit HSV(int r) : Circle(r){
            init();
            top_label_.setString("HSV");

            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << slider_value;
            bottom_label_.setString("V = " + ss.str() );
        }

        sf::Color calculate_color(double alfa, double len)const{
            double s = len/radius_;
            double v = slider_value;
            double h = alfa;

            double c = v*s;
            double x = c * (1 - fabs( fmod(h/(M_PI/3), 2) - 1) );
            double m = v-c;

            double r,g,b;
            if( h <= (1*M_PI/3) ){
                r = c;
                g = x;
                b = 0;
            }else if( h <= (2*M_PI/3) ){
                r = x;
                g = c;
                b = 0;
            }else if( h <= (3*M_PI/3) ){
                r = 0;
                g = c;
                b = x;
            }else if( h <= (4*M_PI/3) ){
                r = 0;
                g = x;
                b = c;
            }else if( h <= (5*M_PI/3) ){
                r = x;
                g = 0;
                b = c;
            }else if( h <= (6*M_PI/3) ){
                r = c;
                g = 0;
                b = x;
            }else {
                r = g = b = -255;
            }
            return sf::Color( (r+m)*255, (g+m)*255, (b+m)*255 );
        }

        void update_circle(double new_value){
            if(fabs(slider_value - new_value) > 0.01){
                slider_value = new_value;

                std::stringstream ss;
                ss << std::fixed << std::setprecision(2) << slider_value;
                bottom_label_.setString("V = " + ss.str() );

                generate_bitmap();
                texture_->update(colors_);
            }
        }
};