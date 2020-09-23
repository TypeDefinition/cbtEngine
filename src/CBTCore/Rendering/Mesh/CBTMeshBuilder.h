#pragma once

// Include CBT
#include "CBTMesh.h"
#include "Core/General/CBTLibrary.h"

NS_CBT_BEGIN

class CBTMeshBuilder
{
private:
    /**
        \brief Private Constructor. All functions should be static. No objects of this class should be created.
    */
    CBTMeshBuilder() {}
    /**
        \brief Private Destructor. All functions should be static. No objects of this class should be created.
    */
    ~CBTMeshBuilder() {}

public:
    static CBTMesh* CreateScreenQuad(const cbtStr& _name);
    static CBTMesh* CreateSkybox(const cbtStr& _name);

    static CBTMesh* CreateQuad(const cbtStr& _name);
    static CBTMesh* LoadAsset(const cbtStr& _name, const cbtStr& _filePath);
};

NS_CBT_END