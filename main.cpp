#include "header.h"


int main(){
    sf::RenderWindow window(sf::VideoMode(1293, 1293), "Game LIFE");
    window.setFramerateLimit(60);
    sf::Event event{};
    bool stop = true;
    fill_field();
    while (window.isOpen()){
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::Space) {
                    stop ^= 1;
                    usleep(100000);
                }
                if (event.key.code == sf::Keyboard::R) {
                    reset_field(window);
                    stop = true;
                    usleep(100000);
                }
                if (event.key.code == sf::Keyboard::F) {
                    fill_random(window);
                    usleep(100000);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed){
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stop){
                    click(sf::Mouse::getPosition(window), window);
                }
                usleep(50000);
            }
        }
        window.clear();
        if(!stop) {
            usleep(2*100000);
            calc_next_state();
            update_field();
        }
        draw_field(window);
        window.display();
    }
    return 0;
}