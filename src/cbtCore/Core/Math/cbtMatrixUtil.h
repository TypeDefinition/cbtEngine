#pragma once

// Include CBT
#include "cbtMatrix.h"
#include "cbtVector3.h"

NS_CBT_BEGIN

/**
    \brief Matrix Utility Class
*/
class cbtMatrixUtil
{
private:
    // Constructor(s) & Destructor
    /**
        \brief Constructor of cbtMatrixUtil.
               It is private to prevent the creation and destruction of a cbtMatrixUtil object.
               cbtMatrixUtil is purely an interface class.

        \sa ~cbtMatrixUtil().
    */
    cbtMatrixUtil() {}
    /**
        \brief Destructor of cbtMatrixUtil.
               It is private to prevent the creation and destruction of a cbtMatrixUtil object.
               cbtMatrixUtil is purely an interface class.

        \sa cbtMatrixUtil().
    */
    ~cbtMatrixUtil() {}

public:
    // Interface Function(s)
    /**
        \brief Get the transpose of a Matrix.

        \param _matrix The Matrix to find the transpose of.

        \return Returns the transpose of _matrix.
    */
    template<typename T, cbtU32 ROW_COUNT, cbtU32 COLUMN_COUNT>
    static cbtMatrix<T, ROW_COUNT, COLUMN_COUNT> GetTransposeMatrix(const cbtMatrix<T, COLUMN_COUNT, ROW_COUNT>& _matrix)
    {
        cbtMatrix<T, ROW_COUNT, COLUMN_COUNT> transposeMatrix;
        for (cbtU32 column = 0; column < COLUMN_COUNT; ++column)
        {
            for (cbtU32 row = 0; row < ROW_COUNT; ++row)
            {
                transposeMatrix[row][column] = _matrix[column][row];
            }
        }
        return transposeMatrix;
    }

    /**
        \brief Get the minor Matrix of a Matrix.

        \param _matrix The Matrix to find the minor Matrix of.
        \param _cofactorRow The cofactor row.
        \param _cofactorColumn The cofactor column.

        \return Returns the minor Matrix of _matrix with _cofactorRow and _cofactorColumn.
    */
    template<typename T, cbtU32 MATRIX_SIZE>
    static cbtMatrix<T, MATRIX_SIZE - 1, MATRIX_SIZE - 1> GetMinorMatrix(const cbtMatrix<T, MATRIX_SIZE, MATRIX_SIZE>& _matrix, cbtU32 cofactorColumn, cbtU32 cofactorRow)
    {
        cbtMatrix<T, MATRIX_SIZE - 1, MATRIX_SIZE - 1> minorMatrix;
        for (cbtU32 majorColumn = 0, minorColumn = 0; majorColumn < MATRIX_SIZE; ++majorColumn)
        {
            if (majorColumn == cofactorColumn) { continue; }
            for (cbtU32 majorRow = 0, minorRow = 0; majorRow < MATRIX_SIZE; ++majorRow)
            {
                if (majorRow == cofactorRow) { continue; }

                minorMatrix[minorColumn][minorRow] = _matrix[majorColumn][majorRow];
                ++minorRow;
            }
            ++minorColumn;
        }
        return minorMatrix;
    }

    /** 
        \brief Get the determinant of a Matrix.

        \param _matrix The Matrix to find the determinant of.

        \return The determinant of _matrix.

        \warning GetDeterminant(const Matrix<T, MATRIX_SIZE, MATRIX_SIZE>&)
                 can only be used on Matrix of floating point types.
        \see Template Function Recursion: [https://msdn.microsoft.com/en-us/library/cdfz33t0.aspx]
    */
    template<typename T, cbtU32 MATRIX_SIZE>
    static CBT_ENABLE_IF_FLOAT(T, T) GetDeterminant(const cbtMatrix<T, MATRIX_SIZE, MATRIX_SIZE>& _matrix)
    {
        T determinant = static_cast<T>(0);

        // To calculate the determinant, we will use row 0 as the cofactor.
        for (cbtU32 column = 0; column < MATRIX_SIZE; ++column)
        {
            // Get the cofactor.
            T cofactor = _matrix[column][0];
            if ((column & 1) == 1) { cofactor = -cofactor; }

            // Get the minor Matrix.
            cbtMatrix<T, MATRIX_SIZE - 1, MATRIX_SIZE - 1> minorMatrix = GetMinorMatrix(_matrix, column, 0);
            
            // Add to the determinant.
            determinant += GetDeterminant(minorMatrix) * cofactor;
        }

        return determinant;
    }

