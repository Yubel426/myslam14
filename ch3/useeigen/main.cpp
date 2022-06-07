#include <iostream>

using namespace std;

#include <ctime>
//
#include <Eigen/Core>

#include <Eigen/Dense>

using namespace Eigen;

int main() {

    Matrix<float , 2 , 3>matrix_23;
    Matrix3d matrix_33 = Matrix3d::Zero();
    MatrixXd matrix_xx;

    matrix_23<<1,2,3,4,5,6;
    //cout<<"matrix_23 is\n"<<matrix_23<<endl;
    //cout<<"matrix_23 is\n"<<matrix_23.transpose()<<endl;
    //cout<<"matrix_23 [2,1] is "<<matrix_23(1,0)<<endl;

    Vector3d v1_3d;
    Matrix<float,3,1> v2_3d;
    v1_3d<<3,2,1;
    v2_3d<<4,5,6;
    Matrix<double,2,1> result =matrix_23.cast<double>() * v1_3d;
    //cout<<result.transpose()<<endl;
    //cout<<result<<endl;

    matrix_33 = Matrix3d::Random();//
    cout<<matrix_33<<endl;
    SelfAdjointEigenSolver<Matrix3d> eigen_solver(matrix_33.transpose()*matrix_33);
    cout << "Eigen values = \n" << eigen_solver.eigenvalues() << endl;
    cout << "Eigen vectors = \n" << eigen_solver.eigenvectors() << endl;






}
