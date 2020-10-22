#pragma once

// Include CBT
#include "cbtMacros.h"
#include "cbtMathUtil.h"

// Include STL
#include <cstring>

NS_CBT_BEGIN

/**
    Represents a matrix of size ROW_COUNT * COLUMN_COUNT.

    Matrix is column-major.
    IMPORTANT: Don't forget to account for the byte size of ROW_COUNT and COLUMN_COUNT when considering the byte size of Matrix.
    So a Matrix<cbtF32, 4, 3> will be 4 * 3 * sizeof(cbtF32) + 2 * sizeof(cbtU32).
    Certain matrix functions such as finding the inverse or determinant of a matrix, can only be done on matrices of floating point type.
*/
    template<typename T, cbtU32 COLUMN_COUNT, cbtU32 ROW_COUNT>
    class cbtMatrix
    {
        typedef cbtMatrix<T, COLUMN_COUNT, ROW_COUNT> Matrix; /// The current CBTMaatrix type.

    private:
        // Variable(s)
        T m_Value[COLUMN_COUNT * ROW_COUNT]; ///< The data of the Matrix, stored in column-major format.

    public:
        static constexpr cbtU32 ELEMENT_COUNT = ROW_COUNT * COLUMN_COUNT;

        // Constructor(s) & Destructor
        /**
            \brief Default constructor for Matrix. Creates a new Matrix of which all values are 0.

            \return A Matrix of which all values are 0.

            \sa ~Matrix
        */
        cbtMatrix()
        {
            SetToZero();
        }

        /**
        \brief Copy Constructor for Matrix. Create a new Matrix which is a copy of _other.

        \param _other The Matrix to copy.

        \return A Matrix which is a copy of _other.

        \sa ~Matrix
        */
        cbtMatrix(const cbtMatrix& _other)
        {
            *this = _other;
        }

        /// Destructor.
        virtual ~cbtMatrix()
        {
        }

        // Interface Function(s)
        /**
            \brief Sets all values of the Matrix to 0.

            \sa Get(cbtU32, cbtU32), Set(T _value, cbtU32 _row, cbtU32 _column)
        */
        inline void SetToZero()
        {
            std::memset(&m_Value[0], 0, ELEMENT_COUNT * sizeof(T));
        }

        /**
            \brief Copy the values of the Matrix to _array in column-major format.
            \param _array The array to copy to.
        */
        inline void CopyToArray(T* _array) const
        {
            std::memcpy(&_array[0], &m_Value[0], ELEMENT_COUNT * sizeof(T));
        }

        // Operator Overload(s)
        /**
            \brief operator= for Matrix.
            \param _rhs The Matrix to perform the operation with.

            \return This matrix which is equal to _rhs.

            \sa operator+(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-(),
                operator-(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator*(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*=(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*(const T),
                operator*=(const T),
                operator*(const CBTMatrix<T, RHS_COLUMN_COUNT, COLUMN_COUNT>&),
                operator[](cbtU32)
        */
        Matrix& operator=(const Matrix& _rhs)
        {
            std::memcpy(&m_Value[0], &_rhs.m_Value[0], ELEMENT_COUNT * sizeof(T));
            return *this;
        }

        /**
            \brief operator+ for Matrix.
            \param _rhs The Matrix to perform the operation with.

            \return The result of this Matrix plus _rhs.

            \sa operator=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-(),
                operator-(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator*(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*=(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*(const T),
                operator*=(const T),
                operator*(const CBTMatrix<T, RHS_COLUMN_COUNT, COLUMN_COUNT>&),
                operator[](cbtU32)
        */
        Matrix operator+(const Matrix& _rhs) const
        {
            Matrix result;
            for (cbtU32 i = 0; i < ELEMENT_COUNT; ++i)
            {
                result.m_Value[i] = m_Value[i] + _rhs.m_Value[i];
            }
            return result;
        }

        /**
            \brief operator+= for Matrix.
            \param _rhs The Matrix to perform the operation with.

            \return This Matrix which is the result of this Matrix plus _rhs.

            \sa operator=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-(),
                operator-(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator*(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*=(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*(const T),
                operator*=(const T),
                operator*(const CBTMatrix<T, RHS_COLUMN_COUNT, COLUMN_COUNT>&),
                operator[](cbtU32)
        */
        Matrix& operator+=(const Matrix& _rhs)
        {
            *this = *this + _rhs;
            return *this;
        }

        /**
            \brief Unary operator- for Matrix.

            \return The negative of this Matrix.

            \sa operator=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator*(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*=(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*(const T),
                operator*=(const T),
                operator*(const CBTMatrix<T, RHS_COLUMN_COUNT, COLUMN_COUNT>&),
                operator[](cbtU32)
        */
        Matrix operator-() const
        {
            Matrix result;
            for (cbtU32 i = 0; i < ELEMENT_COUNT; ++i)
            {
                result.m_Value[i] = -m_Value[i];
            }
            return result;
        }

        /**
            \brief operator- for Matrix.
            \param _rhs The Matrix to perform the operation with.

            \return The result of this Matrix minus _rhs.

            \sa operator=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-(),
                operator-=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator*(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*=(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*(const T),
                operator*=(const T),
                operator*(const CBTMatrix<T, RHS_COLUMN_COUNT, COLUMN_COUNT>&),
                operator[](cbtU32)
        */
        Matrix operator-(const Matrix& _rhs) const
        {
            Matrix result;
            for (cbtU32 i = 0; i < ELEMENT_COUNT; ++i)
            {
                result.m_Value[i] = m_Value[i] - _rhs.m_Value[i];
            }
            return result;
        }

        /**
            \brief operator-= for Matrix.
            \param _rhs The Matrix to perform the operation with.

            \return This Matrix which is the result of this Matrix minus _rhs.

            \sa operator=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-(),
                operator-(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator*(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*=(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*(const T),
                operator*=(const T),
                operator*(const CBTMatrix<T, RHS_COLUMN_COUNT, COLUMN_COUNT>&),
                operator[](cbtU32)
        */
        Matrix& operator-=(const Matrix& _rhs)
        {
            *this = *this - _rhs;
            return *this;
        }

        /**
            \brief operator* for Matrix.
            This number of column this Matrix has must be the same as the number of rows of _rhs.
            The resultant Matrix's size is this <this Matrix's number of rows> * <_rhs's number of columns>.

            Example:\n
            \code{.cpp}
            // RHS_COLUMN_COUNT is deduced automagically via this thingy called Template Argument Deduction. So just typing MatrixA * MatrixB is fine.
            Matrix<2, 3> Foo(const Matrix<2, 5>& _matrixA, const Matrix<5, 3>& matrixB)
            {
                Matrix<2, 3> result = _matrixA * _matrixB;
                return result;
            }
            \endcode

            \param _rhs The Matrix to perform the operation with.

            \return The result of this matrix multiplied by _rhs.

            \sa operator=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-(),
                operator-(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator*=(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*(const T),
                operator*=(const T),
                operator*(const CBTMatrix<T, RHS_COLUMN_COUNT, COLUMN_COUNT>&),
                operator[](cbtU32)
        */
        template<cbtU32 RHS_COLUMN_COUNT>
        cbtMatrix<T, RHS_COLUMN_COUNT, ROW_COUNT>
        operator*(const cbtMatrix<T, RHS_COLUMN_COUNT, COLUMN_COUNT>& _rhs) const
        {
            cbtMatrix<T, RHS_COLUMN_COUNT, ROW_COUNT> result;

            for (cbtU32 column = 0; column < RHS_COLUMN_COUNT; ++column)
            {
                for (cbtU32 row = 0; row < ROW_COUNT; ++row)
                {
                    // Dot Product between the row of this matrix and the column of the right hand side matrix.
                    for (cbtU32 i = 0; i < COLUMN_COUNT; ++i)
                    {
                        result[column][row] += (*this)[i][row] * _rhs[column][i];
                    }
                }
            }

            return result;
        }

        /**
            \brief Scalar operator* for Matrix.
            \param _scalar The scalar to perform the operation with.

            \return The result of this matrix multiplied by _scalar.

            \sa operator=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-(),
                operator-(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator*(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*=(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*=(const T),
                operator*(const CBTMatrix<T, RHS_COLUMN_COUNT, COLUMN_COUNT>&),
                operator[](cbtU32)
        */
        Matrix operator*(const T _scalar) const
        {
            Matrix result = *this;
            for (cbtU32 i = 0; i < ELEMENT_COUNT; ++i)
            {
                result.m_Value[i] = m_Value[i] * _scalar;
            }
            return result;
        }

        /**
            \brief Scalar operator*= for Matrix.
            \param _scalar The scalar to perform the operation with.

            \return This matrix which is the result of this matrix multiplied by _scalar.

            \sa operator=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-(),
                operator-(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator*(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*=(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*(const T),
                operator*(const CBTMatrix<T, RHS_COLUMN_COUNT, COLUMN_COUNT>&),
                operator[](cbtU32)
        */
        Matrix& operator*=(const T _scalar) const
        {
            *this = *this * _scalar;
            return *this;
        }

        /**
            \brief operator[] for Matrix. To get the 5th row and 7th column, use matrix[6][4].
            \param _column the column of the Matrix.

            \return The column of the Matrix specified by _column.

            \sa operator=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-(),
                operator-(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator*(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*=(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*(const T),
                operator*=(const T),
                operator*(const CBTMatrix<T, RHS_COLUMN_COUNT, COLUMN_COUNT>&),
        */
        const T* operator[](cbtU32 _column) const
        {
            return &m_Value[_column * ROW_COUNT];
        }

        /**
        \brief operator[] for Matrix. To get the 5th row and 7th column, use matrix[6][4].
        \param _column the column of the Matrix.

        \return The column of the Matrix specified by _column.

        \sa operator=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-(),
                operator-(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator*(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*=(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*(const T),
                operator*=(const T),
                operator*(const CBTMatrix<T, RHS_COLUMN_COUNT, COLUMN_COUNT>&),
        */
        T* operator[](cbtU32 _column)
        {
            return &m_Value[_column * ROW_COUNT];
        }

        // Friend Function(s)
        /**
            \brief Scalar operator* for Matrix.
            \param _scalar The scalar to perform the operation with.

            \return This matrix which is the result of this matrix multiplied by _scalar.

            \sa operator=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator+=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-(),
                operator-(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator-=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
                operator*(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*=(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
                operator*(const T),
                operator*=(const T),
                operator*(const CBTMatrix<T, RHS_COLUMN_COUNT, COLUMN_COUNT>&),
                operator[](cbtU32)
        */
        friend Matrix operator*(const T _scalar, const Matrix& _matrix)
        {
            return _matrix * _scalar;
        }
    };