    /**
        \brief Get the determinant of a Matrix.

        \param _matrix The Matrix to find the determinant of.

        \return The determinant of _matrix.

        \warning GetDeterminant(const Matrix<T, 2, 2>&) can only be used on Matrix of floating point types.
        \see Template Function Recursion: [https://msdn.microsoft.com/en-us/library/cdfz33t0.aspx]
    */
    template <typename T>
    static CBT_ENABLE_IF_FLOAT(T, T) GetDeterminant(const cbtMatrix<T, 2, 2>& _matrix) { return (_matrix[0][0] * _matrix[1][1]) - (_matrix[1][0] * _matrix[0][1]); }

    /**
        \brief Get the determinant of a Matrix.

        \param _matrix The Matrix to find the determinant of.

        \return The determinant of _matrix.

        \warning GetDeterminant(const Matrix<T, 1, 1>&) can only be used on Matrix of floating point types.
        \see Template Function Recursion: [https://msdn.microsoft.com/en-us/library/cdfz33t0.aspx]
    */
    template <typename T>
    static CBT_ENABLE_IF_FLOAT(T, T) GetDeterminant(const cbtMatrix<T, 1, 1>& _matrix) { return _matrix[0][0]; }

    /**
        \brief Get the determinant of a Matrix.

        \param _matrix The Matrix to find the determinant of.

        \return The determinant of _matrix.

        \warning GetDeterminant(const Matrix<T, 0, 0>&) can only be used on Matrix of floating point types.
        \see Template Function Recursion: [https://msdn.microsoft.com/en-us/library/cdfz33t0.aspx]
    */
    template <typename T>
    static CBT_ENABLE_IF_FLOAT(T, T) GetDeterminant(const cbtMatrix<T, 0, 0>& _matrix) { return static_cast<T>(1); }
    
    /**
        \brief Get the cofactor Matrix of a Matrix.

        \param _matrix The Matrix to find the cofactor Matrix of.

        \return The cofactor Matrix of _matrix.

        \warning GetCofactorMatrix(const Matrix<T, MATRIX_SIZE, MATRIX_SIZE>&) can only be used on a square Matrix of floating point types.
        \see Template Function Recursion: [https://msdn.microsoft.com/en-us/library/cdfz33t0.aspx]
    */
    template<typename T, cbtU32 MATRIX_SIZE>
    static cbtMatrix<CBT_ENABLE_IF_FLOAT(T, T), MATRIX_SIZE, MATRIX_SIZE> GetCofactorMatrix(const cbtMatrix<T, MATRIX_SIZE, MATRIX_SIZE>& _matrix)
    {
        cbtMatrix<T, MATRIX_SIZE, MATRIX_SIZE> cofactorMatrix;

        for (cbtU32 column = 0; column < MATRIX_SIZE; ++column)
        {
            for (cbtU32 row = 0; row < MATRIX_SIZE; ++row)
            {
                T determinant = GetDeterminant(GetMinorMatrix(_matrix, column, row));

                if ((column & 1) == 0)
                {
                    if ((row & 1) == 1) { determinant = -determinant; }
                }
                else
                {
                    if ((row & 1) == 0) { determinant = -determinant; }
                }

                cofactorMatrix[column][row] = determinant;
            }
        }

        return cofactorMatrix;
    }

