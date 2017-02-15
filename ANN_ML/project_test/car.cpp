/*
sudo apt-get install libeigen3-dev
dpkg -p libeigen3-dev
*/
#include <iostream>
#include <Eigen/Dense>
#include <stdio.h>
#include <stdlib.h>
using namespace Eigen;
using namespace std;

#define N_STATES 10
#define N_ACTIONS 4

int policy_function(MatrixXd*Q, MatrixXd*states)
{
	if (((double)rand()/RAND_MAX) > 0.1)
		return 
	
}

void qlearning(MatrixXd*Q, MatrixXd*actions, MatrixXd*states, MatrixXd*rewards, int niter, int state_now) 
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
		//policy fuction();
		//reward_transition_function();
		actions[0](0, i) = action;
		states[0](0, i) = state_prime;
		rewards[0](0, i) = reward;		
		//Q[state, action] = Q[state, action] + alpha * (reward + np.max(Q[state_prime, :]) - Q[state, action]);
		state_now = state_prime;
		if(terminal)
			break;
		
	}
	
}
