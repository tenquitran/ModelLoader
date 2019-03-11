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
    m_vertices.push_back(glm::vec4(x, y, z, w));
}
