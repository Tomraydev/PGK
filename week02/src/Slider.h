#pragma once
#include <SFML/Graphics.hpp>

class Slider : public sf::Drawable, public sf::Transformable {
    public:
        Slider(int w = 40, int h = 255) : width_(w), height_(h){
            rectangle = new sf::RectangleShape(sf::Vector2f(width_, height_));
            rectangle->setOutlineColor(sf::Color::Black);
		    rectangle->setOutlineThickness(1.0);
            rectangle->setPosition(650, 20);

            generate_bitmap();
            tex->create(width_, height_);
            tex->update(colors_);
            rectangle->setTexture(tex);

            generate_marker();
        }
        ~Slider(){
            delete rectangle;
            delete tex;
            delete marker_tex;
            delete marker_sprite;
            delete[] colors_;
            delete[] marker_pixels;
        }

        void draw(sf::RenderTarget &target, sf::RenderStates states)const{
            states.transform *= getTransform();
            target.draw(*rectangle, states);
            target.draw(*marker_sprite, states);
            return;
        }

        void generate_bitmap(){
            colors_ = new sf::Uint8[16*width_*height_];
            tex = new sf::Texture;
            for(int y = 0; y < height_; y++){
                for(int x = 0; x < width_; x++){
                    colors_[4 * (y * width_ + x) + 0] = ((double)y/height_)*255;
                    colors_[4 * (y * width_ + x) + 1] = ((double)y/height_)*255;
                    colors_[4 * (y * width_ + x) + 2] = ((double)y/height_)*255;
                    colors_[4 * (y * width_ + x) + 3] = 255;
                }
            }
            return;
        }

        void generate_marker(){
            marker_w = width_ + 30;
            marker_pixels = new sf::Uint8[16*marker_w * 2];
            marker_tex = new sf::Texture;
            marker_sprite = new sf::Sprite;
            marker_position = 128;
            value_ = 0.5;
            for(int y = 0; y < 2; y++){
                for(int x = 0; x < marker_w; x++){
                    if(x < 12 || x > marker_w - 12){
                        marker_pixels[4 * (y * (marker_w) + x) + 0] = 0;
                        marker_pixels[4 * (y * (marker_w) + x) + 1] = 0;
                        marker_pixels[4 * (y * (marker_w) + x) + 2] = 0;
                        marker_pixels[4 * (y * (marker_w) + x) + 3] = 255;
                    }else {
                        marker_pixels[4 * (y * (marker_w) + x) + 0] = 0;
                        marker_pixels[4 * (y * (marker_w) + x) + 1] = 0;
                        marker_pixels[4 * (y * (marker_w) + x) + 2] = 0;
                        marker_pixels[4 * (y * (marker_w) + x) + 3] = 0;
                    }
                }
            }
            

            marker_tex->create(marker_w, 2);
            marker_tex->update(marker_pixels);
            marker_sprite->setTexture(*marker_tex);
		    marker_sprite->setPosition(650 - (marker_w)/2 + width_/2, 20 + marker_position);
            return;
        }

        void update_marker(int absolute_y){
            int y = absolute_y - 20;
            marker_sprite->setPosition(650 - (marker_w)/2 + width_/2, y + 20);
            marker_position = y;
            value_ = (double)y/height_;
            // std::cout << "updating marker y = " << y << std::endl;
        }

        bool is_in_slider(sf::Vector2f &mouse){
            if(mouse.x < 650 || mouse.x > 650+width_){
                return false;
            }else if (mouse.y < 20 || mouse.y > 20+height_){
                return false;
            }else {
                return true;
            }
        }

        double get_value(){
            return value_;
        }

    private:
        sf::RectangleShape *rectangle;
        sf::Uint8 *colors_;
        sf::Texture *tex;
        sf::Uint8 *marker_pixels;
        sf::Texture *marker_tex;
        sf::Sprite *marker_sprite;
        int width_;
        int height_;

        int marker_position;
        int marker_w;

        double value_;
};