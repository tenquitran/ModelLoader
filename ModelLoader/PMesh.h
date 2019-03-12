#pragma once


namespace ModelLoaderApp
{
    // Mesh. The prefix "P" is used to avoid name clash with the Mesh class from the CommonLibOgl library.
    class PMesh
    {
    public:
#if 0
        // Parameters: name - name of the mesh.
        explicit PMesh(const CAtlString& name);
#else
        PMesh();
#endif

        void setName(const CAtlString& name);
        CAtlString getName() const;

        bool initialize(const MeshData& data);

        void render() const;

        virtual ~PMesh();

    private:
        // Name of the mesh.
        CAtlString m_name;

        GLuint m_vao = {};
        GLuint m_vbo = {};

        GLuint m_index = {};          // index buffer
        GLsizei m_indexCount = {};    // number of indices
    };
}
