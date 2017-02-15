#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#define ESCAPE 27
#define WALL_THICKNESS 0.05
#define WALL_HEIGHT 1.0
#define GRID_WIDTH 1.0
#define NUM_OF_WIDTH 5
#define NUM_OF_HEIGHT 2

class MazeGrid {
	public:
		bool _eW;
		bool _sW;
		bool _wW;
		bool _nW;

		MazeGrid();
		MazeGrid(bool eW, bool sW, bool wW, bool nW);
};

class Maze {
	public:
		MazeGrid mazeGrid[NUM_OF_HEIGHT][NUM_OF_WIDTH];
		Maze();	
		
		void setMap();
		void printMap();
};

class Environment {
	public:
		int initialState[2];
		int finalState[2];
		int state[2];
		bool terminal;
		bool bumpIntoWall;
		Maze maze;

		Environment();
		void action(int direction);
		void reset();
		void render();
};



//void openGLCube(double* thisColor, double (*points)[3]);


#endif
