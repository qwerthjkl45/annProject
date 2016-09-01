#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;


MatrixXd test(MatrixXd a, MatrixXd b)
{
	std::cout << "a + b =\n" << a + b << std::endl;
	return (a+b);
}
int main()
{
  Matrix2d a;
  a << 1, 2,
  3, 4;
  MatrixXd b(2,2);
  b << 2, 3,
  1, 4;
  MatrixXd matrix = test(a, b);
  std::cout << matrix<< std::endl;
  /*std::cout << "a + b =\n" << a + b << std::endl;
  std::cout << "a - b =\n" << a - b << std::endl;
  std::cout << "Doing a += b;" << std::endl;
  a += b;
  std::cout << "Now a =\n" << a << std::endl;
  */
  Vector3d v(1,2,3);
  Vector3d w(1,0,0);
  std::cout << "-v + w - v =\n" << -v + w - v << std::endl;
}
