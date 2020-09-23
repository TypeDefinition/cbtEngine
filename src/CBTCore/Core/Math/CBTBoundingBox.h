#pragma once

// Include CBT
#include "cbtVector3.h"

NS_CBT_BEGIN

/**
    \brief Stores the 8 points of a bounding box.
*/
class cbtBoundingBox
{
public:
    /// The number of points in a bounding box. Value is 8.
    static constexpr cbtU32 NUM_POINTS = 8;

private:
    /// The 8 points of the bounding box.
    CBTVector3F m_Vertices[NUM_POINTS];
    /// The minimum bounds of the bounding box.
    CBTVector3F m_Min;
    /// The maximum bounds of the bounding box.
    CBTVector3F m_Max;

public:
    /**
        \brief Constructor taking in the minimum and maximum bounds of the bounding box.

        \param _minX The minimum X bound of the bounding box.
        \param _minY The minimum Y bound of the bounding box.
        \param _minZ The minimum Z bound of the bounding box.
        \param _maxX The maximum X bound of the bounding box.
        \param _maxY The maximum Y bound of the bounding box.
        \param _maxZ The maximum Z bound of the bounding box.

        \return A cbtBoundingBox
    */
    cbtBoundingBox(cbtF32 _minX = 0.0f, cbtF32 _minY = 0.0f, cbtF32 _minZ = 0.0f, cbtF32 _maxX = 0.0f, cbtF32 _maxY = 0.0f, cbtF32 _maxZ = 0.0f)
    {
        Set(_minX, _minY, _minZ, _maxX, _maxY, _maxZ);
    }

    /**
        \brief Constructor taking in the minimum and maximum bounds of the bounding box.

        \param _min The minimum bounds of the bounding box.
        \param _max The maximum bounds of the bounding box.

        \return A cbtBoundingBox
    */
    cbtBoundingBox(const CBTVector3F& _min, const CBTVector3F& _max) { Set(_min, _max); }

    /**
        \brief Copy Constructor

        \param _other The cbtBoundingBox to copy.

        \return A cbtBoundingBox with the same bounds as _other.
    */
    cbtBoundingBox(const cbtBoundingBox& _other) { *this = _other; }

    /**
        \brief Destructor
    */
    ~cbtBoundingBox() {}

    /**
        \brief Setter function taking in the minimum and maximum bounds of the bounding box.

        \param _min The minimum bounds of the bounding box.
        \param _max The maximum bounds of the bounding box.
    */
    void Set(const CBTVector3F& _min, const CBTVector3F& _max) { Set(_min.m_X, _min.m_Y, _min.m_Z, _max.m_X, _max.m_Y, _max.m_Z); }

    /**
        \brief Setter function taking in the minimum and maximum bounds of the bounding box.

        \param _minX The minimum X bound of the bounding box.
        \param _minY The minimum Y bound of the bounding box.
        \param _minZ The minimum Z bound of the bounding box.
        \param _maxX The maximum X bound of the bounding box.
        \param _maxY The maximum Y bound of the bounding box.
        \param _maxZ The maximum Z bound of the bounding box.
    */
    void Set(cbtF32 _minX, cbtF32 _minY, cbtF32 _minZ, cbtF32 _maxX, cbtF32 _maxY, cbtF32 _maxZ)
    {
        m_Min.Set(_minX, _minY, _minZ);
        m_Max.Set(_maxX, _maxY, _maxZ);

        m_Vertices[0].Set(_minX, _minY, _minZ);
        m_Vertices[1].Set(_minX, _maxY, _minZ);
        m_Vertices[2].Set(_maxX, _maxY, _minZ);
        m_Vertices[3].Set(_maxX, _minY, _minZ);

        m_Vertices[4].Set(_minX, _minY, _maxZ);
        m_Vertices[5].Set(_minX, _maxY, _maxZ);
        m_Vertices[6].Set(_maxX, _maxY, _maxZ);
        m_Vertices[7].Set(_maxX, _minY, _maxZ);
    }

