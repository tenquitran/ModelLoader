#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace CommonLibOgl;
using namespace ModelLoaderApp;

//////////////////////////////////////////////////////////////////////////


Material::Material(const std::string& name)
    : m_name(name.c_str())
{
    if (m_name.IsEmpty())
    {
        ATLASSERT(FALSE); throw EXCEPTION(L"Empty material name");
    }
}

Material::~Material()
{
}
