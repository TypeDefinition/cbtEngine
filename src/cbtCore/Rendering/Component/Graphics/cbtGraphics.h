#pragma once

// Include CBT
#include "Debug/cbtDebug.h"
#include "Game/Component/cbtComponent.h"
#include "Rendering/Material/cbtMaterial.h"

NS_CBT_BEGIN

/*
    const int *ptr;
    int const *ptr; // these two are equivalent: non-const pointer to const int
    
    int *const ptr; // const pointer to non-const int
    
    int const *const ptr; // const pointer to const int
    const int *const ptr; // const pointer to const int
*/

    class cbtGraphics : public cbtComponent
    {
    private:
        // Variable(s)
        cbtRef<cbtMaterial> m_Material;

    public:
        // Constructor(s) & Destructor
        cbtGraphics()
                :m_Material(nullptr)
        {
        }

        virtual ~cbtGraphics()
        {
        }

        // Interface Function(s)
        inline const cbtMaterial* GetMaterial() const
        {
            return m_Material.GetRawPointer();
        }

        inline cbtMaterial* GetMaterial()
        {
            return m_Material.GetRawPointer();
        }

        inline void SetMaterial(cbtMaterial* _material)
        {
            m_Material = _material;
        }
    };

NS_CBT_END