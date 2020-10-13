#pragma once

// Include CBT
#include "cbtMacros.h"
#include "Core/General/cbtRef.h"

// Include STD
#include <vector>

NS_CBT_BEGIN

class cbtVertexBuffer;
class cbtElementBuffer;

// Vertex Array Object
class cbtVertexArray : public cbtManaged
{
protected:
    std::vector<cbtVertexBuffer*> m_VBOs;
    cbtElementBuffer* m_EBO;

    virtual ~cbtVertexArray() {}

public:
    cbtVertexArray()
        : m_EBO(nullptr)
    {}

    virtual void Bind() = 0;
    virtual void AddVBO(cbtVertexBuffer* _vbo) = 0;
    virtual void SetEBO(cbtElementBuffer* _ebo) = 0;

    inline cbtU32 GetVBOCount() const { return (cbtU32)m_VBOs.size(); }
    const cbtVertexBuffer* const* GetVBOs() const { return m_VBOs.empty() ? nullptr : &m_VBOs[0]; }
    cbtVertexBuffer** GetVBOs() { return m_VBOs.empty() ? nullptr : &m_VBOs[0]; }
    const cbtElementBuffer& GetEBO() const { return *m_EBO; }

    static cbtVertexArray* CreateVAO();
};

NS_CBT_END