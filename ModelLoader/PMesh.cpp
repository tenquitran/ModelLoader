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

#if 0
void PMesh::addMeshPart(const std::string& materialName, size_t firstIndex)
{
    m_meshParts.push_back(PMeshPart(materialName, firstIndex));
}
#endif

bool PMesh::initialize(const PMeshData& data)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Set up the vertex buffer.

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, data.m_vertices.size() * sizeof(data.m_vertices[0]), &data.m_vertices[0], GL_STATIC_DRAW);

    // Fill in the vertex position attribute.
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    // Set up the index buffer.

    m_indexCount = data.m_indices.size();

    glGenBuffers(1, &m_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.m_indices.size() * sizeof(data.m_indices[0]), &data.m_indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Add parts of the mesh using separate materials.

    // Number of mesh parts.
    const size_t numberOfParts = data.m_meshParts.size();

    // Indices used by all parts of the mesh.
    size_t usedlndices = {};
    
    for (size_t i = {}; i < numberOfParts; ++i)
    {
        if (i + 1 < numberOfParts)
        {
            // Number of indices in the current part of the mesh.
            size_t meshPartIndices = data.m_meshParts[i + 1].m_firstIndex - data.m_meshParts[i].m_firstIndex;

            m_meshParts.emplace_back(PMeshPart(
                data.m_meshParts[i].m_materialName, 
                data.m_meshParts[i].m_firstIndex, 
                meshPartIndices));

            usedlndices += meshPartIndices;
        }
        else
        {
            m_meshParts.emplace_back(PMeshPart(
                data.m_meshParts[i].m_materialName,
                data.m_meshParts[i].m_firstIndex,
                data.m_indices.size() - usedlndices));    /* the last part of the mesh uses all the remaining indices */
        }
    }

    return true;
}

void PMesh::render() const
{
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);

    // Render each part of the mesh using the corresponding material.
    for (const auto& part : m_meshParts)
    {
        // TODO: use the material
        glDrawElements(GL_TRIANGLES, part.getIndexCount(), GL_UNSIGNED_INT, (const GLvoid *)(part.getFirstIndex() * sizeof(GLuint)));
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