    /**
        \brief Get the cofactor Matrix of a Matrix.

        \param _matrix The Matrix to find the cofactor Matrix of.

        \return The cofactor Matrix of _matrix.

        \warning GetCofactorMatrix(const Matrix<T, 1, 1>&) can only be used on a square Matrix of floating point types.
        \see Template Function Recursion: [https://msdn.microsoft.com/en-us/library/cdfz33t0.aspx]
    */
    template<typename T>
    static cbtMatrix<CBT_ENABLE_IF_FLOAT(T, T), 1, 1> GetCofactorMatrix(const cbtMatrix<T, 1, 1>& _matrix)
    {
        return _matrix;
    }

    /**
        \brief Get the cofactor Matrix of a Matrix.

        \param _matrix The Matrix to find the cofactor Matrix of.

        \return The cofactor Matrix of _matrix.

        \warning GetCofactorMatrix(const Matrix<T, 0, 0>&) can only be used on a square Matrix of floating point types.
        \see Template Function Recursion: [https://msdn.microsoft.com/en-us/library/cdfz33t0.aspx]
    */
    template<typename T>
    static cbtMatrix<CBT_ENABLE_IF_FLOAT(T, T), 0, 0> GetCofactorMatrix(const cbtMatrix<T, 0, 0>& _matrix)
    {
        return _matrix;
    }

    /**
        \brief Get the adjugate Matrix of a Matrix.

        \param _matrix The Matrix to find the adjugate Matrix of.

        \return The adjugate Matrix of _matrix.

        \warning GetAdjugateMatrix(const Matrix<T, MATRIX_SIZE, MATRIX_SIZE>&) can only be used on a square Matrix of floating point types.
    */
    template<typename T, cbtU32 MATRIX_SIZE>
    static cbtMatrix<CBT_ENABLE_IF_FLOAT(T, T), MATRIX_SIZE, MATRIX_SIZE> GetAdjugateMatrix(const cbtMatrix<T, MATRIX_SIZE, MATRIX_SIZE>& _matrix)
    {
        return GetTransposeMatrix(GetCofactorMatrix(_matrix));
    }

    /**
        \brief Get the inverse of a Matrix.

        \param _matrix The Matrix to find the inverse of.

        \return The inverse of _matrix.

        \warning GetInverseMatrix(const Matrix<T, MATRIX_SIZE, MATRIX_SIZE>&) can only be used on a square Matrix of floating point types.
    */
    template<typename T, cbtU32 MATRIX_SIZE>
    static cbtMatrix<CBT_ENABLE_IF_FLOAT(T, T), MATRIX_SIZE, MATRIX_SIZE> GetInverseMatrix(const cbtMatrix<T, MATRIX_SIZE, MATRIX_SIZE>& _matrix)
    {
        CBT_ASSERT(IsInvertible(_matrix));

        return (static_cast<T>(1) / GetDeterminant(_matrix)) * GetAdjugateMatrix(_matrix);
    }

