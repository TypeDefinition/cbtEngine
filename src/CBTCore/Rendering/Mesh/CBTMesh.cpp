// Include CBT
#include "CBTMesh.h"
#include "Core/FileUtil/CBTFileUtil.h"
#include "Core/Math/CBTMatrixUtil.h"

NS_CBT_BEGIN

CBTMesh::CBTMesh(const cbtStr&_name, const CBTVertex _vertices[], cbtU32 _vertexCount, const cbtU32 _indices[], cbtU32 _indexCount)
    : m_Name(_name)
    , m_VertexCount(_vertexCount)
    , m_IndexCount(_indexCount)
{
    // Copy Vertex Data
    m_Vertices = cbtNew CBTVertex[m_VertexCount];
    std::memcpy(m_Vertices, _vertices, sizeof(m_Vertices[0]) * m_VertexCount);

    // Copy Index Data
    m_Indices = cbtNew cbtU32[m_IndexCount];
    std::memcpy(m_Indices, _indices, sizeof(m_Indices[0]) * m_IndexCount);

    // Bounding Box
    CBTVector3F min, max;
    for (cbtU32 i = 0; i < m_VertexCount; ++i)
    {
        min.m_X = CBTMathUtil::Min(min.m_X, _vertices[i].m_Position.m_X);
        min.m_Y = CBTMathUtil::Min(min.m_Y, _vertices[i].m_Position.m_Y);
        min.m_Z = CBTMathUtil::Min(min.m_Z, _vertices[i].m_Position.m_Z);

        max.m_X = CBTMathUtil::Max(max.m_X, _vertices[i].m_Position.m_X);
        max.m_Y = CBTMathUtil::Max(max.m_Y, _vertices[i].m_Position.m_Y);
        max.m_Z = CBTMathUtil::Max(max.m_Z, _vertices[i].m_Position.m_Z);
    }
    m_BoundingBox.Set(min, max);

    m_VAO = CBTVertexArray::CreateVAO();
    m_VAO->Retain();
    // Vertex Data
    {
        // Attach VBO to VAO.
        // glVertexAttribPointer attaches the VBO to the VAO. It also specifies how the VAO should read the various Vertex Attributes from the VBO.
        // Both the VAO and VBO needs to be binded before this function is called.
        // The reason that the offset (last parameter) needs to be a void pointer is due to legacy support. In the past, it used to mean a different thing.
        // For Learning - [https://stackoverflow.com/questions/37972229/glvertexattribpointer-and-glvertexattribformat-whats-the-difference]

        CBTBufferElement position(CBT_F32, 3, false);
        CBTBufferElement normal(CBT_F32, 3, false);
        CBTBufferElement texCoord(CBT_F32, 2, false);
        CBTBufferElement tangent(CBT_F32, 3, false);

        // Create VBO. Ensure that the VBO layout is the same as CBTVertex.
        CBTVertexBuffer* vbo = CBTVertexBuffer::CreateVBO(
            {position, normal, texCoord, tangent},
            CBT_STATIC_DRAW,
            0,
            m_VertexCount * (cbtU32)sizeof(m_Vertices[0]),
            &m_Vertices[0]);

        // Add VBO to VAO
        m_VAO->AddVBO(vbo);
    }

    // Instance Data
    {
        // In OpenGL, a Vertex Attribute can only have a maximum of 4 Floats. So we need to break a matrix down into columns.
        CBTBufferElement instanceModelViewMatrixColumn0(CBT_F32, 4, false);
        CBTBufferElement instanceModelViewMatrixColumn1(CBT_F32, 4, false);
        CBTBufferElement instanceModelViewMatrixColumn2(CBT_F32, 4, false);
        CBTBufferElement instanceModelViewMatrixColumn3(CBT_F32, 4, false);

        CBTBufferElement instanceNormalMatrixColumn0(CBT_F32, 3, false);
        CBTBufferElement instanceNormalMatrixColumn1(CBT_F32, 3, false);
        CBTBufferElement instanceNormalMatrixColumn2(CBT_F32, 3, false);

        CBTVertexBuffer* vbo = CBTVertexBuffer::CreateVBO(
            {
                instanceModelViewMatrixColumn0,
                instanceModelViewMatrixColumn1,
                instanceModelViewMatrixColumn2,
                instanceModelViewMatrixColumn3,

                instanceNormalMatrixColumn0,
                instanceNormalMatrixColumn1,
                instanceNormalMatrixColumn2,
            },
            CBT_STREAM_DRAW, 1, 0, nullptr);

        m_VAO->AddVBO(vbo);
    }

    // EBO
    {
        CBTElementBuffer* ebo = CBTElementBuffer::CreateEBO(m_Indices, (cbtU32)sizeof(m_Indices[0]) * m_IndexCount);
        m_VAO->SetEBO(ebo);
    }
}

CBTMesh::~CBTMesh()
{
    delete[] m_Vertices;
    delete[] m_Indices;
    m_VAO->AutoRelease();
}

void CBTMesh::SetInstanceData(cbtU32 _instanceCount, CBTMeshInstance* _instanceData)
{
    m_VAO->GetVBOs()[VertexBuffers::INSTANCE_DATA]->SetData(_instanceCount * (cbtU32)sizeof(CBTMeshInstance), _instanceData);
}

NS_CBT_END