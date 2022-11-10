#include "header.h"

/// Структура
struct my_Node{
    bool is_alive = false;
    bool change_state = false;
    my_Node()= default;
};

/// Контейнер для "клеток"
static my_Node field[30][30];

/// Заполнение массива клетками
void fill_field(){
    for(auto & i : field) {
        for (auto & j : i) {
            j = my_Node();
        }
    }
}

/// Отрисовка клеток
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

/// Обновление состояния клеток
void update_field(){
    for(auto & i : field){
        for(auto & j : i){
            j.is_alive ^= j.change_state;
            j.change_state = false;
        }
    }
}

/// Подсчет числа соседей клетки
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

/// Расчет следующего состояния поля
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

/// Изменение состояния клетки на которую кликнул пользователь
void click(sf::Vector2i coord, sf::RenderWindow& window){
    int x = (int)(trunc((double)(coord.x - 3) / 43));
    int y = (int)(trunc((double)(coord.y - 3) / 43));
    field[x][y].is_alive ^= 1;
    field[x][y].change_state = false;
    draw_field(window);
}

/// Сброс игрового поля (состояния всех клеток)
void reset_field(sf::RenderWindow& window){
    for(auto & i : field) {
        for (auto & j : i) {
            j.is_alive = false;
            j.change_state = false;
        }
    }
    draw_field(window);
}

/// Объекты для генерации случайных чисел
std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> dist(0,1);

/// Заполнение игрового поля случайными клетками
void fill_random(sf::RenderWindow& window){
    for(auto & i : field) {
        for (auto & j : i) {
            j.is_alive = dist(rng);
            j.change_state = false;
        }
    }
    draw_field(window);
}