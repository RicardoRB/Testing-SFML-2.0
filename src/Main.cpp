#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    int cont = 0;
    bool walk = false;
    float vely = 0;
    float velx = 0;
    bool jump = false;
    bool ground = true;
    bool endjump = false;
    sf::Texture sold;
    sf::Text text;

    sold.setSmooth(true);

    // Load a sprite to display
    if(!sold.loadFromFile("res/sprite/raptor.gif")) {
        return EXIT_FAILURE;
    }

    sf::Font font;
    if (!font.loadFromFile("res/font/arial.ttf")) {
        return EXIT_FAILURE;
    }
    text.setString("U MAD BECAUSE I WIN, LOLOLOLO!");
    text.setFont(font);
    text.setCharacterSize(50);
    text.setPosition(400,300);

    //I declare the vector of sprite
    //when isnt moving (in the begining arent moving)
    sf::IntRect r1(0, 883, 34, 48);
    //I declare the sprite with the vector and
    //the texture
    sf::Sprite spr_sol(sold, r1);

    //I send where the soldier will begging
    spr_sol.setPosition(0, 400);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("res/music/sonic.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    music.play();

    //If I dont put it, in linux can running more fast
    window.setFramerateLimit(500);

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            //On the begining, the soldier no are walking
            //and no are jumping
            walk = false;
            jump = false;
            // Close window : exit
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                //Jump
                ground = false;
                if(!endjump) {
                    jump = true;
                    vely = -1;
                }
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                walk = true;
                velx = -0.5;
                r1.width = 41;

                //Creating the feeling of moving with sprites
                if(r1.left == 40 * 2) {
                    r1.width = 43;
                }
                r1.top = 1;
                r1.left += r1.width;
                if(r1.left > r1.width * 7) {
                    r1.left = 0;
                }
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                walk = true;
                velx = 0.5;

                //Creating the feeling of moving with sprites
                r1.width = 41;
                if(r1.left == 40 * 2) {
                    r1.width = 43;
                }
                r1.top = 1;
                r1.left += r1.width;
                if(r1.left > r1.width * 7) {
                    r1.left = 0;
                }
            }
        }

        if(!walk) {
            r1.width = 34;
            r1.top = 883;
            r1.left += r1.width;
            if(r1.left > r1.width * 2) {
                r1.left = 0;
            }
            velx = 0;
        }

        //The soldier cant jumping the double of its size
        //when the jumping start in 400 Y
        if(spr_sol.getPosition().y <= ((34 * -2) + 400) - 34) {
            jump = false;
            ground = false;
            endjump = true;
        }

        if((!jump && !ground) || endjump) {
            vely = 1;
            endjump = true;
            if(spr_sol.getPosition().y == 400) {
                ground = true;
                endjump = false;
                vely = 0;
            }
        }

        //The text will rotate allways
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
