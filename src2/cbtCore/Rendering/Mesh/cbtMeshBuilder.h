#pragma once

// Include CBT
#include "cbtMesh.h"
#include "Core/General/cbtLibrary.h"

NS_CBT_BEGIN

class cbtMeshBuilder
{
private:
    /**
        \brief Private Constructor. All functions should be static. No objects of this class should be created.
    */
    cbtMeshBuilder() {}
    /**
        \brief Private Destructor. All functions should be static. No objects of this class should be created.
    */
    ~cbtMeshBuilder() {}

public:
    static cbtMesh* CreateScreenQuad(const cbtStr& _name);
    static cbtMesh* CreateSkybox(const cbtStr& _name);

    static cbtMesh* CreateQuad(const cbtStr& _name);
    static cbtMesh* LoadAsset(const cbtStr& _name, const cbtStr& _filePath);
};

NS_CBT_END