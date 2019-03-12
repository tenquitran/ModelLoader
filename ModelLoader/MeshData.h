#pragma once


namespace ModelLoaderApp
{
    // Data describing the mesh.
    struct MeshData
    {
    public:
        // Vertex coordinates.
        std::vector<glm::vec4> m_vertices;

        // Vertex indices.
        std::vector<GLuint> m_indices;

        // Texture coordinates.
        std::vector<glm::vec3> m_texCoords;
    };


    // Unique identifier of the mesh.
    typedef int MeshId;

    // Data about meshes.
    typedef std::map<MeshId, MeshData> Meshes;
}
