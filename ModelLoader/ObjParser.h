#pragma once


namespace ModelLoaderApp
{
    class ObjParser
    {
    public:
        ObjParser();

        virtual ~ObjParser();

        // Parse the OBJ file.
        // Parameters: filePath - full or partial path to the OBJ file;
        //             model - the resulting model.
        // Returns: true on success, false otherwise.
        bool parse(const CAtlString& filePath, PModel& model);

#if 0
        // Get path to the directory containing the model file.
        const CAtlString getModelDirectory() const;
#endif

    private:
        bool parseLine(const std::string& line, Meshes& meshes, Materials& materials);

        void parseVertexCoords(const std::vector<std::string>& tokens, Meshes& meshes);

        void parseFaceElements(const std::vector<std::string>& tokens, Meshes& meshes);

        void parseTextureCoords(const std::vector<std::string>& tokens, Meshes& meshes);

        bool readMaterialInfo(const std::vector<std::string>& tokens, Materials& materials);

    private:
        // true when we need to add new mesh to the model.
        bool m_newMesh = { true };

        // Unique ID of the current mesh.
        MeshId m_currentMeshId = { -1 };

        // Path to the directory containing the model file.
        std::string m_modelDirectory;

        // Number of the current index in the mesh.
        // Used to track indices for parts of the mesh.
        size_t m_meshPartIndex = {};
    };
}
