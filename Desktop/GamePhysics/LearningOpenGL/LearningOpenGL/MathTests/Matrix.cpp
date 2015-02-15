#include "stdafx.h"
#include "CppUnitTest.h"
#include "Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MathTests
{
	TEST_CLASS(Matrix1)
	{
	public:
		
		TEST_METHOD(MatrixScalarMultiply)
		{
			Matrix m = Matrix(2, true);// TODO: Your test code here
			Matrix t = m * 2;
			Assert::AreEqual((float)2, t.Get(0, 0));
			Assert::AreEqual((float)2, t.Get(1, 1));
		}
		TEST_METHOD(MatrixSetAndGet)
		{
			Matrix m = Matrix(2, true);
			m.Set(1, 1, 4);
			Assert::AreEqual((float)4, m.Get(1, 1));
		}
	};
}