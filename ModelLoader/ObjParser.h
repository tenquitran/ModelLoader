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

    private:
        void parseLine(const std::string& line, PModel& model);

        void parseVertexCoords(const std::vector<std::string>& tokens, PModel& model);

        void parseFaceElements(const std::vector<std::string>& tokens, PModel& model);

    private:
        // true when we need to add new mesh to the model.
        bool m_newMesh = { true };

        // Unique ID of the current mesh.
        int m_currentMeshId = { -1 };
    };
}
