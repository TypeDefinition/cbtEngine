// Include Sandbox
#include "GameScene.h"

// Include CBT
#include "Game/Component/Transform/cbtTransform.h"

#include "Rendering/Component/Camera/cbtCamera.h"
#include "Rendering/Component/Graphics/cbtGraphics.h"
#include "Rendering/Component/Light/cbtLight.h"

#include "Rendering/Texture/cbtTextureBuilder.h"
#include "Rendering/Mesh/cbtMeshBuilder.h"
#include "Rendering/Shader/cbtShaderBuilder.h"

// Constructor(s) & Destructor
GameScene::GameScene()
{
    cbtMaterial* floorMaterial = cbtNew cbtMaterial("Floor");
    floorMaterial->SetMesh(cbtMeshBuilder::CreateQuad("Floor"));
    floorMaterial->SetShader(cbtShaderBuilder::CreateShaderProgram("GPass", { "../../assets/Shaders/OpenGL/CBTGeometry.vert" }, { "../../assets/Shaders/OpenGL/CBTGPass.frag" }));
    floorMaterial->SetTextureAlbedo(cbtTextureBuilder::Create2DTexture("Pavement Brick Albedo", "../../assets/Textures/Materials/Pavement/Pavement_Brick_001_Albedo_2048x2048.png"));
    floorMaterial->SetTextureNormal(cbtTextureBuilder::Create2DTexture("Pavement Brick Normal", "../../assets/Textures/Materials/Pavement/Pavement_Brick_001_Normal_2048x2048.png"));
    floorMaterial->SetTextureSpecular(cbtTextureBuilder::Create2DTexture("Pavement Brick Specular", "../../assets/Textures/Materials/Pavement/Pavement_Brick_001_Specular_2048x2048.png"));
    floorMaterial->SetTextureGloss(cbtTextureBuilder::Create2DTexture("Pavement Brick Gloss", "../../assets/Textures/Materials/Pavement/Pavement_Brick_001_Gloss_2048x2048.png"));
    floorMaterial->SetTextureDisplacement(cbtTextureBuilder::Create2DTexture("Pavement Brick Displacement", "../../assets/Textures/Materials/Pavement/Pavement_Brick_001_Displacement_2048x2048.png"));
    floorMaterial->SetTextureScale(CBTVector2F(100.0f, 100.0f));

    cbtMaterial* cubeMaterial = cbtNew cbtMaterial("Cube");
    cubeMaterial->SetMesh(cbtMeshBuilder::LoadAsset("Cube", "../../assets/Models/OBJ/Cube.obj"));
    // cubeMaterial->SetRenderMode(NS_CBT::CBT_RENDER_MODE_FORWARD);
    // cubeMaterial->SetShader(CBTShaderBuilder::CreateShaderProgram("FPass", { "../../assets/Shaders/OpenGL/CBTGeometry.vert" }, { "../../assets/Shaders/OpenGL/CBTFPass.frag"}));
    cubeMaterial->SetShader(cbtShaderBuilder::CreateShaderProgram("GPass", { "../../assets/Shaders/OpenGL/CBTGeometry.vert" }, { "../../assets/Shaders/OpenGL/CBTGPass.frag" }));
    cubeMaterial->SetTextureAlbedo(cbtTextureBuilder::Create2DTexture("Tiles Albedo", "../../assets/Textures/Materials/Tiles/Tiles_001_Albedo_2048x2048.png"));
    cubeMaterial->SetTextureNormal(cbtTextureBuilder::Create2DTexture("Tiles Normal", "../../assets/Textures/Materials/Tiles/Tiles_001_Normal_2048x2048.png"));
    cubeMaterial->SetTextureSpecular(cbtTextureBuilder::Create2DTexture("Tiles Specular", "../../assets/Textures/Materials/Tiles/Tiles_001_Specular_2048x2048.png"));
    cubeMaterial->SetTextureGloss(cbtTextureBuilder::Create2DTexture("Tiles Gloss", "../../assets/Textures/Materials/Tiles/Tiles_001_Gloss_2048x2048.png"));
    cubeMaterial->SetTextureDisplacement(cbtTextureBuilder::Create2DTexture("Tiles Displacement", "../../assets/Textures/Materials/Tiles/Tiles_001_Displacement_2048x2048.png"));
    cubeMaterial->SetTextureScale(CBTVector2F(3.0f, 3.0f));

    cbtMaterial* windowMaterial = cbtNew cbtMaterial("Window");
    windowMaterial->SetMesh(cbtMeshBuilder::CreateQuad("Window"));
    windowMaterial->SetRenderMode(NS_CBT::CBT_RENDER_MODE_FORWARD_TRANSPARENT);
    windowMaterial->SetShader(cbtShaderBuilder::CreateShaderProgram("FPass", { "../../assets/Shaders/OpenGL/CBTGeometry.vert" }, { "../../assets/Shaders/OpenGL/CBTFPass.frag" }));
    windowMaterial->SetTextureAlbedo(cbtTextureBuilder::Create2DTexture("Window Albedo", "../../assets/Textures/Test/Alpha/Window.png"));

    m_Light = AddEntity();
    cbtLight* lightLight = AddComponent<cbtLight>(m_Light);
    lightLight->SetMode(NS_CBT::CBT_LIGHT_DIRECTIONAL);
    lightLight->SetPower(1.0f);
    cbtTransform* lightTransform = AddComponent<cbtTransform>(m_Light);
    lightTransform->SetLocalPosition(CBTVector3F(0.0f, 2.0f, 0.0f));
    lightTransform->SetLocalRotation(80.0f, CBTVector3F::LEFT);

    m_Floor = AddEntity();
    AddComponent<cbtGraphics>(m_Floor)->SetMaterial(floorMaterial);
    cbtTransform* floorTransform = AddComponent<cbtTransform>(m_Floor);
    floorTransform->SetLocalScale(CBTVector3F(100.0f, 100.0f, 100.0f));
    floorTransform->SetLocalRotation(-90.0f, CBTVector3F::LEFT);
    floorTransform->SetLocalPosition(CBTVector3F(0.0f, 0.0f, 0.0f));

    for (cbtU32 i = 0; i < 500; ++i)
    {
        cbtECS cube = AddEntity();
        AddComponent<cbtGraphics>(cube)->SetMaterial(cubeMaterial);
        cbtTransform* cubeTransform = AddComponent<cbtTransform>(cube);
        cubeTransform->SetLocalRotation((cbtF32)cbtMathUtil::RandomInt(0, 360), CBTVector3F::LEFT);
        cubeTransform->SetLocalRotation((cbtF32)cbtMathUtil::RandomInt(0, 360), CBTVector3F::UP);
        cubeTransform->SetLocalRotation((cbtF32)cbtMathUtil::RandomInt(0, 360), CBTVector3F::FORWARDS);
        cubeTransform->SetLocalPosition(CBTVector3F((cbtF32)cbtMathUtil::RandomInt(-20, 20), (cbtF32)cbtMathUtil::RandomInt(-20, 20), (cbtF32)cbtMathUtil::RandomInt(5, 20)));
    }

    for (cbtU32 i = 0; i < 50; ++i)
    {
        cbtECS window = AddEntity();
        AddComponent<cbtGraphics>(window)->SetMaterial(windowMaterial);
        cbtTransform* windowTransform = AddComponent<cbtTransform>(window);
        windowTransform->SetLocalRotation(180.0f, CBTVector3F::UP);
        windowTransform->SetLocalPosition(CBTVector3F((cbtF32)cbtMathUtil::RandomInt(-20, 20), (cbtF32)cbtMathUtil::RandomInt(0, 20), (cbtF32)cbtMathUtil::RandomInt(5, 20)));
    }

    {
        cbtECS player = AddEntity();
        cbtTransform* playerTransform = AddComponent<cbtTransform>(player);
        playerTransform->SetLocalPosition(CBTVector3F(0.0f, 2.0f, 0.0f));
        cbtCamera* playerCamera = AddComponent<cbtCamera>(player);
        playerCamera->SetLightingShader(cbtShaderBuilder::CreateShaderProgram("LPass", { "../../assets/Shaders/OpenGL/CBTScreenQuad.vert" }, { "../../assets/Shaders/OpenGL/CBTLPass.frag" }));
        playerCamera->SetSkyboxColor(cbtColor::MAGENTA);
        playerCamera->SetSkyboxShader(cbtShaderBuilder::CreateShaderProgram("Skybox", { "../../assets/Shaders/OpenGL/CBTSkybox.vert" }, { "../../assets/Shaders/OpenGL/CBTSkybox.frag" }));
        playerCamera->SetSkyboxTexture(cbtTextureBuilder::CreateCubeMap("Skybox", {
            "../../assets/Textures/Skybox/Nebula/Skybox_Nebula_001_Left_2048x2048.png",
            "../../assets/Textures/Skybox/Nebula/Skybox_Nebula_001_Right_2048x2048.png",
            "../../assets/Textures/Skybox/Nebula/Skybox_Nebula_001_Top_2048x2048.png",
            "../../assets/Textures/Skybox/Nebula/Skybox_Nebula_001_Bottom_2048x2048.png",
            "../../assets/Textures/Skybox/Nebula/Skybox_Nebula_001_Front_2048x2048.png",
            "../../assets/Textures/Skybox/Nebula/Skybox_Nebula_001_Back_2048x2048.png"
            }));
        playerCamera->SetPostProcessShaders({
            // CBTShaderBuilder::CreateShaderProgram("Greyscale", { "../../assets/Shaders/OpenGL/CBTScreenQuad.vert" }, { "../../assets/Shaders/OpenGL/CBTGreyscale.frag" }),
            // CBTShaderBuilder::CreateShaderProgram("Blur", { "../../assets/Shaders/OpenGL/CBTScreenQuad.vert" }, { "../../assets/Shaders/OpenGL/CBTBlur.frag" }),
            // CBTShaderBuilder::CreateShaderProgram("Invert", { "../../assets/Shaders/OpenGL/CBTScreenQuad.vert" }, { "../../assets/Shaders/OpenGL/CBTInvert.frag" }),
            cbtShaderBuilder::CreateShaderProgram("Outline", { "../../assets/Shaders/OpenGL/CBTScreenQuad.vert" }, { "../../assets/Shaders/OpenGL/CBTOutline.frag" }),
            });
    }

    {
        cbtECS player = AddEntity();
        cbtTransform* playerTransform = AddComponent<cbtTransform>(player);
        playerTransform->SetLocalPosition(CBTVector3F(5.0f, 2.0f, 0.0f));
        cbtU32 test = cbtFlags<cbtCamera>::FLAGS;
        cbtCamera* playerCamera = AddComponent<cbtCamera>(player);
        playerCamera->SetViewport(cbtViewport(0.5f, 0.5f, 1.0f, 1.0f));
        playerCamera->SetLightingShader(cbtShaderBuilder::CreateShaderProgram("LPass", { "../../assets/Shaders/OpenGL/CBTScreenQuad.vert" }, { "../../assets/Shaders/OpenGL/CBTLPass.frag" }));
        playerCamera->SetSkyboxColor(cbtColor::RED);
        playerCamera->SetSkyboxShader(cbtShaderBuilder::CreateShaderProgram("Skybox", { "../../assets/Shaders/OpenGL/CBTSkybox.vert" }, { "../../assets/Shaders/OpenGL/CBTSkybox.frag" }));
        playerCamera->SetSkyboxTexture(cbtTextureBuilder::CreateCubeMap("Skybox", {
            "../../assets/Textures/Skybox/Nebula/Skybox_Nebula_001_Left_2048x2048.png",
            "../../assets/Textures/Skybox/Nebula/Skybox_Nebula_001_Right_2048x2048.png",
            "../../assets/Textures/Skybox/Nebula/Skybox_Nebula_001_Top_2048x2048.png",
            "../../assets/Textures/Skybox/Nebula/Skybox_Nebula_001_Bottom_2048x2048.png",
            "../../assets/Textures/Skybox/Nebula/Skybox_Nebula_001_Front_2048x2048.png",
            "../../assets/Textures/Skybox/Nebula/Skybox_Nebula_001_Back_2048x2048.png"
            }));
    }
}

GameScene::~GameScene()
{
}