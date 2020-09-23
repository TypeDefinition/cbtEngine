// Include Sandbox
#include "GameScene.h"

// Include CBT
#include "Game/Component/Transform/CBTTransform.h"

#include "Rendering/Component/Camera/CBTCamera.h"
#include "Rendering/Component/Graphics/CBTGraphics.h"
#include "Rendering/Component/Light/CBTLight.h"

#include "Rendering/Texture/CBTTextureBuilder.h"
#include "Rendering/Mesh/CBTMeshBuilder.h"
#include "Rendering/Shader/CBTShaderBuilder.h"

// Constructor(s) & Destructor
GameScene::GameScene()
{
    CBTMaterial* floorMaterial = cbtNew CBTMaterial("Floor");
    floorMaterial->SetMesh(CBTMeshBuilder::CreateQuad("Floor"));
    floorMaterial->SetShader(CBTShaderBuilder::CreateShaderProgram("GPass", { "../../assets/Shaders/OpenGL/CBTGeometry.vert" }, { "../../assets/Shaders/OpenGL/CBTGPass.frag" }));
    floorMaterial->SetTextureAlbedo(CBTTextureBuilder::Create2DTexture("Pavement Brick Albedo", "../../assets/Textures/Materials/Pavement/Pavement_Brick_001_Albedo_2048x2048.png"));
    floorMaterial->SetTextureNormal(CBTTextureBuilder::Create2DTexture("Pavement Brick Normal", "../../assets/Textures/Materials/Pavement/Pavement_Brick_001_Normal_2048x2048.png"));
    floorMaterial->SetTextureSpecular(CBTTextureBuilder::Create2DTexture("Pavement Brick Specular", "../../assets/Textures/Materials/Pavement/Pavement_Brick_001_Specular_2048x2048.png"));
    floorMaterial->SetTextureGloss(CBTTextureBuilder::Create2DTexture("Pavement Brick Gloss", "../../assets/Textures/Materials/Pavement/Pavement_Brick_001_Gloss_2048x2048.png"));
    floorMaterial->SetTextureDisplacement(CBTTextureBuilder::Create2DTexture("Pavement Brick Displacement", "../../assets/Textures/Materials/Pavement/Pavement_Brick_001_Displacement_2048x2048.png"));
    floorMaterial->SetTextureScale(CBTVector2F(100.0f, 100.0f));

    CBTMaterial* cubeMaterial = cbtNew CBTMaterial("Cube");
    cubeMaterial->SetMesh(CBTMeshBuilder::LoadAsset("Cube", "../../assets/Models/OBJ/Cube.obj"));
    // cubeMaterial->SetRenderMode(NS_CBT::CBT_RENDER_MODE_FORWARD);
    // cubeMaterial->SetShader(CBTShaderBuilder::CreateShaderProgram("FPass", { "../../assets/Shaders/OpenGL/CBTGeometry.vert" }, { "../../assets/Shaders/OpenGL/CBTFPass.frag"}));
    cubeMaterial->SetShader(CBTShaderBuilder::CreateShaderProgram("GPass", { "../../assets/Shaders/OpenGL/CBTGeometry.vert" }, { "../../assets/Shaders/OpenGL/CBTGPass.frag" }));
    cubeMaterial->SetTextureAlbedo(CBTTextureBuilder::Create2DTexture("Tiles Albedo", "../../assets/Textures/Materials/Tiles/Tiles_001_Albedo_2048x2048.png"));
    cubeMaterial->SetTextureNormal(CBTTextureBuilder::Create2DTexture("Tiles Normal", "../../assets/Textures/Materials/Tiles/Tiles_001_Normal_2048x2048.png"));
    cubeMaterial->SetTextureSpecular(CBTTextureBuilder::Create2DTexture("Tiles Specular", "../../assets/Textures/Materials/Tiles/Tiles_001_Specular_2048x2048.png"));
    cubeMaterial->SetTextureGloss(CBTTextureBuilder::Create2DTexture("Tiles Gloss", "../../assets/Textures/Materials/Tiles/Tiles_001_Gloss_2048x2048.png"));
    cubeMaterial->SetTextureDisplacement(CBTTextureBuilder::Create2DTexture("Tiles Displacement", "../../assets/Textures/Materials/Tiles/Tiles_001_Displacement_2048x2048.png"));
    cubeMaterial->SetTextureScale(CBTVector2F(3.0f, 3.0f));

    CBTMaterial* windowMaterial = cbtNew CBTMaterial("Window");
    windowMaterial->SetMesh(CBTMeshBuilder::CreateQuad("Window"));
    windowMaterial->SetRenderMode(NS_CBT::CBT_RENDER_MODE_FORWARD_TRANSPARENT);
    windowMaterial->SetShader(CBTShaderBuilder::CreateShaderProgram("FPass", { "../../assets/Shaders/OpenGL/CBTGeometry.vert" }, { "../../assets/Shaders/OpenGL/CBTFPass.frag" }));
    windowMaterial->SetTextureAlbedo(CBTTextureBuilder::Create2DTexture("Window Albedo", "../../assets/Textures/Test/Alpha/Window.png"));

    m_Light = AddEntity();
    CBTLight* lightLight = AddComponent<CBTLight>(m_Light);
    lightLight->SetMode(NS_CBT::CBT_LIGHT_DIRECTIONAL);
    lightLight->SetPower(1.0f);
    CBTTransform* lightTransform = AddComponent<CBTTransform>(m_Light);
    lightTransform->SetLocalPosition(CBTVector3F(0.0f, 2.0f, 0.0f));
    lightTransform->SetLocalRotation(80.0f, CBTVector3F::LEFT);

    m_Floor = AddEntity();
    AddComponent<CBTGraphics>(m_Floor)->SetMaterial(floorMaterial);
    CBTTransform* floorTransform = AddComponent<CBTTransform>(m_Floor);
    floorTransform->SetLocalScale(CBTVector3F(100.0f, 100.0f, 100.0f));
    floorTransform->SetLocalRotation(-90.0f, CBTVector3F::LEFT);
    floorTransform->SetLocalPosition(CBTVector3F(0.0f, 0.0f, 0.0f));

    for (cbtU32 i = 0; i < 500; ++i)
    {
        cbtECS cube = AddEntity();
        AddComponent<CBTGraphics>(cube)->SetMaterial(cubeMaterial);
        CBTTransform* cubeTransform = AddComponent<CBTTransform>(cube);
        cubeTransform->SetLocalRotation((cbtF32)CBTMathUtil::RandomInt(0, 360), CBTVector3F::LEFT);
        cubeTransform->SetLocalRotation((cbtF32)CBTMathUtil::RandomInt(0, 360), CBTVector3F::UP);
        cubeTransform->SetLocalRotation((cbtF32)CBTMathUtil::RandomInt(0, 360), CBTVector3F::FORWARDS);
        cubeTransform->SetLocalPosition(CBTVector3F((cbtF32)CBTMathUtil::RandomInt(-20, 20), (cbtF32)CBTMathUtil::RandomInt(-20, 20), (cbtF32)CBTMathUtil::RandomInt(5, 20)));
    }

    for (cbtU32 i = 0; i < 50; ++i)
    {
        cbtECS window = AddEntity();
        AddComponent<CBTGraphics>(window)->SetMaterial(windowMaterial);
        CBTTransform* windowTransform = AddComponent<CBTTransform>(window);
        windowTransform->SetLocalRotation(180.0f, CBTVector3F::UP);
        windowTransform->SetLocalPosition(CBTVector3F((cbtF32)CBTMathUtil::RandomInt(-20, 20), (cbtF32)CBTMathUtil::RandomInt(0, 20), (cbtF32)CBTMathUtil::RandomInt(5, 20)));
    }

    {
        cbtECS player = AddEntity();
        CBTTransform* playerTransform = AddComponent<CBTTransform>(player);
        playerTransform->SetLocalPosition(CBTVector3F(0.0f, 2.0f, 0.0f));
        CBTCamera* playerCamera = AddComponent<CBTCamera>(player);
        playerCamera->SetLightingShader(CBTShaderBuilder::CreateShaderProgram("LPass", { "../../assets/Shaders/OpenGL/CBTScreenQuad.vert" }, { "../../assets/Shaders/OpenGL/CBTLPass.frag" }));
        playerCamera->SetSkyboxColor(CBTColor::MAGENTA);
        playerCamera->SetSkyboxShader(CBTShaderBuilder::CreateShaderProgram("Skybox", { "../../assets/Shaders/OpenGL/CBTSkybox.vert" }, { "../../assets/Shaders/OpenGL/CBTSkybox.frag" }));
        playerCamera->SetSkyboxTexture(CBTTextureBuilder::CreateCubeMap("Skybox", {
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
            CBTShaderBuilder::CreateShaderProgram("Outline", { "../../assets/Shaders/OpenGL/CBTScreenQuad.vert" }, { "../../assets/Shaders/OpenGL/CBTOutline.frag" }),
            });
    }

    {
        cbtECS player = AddEntity();
        CBTTransform* playerTransform = AddComponent<CBTTransform>(player);
        playerTransform->SetLocalPosition(CBTVector3F(5.0f, 2.0f, 0.0f));
        cbtU32 test = CBTFlags<CBTCamera>::FLAGS;
        CBTCamera* playerCamera = AddComponent<CBTCamera>(player);
        playerCamera->SetViewport(CBTViewport(0.5f, 0.5f, 1.0f, 1.0f));
        playerCamera->SetLightingShader(CBTShaderBuilder::CreateShaderProgram("LPass", { "../../assets/Shaders/OpenGL/CBTScreenQuad.vert" }, { "../../assets/Shaders/OpenGL/CBTLPass.frag" }));
        playerCamera->SetSkyboxColor(CBTColor::RED);
        playerCamera->SetSkyboxShader(CBTShaderBuilder::CreateShaderProgram("Skybox", { "../../assets/Shaders/OpenGL/CBTSkybox.vert" }, { "../../assets/Shaders/OpenGL/CBTSkybox.frag" }));
        playerCamera->SetSkyboxTexture(CBTTextureBuilder::CreateCubeMap("Skybox", {
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