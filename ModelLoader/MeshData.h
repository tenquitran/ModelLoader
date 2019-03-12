#pragma once


namespace ModelLoaderApp
{
    // Unique identifier of the mesh.
    typedef int MeshId;


    // Data describing the mesh.
    struct MeshData
    {
    public:
        // Vertex coordinates.
        std::vector<glm::vec4> m_vertices;

        // Vertex indices.
        std::vector<GLuint> m_indices;
    };


    // Data about meshes.
    typedef std::map<MeshId, MeshData> Meshes;
}
