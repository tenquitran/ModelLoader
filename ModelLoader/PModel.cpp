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

PMesh& PModel::getMesh(MeshId meshId)
{
    std::map<MeshId, PMesh>::iterator mesh = m_meshes.find(meshId);

    if (m_meshes.cend() == mesh)
    {
        ATLASSERT(FALSE); throw EXCEPTION_FMT(L"Model %s: no mesh with ID = %d", (LPCTSTR)getName(), meshId);
    }

    return mesh->second;
}

const PMesh& PModel::getMeshConst(MeshId meshId) const
{
    std::map<MeshId, PMesh>::const_iterator mesh = m_meshes.find(meshId);

    if (m_meshes.cend() == mesh)
    {
        ATLASSERT(FALSE); throw EXCEPTION_FMT(L"Model %s: no mesh with ID = %d", (LPCTSTR)getName(), meshId);
    }

    return mesh->second;
}

bool PModel::initialize(const Meshes& meshes, const Materials& materials)
{
    // Initialize meshes.
    for (const auto& itr : meshes)
    {
        MeshId id = itr.first;

        m_meshes.emplace(std::make_pair(id, PMesh()));

        if (!m_meshes[id].initialize(itr.second))
        {
            std::wcerr << L"Failed to initialize mesh (ID = " << itr.first << '\n';
            ATLASSERT(FALSE); return false;
        }
    }

    // Initialize materials.
    for (const auto& itr : materials)
    {
        m_materials.emplace(std::make_pair(itr.first, PMaterial(itr.second)));
    }

    return true;
}

void PModel::render() const
{
    for (const auto& itr : m_meshes)
    {
        itr.second.render();
    }
}
