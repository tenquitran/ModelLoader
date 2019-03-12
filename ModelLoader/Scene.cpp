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
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    if (0 != m_index)
    {
        glDeleteBuffers(1, &m_index);
    }

    if (0 != m_vbo)
    {
        glDeleteBuffers(1, &m_vbo);
    }

    if (0 != m_vao)
    {
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &m_vao);
    }
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
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // TODO: temp

    //PModel model;

    // Note: "picture_3.obj" is triangulated while "picture_2.obj" is not.
    //if (!m_objParser.parse(L"E:\\natProgs\\graphics2\\ModelLoader\\ModelLoader\\data\\cube\\cube.obj", m_model))
    //if (!m_objParser.parse(L"E:\\natProgs\\graphics2\\ModelLoader\\ModelLoader\\data\\triangle\\triangle.obj", m_model))
    if (!m_objParser.parse(L"E:\\natProgs\\graphics2\\ModelLoader\\ModelLoader\\data\\picture_2\\picture_2.obj", m_model))
    //if (!m_objParser.parse(L"data\\picture_2\\picture_2.obj", model))
    {
        return false;
    }

    // Set up the vertex buffer.

#if 0
#if 0
    // Triangle.
    std::vector<GLfloat> vertices = {
        -0.90f, -0.90f, 0.0f,
         0.85f, -0.90f, 0.0f,
        -0.90f,  0.85f, 0.0f };
#else
    // Cube
    std::vector<GLfloat> vertices = {
        0.036290f, -0.746189f, 1.024370f,
        0.036290f, 1.253811f, 1.024370f,
        0.036290f, -0.746189f, -0.975630f,
        0.036290f, 1.253811f, -0.975630f,
        2.036290f, -0.746189f, 1.024370f,
        2.036290f, 1.253811f, 1.024370f,
        2.036290f, -0.746189f, -0.975630f,
        2.036290f, 1.253811f, -0.975630f };
#endif
#endif

    PMesh& mesh = m_model.getMesh(0);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.m_vertices.size() * sizeof(mesh.m_vertices[0]), &mesh.m_vertices[0], GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

    // Fill in the vertex position attribute.
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    // Set up the index buffer.

#if 0
    // Triangle
#if 0
    std::vector<GLuint> indices = { 0, 1, 2 };
#else
    // Cube.
    std::vector<GLuint> indices = { 
        1, 2, 0,
        3, 6, 2,
        7, 4, 6,
        5, 0, 4,
        6, 0, 2,
        3, 5, 7,
        1, 3, 2,
        3, 7, 6,
        7, 5, 4,
        5, 1, 0,
        6, 4, 0,
        3, 1, 5 };
#endif

    m_indexCount = indices.size();
#else
    //m_indexCount = 12;
    m_indexCount = mesh.m_indices.size();
#endif

    glGenBuffers(1, &m_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.m_indices.size() * sizeof(mesh.m_indices[0]), &mesh.m_indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

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
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);

    //glDrawElements(GL_TRIANGLE_FAN, m_indexCount, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}
