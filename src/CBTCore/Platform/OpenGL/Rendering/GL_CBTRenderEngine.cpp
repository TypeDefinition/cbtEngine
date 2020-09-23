// Include CBT
#include "GL_CBTRenderEngine.h"

#ifdef CBT_OPENGL

NS_CBT_BEGIN

CBTRenderEngine* CBTRenderEngine::CreateInstance() { return cbtNew GL_CBTRenderEngine(); }

void GL_CBTRenderEngine::Init(const CBTWindowProperties& _winProp)
{
    // Create Window
    m_Window = CBTWindow::CreateCBTWindow(_winProp);

    // Initialise GLEW (Must be initialised or textures and meshes and whatever fuck shit will fail. Learnt that the hard way when I forgot to initialise it.)
    GLenum initResult = glewInit();
    CBT_ASSERT(initResult == GLEW_OK);

    m_MaterialLibrary = cbtNew CBTLibrary<CBTMaterial>();
    m_ShaderLibrary = cbtNew CBTLibrary<CBTShaderProgram>();
    m_MeshLibrary = cbtNew CBTLibrary<CBTMesh>();
    m_TextureLibrary = cbtNew CBTLibrary<CBTTexture>();
    m_Renderer = cbtNew CBTRenderer();
}

void GL_CBTRenderEngine::Update()
{
    m_Renderer->Update();
}

void GL_CBTRenderEngine::Exit()
{
    delete m_MaterialLibrary;
    delete m_ShaderLibrary;
    delete m_MeshLibrary;
    delete m_TextureLibrary;
    delete m_Renderer;
    CBTManaged::ClearReleasePool();

    delete m_Window;
    m_Window = nullptr;
}

NS_CBT_END

#endif // CBT_OPENGL