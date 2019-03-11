#pragma once


namespace ModelLoaderApp
{
    class Model
    {
    public:
#if 0
        // Parameters: name - name of the model.
        explicit Model(const CAtlString& name);
#else
        Model();
#endif

        void setName(const CAtlString& name);
        CAtlString getName() const;

        // Add empty mesh to the model.
        // Returns: unique ID of the mesh.
        int addMesh();

        // Add vertex coordinates to the mesh.
        // Parameters: meshId - unique ID of the mesh;
        //             x, y, z, w - vertex coordinates.
        // Exceptions: Exception.
        void addVertex(int meshId, GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f);

        // Add vertex index to the mesh.
        // Parameters: meshId - unique ID of the mesh;
        //             i  - vertex index.
        void addIndex(int meshId, GLuint i);

        virtual ~Model();

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
