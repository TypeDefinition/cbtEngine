#pragma once

// Include CBT
#include "CBTMacros.h"
#include "Core/General/CBTRef.h"

// Include STD
#include <vector>

NS_CBT_BEGIN

class CBTVertexBuffer;
class CBTElementBuffer;

// Vertex Array Object
class CBTVertexArray : public CBTManaged
{
protected:
    std::vector<CBTVertexBuffer*> m_VBOs;
    CBTElementBuffer* m_EBO;

    virtual ~CBTVertexArray() {}

public:
    CBTVertexArray()
        : m_EBO(nullptr)
    {}

    virtual void Bind() = 0;
    virtual void AddVBO(CBTVertexBuffer* _vbo) = 0;
    virtual void SetEBO(CBTElementBuffer* _ebo) = 0;

    inline cbtU32 GetVBOCount() const { return (cbtU32)m_VBOs.size(); }
    const CBTVertexBuffer* const* GetVBOs() const { return m_VBOs.empty() ? nullptr : &m_VBOs[0]; }
    CBTVertexBuffer** GetVBOs() { return m_VBOs.empty() ? nullptr : &m_VBOs[0]; }
    const CBTElementBuffer& GetEBO() const { return *m_EBO; }

    static CBTVertexArray* CreateVAO();
};

NS_CBT_END