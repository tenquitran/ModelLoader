#pragma once


namespace ModelLoaderApp
{
    // Data about a part of the mesh that uses the specified material 
    // (there can be several such parts in the same OBJ file).
    struct PMeshPartInfo
    {
    public:
        PMeshPartInfo(const std::string& materialName, size_t firstIndex)
            : m_materialName(materialName), m_firstIndex(firstIndex)
        {
            if (m_materialName.empty())
            {
                ATLASSERT(FALSE); throw CommonLibOgl::EXCEPTION(L"Empty material name");
            }
        }

#if 0
        void increaseIndexCount()
        {
            ++m_indexCount;
        }
#endif

    public:
        // Name of the material.
        std::string m_materialName;

        // Offset of the first index of the mesh part (relative to the first index of the parent mesh).
        size_t m_firstIndex = {};

#if 0
        // Number of indices in the mesh part.
        size_t m_indexCount = {};
#endif
    };
}
