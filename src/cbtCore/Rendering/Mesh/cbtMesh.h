#pragma once

// Include CBT
#include "cbtMacros.h"
#include "cbtVertex.h"
#include "Core/General/cbtRef.h"
#include "Core/Math/cbtBoundingBox.h"
#include "Core/Math/cbtMatrix.h"
#include "Rendering/Buffer/cbtVertexArray.h"
#include "Rendering/Buffer/cbtVertexBuffer.h"
#include "Rendering/Buffer/cbtBufferLayout.h"
#include "Rendering/Buffer/cbtElementBuffer.h"

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
    struct cbtMeshInstance
    {
    public:
        // Variable(s)
        cbtF32 m_ModelViewMatrix[16];
        cbtF32 m_NormalMatrix[9];

        // Constructor(s) & Destructor
        cbtMeshInstance()
        {
            std::memset(&m_ModelViewMatrix[0], 0, 16 * sizeof(m_ModelViewMatrix[0]));
            std::memset(&m_NormalMatrix[0], 0, 9 * sizeof(m_NormalMatrix[0]));
        }

        cbtMeshInstance(const cbtMeshInstance& _other)
        {
            std::memcpy(m_ModelViewMatrix, _other.m_ModelViewMatrix, 16 * sizeof(m_ModelViewMatrix[0]));
            std::memcpy(m_NormalMatrix, _other.m_NormalMatrix, 9 * sizeof(m_NormalMatrix[0]));
        }

        ~cbtMeshInstance()
        {
        }

        // Interface Function(s)
        inline void SetModelViewMatrix(const cbtMatrix4F& _matrix)
        {
            _matrix.CopyToArray(m_ModelViewMatrix);
        }

        inline void SetNormalMatrix(const cbtMatrix3F& _matrix)
        {
            _matrix.CopyToArray(m_NormalMatrix);
        }
    };

    class cbtMeshBuilder;

    class cbtMesh : public cbtManaged
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
        cbtVertex* m_Vertices;
        /// Vertex Count
        cbtU32 m_VertexCount;
        /// Indices
        cbtU32* m_Indices;
        /// Index Count
        cbtU32 m_IndexCount;
        /// Bounding Box
        cbtBoundingBox m_BoundingBox;
        /// Vertex Array Object
        cbtVertexArray* m_VAO;

        virtual ~cbtMesh();

    public:
        cbtMesh(const cbtStr& _name, const cbtVertex _vertices[], cbtU32 _vertexCount, const cbtU32 _indices[],
                cbtU32 _indexCount);

        inline const cbtStr& GetName() const
        {
            return m_Name;
        }

        inline const cbtBoundingBox& GetBoundingBox() const
        {
            return m_BoundingBox;
        }

        inline cbtU32 GetVertexCount() const
        {
            return m_VertexCount;
        }

        inline cbtU32 GetIndexCount() const
        {
            return m_IndexCount;
        }

        void SetInstanceData(cbtU32 _instanceCount, cbtMeshInstance* _instanceData);

        void Bind()
        {
            m_VAO->Bind();
        }
    };

NS_CBT_END