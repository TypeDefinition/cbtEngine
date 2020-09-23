// Include CBT
#include "cbtMeshBuilder.h"
#include "Core/FileUtil/cbtFileUtil.h"
#include "Core/Math/cbtMatrixUtil.h"

// Include STD
#include <sstream>

NS_CBT_BEGIN

// Mesh Loading & Creation
cbtMesh* cbtMeshBuilder::CreateScreenQuad(const cbtStr& _name)
{
    std::vector<cbtVertex> vertices;

    for (cbtU32 i = 0; i < 4; ++i) { vertices.push_back(cbtVertex()); }

    vertices[0].m_Position.Set(-1.0f, -1.0f, 0.0f);
    vertices[1].m_Position.Set(1.0f, 1.0f, 0.0f);
    vertices[2].m_Position.Set(-1.0f, 1.0f, 0.0f);
    vertices[3].m_Position.Set(1.0f, -1.0f, 0.0f);

    vertices[0].m_Normal.Set(0.0f, 0.0f, 1.0f);
    vertices[1].m_Normal.Set(0.0f, 0.0f, 1.0f);
    vertices[2].m_Normal.Set(0.0f, 0.0f, 1.0f);
    vertices[3].m_Normal.Set(0.0f, 0.0f, 1.0f);

    vertices[0].m_TexCoord.Set(0.0f, 0.0f);
    vertices[1].m_TexCoord.Set(1.0f, 1.0f);
    vertices[2].m_TexCoord.Set(0.0f, 1.0f);
    vertices[3].m_TexCoord.Set(1.0f, 0.0f);

    vertices[0].m_Tangent.Set(1.0f, 0.0f, 0.0f);
    vertices[1].m_Tangent.Set(1.0f, 0.0f, 0.0f);
    vertices[2].m_Tangent.Set(1.0f, 0.0f, 0.0f);
    vertices[3].m_Tangent.Set(1.0f, 0.0f, 0.0f);

    std::vector<cbtU32> indices;

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    indices.push_back(0);
    indices.push_back(3);
    indices.push_back(1);

    return cbtNew cbtMesh(_name, &vertices[0], (cbtU32)vertices.size(), &indices[0], (cbtU32)indices.size());
}

