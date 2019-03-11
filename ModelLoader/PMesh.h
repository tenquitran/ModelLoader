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

        // Add vertex coordinates.
        void addVertex(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f);

        // Add vertex index.
        void addIndex(GLuint i);

        virtual ~PMesh();

        // TODO: make private
    public:
    //private:
        // Name of the mesh.
        CAtlString m_name;

        std::vector<glm::vec4> m_vertices;

        std::vector<GLuint> m_indices;
    };
}
