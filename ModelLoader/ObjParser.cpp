#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace CommonLibOgl;
using namespace ModelLoaderApp;

//////////////////////////////////////////////////////////////////////////


ObjParser::ObjParser()
{
}

ObjParser::~ObjParser()
{
}

bool ObjParser::parse(const CAtlString& filePath, PModel& model)
{
    int pos = filePath.ReverseFind('\\');
    if (-1 == pos)
    {
        std::wcerr << L"Invalid path format: " << filePath.GetString() << '\n';
        ATLASSERT(FALSE); return false;
    }

    m_modelDirectory = CT2A(filePath.Left(pos));

    std::ifstream file(filePath.GetString());

    std::string line;

    if (!file.is_open())
    {
        wchar_t msg[256];
        _wcserror_s(msg, _countof(msg), errno);

        std::wcerr << L"Failed to open file \"" << filePath.GetString() << ": " << msg << '\n';
        ATLASSERT(FALSE); return false;
    }

    Meshes meshes;
    Materials materials;

    while (getline(file, line))
    {
        parseLine(line, meshes, materials);
    }

    if (!model.initialize(meshes, materials))
    {
        std::wcerr << L"Model initialization failed\n";
        return false;
    }

    file.close();

    return true;
}

bool ObjParser::parseLine(const std::string& line, Meshes& meshes, Materials& materials)
{
    if (line.empty())
        {return true;}
    
    std::istringstream ss(line);

    // Line contents parsed to space-separated tokens.
    std::vector<std::string> contents(
        (std::istream_iterator<std::string>(ss)),
        std::istream_iterator<std::string>());

    if ("#" == contents[0])    // comment
    {
        return true;
    }
    else if ("v" == contents[0])    // vertex coordinates
    {
        parseVertexCoords(contents, meshes);
    }
    else if ("vt" == contents[0])    // texture coordinates
    {
        parseTextureCoords(contents, meshes);
    }
    else if ("vn" == contents[0])    // vertex normal
    {
        if (!m_newMesh)
        {
            m_newMesh = true;
        }

        // TODO: implement
        ;
    }
    else if ("f" == contents[0])    // polygonal face element (face index/texture coordinate/normal index)
    {
        parseFaceElements(contents, meshes);
    }
    else if ("mtllib" == contents[0])
    {
        if (!readMaterialInfo(contents, materials))
        {
            return false;
        }
    }
    else if ("usemtl" == contents[0])
    {
        // Add new part of the mesh using the specified material.
        
        if (contents.size() < 2)
        {
            std::wcerr << L"usemtl: no material name\n";
            ATLASSERT(FALSE); return false;
        }
#if 1
        // TODO: add PMeshPartInfo to PMeshData;
        // call PMeshPartInfo::increaseIndexCount() on each subsequent "f" until encountering another "usemtl"
        meshes[m_currentMeshId].m_meshParts.emplace_back(PMeshPartInfo(contents[1], m_meshPartIndex));
#else
        // TODO: call addMeshPart() here 
        // and PMeshPart::increaseIndexCount() on each subsequent "f" until encountering another "usemtl"
#endif
        ;
    }
#if 0     // TODO: parse other data as required
    else if ()
    {
    }
    else if ()
    {
    }
#endif

    return true;
}

void ObjParser::parseVertexCoords(const std::vector<std::string>& tokens, Meshes& meshes)
{
    if (tokens.size() < 4)
    {
        ATLASSERT(FALSE); throw EXCEPTION(L"Invalid number of vertex coordinates");
    }

    if (m_newMesh)
    {
        meshes.insert(std::make_pair(++m_currentMeshId, PMeshData()));

        m_newMesh = false;
    }

    glm::vec4 vertex = {
        atof(tokens[1].c_str()),
        atof(tokens[2].c_str()),
        atof(tokens[3].c_str()),
        1.0f };

    if (tokens.size() > 4)
    {
        vertex.w = atof(tokens[4].c_str());
    }

    meshes[m_currentMeshId].m_vertices.push_back(vertex);
}

