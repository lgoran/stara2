#include "board.h"
#include <iostream>
// Vaš kod dolazi ovdje
Board::Board(): mGrid(sf::Lines),mUniformDist(0,100),mOriginX(100),mOriginY(100),mDx(20),mDy(20)
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            mGridContent[i][j]=-1;
        }
    }
    
    mGrid.resize(200);
    int i=0;
        while (i<42)
        {       
            mGrid[i].position=sf::Vector2f(100,100+10*i);
            mGrid[i+1].position=sf::Vector2f(300,100+10*i);
            i=i+2;
        }
        i=0;
    while (i<22)
        {       
            mGrid[i+42].position=sf::Vector2f(100+10*i,100);
            mGrid[i+1+42].position=sf::Vector2f(100+10*i,500);
            i=i+2;
        }
}
bool Board::checkSpace()
{
    int pozx=(mPiece.mXposition-100)/20;
    int pozy=(mPiece.mYposition-100)/20;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j]!=0 && mGridContent[pozy+i][pozx+j]!=-1)
            return false;
        }
    }
    return true;
}
void Board::spawnPiece()
{
    mPiece.mRotacija = mUniformDist(mRNE)%4;
    tip_tetrimina=mUniformDist(mRNE)%7;
    if(tip_tetrimina==0) mPiece.mType=Tetrimino::Types(0);
    if(tip_tetrimina==1) mPiece.mType=Tetrimino::Types(1);
    if(tip_tetrimina==2) mPiece.mType=Tetrimino::Types(2);
    if(tip_tetrimina==3) mPiece.mType=Tetrimino::Types(3);
    if(tip_tetrimina==4) mPiece.mType=Tetrimino::Types(4);
    if(tip_tetrimina==5) mPiece.mType=Tetrimino::Types(5);
    if(tip_tetrimina==6) mPiece.mType=Tetrimino::Types(6);
    for (int i = 0; i < 4; i++)
    {   
        for (int j = 3; j < 7; j++)
        {
            if(mGridContent[i][j]!=-1)
            {
                gotovo=1;
                break;
            }
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j-3]!=0)
                mGridContent[i][j]=tip_tetrimina;
        }
        if(gotovo==1)
        break;
    }
    mPiece.mXposition=160;
    mPiece.mYposition=100;
}
bool Board::movePiece(int x,int y)
{   
    int pozx=(mPiece.mXposition-100)/20;
    int pozy=(mPiece.mYposition-100)/20;


    if(pozx==0 && x==-20)
    {
        for (int i = 0; i < 4; i++)
        {
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][0] != 0)
                return false;
        }        
    }
    if(pozx==-1 && x==-20)
    {
        for (int i = 0; i < 4; i++)
        {
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][1]!=0)
                return false;
        }        
    }
    if(pozx==-2 && x==-20)return false;    
    if(pozx==6 && x==20)
    {
        for (int i = 0; i < 4; i++)
        {
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][3]!=0)
                return false;
        }        
    }
    if(pozx==7 && x==20)
    {
        for (int i = 0; i < 4; i++)
        {
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][2]!=0)
                return false;
        }        
    }
    if(pozx==8 && x==20) return false;
    if ( x == -20){
        if (pozx != 0) 
            for (int i = 0; i < 4; i++){ 
                if (mGridContent[pozy + i][pozx - 1] != -1 && 
                    mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][0] != 0) return false;
            }
        
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++) {
                if (mGridContent[pozy + i][pozx + j] == -1) continue;
                if (mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j] != 0) continue;
                else if (mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j] == 0){
                    if (mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j+1] != 0) return false;
                    else continue;
                }

            }
        removePiece();
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j] != 0)
                    mGridContent[pozy + i][pozx - 1 + j] = mPiece.mType;
        mPiece.mXposition -= 20;
        return true;
    }
    if ( x == 20){
        if (pozx != 6) 
            for (int i = 0; i < 4; i++){ 
                if (mGridContent[pozy + i][pozx + 4] != -1 && 
                    mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][3] != 0) return false;
            }
        
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++) {
                if (mGridContent[pozy + i][pozx - j + 3] == -1) continue;
                if (mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][3-j] != 0) continue;
                else if (mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][3-j] == 0){
                    if (mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][3-j-1] != 0) return false;
                    else continue;
                }

            }
        removePiece();
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j] != 0)
                    mGridContent[pozy + i][pozx + 1 + j] = mPiece.mType;
        mPiece.mXposition += 20;
        return true;
    }
    if (y == 20){
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++){
                if (pozy + i > 20) return false;
                if (mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j] == 0) continue;
                else{
                    if (mGridContent[pozy + i + 1][pozx + j] != -1 && 
                        mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i+1][j] == 0) return false;
                }
            }
        removePiece();
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j] != 0)
                    mGridContent[pozy + 1 + i][pozx + j] = mPiece.mType;
        mPiece.mYposition += 20;
        return true;
    }
}
void Board::update(int x,int y)
{
    if(x==0 && y==0 && !rotatePiece())
    {
        int pozx=(mPiece.mXposition-100)/20;
        int pozy=(mPiece.mYposition-100)/20;
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
            {
                if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j]!=0)
                    mGridContent[pozy+i][pozx+j]=mPiece.mType;
            }
    }
    else if(y==20 && !movePiece(x,y))
    {
        int a=clearLines();
        spawnPiece();
    }
    else if(y!=20){
        int a=movePiece(x,y);
    }
}
void Board::spaceDown()
{
    for(int i=0;i<20;i++)
        int a=movePiece(0,20);
}
void Board::removePiece()
{
    int pozx=(mPiece.mXposition-100)/20;
    int pozy=(mPiece.mYposition-100)/20;
    for (int i = 0; i < 4; i++)
    {
        for(int j=0;j<4;j++)
        {
            if(mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j]!=0 && mGridContent[pozy+i][pozx+j]!=-1)
                mGridContent[pozy+i][pozx+j]=-1;
        }
    }    
}
bool Board::rotatePiece()
{
    removePiece();
    int pozx=(mPiece.mXposition-100)/20;
    int pozy=(mPiece.mYposition-100)/20;
    int pomrot = (mPiece.mRotacija+1)%4;
    if(pozx==-1)
    {
        for (int i = 0; i < 4; i++)
        {
            for(int j=1;j<4;j++)
            {
                if(mPiece.mDijelovi[mPiece.mType][pomrot][i][j]!=0 && mGridContent[pozy+i][pozx+j]!=-1)
                    return false;
            }
            if(mPiece.mDijelovi[mPiece.mType][pomrot][i][0]!=0)return false;
        }
    }
    if(pozx==-2)return false;
    if(pozx==7)
    {
        for (int i = 0; i < 4; i++)
        {
            for(int j=0;j<3;j++)
            {
                if(mPiece.mDijelovi[mPiece.mType][pomrot][i][j]!=0 && mGridContent[pozy+i][pozx+j]!=-1)
                    return false;
            }
            if(mPiece.mDijelovi[mPiece.mType][pomrot][i][3]!=0)return false;
        }
    }
    if(pozx==8) return false;
    for (int i = 0; i < 4; i++)
    {
        for(int j=0;j<4;j++)
        {
            if(mPiece.mDijelovi[mPiece.mType][pomrot][i][j]!=0 && mGridContent[pozy+i][pozx+j]!=-1)
                return false;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for(int j=0;j<4;j++)
        {
            if(mPiece.mDijelovi[mPiece.mType][pomrot][i][j]!=0)
                mGridContent[pozy+i][pozx+j]=mPiece.mType;
        }
    }
    mPiece.mRotacija=pomrot;
    return true;    
}
bool Board::isLineFull(int y) const
{
    for (int j = 0; j < 10; j++)
    {
        if(mGridContent[y][j]==-1) return false;
    }
    return true;    
}
int Board::clearLines()
{
    int br=0;
    for(int z=0;z<20;z++)
        {
            if(isLineFull(z))
            {
                for(int i=z-1;i>=0;i--)
                {
                    for(int j=0;j<10;j++)
                        mGridContent[i+1][j]=mGridContent[i][j];
                }
                for(int j=0;j<10;j++)
                    mGridContent[0][j]=-1;
                br++;
            }
        }
    return br;
}
int Board::getNoLinesCompleted() const
{
    int br=0;
    for(int z=0;z<20;z++)
        {
            if(isLineFull(z))
            {
                br++;
            }
        }
    return br;
}
bool Board::isGameOver() const
{
    if(gotovo==1) return true;
    return false;
}
void Board::draw(sf::RenderTarget &target, sf::RenderStates states ) const
{
    states.transform *= getTransform();
    target.draw( mGrid, states );
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if(mGridContent[i][j]!=-1)
            {
                sf::RectangleShape mrect;
                mrect.setSize(sf::Vector2f(18,18));
                mrect.setPosition(100 + 20*j,100 + 20*i);
                mrect.setFillColor(mPiece.mColors[mGridContent[i][j]]);
                target.draw(mrect,states);
            }
        }        
    }
}