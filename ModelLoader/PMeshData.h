#pragma once


namespace ModelLoaderApp
{
    // Data describing the mesh.
    struct PMeshData
    {
    public:
        // Vertex coordinates.
        std::vector<glm::vec4> m_vertices;

        // Vertex indices.
        std::vector<GLuint> m_indices;

        // Texture coordinates.
        std::vector<glm::vec3> m_texCoords;

        // Parts of the mesh, each using a separate material.
        std::vector<PMeshPartInfo> m_meshParts;
    };


    // Unique identifier of the mesh.
    typedef int MeshId;

    // Data about meshes.
    typedef std::map<MeshId, PMeshData> Meshes;
}
