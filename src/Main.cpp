#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    int vel = 2;
    int num = 0;
    int cont = 0;
    sf::Texture soldado[7];
    bool derecha = false;
    bool salto = false;
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
    if(!sold.loadFromFile("res/sprite/raptor.gif")) {
        return EXIT_FAILURE;
    }

    sf::Font font;
    if (!font.loadFromFile("res/font/arial.ttf")) {
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
    sf::IntRect r1(0, 883, 34, 48);
    sf::Sprite spr_sol(sold,r1);
    spr_sol.setPosition(0,400);
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("res/music/sonic.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    //music.play();

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
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
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                //Jump
                for(int c = 0; c < 200; c++) {
                    spr_sol.move(0, -1.0);
                    window.clear();
                    window.draw(spr_sol);
                    window.display();
                }

                for(int c = 200; c > 0; c--) {
                    spr_sol.move(0, 1.0);
                    window.clear();
                    window.draw(spr_sol);
                    window.display();
                }
            }
            //Here start the other soldier
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                r1.width = 41;
                spr_sol.move(vel,0);
                if(r1.left == 40*2) {
                    r1.width = 43;
                }
                r1.top = 1;
                r1.left += r1.width;
                if(r1.left > r1.width * 7) {
                    r1.left = 0;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    for(int c = 0; c < 240; c++) {
                        spr_sol.move(vel, -1.0);
                        window.clear();
                        window.draw(spr_sol);
                        window.display();
                    }

                    for(int c = 240; c > 0; c--) {
                        spr_sol.move(vel, 1.0);
                        window.clear();
                        window.draw(spr_sol);
                        window.display();
                    }
                }
            } else {
                r1.width = 34;
                r1.top = 883;
                r1.left += r1.width;
                if(r1.left > r1.width * 2) {
                    r1.left = 0;
                }
            }
        }
        text.setRotation(cont);
        text.setOrigin(400,25);
        cont++;
        // Clear screen
        window.clear();
        window.draw(text);
        spr_sol.setTextureRect(r1);
        window.draw(spr_sol);
        // Draw the sprite
        window.draw(spr_solda[num]);
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
