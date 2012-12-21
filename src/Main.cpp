#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    int cont = 0;
    bool derecha = false;
    float vely = 0;
    float velx = 0;
    bool salto = false;
    bool suelo = true;
    sf::Texture sold;
    sold.setSmooth(true);
    // Load a sprite to display
    //Asigno las imagenes a la clase texture
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
    //Y guardo la posicion
    sf::IntRect r1(0, 883, 34, 48);
    sf::Sprite spr_sol(sold,r1);
    spr_sol.setPosition(0, 400);
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("res/music/sonic.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    music.play();
    window.setFramerateLimit(500);
    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            derecha = false;
            salto = false;
            // Close window : exit
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                //Jump
                if(spr_sol.getPosition().y <= (spr_sol.getScale().y * -2)-400){
                    salto = false;
                }
                else{
                    suelo = false;
                    salto = true;
                    vely = -0.5;
                }
            }
            //Here start the other soldier
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                derecha = true;
                velx = 0.5;
                r1.width = 41;
                //spr_sol.move(vel,0);
                if(r1.left == 40 * 2) {
                    r1.width = 43;
                }
                r1.top = 1;
                r1.left += r1.width;
                if(r1.left > r1.width * 7) {
                    r1.left = 0;
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

        if(!derecha) {
            velx = 0;
        }

        if(!salto && !suelo) {
            vely = 0.5;
            if(spr_sol.getPosition().y == 400){
                suelo = true;
                vely = 0;
            }
        }
        text.setRotation(cont);
        text.setOrigin(400,25);
        cont++;
        spr_sol.move(velx,vely);
        // Clear screen
        window.clear();
        window.draw(text);
        // Draw the sprite
        spr_sol.setTextureRect(r1);
        window.draw(spr_sol);
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
