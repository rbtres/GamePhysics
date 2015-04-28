#include "Matrix.h"
#include <iostream>
//http://easy-learn-c-language.blogspot.com/2013/02/numerical-methods-determinant-of-nxn.html
//help on det for nxn 
//http://www.ccodechamp.com/c-program-to-find-inverse-of-matrix/
//help on inverse matrix
//--------------------------------------------------------------------------------------------
Matrix::Matrix()
:Matrix(2,true)
{
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Matrix::Matrix(const Matrix& rhs)
{
	m_Rows = rhs.GetRowSize();
	m_Columns = rhs.GetColumnSize();
	m_Size = m_Rows * m_Columns;
	mp_Matrix = new float[m_Size];

	for (int i = 0; i < m_Size; i++)
	{
		mp_Matrix[i] = rhs.mp_Matrix[i];
	}
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
Matrix& Matrix::operator=(const Matrix& rhs)
{
	m_Rows = rhs.GetRowSize();
	m_Columns = rhs.GetColumnSize();
	m_Size = m_Rows * m_Columns;
	mp_Matrix = new float[m_Size];

	for (int i = 0; i < m_Size; i++)
	{
		mp_Matrix[i] = rhs.mp_Matrix[i];
	}

	return *this;
}
//--------------------------------------------------------------------------------------------
void Matrix::Set(int row, int column, float value)
{
	mp_Matrix[m_Columns * row + column] = value;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
float Matrix::Get(int row, int column) const 
{
	return mp_Matrix[m_Columns * row + column];
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Matrix Matrix::operator*(const Matrix& rhs) const
{
	
	if (m_Columns == rhs.GetRowSize())
	{
		Matrix returnMatrix = Matrix(m_Rows, rhs.GetColumnSize());

		for (int i = 0; i < m_Rows; i++)
		{
			for (int k = 0; k < m_Columns; k++)
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
Vector3D Matrix::operator*(const Vector3D& rhs) const
{
	float* newMatrix = new float[m_Rows];
	if (m_Columns == 3)
	{
		for (int i = 0; i < m_Rows; i++)
		{
			newMatrix[i] = mp_Matrix[i * m_Rows] * rhs.X + mp_Matrix[i * m_Rows + 1] * rhs.Y + mp_Matrix[i * m_Rows + 2] * rhs.Z;
		}
		Vector3D newV = Vector3D(newMatrix[0], newMatrix[1], newMatrix[2]);
		return newV;
	}
	else
	{
		//cout << "Wrong Size Matrix * Vector multiplication";
		return Vector3D::Zero;
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

//--------------------------------------------------------------------------------------------
float Matrix::Det()
{
	float ratio, det;
	Matrix m = *this;
	if (m_Rows == m_Columns)
	{
		for (int i = 0; i < m_Rows; i++)
		{
			for (int j = i + 1; j < m_Columns; j++)
			{
				if (j > i)
				{
					ratio = m.Get(j, i) / m.Get(i, i);

					for (int k = 0; k < m_Rows; k++)
					{
						m.Set(j,k,(m.Get(j,k)-(ratio*m.Get(i,k))));
					}
				}
			}
		}
		det = 1;
		for (int i = 0; i < m_Rows; i++)
		{
			det *= m.Get(i,i);
		}
		return det;
	}
	else
	{
		//Det does not exist.
		//For sake of returning to make inverse send 0
		return 0;
	}
}
//--------------------------------------------------------------------------------------------

//-----------http://www.sanfoundry.com/cpp-program-finds-inverse-graph-matrix/----------------
Matrix Matrix::InvMatrix() const
{
	Matrix inv = *this;
	if (inv.Det() != 0)
	{
		int n = inv.GetRowSize();
		int i, j, k;
		float d;
		for (int i = 1; i <= n; i++)
		{
			for (j = 1; j <= 2 * n; j++)
			{
				if (j == (i + n))
				{
					inv.Set(i, j, 1);
				}
			}
		}
		for (i = n; i > 1; i--)
		{
			if (inv.Get(i - 1,1) < inv.Get(i,1))
			{
				for (j = 1; j <= n * 2; j++)
				{
					d = inv.Get(i,j);
					inv.Set(i,j, inv.Get(i - 1,j));
					inv.Set(i - 1,j,d);
				}
			}
		}
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n * 2; j++)
			{
				if (j != i)
				{
					d = inv.Get(j,i) / inv.Get(i,i);
					for (k = 1; k <= n * 2; k++)
					{
						inv.Set(j,k,inv.Get(j,k) - (inv.Get(i,k) * d));
					}
				}
			}
		}
		for (i = 1; i <= n; i++)
		{
			d = inv.Get(i,i);
			for (j = 1; j <= n * 2; j++)
			{
				inv.Set(i,j, inv.Get(i,j) / d);
			}
		}
		return inv;
	}

	return Matrix(inv.m_Rows, inv.m_Columns);
}

Vector3D Matrix::Transform(const Vector3D &rhs)const
{
	return *this * rhs;
}
//--------------------------------------------------------------------------------------------

Vector3D Matrix::GetAxis(unsigned int column) const
{ 
	return Vector3D(mp_Matrix[column], mp_Matrix[column + 4], mp_Matrix[column + 8]);
}