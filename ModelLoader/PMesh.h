#pragma once


namespace ModelLoaderApp
{
    class PModel;


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

#if 0
        // Add part of the mesh using the separate material.
        // Parameters: materialName - name of the material used by this part of the mesh;
        //             firstIndex - offset of the first index of the mesh part.
        void addMeshPart(const std::string& materialName, size_t firstIndex);
#endif

        bool initialize(const PMeshData& data, const PModel* parentModel);

        void render() const;

        virtual ~PMesh();

#if 0
    private:
        PMesh(const PMesh&) = delete;
        PMesh& operator=(const PMesh&) = delete;
#endif

    private:
        // Name of the mesh.
        CAtlString m_name;

        GLuint m_vao = {};
        GLuint m_vbo = {};

        GLuint m_index = {};          // index buffer
        GLsizei m_indexCount = {};    // number of indices

        GLuint m_texCoord = {};    // texture coordinates buffer

        // Parts of the mesh, each using a separate material.
        std::vector<PMeshPart> m_meshParts;

        const PModel* m_pParentModel = { nullptr };
    };
}
