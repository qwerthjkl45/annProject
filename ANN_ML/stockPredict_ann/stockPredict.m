%     我的兇巴巴傻肉
%     8 5j694su3 c c 
%
%     stock predit
%     plotData.nym
%     gradientDescent.m
%     computeCost.m

clear ; close all; clc
fprintf("loading data");
data = dlmread('test.txt');
X = data(1:1000, 2:6); %five feature
y = data(10:1009, 5); % 

X_Predict = data(1001: 1200, 2:6);
X_Length = length(X_Predict);
X_Predict =[ones(X_Length, 1), X_Predict(:, :)];
Y_Predict = zeros(X_Length, 1);
Y_ActualValue = data(1010: 1209, 5)

num = zeros(200, 1);
m = length(y);

for iter = 1:200
  num(iter, 1) = iter;
end

% plot data

figure;
plot(num, Y_ActualValue, 'rx', 'MarkerSize', 10);
mu = zeros(1, 5);
sigma = zeros(1, 5);
%plot data finish

%%====part 2 :: running gradientDescent ==============%%


%normalize first
for columns =1: 5
  mu(1, columns) = mean(X(:, columns));
  fprintf("mu %d\n" ,mu(1, columns));
  sigma(1, columns) = std(X(:, columns));
  X(:, columns) = (X(:, columns) .-mu(1, columns))./(2*sigma(1, columns));
end

fprintf('running gradientDescent');
X = [ones(m, 1), X(:,:)];
theta = zeros(6, 1);

iterations = 1000;
alpha = 1;

% compute and display initial cost
J = computeCost(X, y, theta)

% run gradient descent
theta = gradientDescent(X, y, theta, alpha, iterations);


mu = [zeros(1, 1), mu(1, :)]; 
sigma = [0.5, sigma(1, :)];
predict1 = (([1, 147.5,148,145.5,146,55006000] -mu) ./(2*sigma))*theta ;
Y_Predict = ((X_Predict -mu) ./(2*sigma))* theta ;


hold on; % keep previous plot visible
plot(num, Y_Predict, '-');
legend('actul value', 'Linear regression')
hold off