cbtMesh* cbtMeshBuilder::CreateSkybox(const cbtStr& _name)
{
    std::vector<cbtVertex> vertices;

    for (cbtU32 i = 0; i < 24; ++i) { vertices.push_back(cbtVertex()); }
    std::vector<cbtU32> indices;

    // Front
    vertices[0].m_Position.Set(1.0f, -1.0f, 1.0f);
    vertices[1].m_Position.Set(-1.0f, 1.0f, 1.0f);
    vertices[2].m_Position.Set(1.0f, 1.0f, 1.0f);
    vertices[3].m_Position.Set(-1.0f, -1.0f, 1.0f);

    vertices[0].m_Normal.Set(0.0f, 0.0f, -1.0f);
    vertices[1].m_Normal.Set(0.0f, 0.0f, -1.0f);
    vertices[2].m_Normal.Set(0.0f, 0.0f, -1.0f);
    vertices[3].m_Normal.Set(0.0f, 0.0f, -1.0f);

    vertices[0].m_TexCoord.Set(0.0f, 0.0f);
    vertices[1].m_TexCoord.Set(1.0f, 1.0f);
    vertices[2].m_TexCoord.Set(0.0f, 1.0f);
    vertices[3].m_TexCoord.Set(1.0f, 0.0f);

    vertices[0].m_Tangent.Set(-1.0f, 0.0f, 0.0f);
    vertices[1].m_Tangent.Set(-1.0f, 0.0f, 0.0f);
    vertices[2].m_Tangent.Set(-1.0f, 0.0f, 0.0f);
    vertices[3].m_Tangent.Set(-1.0f, 0.0f, 0.0f);

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    indices.push_back(0);
    indices.push_back(3);
    indices.push_back(1);

    // Top
    vertices[4].m_Position.Set(1.0f, 1.0f, 1.0f);
    vertices[5].m_Position.Set(-1.0f, 1.0f, -1.0f);
    vertices[6].m_Position.Set(1.0f, 1.0f, -1.0f);
    vertices[7].m_Position.Set(-1.0f, 1.0f, 1.0f);

    vertices[4].m_Normal.Set(0.0f, -1.0f, 0.0f);
    vertices[5].m_Normal.Set(0.0f, -1.0f, 0.0f);
    vertices[6].m_Normal.Set(0.0f, -1.0f, 0.0f);
    vertices[7].m_Normal.Set(0.0f, -1.0f, 0.0f);

    vertices[4].m_TexCoord.Set(0.0f, 0.0f);
    vertices[5].m_TexCoord.Set(1.0f, 1.0f);
    vertices[6].m_TexCoord.Set(0.0f, 1.0f);
    vertices[7].m_TexCoord.Set(1.0f, 0.0f);

    vertices[4].m_Tangent.Set(-1.0f, 0.0f, 0.0f);
    vertices[5].m_Tangent.Set(-1.0f, 0.0f, 0.0f);
    vertices[6].m_Tangent.Set(-1.0f, 0.0f, 0.0f);
    vertices[7].m_Tangent.Set(-1.0f, 0.0f, 0.0f);

    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(6);

    indices.push_back(4);
    indices.push_back(7);
    indices.push_back(5);

    // Down
    vertices[8].m_Position.Set(1.0f, -1.0f, -1.0f);
    vertices[9].m_Position.Set(-1.0f, -1.0f, 1.0f);
    vertices[10].m_Position.Set(1.0f, -1.0f, 1.0f);
    vertices[11].m_Position.Set(-1.0f, -1.0f, -1.0f);

    vertices[8].m_Normal.Set(0.0f, 1.0f, 0.0f);
    vertices[9].m_Normal.Set(0.0f, 1.0f, 0.0f);
    vertices[10].m_Normal.Set(0.0f, 1.0f, 0.0f);
    vertices[11].m_Normal.Set(0.0f, 1.0f, 0.0f);

    vertices[8].m_TexCoord.Set(0.0f, 0.0f);
    vertices[9].m_TexCoord.Set(1.0f, 1.0f);
    vertices[10].m_TexCoord.Set(0.0f, 1.0f);
    vertices[11].m_TexCoord.Set(1.0f, 0.0f);

    vertices[8].m_Tangent.Set(-1.0f, 0.0f, 0.0f);
    vertices[9].m_Tangent.Set(-1.0f, 0.0f, 0.0f);
    vertices[10].m_Tangent.Set(-1.0f, 0.0f, 0.0f);
    vertices[11].m_Tangent.Set(-1.0f, 0.0f, 0.0f);

    indices.push_back(8);
    indices.push_back(9);
    indices.push_back(10);

    indices.push_back(8);
    indices.push_back(11);
    indices.push_back(9);

    // Left
    vertices[12].m_Position.Set(1.0f, -1.0f, -1.0f);
    vertices[13].m_Position.Set(1.0f, 1.0f, 1.0f);
    vertices[14].m_Position.Set(1.0f, 1.0f, -1.0f);
    vertices[15].m_Position.Set(1.0f, -1.0f, 1.0f);

    vertices[12].m_Normal.Set(-1.0f, 0.0f, 0.0f);
    vertices[13].m_Normal.Set(-1.0f, 0.0f, 0.0f);
    vertices[14].m_Normal.Set(-1.0f, 0.0f, 0.0f);
    vertices[15].m_Normal.Set(-1.0f, 0.0f, 0.0f);

    vertices[12].m_TexCoord.Set(0.0f, 0.0f);
    vertices[13].m_TexCoord.Set(1.0f, 1.0f);
    vertices[14].m_TexCoord.Set(0.0f, 1.0f);
    vertices[15].m_TexCoord.Set(1.0f, 0.0f);

    vertices[12].m_Tangent.Set(0.0f, 0.0f, 1.0f);
    vertices[13].m_Tangent.Set(0.0f, 0.0f, 1.0f);
    vertices[14].m_Tangent.Set(0.0f, 0.0f, 1.0f);
    vertices[15].m_Tangent.Set(0.0f, 0.0f, 1.0f);

    indices.push_back(12);
    indices.push_back(13);
    indices.push_back(14);

    indices.push_back(12);
    indices.push_back(15);
    indices.push_back(13);

    // Right
    vertices[16].m_Position.Set(-1.0f, -1.0f, 1.0f);
    vertices[17].m_Position.Set(-1.0f, 1.0f, -1.0f);
    vertices[18].m_Position.Set(-1.0f, 1.0f, 1.0f);
    vertices[19].m_Position.Set(-1.0f, -1.0f, -1.0f);

    vertices[16].m_Normal.Set(1.0f, 0.0f, 0.0f);
    vertices[17].m_Normal.Set(1.0f, 0.0f, 0.0f);
    vertices[18].m_Normal.Set(1.0f, 0.0f, 0.0f);
    vertices[19].m_Normal.Set(1.0f, 0.0f, 0.0f);

    vertices[16].m_TexCoord.Set(0.0f, 0.0f);
    vertices[17].m_TexCoord.Set(1.0f, 1.0f);
    vertices[18].m_TexCoord.Set(0.0f, 1.0f);
    vertices[19].m_TexCoord.Set(1.0f, 0.0f);

    vertices[16].m_Tangent.Set(0.0f, 0.0f, -1.0f);
    vertices[17].m_Tangent.Set(0.0f, 0.0f, -1.0f);
    vertices[18].m_Tangent.Set(0.0f, 0.0f, -1.0f);
    vertices[19].m_Tangent.Set(0.0f, 0.0f, -1.0f);

    indices.push_back(16);
    indices.push_back(17);
    indices.push_back(18);

    indices.push_back(16);
    indices.push_back(19);
    indices.push_back(17);

    // Back
    vertices[20].m_Position.Set(-1.0f, -1.0f, -1.0f);
    vertices[21].m_Position.Set(1.0f, 1.0f, -1.0f);
    vertices[22].m_Position.Set(-1.0f, 1.0f, -1.0f);
    vertices[23].m_Position.Set(1.0f, -1.0f, -1.0f);

    vertices[20].m_Normal.Set(0.0f, 0.0f, 1.0f);
    vertices[21].m_Normal.Set(0.0f, 0.0f, 1.0f);
    vertices[22].m_Normal.Set(0.0f, 0.0f, 1.0f);
    vertices[23].m_Normal.Set(0.0f, 0.0f, 1.0f);

    vertices[20].m_TexCoord.Set(0.0f, 0.0f);
    vertices[21].m_TexCoord.Set(1.0f, 1.0f);
    vertices[22].m_TexCoord.Set(0.0f, 1.0f);
    vertices[23].m_TexCoord.Set(1.0f, 0.0f);

    vertices[20].m_Tangent.Set(1.0f, 0.0f, 0.0f);
    vertices[21].m_Tangent.Set(1.0f, 0.0f, 0.0f);
    vertices[22].m_Tangent.Set(1.0f, 0.0f, 0.0f);
    vertices[23].m_Tangent.Set(1.0f, 0.0f, 0.0f);

    indices.push_back(20);
    indices.push_back(21);
    indices.push_back(22);

    indices.push_back(20);
    indices.push_back(23);
    indices.push_back(21);

    return cbtNew cbtMesh(_name, &vertices[0], (cbtU32)vertices.size(), &indices[0], (cbtU32)indices.size());
}

