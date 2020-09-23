#pragma once

// Include CBT
#include "Debug/CBTDebug.h"
#include "Game/Component/CBTComponent.h"
#include "Rendering/Material/CBTMaterial.h"

NS_CBT_BEGIN

/*
    const int *ptr;
    int const *ptr; // these two are equivalent: non-const pointer to const int
    
    int *const ptr; // const pointer to non-const int
    
    int const *const ptr; // const pointer to const int
    const int *const ptr; // const pointer to const int
*/

class CBTGraphics : public CBTComponent
{
private:
    // Variable(s)
    CBTRef<CBTMaterial> m_Material;

public:
    // Constructor(s) & Destructor
    CBTGraphics() : m_Material(nullptr) {}
    virtual ~CBTGraphics() {}

    // Interface Function(s)
    inline const CBTMaterial* GetMaterial() const { return m_Material.GetRawPointer(); }
    inline CBTMaterial* GetMaterial() { return m_Material.GetRawPointer(); }
    inline void SetMaterial(CBTMaterial* _material) { m_Material = _material; }
};

NS_CBT_END