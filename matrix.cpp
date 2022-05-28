#include "matrix.h"
#include "string.h"


Matrix::Matrix(int rows_, int cols_)
{

    rows = rows_ ;
    cols =cols_;
    data = NULL;
    if(rows>0 && cols >0)
        data = new float* [rows];

    for (int i =0 ; i<rows ; i++)
    {
        data [i] = new float [cols];

        for(int j =0 ; j<cols ; j++)
        {
            data [i][j]=0.0;
        }
    }
//    if(rows_ == 0 || cols_ == 0)
//    {
//        data = NULL;
//
//    }


//    else
//    {

//    }
}


Matrix::Matrix(int rows_, int cols_, float val)
{
    rows = rows_ ;
    cols =cols_;
    if(rows_ == 0 || cols_ == 0)
    {
        data = NULL;

    }
    else
    {

        data = new float* [rows];
        for (int i =0 ; i<rows ; i++)
        {
            data [i] = new float [cols];

            for(int j =0 ; j<cols ; j++)
            {
                data [i][j]=val;
            }
        }
    }
}


Matrix::Matrix(int rows_, int cols_, MatrixType m_type)
{
    if((m_type == Identity) &&  rows_ == cols_ )
    {
        rows = rows_ ;
        cols =cols_;

        data = new float* [rows];
        for (int i =0 ; i<rows ; i++)
        {
            data [i] = new float [cols];

            for(int j =0 ; j<cols ; j++)
            {
                if(i==j)
                    data[i][j] = 1;
                else
                    data [i][j]=0.0;
            }
        }
    }
    else if ((m_type == Identity) &&  rows_ != cols_ )
    {
        rows = 0;
        cols = 0;
        data = NULL;
        cout<<"Error can't make identity matrix \n";
    }
    else if(m_type == Random)
    {
        rows = rows_ ;
        cols =cols_;
        data = new float* [rows];
        for (int i =0 ; i<rows ; i++)
        {
            data [i] = new float [cols];

            for(int j =0 ; j<cols ; j++)
            {
                data [i][j]=rand();
            }
        }

    }
}

/*Copy constructor: to prevent shallow copy*/
Matrix::Matrix(const Matrix& m)
{
    rows = m.rows;
    cols = m.cols;
    data = new float* [rows];
    for (int i =0 ; i<rows ; i++)
    {
        data [i] = new float [cols];

        for(int j =0 ; j<cols ; j++)
        {
            data [i][j] = m.data[i][j];
        }
    }


}

Matrix::~Matrix()
{
    for(int i =0 ; i<rows ; i++)
    {
        delete[] data [i];
    }
    delete[] data;

}

int Matrix::get_rows() const
{

    return rows ;
}

int Matrix::get_cols() const
{
    return cols;
}

void Matrix::print() const
{
    for(int i = 0; i< rows ; i++)
    {
        for (int j =0; j<cols ; j++)
        {
            cout << data[i][j] << " " ;
        }
        cout<<"\n";
    }
}

float& Matrix::access(int r_ind, int c_ind)
{
    if(r_ind < rows &&  c_ind < cols)
    {
        return data [r_ind][c_ind];
    }

}

Matrix Matrix::operator+(const Matrix& m) const
{
    if((rows != m.rows) || cols != m.cols )
    {
        Matrix* m = new Matrix (0,0);
        return *m;
    }
    Matrix* res = new Matrix(rows, cols);
    for(int i = 0; i< rows ; i++)
    {
        for (int j =0; j<cols ; j++)
        {
            res->data[i][j] = data[i][j] + m.data [i][j];
        }

    }


    return *res;
}

Matrix Matrix::operator-(const Matrix& m) const
{
    if((rows != m.rows) || cols != m.cols )
    {
        Matrix* m = new Matrix (0,0);
        return *m;
    }
    Matrix* res = new Matrix(rows, cols);
    for(int i = 0; i< rows ; i++)
    {
        for (int j =0; j<cols ; j++)
        {
            res->data[i][j] = data[i][j] - m.data [i][j];
        }

    }


    return *res;
}

