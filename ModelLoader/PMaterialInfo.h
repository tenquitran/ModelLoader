#pragma once


namespace ModelLoaderApp
{
    struct PMaterialInfo
    {
    public:
        PMaterialInfo() = default;

        explicit PMaterialInfo(const std::string& materialName)
            : m_materialName(materialName)
        {
            if (m_materialName.empty())
            {
                ATLASSERT(FALSE); throw CommonLibOgl::EXCEPTION(L"Empty material name");
            }
        }

    public:
        // Name of the material.
        std::string m_materialName;

        // Full path to the file storing the diffuse texture.
        std::string m_texDiffusePath;

        // TODO: other data (diffuse coefficient, etc.)
    };


    // Data about materials.
    // Key: name of the material.
    typedef std::map<std::string, PMaterialInfo> Materials;
}
