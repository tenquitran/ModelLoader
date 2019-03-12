#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace CommonLibOgl;
using namespace ModelLoaderApp;

//////////////////////////////////////////////////////////////////////////


#if 0
PMesh::PMesh(const CAtlString& name)
    : m_name(name)
{
    if (m_name.IsEmpty())
    {
        ATLASSERT(FALSE); throw EXCEPTION(L"Empty mesh name");
    }
}
#else
PMesh::PMesh()
{
}
#endif

PMesh::~PMesh()
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

void PMesh::setName(const CAtlString& name)
{
    m_name = name;
}

CAtlString PMesh::getName() const
{
    return m_name;
}

void PMesh::addVertex(GLfloat x, GLfloat y, GLfloat z, GLfloat w /*= 1.0f*/)
{
#if 0
    // TODO: temp. Scale down the mesh.
    m_vertices.push_back(glm::vec4(x / 30.0f, y / 30.0f, z / 30.0f, w));
#else
    m_vertices.push_back(glm::vec4(x, y, z, w));
#endif
}

void PMesh::addIndex(GLuint i)
{
    m_indices.push_back(i);

    // TODO: currently, we cannot process negative indices
    ATLASSERT(i >= 0);
}

bool PMesh::initialize()
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Set up the vertex buffer.

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices[0]), &m_vertices[0], GL_STATIC_DRAW);

    // Fill in the vertex position attribute.
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    // Set up the index buffer.

    m_indexCount = m_indices.size();

    glGenBuffers(1, &m_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(m_indices[0]), &m_indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return true;
}

void PMesh::render() const
{
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);

    //glDrawElements(GL_TRIANGLE_FAN, m_indexCount, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