void ObjParser::parseFaceElements(const std::vector<std::string>& tokens, Meshes& meshes)
{
    if (!m_newMesh)
    {
        m_newMesh = true;
    }

    if (tokens.size() < 4)
    {
        ATLASSERT(FALSE); throw EXCEPTION(L"Invalid number of face indices");
    }

    // Polygonal face element: face index/texture coordinate/normal index
    // Texture coordinate and normal index are optional.
    // Thus, we should break each part of the line using '/' as a separator.

    size_t count = tokens.size();

    const char delimiter = '/';

    std::vector<GLuint> indices;
    std::vector<GLuint> texCoordIndices;
    std::vector<GLuint> normalIndices;

    std::string item;

    for (size_t i = 1; i < count; ++i)
    {
        std::istringstream ss(tokens[i]);

        int k = 1;

        while (std::getline(ss, item, delimiter))
        {
            switch (k++)
            {
            case 1:
                indices.push_back(atoi(item.c_str()));
                break;
            case 2:
                if (!item.empty())
                {
                    texCoordIndices.push_back(atoi(item.c_str()));
                }
                break;
            case 3:
                if (!item.empty())
                {
                    normalIndices.push_back(atoi(item.c_str()));
                }
                break;
            default:
                break;
            }
        }
    }

    // Add indices to the mode.
    switch (indices.size())
    {
    case 3:    // triangle: add as is
        for (const auto& ind : indices)
        {
            meshes[m_currentMeshId].m_indices.push_back(ind - 1);

            ++m_meshPartIndex;
        }
        break;
    case 4:    // quadrilateral: the order is 0, 1, 2 for the first triangle and 0, 2, 3 for the second one
        for (size_t m = {}; m < 3; ++m)
        {
            meshes[m_currentMeshId].m_indices.push_back(indices[m] - 1);

            ++m_meshPartIndex;
        }

        meshes[m_currentMeshId].m_indices.push_back(indices[0] - 1);
        ++m_meshPartIndex;

        meshes[m_currentMeshId].m_indices.push_back(indices[2] - 1);
        ++m_meshPartIndex;

        meshes[m_currentMeshId].m_indices.push_back(indices[3] - 1);
        ++m_meshPartIndex;
        break;
    default:
        // TODO: how to handle this?
        ATLASSERT(FALSE); break;
    }
}

void ObjParser::parseTextureCoords(const std::vector<std::string>& tokens, Meshes& meshes)
{
    if (!m_newMesh)
    {
        m_newMesh = true;
    }

    if (tokens.size() < 2)
    {
        ATLASSERT(FALSE); throw EXCEPTION(L"Invalid number of texture coordinates");
    }

    glm::vec3 texCoord = {
        atof(tokens[1].c_str()),
        0.0f,
        0.0f };

    if (tokens.size() > 2)
    {
        texCoord.y = atof(tokens[2].c_str());
    }

    if (tokens.size() > 3)
    {
        texCoord.y = atof(tokens[3].c_str());
    }

    meshes[m_currentMeshId].m_texCoords.push_back(texCoord);
}

bool ObjParser::readMaterialInfo(const std::vector<std::string>& tokens, Materials& materials)
{
    if (tokens.size() < 2)
    {
        ATLASSERT(FALSE); throw EXCEPTION(L"Invalid number of material data items");
    }

    std::string fileName = tokens[1];

    CAtlString filePath;
    filePath.Format(L"%S\\%S", m_modelDirectory.c_str(), fileName.c_str());

    std::ifstream file(filePath.GetString());

    std::string line;

    if (!file.is_open())
    {
        wchar_t msg[256];
        _wcserror_s(msg, _countof(msg), errno);

        std::wcerr << L"Failed to open file \"" << filePath.GetString() << ": " << msg << '\n';
        ATLASSERT(FALSE); return false;
    }

    // TODO: add material to the mesh using m_currentMeshId.
    // We'll probably need to refer to a mesh (via the model) instead of storing data in MeshData (to avoid copying textures, etc.).
#if 0
    // Currently, the key is the material name.
    std::map<std::string, Material> materials;
#endif

    std::string currentMaterial;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::istringstream ss(line);

        std::vector<std::string> tokens(
            (std::istream_iterator<std::string>(ss)),
            std::istream_iterator<std::string>());

        if ("newmtl" == tokens[0])    // material name
        {
            if (tokens.size() < 2)
            {
                std::wcerr << L"No material name\n";
                ATLASSERT(FALSE); return false;
            }

            currentMaterial = tokens[1];

            materials.emplace(std::make_pair(currentMaterial, PMaterialInfo(currentMaterial)));
        }
        else if ("map_Kd" == tokens[0])    // diffuse texture name
        {
            if (tokens.size() < 2)
            {
                std::wcerr << L"No diffuse texture name\n";
                ATLASSERT(FALSE); return false;
            }

            materials[currentMaterial].m_texDiffusePath = m_modelDirectory + '\\' + tokens[1];
        }
        // TODO: read other data
#if 0
        else if ()
        {
        }
#endif
    }

    file.close();

    return true;
}
