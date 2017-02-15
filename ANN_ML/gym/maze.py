import numpy as np
import pylab
import scipy
import pandas as pd
import matplotlib.pyplot as plt 


def qlearning(reward_transition_function, 
              policy_function, 
              gamma,
              alpha,
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
		return int(np.random.rand() *Q.shape[1]);

def left_right_world(action, state, step):
	reward = 0;
	is_terminal = False;
	if action:
	#go th the right
		next_state = state +1;
		if next_state == 4: 			
			#reward = words[next_state];
			reward = 1;			
			is_terminal = True;
	else :
	# go to left
		next_state = state -1;
		if next_state == 0:
			reward = -1;
			#reward = words[next_state];
			is_terminal = True;	

	return (reward, next_state, is_terminal);


#def words_to_state


words = np.array([-1, 0, 0, 0, 1]);
Q = np.zeros((5, 2));
for i in range(50):
	Q, actions, states, rewards = qlearning(left_right_world,
		                                greedy_policy,
		                                1.0,
		                                0.1,
		                                5,
		                                2,
		                                niter = 50,
		                                state = int(5 / 2),
		                                Q = Q)

		
	#print 'times : %d' %(i);
print 'actions';
print actions;
	#print 'states';
	#print states;
print 'rewards';
print rewards;
		
















