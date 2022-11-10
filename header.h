//
// Created by tosha on 20/10/2022.
//

#ifndef SFMLLIFE_HEADER_H
#define SFMLLIFE_HEADER_H

#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <cmath>
#include <random>

void draw_field(sf::RenderWindow& window);
void update_field();
void calc_next_state();
void click(sf::Vector2i coord, sf::RenderWindow& window);
void reset_field(sf::RenderWindow& window);
void fill_random(sf::RenderWindow& window);

#endif //SFMLLIFE_HEADER_H
