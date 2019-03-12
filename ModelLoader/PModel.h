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

        // Get mesh (constant and non-constant versions).
        // Parameters: meshId - unique ID of the mesh.
        // Throws: Exception.
        PMesh& getMesh(MeshId meshId);
        const PMesh& getMeshConst(MeshId meshId) const;

        bool initialize(const Meshes& meshes);

        void render() const;

        virtual ~PModel();

    private:
        // Name of the model.
        CAtlString m_name;

        // Meshes of the model.
        std::map<MeshId, PMesh> m_meshes;

        // Unique ID of the next mesh.
        MeshId m_nextMeshId = {};
    };
}
