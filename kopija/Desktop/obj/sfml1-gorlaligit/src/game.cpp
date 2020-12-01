#include "game.h"
#include <stdexcept> // za runtime error

// kreiramo varijablu window u inicijalizacijskoj listi

// unija je struktura u kojoj sve varijable strukture su na istoj mem lokaciji
// stedi prostor, moramo znati sto se tamo nalazi da bi mogli dohvatiti

// oblici koje mozemo iscrtavati nalaze se u klasi Shape (ima drawable za crtanje i transformable da ga mozemo micati i transformirati)
// mi ćemo koristiti krug CircleShape kojeg u konstruktoru namjestimo
// u inicijalizacijsku listu kompiler ubaci defaultni konstruktor pa ne moramo mi

// RectangleShape dajemo vektor2f s dvije dimenzije- x i y koordinate

// vertex array (lista Vertexa)
// niz linija najjednostavnij iscrtati pomocu te klase
// polje razlicitih oblika zadanih svojim vrhovima, zadani u primitive types (tocke, linije, ... - nas zanimaju linije, zelimo to nacrtati)
// inicijaliziramo u inicijalizacijskoj listi jer ne zelimo defaultni
// damo mu samo tip kojeg cemo spremati (prazno polje vrhova), drugi argument je 0, tj nemamo jos niti jednu liniju unutra jos, kasnije cemo appendati
// svaki par tocaka predstavlja liniju, iscrta se linija od jjedne do druge tocke (za triangle bi bilo tri tocke)
// prvi argument u konstruktoru kaze na koji nacin ce se tocke koje stavimo u polje interpretirati (kako ce se povezivati - duzinama, trokutima itd. po svake dvije u paru ili svake tri... )
// prije appenda moramo resizeati ( sacuva stare elemente ako damo vecu velicinu, obrise ako damo manju - sve elemente inicijalizira na defaultne vrijednosti )


// klasa Vertex sadrzi postion i boju

// dvije klase za ispisivanje teksta: Text (iscratva samo tekst - ponasa se kao slika, jednako iscrtavamo i transformiramo)
// za Text moramo uvijek loadati font u njega jer SFML nema svoje fontove (moramo downloadati fontove, ttf fileovi, stavimo ih u recimo data folder)
//  u cmake lists ne moramo dodati font jer vec imamo custom_comand koji cijeli data direktorij kopira u izvrsni

Game::Game() : mWindow(sf::VideoMode(400, 400), "SFML window"), mVA( sf::Lines )
{
    if (!mTexture.loadFromFile("cb.bmp"))
        throw std::runtime_error("Cannot open file cb.bmp!");

    // postavljanje texture u sprite
    mSprite.setTexture( mTexture );

    mCircle.setRadius( 40.f );
    mCircle.setFillColor( sf::Color::Yellow ); // ostale boje definiram s r g b komponentama
    mCircle.setOutlineThickness( 5.f );
    mCircle.setOutlineColor( sf::Color::Red );
    mCircle.setOrigin( mCircle.getLocalBounds().width/2, // postavlajmo origin u centar kruga
                       mCircle.getLocalBounds().height/2 ); // sada transformacije radimo u odnosu na ovaj novi centar
    mCircle.setPosition( 200.f, 200.f ); // centar kruga postavljamo na 200px i 200px


    // mozemo unutra stavljati i teksture, slike, umjesto same boje
    mRect.setSize( sf::Vector2f( 200, 100 ) );
    mRect.setFillColor( sf::Color::Blue );
    mRect.setPosition( 200.f ,0.f );

    mVA.resize( 3*2 ); // tri linije po dvije tocke ako zelimo nacrtati trokut
    // moramo sada inicijalizirati 6 tocaka
    // prve dvije tocke su prva linija
    // ako zelimo trokut treca tocka mora biti jednaka kao prva
    // trokut nije optimalno ovako crtati jer moramo ponavljati tocke (ako jednostavno koristimo Triangle umjesto Lines je lakse)
    mVA[0].position = sf::Vector2f( 200, 250 ); // posto je vektor mozemo koristiti indekse
    mVA[1].position = sf::Vector2f( 250, 250 );
    mVA[2].position = sf::Vector2f( 250, 250 );
    mVA[3].position = sf::Vector2f( 250, 300 );
    mVA[4].position = sf::Vector2f( 250, 300 );
    mVA[5].position = sf::Vector2f( 200, 250 );


    //if( ! mFont.loadFromFile( "LangrishScript.ttf" ) ) // ako nije dobro ucitano
    //    throw std::runtime_error("Nije dobro ucitan font");

    mText.setFont(mFont);
    mText.setString( "Text" ); // sa stringom dajemo tekst
    mText.setCharacterSize( 18 );
    mText.setStyle( sf::Text::Bold | sf::Text::Underlined ); // bold, italic itd, styleovi su zastavice pa ih mozemo spajati
    mText.setPosition( 100, 300 );
    mText.setRotation( 90 ); // rotiranje se radi u stupnjevima, pozitivno je u smjeru kazaljke na satu

}

