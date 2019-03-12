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
PModel::PModel()
{
}
#endif

PModel::~PModel()
{
}

void PModel::setName(const CAtlString& name)
{
    m_name = name;
}

CAtlString PModel::getName() const
{
    return m_name;
}

int PModel::addMesh()
{
    int meshId = m_nextMeshId++;

    m_meshes.insert(std::make_pair(meshId, PMesh()));

    return meshId;
}

PMesh& PModel::getMesh(int meshId)
{
    std::map<int, PMesh>::iterator mesh = m_meshes.find(meshId);

    if (m_meshes.cend() == mesh)
    {
        ATLASSERT(FALSE); throw EXCEPTION_FMT(L"Model %s: no mesh with ID = %d", (LPCTSTR)getName(), meshId);
    }

    return mesh->second;
}

const PMesh& PModel::getMeshConst(int meshId) const
{
    std::map<int, PMesh>::const_iterator mesh = m_meshes.find(meshId);

    if (m_meshes.cend() == mesh)
    {
        ATLASSERT(FALSE); throw EXCEPTION_FMT(L"Model %s: no mesh with ID = %d", (LPCTSTR)getName(), meshId);
    }

    return mesh->second;
}

void PModel::addVertex(int meshId, GLfloat x, GLfloat y, GLfloat z, GLfloat w /*= 1.0f*/)
{
#if 1
    PMesh& mesh = getMesh(meshId);
#else
    std::map<int, PMesh>::iterator mesh = m_meshes.find(meshId);

    if (m_meshes.cend() == mesh)
    {
        ATLASSERT(FALSE); throw EXCEPTION_FMT(L"Model %s: no mesh with ID = %d", (LPCTSTR)getName(), meshId);
    }
#endif

    mesh.addVertex(x, y, z, w);
}

void PModel::addIndex(int meshId, GLuint i)
{
#if 1
    PMesh& mesh = getMesh(meshId);
#else
    std::map<int, PMesh>::iterator mesh = m_meshes.find(meshId);

    if (m_meshes.cend() == mesh)
    {
        ATLASSERT(FALSE); throw EXCEPTION_FMT(L"Model %s: no mesh with ID = %d", (LPCTSTR)getName(), meshId);
    }

    mesh->second.addIndex(i);
#endif

    mesh.addIndex(i);
}
