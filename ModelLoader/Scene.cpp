#include "stdafx.h"
#include "Scene.h"

//////////////////////////////////////////////////////////////////////////

using namespace CommonLibOgl;
using namespace ModelLoaderApp;

//////////////////////////////////////////////////////////////////////////


Scene::Scene(const glm::vec3& backgroundColor, CameraPtr& spCamera, GLuint programId)
    : m_backgroundColor(backgroundColor), m_spCamera(spCamera), m_programId(programId)
{
}

Scene::~Scene()
{
}

bool Scene::initialize()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_MULTISAMPLE);

    glClearColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, 1.0f);

    if (!initializeContents())
    {
        std::wcerr << L"Failed to initialize scene contents\n";
        return false;
    }

    updateUniforms();

    return true;
}

bool Scene::initializeContents()
{
    // Note: "picture_3.obj" is triangulated while "picture_2.obj" is not.
    //if (!m_objParser.parse(L"E:\\natProgs\\graphics2\\ModelLoader\\ModelLoader\\data\\cube\\cube.obj", m_model))
    //if (!m_objParser.parse(L"E:\\natProgs\\graphics2\\ModelLoader\\ModelLoader\\data\\triangle\\triangle.obj", m_model))
    if (!m_objParser.parse(L"E:\\natProgs\\graphics2\\ModelLoader\\ModelLoader\\data\\picture_2\\picture_2.obj", m_model))
    //if (!m_objParser.parse(L"data\\picture_2\\picture_2.obj", model))
    {
        return false;
    }

    updateUniforms();

    return true;
}

void Scene::updateUniforms() const
{
    // Our shaders don't use the uniforms.
    // The code is left as a reference for more complex projects.
#if 1
    ATLASSERT(m_programId);

    glUseProgram(m_programId);

    // TODO:
    //     1) comment out the uniforms you don't need.
    //     2) correct the uniform locations if required.

    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(m_spCamera->getModelViewProjectionMatrix()));

#if 0
    glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(m_spCamera->getProjectionMatrix()));

    glm::mat4 modelView = m_spCamera->getModelViewMatrix();

    // WARNING: we are using the fact that there are no non-uniform scaling. If this will change, use the entire 4x4 matrix.
    glm::mat3 normal = glm::mat3(glm::transpose(glm::inverse(modelView)));
    //glm::mat3 normal = glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]));

    glUniformMatrix3fv(2, 1, GL_FALSE, glm::value_ptr(normal));

    glUniformMatrix4fv(3, 1, GL_FALSE, glm::value_ptr(modelView));
#endif

    glUseProgram(0);
#endif
}

void Scene::translateCamera(const glm::vec3& diff)
{
    m_spCamera->translate(diff);

    updateUniforms();
}

void Scene::rotateCamera(const glm::vec3& degrees)
{
    m_spCamera->rotate(degrees);

    updateUniforms();
}

GLfloat Scene::getCameraScale() const
{
    return m_spCamera->getScale();
}

void Scene::scaleCamera(GLfloat amount)
{
    m_spCamera->scale(amount);

    updateUniforms();
}

void Scene::resize(GLfloat aspectRatio)
{
    m_spCamera->resize(aspectRatio);

    updateUniforms();
}

void Scene::render() const
{
    ATLASSERT(m_programId);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    updateUniforms();

    glUseProgram(m_programId);

    m_model.render();

    glUseProgram(0);
}
