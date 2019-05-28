//
// Created by Krzysztof Bednarski on 28.03.2019.
//

#include "Square.h"

/**
 * @return - zwraca czy kafelek wolny czy nie
 */
bool Square::getFree() {
    return isFree;
}

/**
 * @param isFree - pozwala na zmiane stanu kafelka na wolny lub zajety
 */
void Square::setFree(bool isFree) {
    this->isFree = isFree;
}

/**
 * @return - zwraca pozycje kafelka na planszy
 */
int *Square::getPosition() const {
    return position;
}