    /**
        \brief Get the inverse of a Matrix. This is the fast optimization version for Matrix<T, 4, 4>.

        \param _matrix The Matrix to find the inverse of.

        \return The inverse of _matrix.

        \warning GetInverseMatrix(const Matrix<T, 4, 4>&) can only be used on a square Matrix of floating point types.
    */
    template<typename T>
    static cbtMatrix<CBT_ENABLE_IF_FLOAT(T, T), 4, 4> GetInverseMatrix(const cbtMatrix<T, 4, 4>& _matrix)
    {
        /* Previously, m_Value of CBTMatrix was public, so these equations was something like inverse.m_Value[5] = ...
        Since m_Value is not longer public, and I don't feel like manually counting which index in m_Value corresponds to which column and row,
        I simply replace .m_Value with [0] and it returns the same thing. This is why you see things like _matrix[0][15] for a 4 by 4 matrix. */

        cbtMatrix<T, 4, 4> inverse;

        inverse[0][0] =
            _matrix[0][5] * _matrix[0][10] * _matrix[0][15] -
            _matrix[0][5] * _matrix[0][11] * _matrix[0][14] -
            _matrix[0][9] * _matrix[0][6] * _matrix[0][15] +
            _matrix[0][9] * _matrix[0][7] * _matrix[0][14] +
            _matrix[0][13] * _matrix[0][6] * _matrix[0][11] -
            _matrix[0][13] * _matrix[0][7] * _matrix[0][10];

        inverse[0][4] =
            -_matrix[0][4] * _matrix[0][10] * _matrix[0][15] +
            _matrix[0][4] * _matrix[0][11] * _matrix[0][14] +
            _matrix[0][8] * _matrix[0][6] * _matrix[0][15] -
            _matrix[0][8] * _matrix[0][7] * _matrix[0][14] -
            _matrix[0][12] * _matrix[0][6] * _matrix[0][11] +
            _matrix[0][12] * _matrix[0][7] * _matrix[0][10];

        inverse[0][8] =
            _matrix[0][4] * _matrix[0][9] * _matrix[0][15] -
            _matrix[0][4] * _matrix[0][11] * _matrix[0][13] -
            _matrix[0][8] * _matrix[0][5] * _matrix[0][15] +
            _matrix[0][8] * _matrix[0][7] * _matrix[0][13] +
            _matrix[0][12] * _matrix[0][5] * _matrix[0][11] -
            _matrix[0][12] * _matrix[0][7] * _matrix[0][9];

        inverse[0][12] =
            -_matrix[0][4] * _matrix[0][9] * _matrix[0][14] +
            _matrix[0][4] * _matrix[0][10] * _matrix[0][13] +
            _matrix[0][8] * _matrix[0][5] * _matrix[0][14] -
            _matrix[0][8] * _matrix[0][6] * _matrix[0][13] -
            _matrix[0][12] * _matrix[0][5] * _matrix[0][10] +
            _matrix[0][12] * _matrix[0][6] * _matrix[0][9];

        inverse[0][1] =
            -_matrix[0][1] * _matrix[0][10] * _matrix[0][15] +
            _matrix[0][1] * _matrix[0][11] * _matrix[0][14] +
            _matrix[0][9] * _matrix[0][2] * _matrix[0][15] -
            _matrix[0][9] * _matrix[0][3] * _matrix[0][14] -
            _matrix[0][13] * _matrix[0][2] * _matrix[0][11] +
            _matrix[0][13] * _matrix[0][3] * _matrix[0][10];

        inverse[0][5] =
            _matrix[0][0] * _matrix[0][10] * _matrix[0][15] -
            _matrix[0][0] * _matrix[0][11] * _matrix[0][14] -
            _matrix[0][8] * _matrix[0][2] * _matrix[0][15] +
            _matrix[0][8] * _matrix[0][3] * _matrix[0][14] +
            _matrix[0][12] * _matrix[0][2] * _matrix[0][11] -
            _matrix[0][12] * _matrix[0][3] * _matrix[0][10];

        inverse[0][9] =
            -_matrix[0][0] * _matrix[0][9] * _matrix[0][15] +
            _matrix[0][0] * _matrix[0][11] * _matrix[0][13] +
            _matrix[0][8] * _matrix[0][1] * _matrix[0][15] -
            _matrix[0][8] * _matrix[0][3] * _matrix[0][13] -
            _matrix[0][12] * _matrix[0][1] * _matrix[0][11] +
            _matrix[0][12] * _matrix[0][3] * _matrix[0][9];

        inverse[0][13] =
            _matrix[0][0] * _matrix[0][9] * _matrix[0][14] -
            _matrix[0][0] * _matrix[0][10] * _matrix[0][13] -
            _matrix[0][8] * _matrix[0][1] * _matrix[0][14] +
            _matrix[0][8] * _matrix[0][2] * _matrix[0][13] +
            _matrix[0][12] * _matrix[0][1] * _matrix[0][10] -
            _matrix[0][12] * _matrix[0][2] * _matrix[0][9];

        inverse[0][2] =
            _matrix[0][1] * _matrix[0][6] * _matrix[0][15] -
            _matrix[0][1] * _matrix[0][7] * _matrix[0][14] -
            _matrix[0][5] * _matrix[0][2] * _matrix[0][15] +
            _matrix[0][5] * _matrix[0][3] * _matrix[0][14] +
            _matrix[0][13] * _matrix[0][2] * _matrix[0][7] -
            _matrix[0][13] * _matrix[0][3] * _matrix[0][6];

        inverse[0][6] =
            -_matrix[0][0] * _matrix[0][6] * _matrix[0][15] +
            _matrix[0][0] * _matrix[0][7] * _matrix[0][14] +
            _matrix[0][4] * _matrix[0][2] * _matrix[0][15] -
            _matrix[0][4] * _matrix[0][3] * _matrix[0][14] -
            _matrix[0][12] * _matrix[0][2] * _matrix[0][7] +
            _matrix[0][12] * _matrix[0][3] * _matrix[0][6];

        inverse[0][10] =
            _matrix[0][0] * _matrix[0][5] * _matrix[0][15] -
            _matrix[0][0] * _matrix[0][7] * _matrix[0][13] -
            _matrix[0][4] * _matrix[0][1] * _matrix[0][15] +
            _matrix[0][4] * _matrix[0][3] * _matrix[0][13] +
            _matrix[0][12] * _matrix[0][1] * _matrix[0][7] -
            _matrix[0][12] * _matrix[0][3] * _matrix[0][5];

        inverse[0][14] =
            -_matrix[0][0] * _matrix[0][5] * _matrix[0][14] +
            _matrix[0][0] * _matrix[0][6] * _matrix[0][13] +
            _matrix[0][4] * _matrix[0][1] * _matrix[0][14] -
            _matrix[0][4] * _matrix[0][2] * _matrix[0][13] -
            _matrix[0][12] * _matrix[0][1] * _matrix[0][6] +
            _matrix[0][12] * _matrix[0][2] * _matrix[0][5];

        inverse[0][3] =
            -_matrix[0][1] * _matrix[0][6] * _matrix[0][11] +
            _matrix[0][1] * _matrix[0][7] * _matrix[0][10] +
            _matrix[0][5] * _matrix[0][2] * _matrix[0][11] -
            _matrix[0][5] * _matrix[0][3] * _matrix[0][10] -
            _matrix[0][9] * _matrix[0][2] * _matrix[0][7] +
            _matrix[0][9] * _matrix[0][3] * _matrix[0][6];

        inverse[0][7] =
            _matrix[0][0] * _matrix[0][6] * _matrix[0][11] -
            _matrix[0][0] * _matrix[0][7] * _matrix[0][10] -
            _matrix[0][4] * _matrix[0][2] * _matrix[0][11] +
            _matrix[0][4] * _matrix[0][3] * _matrix[0][10] +
            _matrix[0][8] * _matrix[0][2] * _matrix[0][7] -
            _matrix[0][8] * _matrix[0][3] * _matrix[0][6];

        inverse[0][11] =
            -_matrix[0][0] * _matrix[0][5] * _matrix[0][11] +
            _matrix[0][0] * _matrix[0][7] * _matrix[0][9] +
            _matrix[0][4] * _matrix[0][1] * _matrix[0][11] -
            _matrix[0][4] * _matrix[0][3] * _matrix[0][9] -
            _matrix[0][8] * _matrix[0][1] * _matrix[0][7] +
            _matrix[0][8] * _matrix[0][3] * _matrix[0][5];

        inverse[0][15] =
            _matrix[0][0] * _matrix[0][5] * _matrix[0][10] -
            _matrix[0][0] * _matrix[0][6] * _matrix[0][9] -
            _matrix[0][4] * _matrix[0][1] * _matrix[0][10] +
            _matrix[0][4] * _matrix[0][2] * _matrix[0][9] +
            _matrix[0][8] * _matrix[0][1] * _matrix[0][6] -
            _matrix[0][8] * _matrix[0][2] * _matrix[0][5];

        T determinant = _matrix[0][0] * inverse[0][0] + _matrix[0][1] * inverse[0][4] + _matrix[0][2] * inverse[0][8] + _matrix[0][3] * inverse[0][12];
        CBT_ASSERT(!cbtMathUtil::IsApproxEqual(determinant, static_cast<T>(0)));
        determinant = static_cast<T>(1) / determinant;

        for (cbtU32 i = 0; i < 16; ++i)
        {
            inverse[0][i] = inverse[0][i] * determinant;
        }

        return inverse;
    }

