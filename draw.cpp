#include "header.h"


struct my_Node{
    bool is_alive = false;
    bool change_state = false;
    my_Node()= default;
};

static my_Node field[30][30];

void fill_field(){
    for(auto & i : field) {
        for (auto & j : i) {
            j = my_Node();
        }
    }
}

void draw_field(sf::RenderWindow& window){
    for(int i = 0; i < 30; i++){
        for(int j = 0; j < 30; j++){
            auto rect = sf::RectangleShape(sf::Vector2f(40, 40));
            rect.move((float)(3 + (40 + 3) * i), (float)(3 + (40 + 3) * j));
            if (field[i][j].is_alive)
                rect.setFillColor(sf::Color::Black);
            window.draw(rect);
        }
    }
}

void update_field(){
    for(auto & i : field){
        for(auto & j : i){
            j.is_alive ^= j.change_state;
            j.change_state = false;
        }
    }
}

int calc_alive_neighbours(int i, int j){
    int q = 0;
    for(int k = -1; k <= 1; k++){
        for(int l = -1; l <= 1; l++){
            if (k == 0 and l == 0)
                 continue;
            if (i + k == 30 or j + l == 30 or i + k == -1 or j + l == -1)
                continue;
            if (field[i + k][j + l].is_alive)
                q += 1;
        }
    }
    return q;
}

void calc_next_state(){
    for(int i = 0; i < 30; i++){
        for(auto j = 0; j < 30; j++){
            auto q = calc_alive_neighbours(i, j);
            if (field[i][j].is_alive){
                if (q == 2 or q == 3){
                    field[i][j].change_state = false;
                }
                else field[i][j].change_state = true;
            }
            else if (q == 3)
                field[i][j].change_state = true;
        }
    }
}

void click(sf::Vector2i coord, sf::RenderWindow& window){
    int x = coord.x;
    int y = coord.y;
    field[(int)(trunc((double)(x - 3) / 43))][(int)(trunc((double)(y - 3) / 43))].is_alive ^= 1;
    draw_field(window);
}

void reset_field(sf::RenderWindow& window){
    for(auto & i : field) {
        for (auto & j : i) {
            j.is_alive = false;
            j.change_state = false;
        }
    }
    draw_field(window);
}

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> dist(0,1);

void fill_random(sf::RenderWindow& window){
    for(auto & i : field) {
        for (auto & j : i) {
            j.is_alive = dist(rng);
            j.change_state = false;
        }
    }
    draw_field(window);
}