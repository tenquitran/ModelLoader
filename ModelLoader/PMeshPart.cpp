#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace CommonLibOgl;
using namespace ModelLoaderApp;

//////////////////////////////////////////////////////////////////////////


PMeshPart::PMeshPart(const std::string& materialName, size_t firstIndex, size_t indexCount)
    : m_materialName(materialName), m_firstIndex(firstIndex), m_indexCount(indexCount)
{
    if (m_materialName.empty())
    {
        ATLASSERT(FALSE); throw EXCEPTION(L"Empty material name");
    }
    else if (m_indexCount < 1)
    {
        ATLASSERT(FALSE); throw EXCEPTION(L"Mesh part: invalid index count");
    }
}

PMeshPart::~PMeshPart()
{
}

size_t PMeshPart::getFirstIndex() const
{
    return m_firstIndex;
}

size_t PMeshPart::getIndexCount() const
{
    return m_indexCount;
}