    /**
        \brief Checks if a Matrix is invertible.

        \param _matrix The Matrix to check.

        \return Return true if _matrix is invertible. Otherwise, return false.

        \warning IsInvertible(const Matrix<T, MATRIX_SIZE, MATRIX_SIZE>&) can only be used on a square Matrix of floating point types.
    */
    template<typename T, cbtU32 MATRIX_SIZE>
    static CBT_ENABLE_IF_FLOAT(T, cbtBool) IsInvertible(const cbtMatrix<T, MATRIX_SIZE, MATRIX_SIZE>& _matrix)
    {
        return !cbtMathUtil::IsApproxEqual(GetDeterminant(_matrix), static_cast<T>(0));
    }

    /**
        \brief Sets a Matrix to an identity Matrix.

        \param _matrix The Matrix to set to an identity Matrix.

        \return Returns _matrix, set to an identity Matrix.

        \warning SetToIdentity(Matrix<T, MATRIX_SIZE, MATRIX_SIZE>&) can only be used on square matrices.
    */
    template<typename T, cbtU32 MATRIX_SIZE>
    static void SetToIdentity(cbtMatrix<T, MATRIX_SIZE, MATRIX_SIZE>& _matrix)
    {
        _matrix.SetToZero();
        for (cbtU32 i = 0; i < MATRIX_SIZE; ++i)
        {
            _matrix[i][i] = static_cast<T>(1);
        }
    }

