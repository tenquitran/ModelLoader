#pragma once


namespace ModelLoaderApp
{
    // 3D model. The prefix "P" is used for consistency with PMesh.
    class PModel
    {
    public:
#if 0
        // Parameters: name - name of the model.
        explicit Model(const CAtlString& name);
#else
        PModel();
#endif

        void setName(const CAtlString& name);
        CAtlString getName() const;

        // Add empty mesh to the model.
        // Returns: unique ID of the mesh.
        int addMesh();

        // Get mesh.
        // Parameters: meshId - unique ID of the mesh.
        // Throws: Exception.
        PMesh& getMesh(int meshId);

        // Add vertex coordinates to the mesh.
        // Parameters: meshId - unique ID of the mesh;
        //             x, y, z, w - vertex coordinates.
        // Throws: Exception.
        void addVertex(int meshId, GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f);

        // Add vertex index to the mesh.
        // Parameters: meshId - unique ID of the mesh;
        //             i  - vertex index.
        // Throws: Exception.
        void addIndex(int meshId, GLuint i);

        virtual ~PModel();

    private:
        // Name of the model.
        CAtlString m_name;

        // Meshes of the model.
        // Key: unique ID of the mesh.
        std::map<int, PMesh> m_meshes;

        // Unique ID of the next mesh.
        int m_nextMeshId = {};
    };
}
