#include "checkML.h"
#include "Game.h"
#include <iostream>



using namespace std;

int main(int argc, char* argv[])
{
	try {
		Game game;
		game.run();
	}
	catch (const std::string& msg) {
		cerr << "Error: " << msg << endl;
	}

	return 0;
}