    template<typename T, cbtU32 MATRIX_SIZE>
    static cbtMatrix<T, MATRIX_SIZE, MATRIX_SIZE> GetIdentityMatrix()
    {
        cbtMatrix<T, MATRIX_SIZE, MATRIX_SIZE> identityMatrix;
        SetToIdentity(identityMatrix);
        return identityMatrix;
    }

    // Graphics Utility
    /**
        \brief Get a perspective Matrix based on specified values.

        \param _aspectRatio Aspect Ratio
        \param _fov Field of View
        \param _nearPlane Near Plane
        \param _farPlane Far Plane

        \return Returns a perspective Matrix based on the specified parameters.

        \warning _fov is the angle between the view direction and the extreme left or right border of what the camera can see.
                 So a FOV of 35° actually has a total viewing angle 70°.
        \see Perspective Matrix [http://ogldev.atspace.co.uk/www/tutorial12/tutorial12.html]
    */
    static cbtMatrix4F GetPerspectiveMatrix(cbtF32 _aspectRatio, cbtF32 _fov, cbtF32 _nearPlane, cbtF32 _farPlane)
    {
        cbtMatrix4F perspectiveMatrix;

        /*
        AR = Aspect Ratio
        FOV = Field of View
        N = Near Plane
        F = Far Plane

        Perspective Matrix:
        | 1/(tan(FOV) * AR)         0                0              0       |
        |          0            1/tan(FOV)           0              0       |
        |          0                  0        (-N-F)/(N-F)   (2*F*N)/(N-F) |
        |          0                  0              1              0       |
        */

        perspectiveMatrix[0][0] = 1.0f / (std::tan(_fov * cbtMathUtil::DEG2RAD) * _aspectRatio);
        perspectiveMatrix[1][1] = 1.0f / std::tan(_fov * cbtMathUtil::DEG2RAD);
        perspectiveMatrix[2][2] = (-_nearPlane - _farPlane) / (_nearPlane - _farPlane);
        perspectiveMatrix[3][2] = (2.0f * _farPlane * _nearPlane) / (_nearPlane - _farPlane);
        perspectiveMatrix[2][3] = 1.0f;

        return perspectiveMatrix;
    }