Matrix Matrix::operator*(float val) const
{
    Matrix* res = new Matrix(rows, cols);
    for(int i = 0; i< rows ; i++)
    {
        for (int j =0; j<cols ; j++)
        {
            res->data[i][j] = data[i][j] *val;
        }

    }


    return *res;

}

Matrix Matrix::operator/(float val) const
{
    Matrix* res = new Matrix(rows, cols);
    for(int i = 0; i< rows ; i++)
    {
        for (int j =0; j<cols ; j++)
        {
            res->data[i][j] = data[i][j] / val;
        }

    }


    return *res;

}

Matrix Matrix::operator*(const Matrix& m) const
{
    if((cols != m.rows) )
    {
        Matrix* res = new Matrix (0,0);
        return * res;
    }
    Matrix* res = new Matrix(rows, m.cols,0);
    for(int i = 0,k=0,c=0; i<res->rows; i++)
    {
        for(int j =0; j<res->cols; j++)
        {
            for(int x = 0; x<cols; x++)

                res->data[i][j] += (data[k][x] * m.data[x][c]);

        }
        if (k<(rows-1 ))
            k++;
        if(c<(m.cols - 1))
            c++;
    }
    return *res;


}



bool Matrix::operator==(const Matrix& m) const
{
    if(rows == m.rows && cols == m.cols )
    {
        bool res = true;
        {
            for (int i =0; i<rows; i++)
            {
                for(int j =0; j<cols ; j++)
                {
                    if(data [i][j] != m.data[i][j])
                        res = false;
                }
            }
        }
        return res;
    }
    else
        return false;

}

bool Matrix::operator!=(const Matrix& m) const
{
    if(rows == m.rows && cols == m.cols )
    {
        bool res = false;
        {
            for (int i =0; i<rows; i++)
            {
                for(int j =0; j<cols ; j++)
                {
                    if(data [i][j] != m.data[i][j])
                        res = true;
                }
            }
        }
        return res;
    }
    else
        return true;

}

bool Matrix::isIdentity() const
{
    bool res = true;
    for (int i =0; i<rows; i++)
    {
        for(int j =0; j<cols ; j++)
        {
            if(i==j && data[i][j] !=1)
                res = false;
            else if(i != j && data[i][j] != 0)
                res = false;
        }
    }
    return res;
}

bool Matrix::isIdempotent() const
{}

bool Matrix::isSquare() const
{}

bool Matrix::isSymmetric() const
{}

bool Matrix::isUpperTriangle() const
{}

bool Matrix::isLowerTriangle() const
{}

Matrix Matrix::transpose() const
{
    Matrix* res = new Matrix(cols,rows,0);
    for (int i =0; i<rows; i++)
    {
        for(int j =0; j<cols ; j++)
        {
            res->data[j][i] = data [i][j];
        }
    }
    return *res;
}

void Matrix::fill(float val)
{
    for (int i =0; i<rows; i++)
    {
        for(int j =0; j<cols ; j++)
        {
            data [i][j] = val;
        }
    }
}

float Matrix::minElement() const
{
    float res = data[0][0];
    for (int i =0; i<rows; i++)
    {
        for(int j =0; j<cols ; j++)
        {
            if(data [i][j] < res)
                res = data[i][j];
        }
    }
    return res;
}

float Matrix::maxElement() const
{
    float res = data[0][0];
    for (int i =0; i<rows; i++)
    {
        for(int j =0; j<cols ; j++)
        {
            if(data [i][j] > res)
                res = data[i][j];
        }
    }
    return res;
}

