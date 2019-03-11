#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace CommonLibOgl;
using namespace ModelLoaderApp;

//////////////////////////////////////////////////////////////////////////


#if 0
Model::Model(const CAtlString& name)
    : m_name(name)
{
    if (m_name.IsEmpty())
    {
        ATLASSERT(FALSE); throw EXCEPTION(L"Empty model name");
    }
}
#else
Model::Model()
{
}
#endif

Model::~Model()
{
}

void Model::setName(const CAtlString& name)
{
    m_name = name;
}

CAtlString Model::getName() const
{
    return m_name;
}

int Model::addMesh()
{
    int meshId = m_nextMeshId++;

    m_meshes.insert(std::make_pair(meshId, PMesh()));

    return meshId;
}

void Model::addVertex(int meshId, GLfloat x, GLfloat y, GLfloat z, GLfloat w /*= 1.0f*/)
{
    std::map<int, PMesh>::iterator mesh = m_meshes.find(meshId);

    if (m_meshes.cend() == mesh)
    {
        ATLASSERT(FALSE); throw EXCEPTION_FMT(L"Model %s: no mesh with ID = %d", (LPCTSTR)getName(), meshId);
    }

    mesh->second.addVertex(x, y, z, w);
}
