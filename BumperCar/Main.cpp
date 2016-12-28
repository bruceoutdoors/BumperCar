/********************************************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1122702848 Lee Zhen Yong
Contacts    #1 : 0163188854 bruceoutdoors@gmail.com
ID and Name #2 : 1141125087 Hii Yong Lian
Contacts    #2 : 0164111005 yonglian146@gmail.com
********************************************/

#include "Game.hpp"

#include <stdexcept>
#include <iostream>


int main()
{
	try
	{
		Game game;
		game.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}