void Game::run()
{
//    while ( mWindow.isOpen() )
//    {
//        // Process events
//        sf::Event event;
//        while (mWindow.pollEvent(event))
//        {
//            // Close window : exit
//            if (event.type == sf::Event::Closed)
//                mWindow.close();
//        }
//        // Clear screen
//        mWindow.clear();
//        // Draw the sprite
//        mWindow.draw(mSprite);
//        // Update the window
//        mWindow.display();
//    }

    sf::Clock clock; // odmah krene mjeriti
    sf::Time  protekloVrijeme = sf::Time::Zero; // Zero je staticka varijabla koja predtavlja nulu
    // nema operatora konverzije pa ne mozemo inicijalizirati s 0
    sf::Time dt = sf::seconds( 1.00/60.f ); // inicjaliziramo vrijeme, update windowa da se radi max s 1/60 sekunde

    while( mWindow.isOpen() )
    {

        procesEvent();
        // dodajemo vrijeme jer inace prilikom stiskanja tipke odjuri sve

        // sf::Time dt = clock.restart(); // vrati proteklo vrijeme i restarta sat istovremeno
        // dt je vrijeme izmedu dva poziva metode update
        // vazno je da nema kolizija, da update uvijek dobiva isti dt
        // koristi se fiksiranje koraka dt
        // esencijalno za dobro funkcioniranje animacije/simulacije

        protekloVrijeme += clock.restart();

        while( protekloVrijeme >= dt )
        {
            protekloVrijeme -= dt;
            // ako je proteklo vrijeme puno vece od dt onda vise puta iscrtavamo
            // update radi uvijek s istim vremenskim korakom dt
            update( dt );
        }
        // ako nakon ove petlje ostane nesto malo u proteklo vrijeme, kasnije ga koristimo opet

        render();
    }

}

void Game::procesEvent()
{

    sf::Event event;
    while ( mWindow.pollEvent( event ) )
    {
        // Close window : exit
        switch( event.type )
        {
            case sf::Event::Closed:
                mWindow.close();
            break;
            // temeljem eventa pozivamo metodu update
            case sf::Event::KeyPressed:
            // key je varijabla u uniji i nju mozemo dohvatiti tek ako je KeyPressed
            // kada stisnemo tipku samo jednom se generira event keypressed
            // takoder za key release
            // izmedu tog dvoje ce proci neko vrijeme za koje je varijabla true i sve za to vrijeme se pomicemo desno
                if( event.key.code == sf::Keyboard::Left )
                    // kad je tipka stisnuta lijevo, mi smo taj event procitali
                    // onda prenosimo tu info dalje
                    mLeftPressed = true;
                if( event.key.code == sf::Keyboard::Right )
                    mRightPressed = true;
                if( event.key.code == sf::Keyboard::Up )
                    mUpPressed = true;
                if( event.key.code == sf::Keyboard::Down )
                    mDownPressed = true;
            break;
            case sf::Event::KeyReleased:
                if( event.key.code == sf::Keyboard::Left )
                    mLeftPressed = false;
                if( event.key.code == sf::Keyboard::Right )
                    mRightPressed = false;
                if( event.key.code == sf::Keyboard::Up )
                    mUpPressed = false;
                if( event.key.code == sf::Keyboard::Down )
                    mDownPressed = false;
            break;
        }

//        if (event.type == sf::Event::Closed) // ispitujemo dogadaj je li prozor zatvoren
//            mWindow.close();
    }
}

void Game::update( sf::Time const & dt )
{
    float brzina = 300.0f; // broj piksela za koje se smijemo pomaknuti u sekundi
    float dx = brzina * dt.asSeconds(); // pomak koji moramo napraviti

    if( mLeftPressed ) // micemo sprite na lijevo
    {
        // pomak za jedan piksel ulijevo
        mSprite.move( -dx, 0.0f ); // sve info su u pikselima za koje se koristi varijabla float
    }
    if( mRightPressed )
    {
        mSprite.move( dx, 0.0f );
    }
    // os y u svim grafickim programima ide odozgo prema dolje
    if( mUpPressed )
    {
        mSprite.move( 0.0f, -dx );
    }
    if( mDownPressed )
    {
        mSprite.move( 0.0f, dx );
    }


    mText.move( 1.f, 0  ); // pomicemo tekst za jedan pixel udesno svaki puta kada se slika updatea
    mText.rotate( 3 ); // rotira oko origina u odnosu na prethodnu rotaciju
    // postoji i transformacija scale koja moze skalirati tj. mjenjati velicinu
}

void Game::render()
{
    // Clear screen
    mWindow.clear();
    // Draw the sprite
    // u draw metodi moramo iscrtati sve oblike koje zelimo vidjeti
    // bitan je redoslijed jer se onda jedno iscrtava preko drugoga
    mWindow.draw(mSprite);
    mWindow.draw(mCircle);
    mWindow.draw(mRect);
    mWindow.draw(mVA);
    mWindow.draw(mText);
    // Update the window
    mWindow.display();
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states ) const
{
    // states je objekt koji ima shader, texture, transform
    // nama je bitan transform jer on nosi transformaciju koju radimo
    // klasa prosiruje transformable pa imamo get transform metodu

    states.transform *= getTransform();  // komponiramo sa transformacijom iz states varijable, defaultno je tamo identiteta

    // iscrtavamo sve sto imamo u nasoj klasi
    target.draw( mText, states );
    target.draw( mCircle, states );

}
