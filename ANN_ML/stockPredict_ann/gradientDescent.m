function [theta, J_history] = gradientDescent(X, y, theta, alpha, num_iters)
%GRADIENTDESCENT Performs gradient descent to learn theta
%   theta = GRADIENTDESENT(X, y, theta, alpha, num_iters) updates theta by 
%   taking num_iters gradient steps with learning rate alpha

% Initialize some useful values
m = length(y); % number of training examples
J_history = zeros(num_iters, 1);


for iter = 1:num_iters

    % ====================== YOUR CODE HERE ======================
    % Instructions: Perform a single gradient step on the parameter vector
    %               theta. 
    %
    % Hint: While debugging, it can be useful to print out the values
    %       of the cost function (computeCost) and gradient here.
    %
    h= X* theta;
    sum1 = ((h-y)')*X(:, 1);
    sum2 = ((h-y)')*X(:, 2);
    sum3 = ((h-y)')*X(:, 3);
    sum4 = ((h-y)')*X(:, 4);
    sum5 = ((h-y)')*X(:, 5);
    sum6 = ((h-y)')*X(:, 6); 
    theta(1, 1) = theta(1, 1)  -(alpha*sum1/ m);
    theta(2, 1) = theta(2, 1) - (alpha*sum2/ m);
    theta(3, 1) = theta(3, 1) - (alpha*sum3/ m);
    theta(4, 1) = theta(4, 1) - (alpha*sum4/ m);
    theta(5, 1) = theta(5, 1) - (alpha*sum5/ m);
    theta(6, 1) = theta(6, 1) - (alpha*sum6/ m);
    
    %fprintf(" iteration %d theta(1, 1) %d sum1 %d\n", iter, theta(1,1), sum1);






    % ============================================================

    % Save the cost J in every iteration    
    J_history(iter) = computeCost(X, y, theta);

end

end