cbtMesh* cbtMeshBuilder::CreateQuad(const cbtStr& _name)
{
    cbtVertex vertices[4];

    vertices[0].m_Position.Set(-0.5f, -0.5f, 0.0f);
    vertices[1].m_Position.Set(0.5f, 0.5f, 0.0f);
    vertices[2].m_Position.Set(-0.5f, 0.5f, 0.0f);
    vertices[3].m_Position.Set(0.5f, -0.5f, 0.0f);

    vertices[0].m_Normal.Set(0.0f, 0.0f, 1.0f);
    vertices[1].m_Normal.Set(0.0f, 0.0f, 1.0f);
    vertices[2].m_Normal.Set(0.0f, 0.0f, 1.0f);
    vertices[3].m_Normal.Set(0.0f, 0.0f, 1.0f);

    vertices[0].m_TexCoord.Set(0.0f, 0.0f);
    vertices[1].m_TexCoord.Set(1.0f, 1.0f);
    vertices[2].m_TexCoord.Set(0.0f, 1.0f);
    vertices[3].m_TexCoord.Set(1.0f, 0.0f);

    vertices[0].m_Tangent.Set(1.0f, 0.0f, 0.0f);
    vertices[1].m_Tangent.Set(1.0f, 0.0f, 0.0f);
    vertices[2].m_Tangent.Set(1.0f, 0.0f, 0.0f);
    vertices[3].m_Tangent.Set(1.0f, 0.0f, 0.0f);

    cbtU32 indices[6];

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;

    indices[3] = 0;
    indices[4] = 3;
    indices[5] = 1;

    return cbtNew cbtMesh(_name, &vertices[0], 4, &indices[0], 6);
}

