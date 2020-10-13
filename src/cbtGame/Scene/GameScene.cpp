// Include Sandbox
#include "GameScene.h"

// Include cbt
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
    floorMaterial->SetShader(cbtShaderBuilder::CreateShaderProgram("GPass", { "./../assets/shaders/GL/cbtGeometry.vert" }, { "./../assets/shaders/GL/cbtGPass.frag" }));
    floorMaterial->SetTextureAlbedo(cbtTextureBuilder::Create2DTexture("Pavement Brick Albedo", "./../assets/textures/Materials/Pavement/Pavement_Brick_001_Albedo_2048x2048.png"));
    floorMaterial->SetTextureNormal(cbtTextureBuilder::Create2DTexture("Pavement Brick Normal", "./../assets/textures/Materials/Pavement/Pavement_Brick_001_Normal_2048x2048.png"));
    floorMaterial->SetTextureSpecular(cbtTextureBuilder::Create2DTexture("Pavement Brick Specular", "./../assets/textures/Materials/Pavement/Pavement_Brick_001_Specular_2048x2048.png"));
    floorMaterial->SetTextureGloss(cbtTextureBuilder::Create2DTexture("Pavement Brick Gloss", "./../assets/textures/Materials/Pavement/Pavement_Brick_001_Gloss_2048x2048.png"));
    floorMaterial->SetTextureDisplacement(cbtTextureBuilder::Create2DTexture("Pavement Brick Displacement", "./../assets/textures/Materials/Pavement/Pavement_Brick_001_Displacement_2048x2048.png"));
    floorMaterial->SetTextureScale(cbtVector2F(100.0f, 100.0f));

    cbtMaterial* cubeMaterial = cbtNew cbtMaterial("Cube");
    cubeMaterial->SetMesh(cbtMeshBuilder::LoadAsset("Cube", "./../assets/models/OBJ/Cube.obj"));
    // cubeMaterial->SetRenderMode(NS_CBT::CBT_RENDER_MODE_FORWARD);
    // cubeMaterial->SetShader(cbtShaderBuilder::CreateShaderProgram("FPass", { "./../assets/shaders/GL/cbtGeometry.vert" }, { "./../assets/shaders/GL/cbtFPass.frag"}));
    cubeMaterial->SetShader(cbtShaderBuilder::CreateShaderProgram("GPass", { "./../assets/shaders/GL/cbtGeometry.vert" }, { "./../assets/shaders/GL/cbtGPass.frag" }));
    cubeMaterial->SetTextureAlbedo(cbtTextureBuilder::Create2DTexture("Tiles Albedo", "./../assets/textures/Materials/Tiles/Tiles_001_Albedo_2048x2048.png"));
    cubeMaterial->SetTextureNormal(cbtTextureBuilder::Create2DTexture("Tiles Normal", "./../assets/textures/Materials/Tiles/Tiles_001_Normal_2048x2048.png"));
    cubeMaterial->SetTextureSpecular(cbtTextureBuilder::Create2DTexture("Tiles Specular", "./../assets/textures/Materials/Tiles/Tiles_001_Specular_2048x2048.png"));
    cubeMaterial->SetTextureGloss(cbtTextureBuilder::Create2DTexture("Tiles Gloss", "./../assets/textures/Materials/Tiles/Tiles_001_Gloss_2048x2048.png"));
    cubeMaterial->SetTextureDisplacement(cbtTextureBuilder::Create2DTexture("Tiles Displacement", "./../assets/textures/Materials/Tiles/Tiles_001_Displacement_2048x2048.png"));
    cubeMaterial->SetTextureScale(cbtVector2F(3.0f, 3.0f));

    cbtMaterial* windowMaterial = cbtNew cbtMaterial("Window");
    windowMaterial->SetMesh(cbtMeshBuilder::CreateQuad("Window"));
    windowMaterial->SetRenderMode(NS_CBT::CBT_RENDER_MODE_FORWARD_TRANSPARENT);
    windowMaterial->SetShader(cbtShaderBuilder::CreateShaderProgram("FPass", { "./../assets/shaders/GL/cbtGeometry.vert" }, { "./../assets/shaders/GL/cbtFPass.frag" }));
    windowMaterial->SetTextureAlbedo(cbtTextureBuilder::Create2DTexture("Window Albedo", "./../assets/textures/Test/Alpha/Window.png"));

    m_Light = AddEntity();
    cbtLight* lightLight = AddComponent<cbtLight>(m_Light);
    lightLight->SetMode(NS_CBT::CBT_LIGHT_DIRECTIONAL);
    lightLight->SetPower(1.0f);
    cbtTransform* lightTransform = AddComponent<cbtTransform>(m_Light);
    lightTransform->SetLocalPosition(cbtVector3F(0.0f, 2.0f, 0.0f));
    lightTransform->SetLocalRotation(80.0f, cbtVector3F::LEFT);

    m_Floor = AddEntity();
    AddComponent<cbtGraphics>(m_Floor)->SetMaterial(floorMaterial);
    cbtTransform* floorTransform = AddComponent<cbtTransform>(m_Floor);
    floorTransform->SetLocalScale(cbtVector3F(100.0f, 100.0f, 100.0f));
    floorTransform->SetLocalRotation(-90.0f, cbtVector3F::LEFT);
    floorTransform->SetLocalPosition(cbtVector3F(0.0f, 0.0f, 0.0f));

    for (cbtU32 i = 0; i < 500; ++i)
    {
        cbtECS cube = AddEntity();
        AddComponent<cbtGraphics>(cube)->SetMaterial(cubeMaterial);
        cbtTransform* cubeTransform = AddComponent<cbtTransform>(cube);
        cubeTransform->SetLocalRotation((cbtF32)cbtMathUtil::RandomInt(0, 360), cbtVector3F::LEFT);
        cubeTransform->SetLocalRotation((cbtF32)cbtMathUtil::RandomInt(0, 360), cbtVector3F::UP);
        cubeTransform->SetLocalRotation((cbtF32)cbtMathUtil::RandomInt(0, 360), cbtVector3F::FORWARDS);
        cubeTransform->SetLocalPosition(cbtVector3F((cbtF32)cbtMathUtil::RandomInt(-20, 20), (cbtF32)cbtMathUtil::RandomInt(-20, 20), (cbtF32)cbtMathUtil::RandomInt(5, 20)));
    }

    for (cbtU32 i = 0; i < 50; ++i)
    {
        cbtECS window = AddEntity();
        AddComponent<cbtGraphics>(window)->SetMaterial(windowMaterial);
        cbtTransform* windowTransform = AddComponent<cbtTransform>(window);
        windowTransform->SetLocalRotation(180.0f, cbtVector3F::UP);
        windowTransform->SetLocalPosition(cbtVector3F((cbtF32)cbtMathUtil::RandomInt(-20, 20), (cbtF32)cbtMathUtil::RandomInt(0, 20), (cbtF32)cbtMathUtil::RandomInt(5, 20)));
    }

    {
        cbtECS player = AddEntity();
        cbtTransform* playerTransform = AddComponent<cbtTransform>(player);
        playerTransform->SetLocalPosition(cbtVector3F(0.0f, 2.0f, 0.0f));
        cbtCamera* playerCamera = AddComponent<cbtCamera>(player);
        playerCamera->SetLightingShader(cbtShaderBuilder::CreateShaderProgram("LPass", { "./../assets/shaders/GL/cbtScreenQuad.vert" }, { "./../assets/shaders/GL/cbtLPass.frag" }));
        playerCamera->SetSkyboxColor(cbtColor::MAGENTA);
        playerCamera->SetSkyboxShader(cbtShaderBuilder::CreateShaderProgram("Skybox", { "./../assets/shaders/GL/cbtSkybox.vert" }, { "./../assets/shaders/GL/cbtSkybox.frag" }));
        playerCamera->SetSkyboxTexture(cbtTextureBuilder::CreateCubeMap("Skybox", {
            "./../assets/textures/Skybox/Nebula/Skybox_Nebula_001_Left_2048x2048.png",
            "./../assets/textures/Skybox/Nebula/Skybox_Nebula_001_Right_2048x2048.png",
            "./../assets/textures/Skybox/Nebula/Skybox_Nebula_001_Top_2048x2048.png",
            "./../assets/textures/Skybox/Nebula/Skybox_Nebula_001_Bottom_2048x2048.png",
            "./../assets/textures/Skybox/Nebula/Skybox_Nebula_001_Front_2048x2048.png",
            "./../assets/textures/Skybox/Nebula/Skybox_Nebula_001_Back_2048x2048.png"
            }));
        playerCamera->SetPostProcessShaders({
            cbtShaderBuilder::CreateShaderProgram("Greyscale", { "./../assets/shaders/GL/cbtScreenQuad.vert" }, { "./../assets/shaders/GL/cbtGreyscale.frag" }),
            cbtShaderBuilder::CreateShaderProgram("Blur", { "./../assets/shaders/GL/cbtScreenQuad.vert" }, { "./../assets/shaders/GL/cbtBlur.frag" }),
            cbtShaderBuilder::CreateShaderProgram("Invert", { "./../assets/shaders/GL/cbtScreenQuad.vert" }, { "./../assets/shaders/GL/cbtInvert.frag" }),
            cbtShaderBuilder::CreateShaderProgram("Outline", { "./../assets/shaders/GL/cbtScreenQuad.vert" }, { "./../assets/shaders/GL/cbtOutline.frag" }),
            });
    }

    {
        cbtECS player = AddEntity();
        cbtTransform* playerTransform = AddComponent<cbtTransform>(player);
        playerTransform->SetLocalPosition(cbtVector3F(5.0f, 2.0f, 0.0f));
        cbtU32 test = cbtFlags<cbtCamera>::FLAGS;
        cbtCamera* playerCamera = AddComponent<cbtCamera>(player);
        playerCamera->SetViewport(cbtViewport(0.5f, 0.5f, 1.0f, 1.0f));
        playerCamera->SetLightingShader(cbtShaderBuilder::CreateShaderProgram("LPass", { "./../assets/shaders/GL/cbtScreenQuad.vert" }, { "./../assets/shaders/GL/cbtLPass.frag" }));
        playerCamera->SetSkyboxColor(cbtColor::RED);
        playerCamera->SetSkyboxShader(cbtShaderBuilder::CreateShaderProgram("Skybox", { "./../assets/shaders/GL/cbtSkybox.vert" }, { "./../assets/shaders/GL/cbtSkybox.frag" }));
        playerCamera->SetSkyboxTexture(cbtTextureBuilder::CreateCubeMap("Skybox", {
            "./../assets/textures/Skybox/Nebula/Skybox_Nebula_001_Left_2048x2048.png",
            "./../assets/textures/Skybox/Nebula/Skybox_Nebula_001_Right_2048x2048.png",
            "./../assets/textures/Skybox/Nebula/Skybox_Nebula_001_Top_2048x2048.png",
            "./../assets/textures/Skybox/Nebula/Skybox_Nebula_001_Bottom_2048x2048.png",
            "./../assets/textures/Skybox/Nebula/Skybox_Nebula_001_Front_2048x2048.png",
            "./../assets/textures/Skybox/Nebula/Skybox_Nebula_001_Back_2048x2048.png"
            }));
    }
}

GameScene::~GameScene()
{
}