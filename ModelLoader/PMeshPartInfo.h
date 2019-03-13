#pragma once


namespace ModelLoaderApp
{
    // Data about a part of the mesh that uses the specified material 
    // (there can be several such parts in the same OBJ file).
    struct PMeshPartInfo
    {
    public:
        void increaseIndexCount()
        {
            ++m_indexCount;
        }

    public:
        // Name of the material.
        std::string m_materialName;

        // Offset of the first index of the mesh part (relative to the first index of the parent mesh).
        size_t m_firstIndex = {};

        // Number of indices in the mesh part.
        size_t m_indexCount = {};
    };
}
