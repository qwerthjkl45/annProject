/*
sudo apt-get install libeigen3-dev
dpkg -p libeigen3-dev
*/
#include <iostream>
#include <Eigen/Dense>
#include <stdio.h>
#include <stdlib.h>
#include "environment.h"
using namespace Eigen;
using namespace std;

#define N_STATES 10
#define N_ACTIONS 4
#define N_ITER 70
#define MAZE_WIDTH 5
#define MAZE_HEIGHT 2
//static MatrixXd maze(2, 5); 
Environment env;
Maze maze = env.maze;
enum ACTION
{
 TOP = 0,
 RIGHT,
 BOTTOM,
 LEFT
};

int policy_function(MatrixXd*Q, int state, double threshold)
{
	if ((rand()/(double)RAND_MAX) > threshold)
	{
		int action = 0;
		Q->row(state).maxCoeff(&action);
		return action;
	}		
	else 
	{
		return (int)((rand()/(double)RAND_MAX) * N_ACTIONS);
	}
		
	
}

void maze_world(int *reward, int *state_prime, bool *is_terminal, int action, int state, int step)
{
	env.action(action);
	*state_prime = (env.state[0]*MAZE_WIDTH) + env.state[1];
	*is_terminal = env.terminal;
	//cout<< "terminal "<< env.terminal<<" action "<< action << " next_step " <<*state_prime <<endl;
	if(env.bumpIntoWall)
		*reward = -1 -step;
	else if(*state_prime == 9)
		*reward = 100;
	else
		*reward = -step;
	/**reward = 0;
	*is_terminal = false;
	switch(action)
	{
		case RIGHT:
			if((state % 5) == 4)
				*state_prime = state;
			else
				*state_prime = state +1 ;
			break;		
		case LEFT:
			if (((state - 1) < 0 ) || (((state) %5) == 0))
				*state_prime = state;
			else
				*state_prime = state -1;
			break;
		case TOP:
			if((state - 5) < 0)
				*state_prime = state;
			else
				*state_prime = state -5;
			break;
		case BOTTOM:
			if((state + 5) > 9)
				*state_prime = state;
			else 
				*state_prime = state +5;
			break;
	}
	if(*state_prime == 9)
	{
		*reward = 1000;
		*is_terminal = true;
	}
	else if(*state_prime == 0 )
	{
		*reward = -1000 -step;
		*is_terminal = true;
	}
	else 
	{	
		*reward = -100-step ;
	}*/
		
			
	
}

void qlearning(MatrixXd*Q, MatrixXd*actions, MatrixXd*states, MatrixXd*rewards, int niter, int state_now, int training_times) 
{
	actions->setZero();// 1*niter
	states->setZero();// 1*niter
	rewards ->setZero();
	
	int action =0;
	int reward = 0;
	int state_prime = 0;
	bool terminal = false;
	
	for(int i = 0; i < niter; i++)
	{
		if(training_times < 350)
			action = policy_function(Q, state_now, 0.5);
		else
			action = policy_function(Q, state_now, 0.1);
		maze_world(&reward, &state_prime, &terminal, action, state_now, i);
		//cout<<"  terminal "<<terminal<<endl; 
		actions[0](0, i) = action;
		states[0](0, i) = state_prime;
		rewards[0](0, i) = reward;	
		Q[0](state_now, action) = (0.9 *Q[0](state_now, action)) + (0.1*(reward + Q->row(state_prime).maxCoeff()));
		//Q[state, action] = Q[state, action] + alpha * (reward + np.max(Q[state_prime, :]) - Q[state, action]);
		state_now = state_prime;
		if(terminal)
		{
			//cout<<"enter terminal"<<endl;
			return;
		}
			
	}
	
}

int main()
{
	cout<< "start terminal "<< env.terminal<<endl;
	MatrixXd Q(MAZE_WIDTH *MAZE_HEIGHT, N_ACTIONS);
	
	Q.setZero();
	//cout <<"Q: \n"<< Q <<"\n\n\n"<<endl;
	MatrixXd actions(1, N_ITER);
	MatrixXd states(1, N_ITER);
	MatrixXd rewards(1, N_ITER);
	bool terminal = false;
	//env.render();
	//env.action(0);
	
	for(int i = 0; i < 10; i++)
	{
	
		env.reset();
		qlearning(&Q, &actions, &states, &rewards, N_ITER, 1, i);
		//if(terminal)
			//break;
	}
	env.reset();
	env.render();
	cout<<"start action 1"<<endl;
	env.action(1);
	for(int i = 0 ; i< 5; i++)
	{
		env.action(actions(0, i));
		cout<<"hello"<<endl;
		sleep(5000);	
	}
	std::cout << "Now actions \n" << states << std::endl;
	return 0;
}
