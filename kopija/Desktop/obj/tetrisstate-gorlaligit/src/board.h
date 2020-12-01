#ifndef BOARD_H
#define BOARD_H
#include <SFML/Graphics.hpp>
#include "tetrimino.h"
#include <random>

/** Klasa Board -- Ubaciti vlastiti verziju ako postoje izmjene u odnosu na predloženi 
 *                 izgled klase !!!!!!!
 *
 *  Klasa implementira svu logiku Tetris igre.
 */
class Board : public sf::Drawable, public sf::Transformable, public sf::NonCopyable {
public:
    Board();
    ~Board();
    void update(int x,int y);
    // Pozicioniraj novi tetrimino na ploči.
    void spawnPiece();
    bool isGameOver() const { return mGameOver; }
    void clearState();
    int  getNoLinesCompleted() const ;
    void clearNoLinesCompleted() { mNoLinesCompleted = 0; }
	// Nove metode za konverziju brzine u mDt.
    void  setSpeed(float speed) { mDt = 1.0f/speed;}
    float getSpeed() const { return 1.0f/mDt; }
    void spaceDown();
private:
    static const int EMPTY = -1;
    static const int mCols = 10;
    static const int mRows = 2* mCols;

    sf::VertexArray mGrid;
	int mGridContent[mRows][mCols]; // Logički prikaz mreže

    // Dimenzije mreže
    float mLeftMargin = 100.f;
    float mTopMargin = 100.0f;
    float mWidth=200.f;
    float mHeight=2*mWidth;
    // Početak mreže = gornji lijevi kut
    float mOriginX, mOriginY;
    // Dimenzije ćelija
    float mDx, mDy;
    float mDt = 0.3f; // sekunde
    bool mGameOver = false;
    // Broj linija obrisanih od jedom (0,1,2,3 ili 4)
    int mNoLinesCompleted = 0;

    // Generiranje slučajnog elementa.
    std::random_device r;
    std::default_random_engine mRNE;
    std::uniform_int_distribution<> mUniformDist;

    Tetrimino mPiece;

    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
    
    // Provjerava da li se komad može smjestiti na ploču.
    bool checkSpace();
    // Smjesti komad na ploču. Pretpostavlja se da je checkSpace(piece) vratio true.
    void placePiece();
    // Ukloni komad sa ploče.
    void removePiece();
    // Pomakni komad ako je moguće. Vrati true ako je pomak izvršen, inače false.
    bool movePiece(int x, int y);
    // Rotiraj komad. Vrati true ako je rotacija izvršena, inače false.
    bool rotatePiece();
    // Da li je linija y prazna ili nije ?
    bool isLineFull(int y) const;
    // Obriši kompletne linije i vrati broj obrisanih linija
    int clearLines();
    // Obriši liniju y i translatiraj sve linije iznad nje prema dolje.
    void deleteLine(int y);

};

#endif // BOARD_H
