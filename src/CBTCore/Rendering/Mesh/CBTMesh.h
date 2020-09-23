#pragma once

// Include CBT
#include "CBTMacros.h"
#include "CBTVertex.h"
#include "Core/General/CBTRef.h"
#include "Core/Math/CBTBoundingBox.h"
#include "Core/Math/CBTMatrix.h"
#include "Rendering/Buffer/CBTVertexArray.h"
#include "Rendering/Buffer/CBTVertexBuffer.h"
#include "Rendering/Buffer/CBTBufferLayout.h"
#include "Rendering/Buffer/CBTElementBuffer.h"

NS_CBT_BEGIN

/** Mesh stores the vertex attributes of a 3D Model.

  * A VAO can store up to 16 vertex attributes.

  * Vertex Attributes:
  *
  * Per Vertex Data (Stored in VBO 0)
  *
  * 00 - Position
  * 01 - Normal
  * 02 - Texture Coordinate
  * 03 - Tangent

  * Per Instance Data (Stored in VBO 1)
  *
  * 04 - Instance Model View Matrix Column 0
  * 05 - Instance Model View Matrix Column 1
  * 06 - Instance Model View Matrix Column 2
  * 07 - Instance Model View Matrix Column 3
  * 08 - Instance Normal Matrix Column 0
  * 09 - Instance Normal Matrix Column 1
  * 10 - Instance Normal Matrix Column 2
  * 11 - To Be Defined
  * 12 - To Be Defined
  * 13 - To Be Defined
  * 14 - To Be Defined
  * 15 - To Be Defined */
struct CBTMeshInstance
{
public:
    // Variable(s)
    cbtF32 m_ModelViewMatrix[16];
    cbtF32 m_NormalMatrix[9];

    // Constructor(s) & Destructor
    CBTMeshInstance()
    {
        std::memset(&m_ModelViewMatrix[0], 0, 16 * sizeof(m_ModelViewMatrix[0]));
        std::memset(&m_NormalMatrix[0], 0, 9 * sizeof(m_NormalMatrix[0]));
    }
    CBTMeshInstance(const CBTMeshInstance& _other)
    {
        std::memcpy(m_ModelViewMatrix, _other.m_ModelViewMatrix, 16 * sizeof(m_ModelViewMatrix[0]));
        std::memcpy(m_NormalMatrix, _other.m_NormalMatrix, 9 * sizeof(m_NormalMatrix[0]));
    }
    ~CBTMeshInstance() {}

    // Interface Function(s)
    inline void SetModelViewMatrix(const CBTMatrix4F& _matrix) { _matrix.CopyToArray(m_ModelViewMatrix); }
    inline void SetNormalMatrix(const CBTMatrix3F& _matrix) { _matrix.CopyToArray(m_NormalMatrix); }
};

class CBTMeshBuilder;

class CBTMesh : public CBTManaged
{
public:
    /// An enum to represent the VBOs.
    enum VertexBuffers
    {
        VERTEX_DATA = 0,
        INSTANCE_DATA,

        NUM_VBO_CATEGORY,
    };

protected:
    /// The name of the Mesh.
    const cbtStr m_Name;
    /// Vertices
    CBTVertex* m_Vertices;
    /// Vertex Count
    cbtU32 m_VertexCount;
    /// Indices
    cbtU32* m_Indices;
    /// Index Count
    cbtU32 m_IndexCount;
    /// Bounding Box
    CBTBoundingBox m_BoundingBox;
    /// Vertex Array Object
    CBTVertexArray* m_VAO;

    virtual ~CBTMesh();

public:
    CBTMesh(const cbtStr&_name, const CBTVertex _vertices[], cbtU32 _vertexCount, const cbtU32 _indices[], cbtU32 _indexCount);

    inline const cbtStr& GetName() const { return m_Name; }
    inline const CBTBoundingBox& GetBoundingBox() const { return m_BoundingBox; }
    inline cbtU32 GetVertexCount() const { return m_VertexCount; }
    inline cbtU32 GetIndexCount() const { return m_IndexCount; }

    void SetInstanceData(cbtU32 _instanceCount, CBTMeshInstance* _instanceData);
    void Bind() { m_VAO->Bind(); }
};

NS_CBT_END