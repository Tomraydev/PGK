#include "main.h"
using namespace std;

#define M 16 // margin
#define P 50 // padding

int main(){
	sf::Clock clock;
	// sf::Time time = sf::Time::Zero; // Unnecessary
	unsigned int FPS = 0 , frame_counter = 0;

	//inicjalizacja 

	sf::Font font;
	if (!font.loadFromFile("Roboto-Regular.ttf")){
		cout << "Error: cannot load the font" << endl;
		return 1;
	}
	sf::Text *FPS_text = new sf::Text;
	FPS_text->setFont(font);
	FPS_text->setCharacterSize(16);
	FPS_text->setFillColor(sf::Color::Black);
	FPS_text->setPosition(650 - 15,25+255); 

	sf::RenderWindow window(
		sf::VideoMode(750,640), // 1000,700
		"GFK Lab 02 - Tomasz Rajchel",
		sf::Style::Titlebar | sf::Style::Close
	);
	// window.setFramerateLimit(60); // remove to test efficiency
	window.setPosition(sf::Vector2i( (1366/2) - (window.getSize().x)/2 ,0)); // center window horizontally
	
	Slider slider;
	sf::Event event;
	struct User {
		bool is_clicked = false;
	};
	User us;

	const int circle_radius = 128;

	HSL hsl(circle_radius);
	HSV hsv(circle_radius);
	CMY cmy(circle_radius);
	RGB rgb(circle_radius);

	hsl.setPosition(M,M);
	hsv.setPosition(M+50+2*circle_radius, M);
	cmy.setPosition(M, M + P + 2*circle_radius);
	rgb.setPosition(M + P + 2*circle_radius, M + P + 2*circle_radius);

	clock.restart().asMilliseconds();
	while (window.isOpen()){
		window.clear(sf::Color::White);

		//EVENTS
		while (window.pollEvent(event)){
			switch (event.type){
				case sf::Event::Closed:{
					window.close();
					break;
				}

                case sf::Event::KeyPressed:{
					if(event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Q){
						window.close();
						break;
                    }
                }

				case sf::Event::MouseButtonPressed:{
					sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
					if(slider.is_in_slider(mouse)){
						slider.update_marker(mouse.y);
						us.is_clicked = true;
					}
					break;
				}

				case sf::Event::MouseButtonReleased:{
					us.is_clicked = false;
					break;
				}

				case sf::Event::MouseMoved:{
					sf::Vector2f mouse(event.mouseMove.x, event.mouseMove.y);
					if(us.is_clicked && slider.is_in_slider(mouse) ){
						slider.update_marker(mouse.y);
					}
					break;
				}
				
				default : break;
            }
		}

		//UPDATING TEXTURES
		hsl.update_circle(slider.get_value() );
		hsv.update_circle(slider.get_value() );
		cmy.update_circle(slider.get_value() );
		rgb.update_circle(slider.get_value() );

		//DRAWING EVERYTHING
		window.draw(hsl);
		window.draw(hsv);
		window.draw(cmy);
		window.draw(rgb);

		window.draw(slider);
		window.draw(*FPS_text);

		window.display();

		//MEASURING TIME
		if (clock.getElapsedTime().asSeconds() >= 1.0f){
			FPS = (unsigned int)((float)frame_counter / clock.getElapsedTime().asSeconds());
			string FPS_string = to_string(FPS) + " FPS";
			// cout << FPS_string << endl;
			FPS_text->setString(FPS_string);
			clock.restart();
			frame_counter = 0;
		}
		frame_counter++;

	}
	return 0;
}