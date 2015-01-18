//============================================================================================
//Create by Robert Bethune
//Matrix.h
//Base Matrix Class has addition(+), multiplication scalar(*), multiplication matrix(*),
//multiplaction vector(*), subtraction(-)
//Creation Date 1/17/2015
//============================================================================================
#pragma once
#include "Vector3D.h"
//============================================================================================
class Matrix
{
public:
	Matrix();
	Matrix(int length, bool identity);
	Matrix(int rows, int columns);
	Matrix(int rows, int columns, float* matrixArray);
	~Matrix();
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	Matrix operator-(const Matrix&) const;
	Matrix operator+(const Matrix&) const;
	Matrix operator*(const Matrix&) const;
	Matrix operator*(const float&) const;
	Matrix operator*(const Vector3D&) const;
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	void Set(int row, int column, float value);
	float Get(int row, int column) const;

	bool SameDim(const Matrix& rhs) const;

	float GetArrayIndex(int i) const { return mp_Matrix[i]; }

	int  GetRowSize() const { return m_Rows; }
	int  GetColumnSize() const { return m_Columns; }

	float Det();
	Matrix InvMatrix();

//--------------------------------------------------------------------------------------------
//============================================================================================
private:
//--------------------------------------------------------------------------------------------
	float* mp_Matrix;
	int m_Rows;
	int m_Columns;
	int m_Size;
//--------------------------------------------------------------------------------------------
};
//============================================================================================
