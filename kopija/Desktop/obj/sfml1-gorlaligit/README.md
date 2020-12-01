# Uvod u SFML

U direktoriju `src/` se nalazi jedan jednostavan SFML program.
U njemu koristimo sljedeće objekte:

*   [sf::RenderWindow](http://www.sfml-dev.org/documentation/2.4.2/classsf_1_1RenderWindow.php)
*   [sf::VideoMode](http://www.sfml-dev.org/documentation/2.4.2/classsf_1_1VideoMode.php)
*   [sf::Texture](http://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Texture.php)
*   [sf::Sprite](http://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Sprite.php)
*   [sf::Event](http://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Event.php)

U prvm koraku je potrebno reorganizirati program tako da se sav kod
smjesti u jednu klasu koju ćemo zvati `Game`. Program se izvršava pozivom
metode `Game::run()`.

U drugom koraku treba implementirati pomicanje objekta pomoću tipkovnice.

U trećem koraku treba kontrolirati brzinu pomicanja pomoću dodatne varijable.

Konačno treba primijeniti `fiksan vremenski korak`.

Više detalja nalazi se u [doc/SFMLintro.html](doc/SFMLintro.html).

Informacije o iscrtavanju objekata nalaze se u [doc/iscrtavanje.html](doc/iscrtavanje.html).

Informacije o transformacijama objekta nalaze se u [doc/transformacije.html](doc/transformacije.html).

Informacije o _stablu scene_  nalaze se u [doc/SFMLgraph.html](doc/SFMLgraph.html).