/**
        \brief operator*= for Matrix.
        This number of column this Matrix has must be the same as the number of rows of _rhs.
        The resultant Matrix's size is this <this Matrix's number of rows> * <_rhs's number of columns>.

        Example:\n
        \code{.cpp}
        // RHS_COLUMN_COUNT is deduced automagically via this thingy called Template Argument Deduction. So just typing MatrixA * MatrixB is fine.
        Matrix<2, 3> Foo(const Matrix<2, 5>& _matrixA, const Matrix<5, 3>& matrixB)
        {
        Matrix<2, 3> result = _matrixA * _matrixB;
        return result;
        }
        \endcode

        \param _rhs The Matrix to perform the operation with.

        \return This matrix which is the result of this matrix multiplied by _rhs.

        \sa operator=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
            operator+(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
            operator+=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
            operator-(),
            operator-(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
            operator-=(const Matrix<T, COLUMN_COUNT, ROW_COUNT>&),
            operator*(const Matrix<T, COLUMN_COUNT, RHS_COLUMN_COUNT>&),
            operator*(const T),
            operator*=(const T),
            operator*(const CBTMatrix<T, RHS_COLUMN_COUNT, COLUMN_COUNT>&),
            operator[](cbtU32)
    */
    template<typename T, cbtU32 MATRIX_SIZE>
    cbtMatrix<T, MATRIX_SIZE, MATRIX_SIZE>&
    operator*=(cbtMatrix<T, MATRIX_SIZE, MATRIX_SIZE>& _lhs, const cbtMatrix<T, MATRIX_SIZE, MATRIX_SIZE>& _rhs)
    {
        _lhs = _lhs * _rhs;
        return _lhs;
    }

// Type Definition(s)
    typedef cbtMatrix<cbtF32, 2, 2> cbtMatrix2F;
    typedef cbtMatrix<cbtF32, 3, 3> cbtMatrix3F;
    typedef cbtMatrix<cbtF32, 4, 4> cbtMatrix4F;
    typedef cbtMatrix<cbtF32, 5, 5> cbtMatrix5F;

NS_CBT_END