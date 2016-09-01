import numpy as np
import pandas as pd
import gym
import functools

env = gym.make("CartPole-v0");
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

	actions = np.zeros(niter);
	states = np.zeros(niter); 
	rewards = np.zeros(niter);
	
	for i in range(niter):
		action = policy_function(Q, state, 0.1);
		reward, state_prime, is_terminal = reward_transition_function(action, state, i);
		actions[i] = action;
		rewards[i] = reward;
		states[i] = state_prime;
		Q[state, action] = Q[state, action] + alpha * (reward + np.max(Q[state_prime, :]) - Q[state, action]);

		state = state_prime;
		if is_terminal:
			break;
	return (Q, actions, states, rewards);

def reward_function(action, state, step):
	angle, reward, done, _ = env.step(action);
	state_prime = observation_to_state(angle);#divide into 18 stages;
	if done:
		reward = step - 195;
	return (reward, state_prime, done);

def greedy_policy(Q, state, epsion):
	if np.random.rand() > epsion:
		return np.argmax(Q[state, :]);
	else:
		return int(np.random.rand() *Q.shape[1]);

def observation_to_state(observation):
	observation = (observation > 0) * 1
    	return np.sum(observation * np.array([2 ** i for i in range(4)]))

epsilon = 0.1
frames = [];
Q = np.zeros((18, 2));
trainingTimes = 5000;
env.monitor.start('/tmp/cartpole-experiment-1')
for i in range(trainingTimes):
	angle = env.reset();
	state = observation_to_state(angle);
	#print i;
	Q, actions, states, rewards = qlearning(reward_function,
                                            greedy_policy,
                                            1,  
                                            .4, 
                                            18, 
                                            env.action_space.n, 
                                            niter = 600, 
                                            state = state,
                                            Q = Q
                                            )
	if i >= 2500:
		env.render();
env.monitor.close()        

















	







	
