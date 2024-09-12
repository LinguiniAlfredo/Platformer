#include <iostream>
#include "Player.h"
using namespace std;

Player::Player()
{
	collision = nullptr;
	physics = nullptr;
}

Player::~Player()
{
	cout << "destroying player \n";
	delete collision;
	collision = nullptr;
	delete physics;
	physics = nullptr;
}

void Player::move()
{

}
void Player::jump()
{

}