#include "game.h"
#include <SFML/Graphics.hpp>
// graficka biblioteka koja dosta koristi nasljedivanje
// ima malo klasa, mala i elegnatna biblioteka, funkcionalna za kreiranje video igara u 2D
//
//
//

int main()
{
//    // Create the main window
//    // RenderWindow prozor na koji isrctavamo; velicina i ime prozoraa
//    // uvijek ga otvaramo na taj nacin

//    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML window");

//    // Load a sprite to display
//    // utociti sliku na prozor
//    // klasa texture predstavlja sliku
//    // load from file moze ucitati slike iz raznih izvore


//    sf::Texture texture;
//    if (!texture.loadFromFile("cb.bmp"))
//        throw std::runtime_error("Cannot open file cb.bmp!");
//    sf::Sprite sprite(texture);

//    // sprite pravokutnik, koji dio slike prikazujemo
//    // sprite je klasa mala koja uzima texture, ima referencu na memoriju u texture

//	// Start the game loop
//    // graficki programi su programi vodeni dogadajima - petlja dok je prozor otvoren


//    while (window.isOpen())
//    {
//        // osluskujemo dogadaje u petlji
//        // Process events
//        sf::Event event;


//        // poll dohvaca dogadaj iz reda dogadaja i onda ga procesiramo sve dok red dogadaja
//        // ne postanje prazan, pritisci na tipke, klikovi misa, resize ekrana, ...,
//        // poll ispuni referencu event s novim dogadajem
//        // ispitujemo koji je tip eventa i onda izvrsavamo odgovarajucu radnju


//        while (window.pollEvent(event))
//        {
//            // Close window : exit
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }


//        // iscrtavanje na ekran - clear da ocisti, draw da crta - svaki puta ju zovemo za svaki objekt
//        // iscrtavamo sprite a ne texture
//        // tek kad pozoovemo display onda se iscrta na ekran, do tad je u bufferu
//        // ova nasa petlja samo brzo iscrtava istu sliku na ekran


//        // Clear screen
//        window.clear();
//        // Draw the sprite
//        window.draw(sprite);
//        // Update the window
//        window.display();
//    }

    Game game;
    game.run();

    return 0;
}
