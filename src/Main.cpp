#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    int vel = 4;
    int num = 0;
    int cont = 0;
    sf::Texture soldado[7];
    bool derecha = false;
    sf::Texture sold;
    sold.setSmooth(true);
    // Load a sprite to display
    //Asigno las imagenes a la clase texture
    for (int i = 0; i < 7; i++) {
        std::stringstream concat;
        std::string cadena = "res/sprite/derecha/derecha";
        concat << cadena << i + 1 << ".png";
        cadena = concat.str();
        std::cout << cadena << std::endl;
        if (!soldado[i].loadFromFile(cadena)) {
            return EXIT_FAILURE;
        }
        soldado[i].setSmooth(true);
    }
    if(!sold.loadFromFile("res/sprite/raptor.gif")){
        return EXIT_FAILURE;
    }

    sf::Font font;
    if (!font.loadFromFile("res/font/arial.ttf")){
        return EXIT_FAILURE;
    }
    sf::Text text("U MAD BECAUSE I WIN, LOLOLOLO!", font, 50);
    text.setPosition(400,300);
    //Asigno la textura al sprite
    //Y guardo la posicion de cada uno
    sf::Sprite spr_solda[8];
    sf::Vector2f pos_sol[8];
    for (int i = 0; i < 7 ; i++) {
        spr_solda[i].setTexture(soldado[i]);
        spr_solda[i].setPosition(0, 553);
        pos_sol[i] = spr_solda[i].getPosition();
    }
    sf::IntRect r1(0, 885, 34, 47);
    sf::Sprite spr_sol(sold,r1);
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("res/music/sonic.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    music.play();

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if(derecha == true) {
                    for (int i = 0; i < 7 ; i++) {
                        pos_sol[i] = spr_solda[i].getPosition();
                    }
                }
                if(num <= 0) {
                    spr_solda[num].setPosition(pos_sol[6].x - vel, pos_sol[6].y);
                    pos_sol[num] = spr_solda[num].getPosition();
                } else {
                    spr_solda[num].setPosition(pos_sol[num - 1].x - vel, pos_sol[num - 1].y);
                    pos_sol[num] = spr_solda[num].getPosition();
                }
                std::cout << "Izquierda" << std::endl;
                num++;

                if(num >= 7) {
                    num = 0;
                }
                // left key is pressed: move our character
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                derecha = true;
                if(num <= 0) {
                    spr_solda[num].setPosition(pos_sol[6].x + vel, pos_sol[6].y);
                    pos_sol[num] = spr_solda[num].getPosition();
                } else {
                    spr_solda[num].setPosition(pos_sol[num - 1].x + vel, pos_sol[num - 1].y);
                    pos_sol[num] = spr_solda[num].getPosition();
                }
                std::cout << "Derecha" << std::endl;
                num++;

                if(num >= 7) {
                    num = 0;
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                std::cout << "Arriba" << std::endl;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                std::cout << "Abajo" << std::endl;
            }
        }
        text.setRotation(cont);
        text.setOrigin(400,25);
        cont++;
        // Clear screen
        window.clear();
        window.draw(text);
        r1.left = r1.left + 34;
        if(r1.left > 96){
            r1.left = 0;
        }
        std::cout << r1.left << std::endl;
        spr_sol.setTextureRect(r1);
        window.draw(spr_sol);
        // Draw the sprite
        window.draw(spr_solda[num]);
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
