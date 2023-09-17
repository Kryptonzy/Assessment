#include <iostream>
class Matrix {
public:
    Matrix(int rows, int cols); 
    ~Matrix();
    friend std::istream& operator>>(std::istream& in, Matrix& matrix);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator/(const Matrix& other);
    Matrix operator*(Matrix &other);
    Matrix(int rows, int cols, int** matrix);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix &&other);
    bool operator==(const Matrix& other);
 private:
     int rows;
     int cols;
     int **matrix;
 };
Matrix::Matrix(int rows, int cols)
{   
    this->rows = rows;
    this->cols = cols;
    matrix = new int*[rows];
    for (int i = 0; i < rows; i++) 
    {
        matrix[i] = new int[cols];
    }
}                             
Matrix::~Matrix() 
{
    for (int i = 0; i < rows; i++) 
        delete[] matrix[i];
}                                               
std::istream& operator>>(std::istream& in, Matrix& matrix)
{
    for(int i=0;i<matrix.rows;i++)
    {
        for(int j=0;j<matrix.cols;j++)
        {
            in >> matrix.matrix[i][j];
        }
    }
    return in;
}
std::ostream& operator<<(std::ostream& os, const Matrix& matrix) 
{
    os << "[";
    for(int i=0;i<matrix.rows;i++)
    {
        for(int j=0;j<matrix.cols;j++)
        {
            os << matrix.matrix[i][j] << ",";
        }
        os << std::endl;
    }
    os << "]";
    return os;
}
Matrix Matrix::operator*(Matrix &other)
{
    Matrix result(this->rows,other.cols);
    for(int a=0;a<this->rows;a++)
    {
        for(int b=0;b<other.cols;b++)
        {
            int sum= 0;
            for(int i=0;i<this->cols;i++)
            {
                sum+=this->matrix[a][i]*other.matrix[i][b];
            }
            result.matrix[a][b]=sum;
        }
    }
    return result;
}
Matrix::Matrix(int rows, int cols, int** matrix):Matrix(rows,cols)
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            this->matrix[i][j]=matrix[i][j];
        }
    }
}
Matrix::Matrix(const Matrix& other):Matrix(other.rows,other.cols,other.matrix){}
Matrix::Matrix(Matrix&& other):Matrix(other.rows,other.cols,other.matrix){}
Matrix& Matrix::operator=(const Matrix& other)
{
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = new int*[rows];
    for (int i = 0; i < rows; i++) 
    {
        this->matrix[i] = new int[cols];
    }
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            this->matrix[i][j]=other.matrix[i][j];
        }
    }
    return *this;
}
Matrix& Matrix::operator=(Matrix &&other)
{
    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    rows = other.rows;
    cols = other.cols;
    matrix = other.matrix;
    other.rows = 0;
    other.cols = 0;
    other.matrix = nullptr;
    return *this;
}
Matrix Matrix::operator+(const Matrix& other)
{
    Matrix result(rows,cols);
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            result.matrix[i][j]=this->matrix[i][j]+other.matrix[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator-(const Matrix& other)
{
    Matrix result(rows,cols);
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            result.matrix[i][j]=this->matrix[i][j]-other.matrix[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator/(const Matrix& other)
{
    Matrix result(rows,cols);
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            result.matrix[i][j]=this->matrix[i][j]/other.matrix[i][j];
        }
    }
    return result;
}
bool Matrix::operator==(const Matrix& other)
{
    if(this->rows!=other.rows||this->cols!=other.cols)
    {
        return false;
    }
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            if(this->matrix[i][j]!=other.matrix[i][j])
            {
                return false;
            }
        }
    }
    return true;
}