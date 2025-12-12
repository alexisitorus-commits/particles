#include "Matrices.h"
#include <cmath>

namespace Matrices
{
    Matrix::Matrix(int _rows, int _cols)
    {
        rows = _rows;
        cols = _cols;
        a.resize(rows);
        for (int i = 0; i < rows; i++)
        {
            a[i].resize(cols, 0);
        }
    }

    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            throw runtime_error("Error: dimensions must agree");
        }

        Matrix result(a.getRows(), a.getCols());
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                result(i, j) = a(i, j) + b(i, j);
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getRows())
        {
            throw runtime_error("Error: dimensions must agree");
        }

        Matrix result(a.getRows(), b.getCols());

        for (int k = 0; k < b.getCols(); k++)
        {
            for (int i = 0; i < a.getRows(); i++)
            {
                double sum = 0;
                for (int j = 0; j < a.getCols(); j++)
                {
                    sum += a(i, j) * b(j, k);
                }
                result(i, k) = sum;
            }
        }
        return result;
    }

    bool operator==(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            return false;
        }

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                if (std::abs(a(i, j) - b(i, j)) >= 0.001)
                {
                    return false;
                }
            }
        }
        return true;

    }

    bool operator!=(const Matrix& a, const Matrix& b)
    {
        return !(a == b);
    }

    std::ostream& operator<<(ostream& os, const Matrix& a)
    {
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                os << std::setw(10) << a(i, j) << " ";
            }
            os << endl;
        }
        return os;
    }

    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
    {
        (*this)(0, 0) = cos(theta);
        (*this)(0, 1) = -sin(theta);
        (*this)(1, 0) = sin(theta);
        (*this)(1, 1) = cos(theta);
	}

    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
    {
        (*this)(0, 0) = scale;
        (*this)(0, 1) = 0;
        (*this)(1, 0) = 0;
        (*this)(1, 1) = scale;
	}

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int numPoints) : Matrix(2, numPoints)
    {
        for (int j = 0; j < numPoints; j++)
        {
            (*this)(0, j) = xShift;
            (*this)(1, j) = yShift;
        }
	}

}