float Matrix::determinant()
{
    if(rows != cols)
    {
        cout<<"Error can't detrmine";
        return 0;
    }

    if(rows == 1)
        return data[0][0];
    double res = 1;
    if(isIdentity())
    {
        for(int i = 0 ;i<rows;i++)
            res*= data[i][i];
        return res;
    }

    res = 1;
    Matrix* subcolmatrix = new Matrix(rows-1,cols-1);
    for(int i =0; i<rows-1; i++)
    {
        for(int j =0; j<cols-1; j++)
            subcolmatrix->data[i][j] = data[i+1][j+1];
    }


    int sign = 1;

    for(int k = 0 ; k<cols-1 ; k++)
    {

        res+= sign*data[0][k]*subcolmatrix->determinant();
        sign *= -1;
        subcolmatrix->SwapColWith(this,k);

    }
    return res;

    // O(d(n)) = n^n


}


string Matrix::toString() const
{
    string res = "";
    char ch;
    int x ;

    for (int i =0; i<rows; i++)
    {
        for(int j =0; j<cols ; j++)
        {
            x =data[i][j];
            while( x >=10)
            {
                ch = '0' + (x % 10);
                res += ch;

                x/= 10;
            }
            ch = '0' + x ;
            res += ch;
            res += " ";


        }
        res += "\n";
    }
    return res;
}



Matrix* Matrix :: DeleteCol(int index,int* col)
{
    for(int i =0 ; i<rows; i++)
        col[i] = data[i][index];
    Matrix* Newmat = new Matrix (rows,cols-1);
    bool after = false;
    for(int i =0 ; i<cols-1 ; i++)
    {
        for(int j =0 ; j<rows; j++)
        {
            if(index==i)
                after = true;
            if(!after)
                Newmat->data[j][i] = data[j][i];
            else
            {
                Newmat->data[j][i] = data[j][i+1];
            }
        }

    }
    return Newmat;
}
Matrix* Matrix:: DeleteRow (int row)
{
    Matrix* Newmat = new Matrix (rows-1,cols);
    bool after = false;
    for(int i =0 ; i<rows-1 ; i++)
    {
        for(int j =0 ; j<cols; j++)
        {
            if(row==i)
                after = true;
            if(!after)
                Newmat->data[i][j] = data[i][j];
            else
                Newmat->data[i][j] = data[i+1][j];
        }
    }
    return Newmat;

}

void Matrix::SwapColWith(Matrix* mat,int index)
{
    for(int i =0 ; i<rows; i++)
    {
        data[i][index] = mat->data[i+1][index] ;
    }
}

Matrix Matrix::inverse()
{
    return adjugate() / determinant();
}
Matrix Matrix::adjugate()
{
     if (!isSquare()) {
    cerr << "matrix has no adjugate\n";
    exit(-1);
  }
  Matrix adj(rows, cols);
  for (int i = 0; i < rows; i++) {
    Matrix tmp(rows - 1, cols - 1);
    for (int j = 0, jj = 0; j < rows; j++)
      if (j != i) {
        for (int k = 1; k < cols; k++)
          tmp.access(jj, k - 1) = data[j][k];
        jj++;
      }
    for (int j = 0; j < cols; j++) {
      adj.access(i, j) = (i + j) & 1 ? -1 : 1;
      adj.access(i, j) *= tmp.determinant();
      if (j != cols - 1) {
        for (int k = 0, kk = 0; k < rows; k++)
          if (k != i) {
            tmp.access(kk, j) = data[k][j];
            kk++;
          }
      }
    }
  }
  return adj.transpose();
}

Matrix &Matrix::operator/=( Matrix &mat) {
   Matrix res(rows , mat.cols);
   res = *this * mat.inverse();
  return res;
}

 Matrix Matrix:: operator/( Matrix& m) const
 {
      Matrix res(*this);
  res /= m;
  return res;
 }
//bool isSymmetric() const;
/*bool Matrix :: isUpperTriangle() const
{
    bool upper = true;
    for(int i = 0 ; i<rows;i++)
        for(int j = 0;j<cols;j++)
            if(i<j && data[i][j]!= 0)
                upper = false;
    return upper;
}
bool Matrix :: isLowerTriangle() const
{
     bool lower = true;
    for(int i = 0 ; i<rows;i++)
        for(int j = 0;j<cols;j++)
            if(i>j && data[i][j]!= 0)
                lower = false;
    return lower;
}*/

