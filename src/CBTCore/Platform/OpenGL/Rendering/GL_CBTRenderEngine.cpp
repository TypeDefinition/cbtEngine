// Include CBT
#include "GL_cbtRenderEngine.h"

#ifdef CBT_OPENGL

NS_CBT_BEGIN

cbtRenderEngine* cbtRenderEngine::CreateInstance() { return cbtNew GL_cbtRenderEngine(); }

void GL_cbtRenderEngine::Init(const cbtWindowProperties& _winProp)
{
    // Create Window
    m_Window = cbtWindow::CreateCBTWindow(_winProp);

    // Initialise GLEW (Must be initialised or textures and meshes and whatever fuck shit will fail. Learnt that the hard way when I forgot to initialise it.)
    GLenum initResult = glewInit();
    CBT_ASSERT(initResult == GLEW_OK);

    m_MaterialLibrary = cbtNew cbtLibrary<cbtMaterial>();
    m_ShaderLibrary = cbtNew cbtLibrary<cbtShaderProgram>();
    m_MeshLibrary = cbtNew cbtLibrary<cbtMesh>();
    m_TextureLibrary = cbtNew cbtLibrary<cbtTexture>();
    m_Renderer = cbtNew cbtRenderer();
}

void GL_cbtRenderEngine::Update()
{
    m_Renderer->Update();
}

void GL_cbtRenderEngine::Exit()
{
    delete m_MaterialLibrary;
    delete m_ShaderLibrary;
    delete m_MeshLibrary;
    delete m_TextureLibrary;
    delete m_Renderer;
    cbtManaged::ClearReleasePool();

    delete m_Window;
    m_Window = nullptr;
}

NS_CBT_END

#endif // CBT_OPENGL