cbtMesh* cbtMeshBuilder::LoadAsset(const cbtStr& _name, const cbtStr& _filePath)
{
    // Vertex Data and Index Data
    std::vector<cbtVertex> vertices;
    std::vector<cbtU32> indices;

    // Vertex Attribute(s)
    std::vector<CBTVector3F> positions;
    std::vector<CBTVector3F> normals;
    std::vector<CBTVector2F> texCoords;

    // Read the file.
    cbtStr fileString = cbtFileUtil::FileToString(_filePath);
    std::stringstream ss(fileString.c_str());
    while (ss.good())
    {
        cbtStr line;
        std::getline(ss, line, '\n');

        // Position
        if (std::strncmp("v ", line.c_str(), 2) == 0)
        {
            CBTVector3F position;
            sscanf_s(line.c_str() + 2, "%f%f%f", &position.m_X, &position.m_Y, &position.m_Z);
            positions.push_back(position);
        }

        // TexCoord
        if (std::strncmp("vt ", line.c_str(), 3) == 0)
        {
            CBTVector2F texCoord;
            sscanf_s(line.c_str() + 3, "%f%f", &texCoord.m_X, &texCoord.m_Y);
            texCoords.push_back(texCoord);
        }

        // Normal
        if (std::strncmp("vn ", line.c_str(), 3) == 0)
        {
            CBTVector3F normal;
            sscanf_s(line.c_str() + 3, "%f%f%f", &normal.m_X, &normal.m_Y, &normal.m_Z);
            normals.push_back(normal);
        }

        // Faces
        if (std::strncmp("f ", line.c_str(), 2) == 0)
        {
            cbtU32 positionIndices[3];
            cbtU32 texCoordIndices[3];
            cbtU32 normalIndices[3];

            cbtS32 matches = sscanf_s(
                line.c_str() + 2,
                "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                &positionIndices[0], &texCoordIndices[0], &normalIndices[0],
                &positionIndices[1], &texCoordIndices[1], &normalIndices[1],
                &positionIndices[2], &texCoordIndices[2], &normalIndices[2]
            );

            if (matches != 9)
            {
                cbtStr assertMessage = "Cannot load mesh [" + _filePath + "]. Make sure that the mesh is triangulated!";
                CBT_LOG_ERROR(CBT_LOG_CATEGORY_RENDER, assertMessage.c_str());
                CBT_ASSERT(false);
                return nullptr;
            }

            // Add the Vertex.
            for (cbtU32 i = 0; i < 3; ++i)
            {
                cbtVertex vertex;

                vertex.m_Position = positions[positionIndices[i] - 1]; // -1 because .OBJ starts their index at 1.
                vertex.m_Normal = normals[normalIndices[i] - 1];
                vertex.m_TexCoord = texCoords[texCoordIndices[i] - 1];

                vertices.push_back(vertex);
            }
        }
    }

    // Index the vertices. (This defeats the point of indexing, since vertex data is still repeated, but creating a proper solution is too troublesome for now.)
    for (cbtU32 i = 0; i < vertices.size(); ++i)
    {
        indices.push_back(i);
    }

    // Set Tangents
    for (cbtU32 i = 0; i < indices.size(); i += 3)
    {
        // This gives us 2 of the 3 edges.
        cbtMatrix<cbtF32, 3, 2> edges;
        edges[0][0] = vertices[indices[i + 1]].m_Position.GetX() - vertices[indices[i]].m_Position.GetX();
        edges[1][0] = vertices[indices[i + 1]].m_Position.GetY() - vertices[indices[i]].m_Position.GetY();
        edges[2][0] = vertices[indices[i + 1]].m_Position.GetZ() - vertices[indices[i]].m_Position.GetZ();
        edges[0][1] = vertices[indices[i + 2]].m_Position.GetX() - vertices[indices[i]].m_Position.GetX();
        edges[1][1] = vertices[indices[i + 2]].m_Position.GetY() - vertices[indices[i]].m_Position.GetY();
        edges[2][1] = vertices[indices[i + 2]].m_Position.GetZ() - vertices[indices[i]].m_Position.GetZ();

        // We have the length of 2 edges, and we know that each the edges can be represented by
        // some length of the tangent + some length of the bitangent.
        // One way we can find that length is by using the UV coordinates.
        // So for example, we know that for one of the edges,
        // the ratio of the edge along the tangent axis (also the same as the U axis for the texture coordinates) is U1 - U0 and.
        // the ratio of the edge along the bitangent axis (also the same as the U axis for the texture coordinates) is V1 - V0.
        cbtMatrix<cbtF32, 2, 2> tangentToBitangentRatio;
        tangentToBitangentRatio[0][0] = vertices[indices[i + 1]].m_TexCoord.GetX() - vertices[indices[i]].m_TexCoord.GetX();
        tangentToBitangentRatio[1][0] = vertices[indices[i + 1]].m_TexCoord.GetY() - vertices[indices[i]].m_TexCoord.GetY();
        tangentToBitangentRatio[0][1] = vertices[indices[i + 2]].m_TexCoord.GetX() - vertices[indices[i]].m_TexCoord.GetX();
        tangentToBitangentRatio[1][1] = vertices[indices[i + 2]].m_TexCoord.GetY() - vertices[indices[i]].m_TexCoord.GetY();

        cbtMatrix<cbtF32, 3, 2> tangents = cbtMatrixUtil::GetInverseMatrix(tangentToBitangentRatio) * edges;

        vertices[indices[i + 0]].m_Tangent += CBTVector3F(tangents[0][0], tangents[1][0], tangents[2][0]);
        vertices[indices[i + 1]].m_Tangent += CBTVector3F(tangents[0][0], tangents[1][0], tangents[2][0]);
        vertices[indices[i + 2]].m_Tangent += CBTVector3F(tangents[0][0], tangents[1][0], tangents[2][0]);
    }

    for (cbtU32 i = 0; i < vertices.size(); ++i) { Normalize(vertices[i].m_Tangent); }

    // Create the mesh.
    return cbtNew cbtMesh(_name, &vertices[0], (cbtU32)vertices.size(), &indices[0], (cbtU32)indices.size());
}

NS_CBT_END