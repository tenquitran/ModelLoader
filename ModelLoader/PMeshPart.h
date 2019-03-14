#pragma once


namespace ModelLoaderApp
{
    // Part of the mesh that uses a separate material 
    // (there can be several such parts in the same OBJ file).
    class PMeshPart
    {
    public:
        // Parameters: materialName - name of the material used by this part of the mesh;
        //             firstIndex - offset of the first index of the mesh part;
        //             indexCount - number of indices in the mesh part.
        PMeshPart(const std::string& materialName, size_t firstIndex, size_t indexCount);

        virtual ~PMeshPart();

        size_t getFirstIndex() const;

        size_t getIndexCount() const;

    private:
        // Name of the material.
        std::string m_materialName;

        // Offset of the first index of the mesh part (relative to the first index of the parent mesh).
        size_t m_firstIndex = {};

        // Number of indices in the mesh part.
        size_t m_indexCount = {};
    };
}
