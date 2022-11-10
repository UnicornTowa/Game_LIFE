#include "header.h"


int main(){
    /// Создание окна
    sf::RenderWindow window(sf::VideoMode(1293, 1293), "Game LIFE");
    window.setFramerateLimit(60);
    sf::Event event{};

    /// Состояние паузы
    bool stop = true;

    /// Заполнение массива "клетками"
    fill_field();

    /// Основной цикл
    while (window.isOpen()){
        while (window.pollEvent(event)){
            /// Закрытие окна
            if (event.type == sf::Event::Closed) window.close();
            /// Считывание нажатых клавиш
            if (event.type == sf::Event::KeyPressed)
            {
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
            /// Считывание клика мыши
            if (event.type == sf::Event::MouseButtonPressed){
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stop){
                    click(sf::Mouse::getPosition(window), window);
                }
                usleep(50000);
            }
        }
        /// Очистка окна
        window.clear();
        /// Расчет следующего состояния если пауза не активна
        if(!stop) {
            usleep(2*100000);
            calc_next_state();
            update_field();
        }
        /// Отрисовка поля
        draw_field(window);
        window.display();
    }
    return 0;
}