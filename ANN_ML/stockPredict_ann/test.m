%test
data = dlmread('test.txt');
X = data(1001: 1226, 2:6);
Y = data(1002:1227, 2);

m = length(X);
Y_Predict = zeros(m ,1);
X = [ones(m, 1), X(:, :)];
num = zeros(m ,1);

for iter= 1:m
  num(iter, 1) = iter;
end

theta = [  98.367000;
   44.266771;
    0.215277;
   -0.060994;
   -0.528660;
   -0.018175 ];
   
mu = [  0.0000e+00,  9.8294e+01,  9.8501e+01,  9.6911e+01,  9.7734e+01,  3.9011e+07 ];
sigma = [  5.0000e-01,  2.1969e+01,  2.3530e+01,  2.3163e+01,  2.3329e+01,  1.8187e+07 ];

Y_Predict = ((X_Predict -mu) ./(2*sigma))* theta ;
%plot(num, Y_Predict, '-');
