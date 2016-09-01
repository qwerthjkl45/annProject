#include <iostream>
#include <Eigen/Dense>
#include <stdio.h>
#include <stdlib.h>
using namespace Eigen;
using namespace std;

void test(MatrixXd* b)
{

     b[0](0, 1) = 100;
     cout << b[0](0, 1) <<endl;
}
int main()
{
  double rndf  = (double)rand()/RAND_MAX;
  printf("%f", rndf);
  Matrix2d a;
  a << 1, 2,
  3, 4;
  MatrixXd b(2,2);
  b << 2, 3,
  1, 4;
  //b.setZero(2, 2);
  MatrixXd c(1, 2);
  c(0, 0) = 12;
  std::cout << "Now b =\n" << c<< std::endl;
  test(&b);
  std::cout << "Now b =\n" << b << std::endl;
  Vector3d v(1,2,3);
  Vector3d w(1,0,0);
  std::cout << "-v + w - v =\n" << -v + w - v << std::endl;
}

// g++ -I/usr/include/eigen3 car.cpp -o my_exec

