//
// Created by Krzysztof Bednarski on 28.03.2019.
//

#ifndef UNTITLED_SQUARE_H
#define UNTITLED_SQUARE_H

#include <iostream>

using namespace std;

/**
 * Klasa odpowiedzialna za implementacje kafelka
 */
class Square {
private:
    bool isFree;
    int *position;
public:
    Square(int x, int y) {
        isFree = true;
        position = new int[2];
        position[0] = x;
        position[1] = y;
    }

    ~Square(){
      //std::cout<<"Square: x = "<< position[0]<<" y = "<< position[1] << " Destroyed" <<std::endl;
      delete position;
    }

    bool getFree();

    void setFree(bool isFree);

    int *getPosition() const;
};


#endif //UNTITLED_SQUARE_H
