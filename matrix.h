#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <string>
#include <cstdlib> // #include 	<stdlib.h>
#include <conio.h>
#include <time.h>
#include <sstream>
#include <cmath>

using namespace std;
enum MatrixType {Identity, Random};
/*
 * [1] Copy constructor (to prevent shallow copy)
 *
 * [2] Delegating Constructors:
 * Matrix(int rows_, int cols_, float val)
 * :Matrix(rows_, cols_) // Delegate constructor
 * {
 *	// set all elements to val.
 * }
 *
 * [3] How to return objects created with dynamic Mem. allocation?
 * 1. Return a pointer to the object.
 * 2. Return a reference instead.
 *    The 2nd approach is implemented in Lafore Pg. 465-466
 * 	  "Another approach to new".
 * Matrix& Matrix::operator+(Matrix& m)
 * {
 *  	Matrix* res = new Matrix(rows, cols);
 *		// ...
 *		return (*res);
 * }
 * Note: the caller function should keep track of the address of
 * object returned by reference, to delete it later on.
 *
*/

class Matrix
{
private:
    int rows;
    int cols;
    float **data;
public:
    Matrix(int rows_, int cols_);
    Matrix(int rows_, int cols_, float val);
    Matrix(int rows_, int cols_, MatrixType m_type);
    /*Copy constructor: to prevent shallow copy*/
    Matrix(const Matrix& m);
    ~Matrix();
    int get_rows() const;
    int get_cols() const;
    void print() const;
    float& access(int r_ind, int c_ind);
    Matrix operator+(const Matrix& m) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator*(float val) const;
    Matrix operator/(float val) const;
    Matrix operator*(const Matrix& m) const;
    Matrix inverse();
    Matrix adjugate();
    Matrix &operator/=( Matrix &mat);
    /*Bonus: Matrix Inverse*/
    Matrix operator/( Matrix& m) const;
    bool operator==(const Matrix& m) const;
    bool operator!=(const Matrix& m) const;
    bool isIdentity() const;
    bool isIdempotent() const;
    bool isSquare() const;
    bool isSymmetric() const;
    bool isUpperTriangle() const;
    bool isLowerTriangle() const;
    Matrix transpose() const;
    void fill(float val);
    void FillMatrix();
    float minElement() const;
    float maxElement() const;
    /*Bonus: Determinant*/
    float determinant() ;
    /*Bonus: stringify Matrix*/
    string toString() const;
    Matrix* DeleteCol(int index,int* col);
    Matrix* DeleteRow(int row);
    void SwapColWith(Matrix* mat,int index);

};

#endif // MATRIX_H
