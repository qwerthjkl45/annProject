import numpy as np
import pylab
import scipy
import pandas as pd
import matplotlib.pyplot as plt 


def qlearning(reward_transition_function, #function
              policy_function, #function
              gamma, #no
              alpha, #no
              nstates, 
              nactions,
              niter,
              state,
              Q ,
             ):

	if Q is None:
		Q = np.zeros(nstates, nactions);

	if state is None:
		state = int(np.random.rand() * nstates);

	actions = np.zeros(niter);
	states = np.zeros(niter);
	rewards = np.zeros(niter);

	for i in range(niter):
		action = policy_function(Q, state);
		reward, state_prime, is_terminal = reward_transition_function(action, state, i);
		actions[i] = action;
		states[i] = state_prime; #why not state;
		rewards[i] = reward;
		Q[state, action] = Q[state, action] + alpha * (reward + np.max(Q[state_prime, :]) - Q[state, action]);

		state = state_prime;
		if is_terminal:
			break;

	return (Q, actions, states, rewards)


def greedy_policy(Q, state):
	if np.random.rand() > 0.1:
		return np.argmax(Q[state, :]);
	else:
		return int(np.random.rand() *4);

def left_right_world(action, state, step):
	reward = 0;
	is_terminal = False;
	if action == 0:
	#go th the right
		if( (state ) % 5 ) == 4 :
			next_state = state;
		else:
			next_state = state +1;
		if next_state == 9: 			
			reward = 1;			
			is_terminal = True;
	elif action == 1:
	# go to left
		if ((state - 1) < 0 ) or (((state) %5) == 0):
			next_state = state;
		else :
			next_state = state -1;
		if next_state == 0:
			reward = -1;
			is_terminal = True;
	elif action == 2:
	#go to top
		if(state - 5)< 0:
			next_state = state;
		else :
			next_state = state -5;
		if next_state == 0:
			reward = -1;
			is_terminal = True;
	else :
	#go to bottom
		if(state + 5) > 9:
			next_state = state;
		else:
			next_state = state +5;
		if next_state == 9:
			reward = 1;
			is_terminal = True;
	if next_state == 2:
		reward = -1;
	return (reward, next_state, is_terminal);


#def words_to_state
#[-1, 0, -1, 0, 0]
#[ 0, 0, 0, 0, 1]


mazes = np.array([[-1, 0, -1, 0, 0],[ 0, 0, 0, 0, 1]] )
#print two_worlds.size;
action_num = 4;
Q = np.zeros((mazes.size, action_num));
for i in range(500):
	Q, actions, states, rewards = qlearning(left_right_world,
		                                greedy_policy,
		                                1.0,
		                                0.1,
		                                mazes.size,
		                                action_num,
		                                niter = 100,
		                                state = 1,
		                                Q = Q)

		
	#print 'times : %d' %(i);
print 'actions';
print actions;
	#print 'states';
	#print states;
print 'states';
print states;

for walk in range(100):
	state = states[walk];
	mazes = mazes.astype(np.str);
	mazes[(int)(state / 5)][state % 5] = '*';
	if state == 9:
		break;

print mazes;	
		
