    /**
        \brief Get the nth vertex of the bounding box as specified by _index.

        \param _index The index of the vertex.

        \return The nth vertex of the bounding box as specified by _index.
    */
    inline const CBTVector3F& GetVertex(cbtU32 _index) const { return m_Vertices[_index]; }
    /**
        \brief Get a pointer to the array of vertices of the bounding box.

        \return A pointer to the array of vertices of the bounding box.
    */
    inline const CBTVector3F* GetVertices() { return &m_Vertices[0]; }

    /**
        \brief Get the minimum bounds of the bounding box.

        \return The minimum bounds of the bounding box.
    */
    inline CBTVector3F GetMin() const { return m_Min; }
    /**
        \brief Get the minimum X bound of the bounding box.

        \return The minimum X bound of the bounding box.
    */
    inline cbtF32 GetMinX() const { return m_Min.m_X; }
    /**
        \brief Get the minimum Y bound of the bounding box.

        \return The minimum Y bound of the bounding box.
    */
    inline cbtF32 GetMinY() const { return m_Min.m_Y; }
    /**
        \brief Get the minimum Z bound of the bounding box.

        \return The minimum Z bound of the bounding box.
    */
    inline cbtF32 GetMinZ() const { return m_Min.m_Z; }

    /**
        \brief Get the maximum bounds of the bounding box.

        \return The maximum bounds of the bounding box.
    */
    inline CBTVector3F GetMax() const { return m_Max; }
    /**
        \brief Get the maximum X bound of the bounding box.

        \return The maximum X bound of the bounding box.
    */
    inline cbtF32 GetMaxX() const { return m_Max.m_X; }
    /**
        \brief Get the maximum Y bound of the bounding box.

        \return The maximum Y bound of the bounding box.
    */
    inline cbtF32 GetMaxY() const { return m_Max.m_Y; }
    /**
        \brief Get the maximum Z bound of the bounding box.

        \return The maximum Z bound of the bounding box.
    */
    inline cbtF32 GetMaxZ() const { return m_Max.m_Z; }

    /**
        \brief Get the size of the bounding box.

        \return The size of the bounding box.
    */
    inline CBTVector3F GetSize() const { return m_Max - m_Min; }
    /**
        \brief Get the X size of the bounding box.

        \return The X size of the bounding box.
    */
    inline cbtF32 GetSizeX() const { return m_Max.m_X - m_Min.m_X; }
    /**
        \brief Get the Y size of the bounding box.

        \return The Y size of the bounding box.
    */
    inline cbtF32 GetSizeY() const { return m_Max.m_Y - m_Min.m_Y; }
    /**
        \brief Get the Z size of the bounding box.

        \return The Z size of the bounding box.
    */
    inline cbtF32 GetSizeZ() const { return m_Max.m_Z - m_Min.m_Z; }

    /**
        \brief Get the nth vertex of the bounding box as specified by _index.

        \param _index The index of the vertex.

        \return The nth vertex of the bounding box as specified by _index.
    */
    const CBTVector3F& operator[](cbtU32 _index) const { return m_Vertices[_index]; }

    /**
        \brief Check if this bounding box is the same as another bounding box.

        \param _rhs The bounding box to check against.

        \return Returns true if this bounding box is the same as the other bounding box. Otherwise, return false.
    */
    cbtBool operator==(const cbtBoundingBox& _rhs) const { return (m_Max == _rhs.m_Max) && (m_Min == _rhs.m_Min); }

    /**
        \brief Check if this bounding box is not the same as another bounding box.

        \param _rhs The bounding box to check against.

        \return Returns false if this bounding box is the same as the other bounding box. Otherwise, return true.
    */
    cbtBool operator!=(const cbtBoundingBox& _rhs) const { return !(*this == _rhs); }

    /**
        \brief Set this bounding box to be equal to another bounding box.

        \param _rhs The bounding box to copy.

        \return This bounding box after copying _rhs.
    */
    cbtBoundingBox& operator=(const cbtBoundingBox& _rhs)
    {
        m_Min = _rhs.m_Min; m_Max = _rhs.m_Max;
        for (cbtU32 i = 0; i < 8; ++i) { this->m_Vertices[i] = _rhs.m_Vertices[i]; }
        return *this;
    }
};

NS_CBT_END