#include "Player.h"

Player::Player() : board(ROWS, COLS) {
  sunkenShips = 0;
}

void Player::printBoard() {
  board.print();
}

/**
  * Takes an object of type Ship and and change the values
  * of the coordinates from zero to one on the board
  */
void Player::placeShip(Ship ship) {
  board.placeShip(ship);
}

// Add a ship to the list of ships
void Player::addShip(Ship ship) {
  this->ships.push_back(ship);
}

void Player::hit(int x, int y) {
  for (auto &ship : ships) {
    if (ship.isHit(x, y)) {
      Player::isShipSunken(ship);
      this->board.setPixel('e', x, y, 3);
    } else {
      if (this->board.getPixel('m', x, y) != 3) {
        this->board.setPixel('e', x, y, 2);
      }
    }
  }
}

/**
 * Increase the number of suken ships if the ship
 * is suken
 */
bool Player::isShipSunken(Ship ship) {
  if (ship.isSunken()) {
    this->sunkenShips++;
    return true;
  } else {
    return false;
  }
}

int Player::getSunkenShips() {
  return this->sunkenShips;
}

bool Player::createShip(int startX, int startY, int endX, int endY) {
  if (!Player::isValidShipCoordinates(startX, startY, endX, endY)) {
    return false;
  }

  Ship ship;
  ship.create(startX, startY, endX, endY);
  Player::addShip(ship);
  return true;  
}

bool Player::isValidShipCoordinates(int startX, int startY, int endX, int endY) {
  // ship instead of &ship because it generates a copy of the ship and
  // the isHit method won't increase the number of hits on the original ship
  for (auto ship : this->ships) {
    for (int i = startX; i <= endX; i++) {
      for (int j = startY; j <= endY; j++) {
        if (ship.isHit(i, j)) {
          return false;
        }
      }
    }
  }
  return true;
}

Ship Player::getShip(int arrayPosition) {
  if (arrayPosition < 0 || arrayPosition >= this->ships.size()) {
    Ship ship;
    ship.create(0, 0, 0, 0);
    return ship;
  }
  return this->ships[arrayPosition];
}

std::vector<Ship> Player::getShipsList() {
  return ships;
}

void Player::setCursor(char id, int x, int y) {
  this->board.setCursor(id, x, y);
}
