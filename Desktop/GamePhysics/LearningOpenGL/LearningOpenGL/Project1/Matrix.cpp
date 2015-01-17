#include "Matrix.h"
#include <iostream>

//--------------------------------------------------------------------------------------------
Matrix::Matrix()
:Matrix(2,true)
{
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Matrix::Matrix(int rows, int columns)
{
	m_Rows = rows;
	m_Columns = columns;
	m_Size = m_Rows * m_Columns;
	mp_Matrix = new float[m_Size];

	for (int i = 0; i < m_Size; i++)
	{
		mp_Matrix[i] = 0;
	}
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Matrix::Matrix(int length, bool identity)
:Matrix(length,length)
{
	if (identity)
	{
		for (int row = 0; row < m_Rows; row++)
		{
			mp_Matrix[(m_Rows * row) + row] = 1;
		}
	}
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Matrix::Matrix(int rows, int columns, float* matrixArray)
{
	m_Rows = rows;
	m_Columns = columns;
	m_Size = m_Rows * m_Columns;
	mp_Matrix = new float[m_Size];

	for (int i = 0; i < m_Size; i++)
	{
		mp_Matrix[i] = matrixArray[i];
	}
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Matrix::~Matrix()
{
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void Matrix::Set(int row, int column, float value)
{
	mp_Matrix[m_Columns * row + column] = value;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
float Matrix::Get(int row, int column) const 
{
	return mp_Matrix[m_Size * row + column];
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Matrix Matrix::operator*(const Matrix& rhs) const
{
	
	if (m_Columns == rhs.GetRowSize())
	{
		Matrix returnMatrix = Matrix(m_Rows, rhs.GetColumnSize());
		for (int i = 0; i < rhs.GetColumnSize(); i++)
		{
			for (int k = 0; k < rhs.GetRowSize(); k++)
			{
				float value = 0;

				for (int j = 0; j < m_Rows; j++)
				{
					value += Get(i, j) * rhs.Get(j, k);
				}

				returnMatrix.Set(i, k, value);
			}
		}
		return returnMatrix;
	}
	else
	{
		//cout << "Wrong Size Matrix * Matrix multiplication";
		return *this;
	}
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Matrix Matrix::operator*(const Vector3D& rhs) const
{
	float* newMatrix = new float[m_Rows];
	if (m_Columns == 3)
	{
		for (int i = 0; i < m_Rows; i++)
		{
			newMatrix[i] = mp_Matrix[i * m_Rows] * rhs.X + mp_Matrix[i * m_Rows + 1] * rhs.Y + mp_Matrix[i * m_Rows + 2] * rhs.Z;
		}
		return Matrix(m_Rows, 1, newMatrix);
	}
	else
	{
		//cout << "Wrong Size Matrix * Vector multiplication";
		return *this;
	}
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Matrix Matrix::operator*(const float& rhs) const
{
	float* newArray = new float[m_Size];
	for (int i = 0; i < m_Size; i++)
	{
		newArray[i] = mp_Matrix[i] * rhs;
	}
	return Matrix(m_Rows, m_Columns, newArray);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Matrix Matrix::operator+(const Matrix& rhs) const
{
	float* array = new float[m_Size];

	if (SameDim(rhs))
	{
		for (int i = 0; i > m_Size; i++)
		{
			array[i] = mp_Matrix[i] + rhs.GetArrayIndex(i);
		}

		return Matrix(m_Rows, m_Columns, array);
	}
	else
	{
		return Matrix(m_Rows, m_Columns, mp_Matrix);
	}


}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Matrix Matrix::operator-(const Matrix& rhs) const
{
	float* array = new float[m_Size];

	if (SameDim( rhs))
	{
		for (int i = 0; i > m_Size; i++)
		{
			array[i] = mp_Matrix[i] - rhs.GetArrayIndex(i);
		}

		return Matrix(m_Rows, m_Columns, array);
	}
	else
	{
		return Matrix(m_Rows, m_Columns, mp_Matrix);
	}

	
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
bool Matrix::SameDim(const Matrix& rhs) const
{
	return m_Columns == rhs.GetColumnSize() && m_Rows == rhs.GetRowSize();
}
//--------------------------------------------------------------------------------------------