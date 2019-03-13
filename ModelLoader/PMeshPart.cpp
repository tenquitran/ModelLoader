#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace CommonLibOgl;
using namespace ModelLoaderApp;

//////////////////////////////////////////////////////////////////////////


PMeshPart::PMeshPart(const std::string& materialName, size_t firstIndex, size_t indexCount)
    : m_material(materialName), m_firstIndex(firstIndex), m_indexCount(indexCount)
{
    if (m_indexCount < 1)
    {
        ATLASSERT(FALSE); throw EXCEPTION(L"Mesh part: invalid index count");
    }
}

PMeshPart::~PMeshPart()
{
}

#if 0
void PMeshPart::increaseIndexCount()
{
    ++m_indexCount;
}
#endif