    /**
        \brief Get a orthographic Matrix based on specified values.

        \param _aspectRatio Aspect Ratio
        \param _orthoSize How much the camera can see along the vertical axis.
                          So a square of size 3 will take up 75% of the vertical space of a window if _orthoSize is 4.
        \param _nearPlane Near Plane
        \param _farPlane Far Plane

        \return Returns a perspective Matrix based on the specified parameters.
    */
    static cbtMatrix4F GetOrthographicMatrix(cbtF32 _aspectRatio, cbtF32 _orthoSize, cbtF32 _nearPlane, cbtF32 _farPlane)
    {
        // [https://en.wikipedia.org/wiki/Orthographic_projection]
        // Most tutorial take the absolute position of the viewing box in the world as the input.
        // So there is a need to translate the box back to the origin.
        // We do not need to do so as we do our calculation assuming that we are already at the origin.

        cbtF32 top = _orthoSize * 0.5f;
        cbtF32 bottom = -top;
        cbtF32 right = top * _aspectRatio;
        cbtF32 left = bottom * _aspectRatio;

        cbtMatrix4F orthoMatrix;
        SetToIdentity(orthoMatrix);

        orthoMatrix[0][0] = 2.0f / (right - left);
        orthoMatrix[1][1] = 2.0f / (top - bottom);
        orthoMatrix[2][2] = 2.0f / (_farPlane - _nearPlane);

        return orthoMatrix;
    }

    /**
        \brief Get a view Matrix based on specified values.
        
        \param _aspectRatio Aspect Ratio
        \param _forward The direction the camera is facing.
        \param _up The direction pointing upwards of the camera.
        \param _position The position of the camera in world space.

        \return Returns a view Matrix based on specified values.
    */
    static cbtMatrix4F GetViewMatrix(const cbtVector3F& _forward, const cbtVector3F& _up, const cbtVector3F& _position)
    {
        /* Even though OpenGL uses right handed coordinates, when converting to Camera Space, we negate the X-Axis because NDC uses left-handed coordinates
        system. In NDC, the Z-Axis points into the screen, The Y-Axis points upwards and the X-Axis points to the right. */
        cbtVector3F right = Cross(_forward, _up);

        cbtMatrix4F viewMatrix;
        viewMatrix[3][3] = 1.0f;

        // Column 0
        viewMatrix[0][0] = right.GetX();
        viewMatrix[0][1] = _up.GetX();
        viewMatrix[0][2] = _forward.GetX();

        // Column 1
        viewMatrix[1][0] = right.GetY();
        viewMatrix[1][1] = _up.GetY();
        viewMatrix[1][2] = _forward.GetY();

        // Column 2
        viewMatrix[2][0] = right.GetZ();
        viewMatrix[2][1] = _up.GetZ();
        viewMatrix[2][2] = _forward.GetZ();

        // Translation
        // When we move the camera forward, we are actually moving the world backwards.
        // Therefore we need to negate the translation.
        viewMatrix *= GetTranslationMatrix(-_position);

        return viewMatrix;
    }

    /**
        \brief Get a translation Matrix based on a Vector3 translation.

        \param _translation The translation in Vector3 form.

        \return Returns a translation Matrix based on a Vector3 translation.
    */
    static cbtMatrix4F GetTranslationMatrix(const cbtVector3F& _translation)
    {
        cbtMatrix4F translationMatrix;
        SetToIdentity(translationMatrix);

        translationMatrix[3][0] = _translation.GetX();
        translationMatrix[3][1] = _translation.GetY();
        translationMatrix[3][2] = _translation.GetZ();

        return translationMatrix;
    }

    /**
        \brief Get a scale Matrix based on a Vector3 scale.

        \param _scale The scale in Vector3 form.

        \return Returns a scale Matrix based on a Vector3 scale.
    */
    static cbtMatrix4F GetScaleMatrix(const cbtVector3F& _scale)
    {
        cbtMatrix4F scaleMatrix;

        scaleMatrix[0][0] = _scale.GetX();
        scaleMatrix[1][1] = _scale.GetY();
        scaleMatrix[2][2] = _scale.GetZ();
        scaleMatrix[3][3] = 1.0f;

        return scaleMatrix;
    }
};

NS_CBT_END