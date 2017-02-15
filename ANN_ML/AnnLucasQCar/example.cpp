#include "environment.h"
#include <iostream>
using namespace std;

Environment env;
Maze maze = env.maze;

int main(int argc, char **argv) {
	env.render();
	cout << env.state[0] << "," << env.state[1] << "," << env.terminal << "," << env.bumpIntoWall;
	cout << "\n";
	env.action(1);
	env.action(1);
	env.action(1);
	env.action(0);
	cout << env.state[0] << "," << env.state[1] << "," << env.terminal << "," << env.bumpIntoWall;
	cout << "\n";
	env.action(2);
	cout << env.state[0] << "," << env.state[1] << "," << env.terminal << "," << env.bumpIntoWall;
	return 0;
}
