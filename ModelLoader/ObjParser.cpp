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
    std::ifstream file(filePath.GetString());

    std::string line;

    if (!file.is_open())
    {
        wchar_t msg[256];
        _wcserror_s(msg, _countof(msg), errno);

        std::wcerr << L"Failed to open file \"" << filePath.GetString() << ": " << msg << '\n';
        ATLASSERT(FALSE); return false;
    }

    while (getline(file, line))
    {
        parseLine(line, model);
    }

    file.close();

    return true;
}

void ObjParser::parseLine(const std::string& line, PModel& model)
{
    if (line.empty())
        {return;}
    
    std::istringstream ss(line);

    // Line contents parsed to space-separated tokens.
    std::vector<std::string> contents(
        (std::istream_iterator<std::string>(ss)),
        std::istream_iterator<std::string>());

    if ("#" == contents[0])    // comment
    {
        return;
    }
    else if ("v" == contents[0])    // vertex coordinates
    {
        parseVertexCoords(contents, model);
    }
    else if ("vt" == contents[0])    // texture coordinates
    {
        if (!m_newMesh)
        {
            m_newMesh = true;
        }

        // TODO: implement
        ;
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
        parseFaceElements(contents, model);
    }
    else if ("mtllib" == contents[0])
    {
        // TODO: implement
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
}

void ObjParser::parseVertexCoords(const std::vector<std::string>& tokens, PModel& model)
{
    if (tokens.size() < 4)
    {
        ATLASSERT(FALSE); throw EXCEPTION(L"Invalid number of vertex coordinates");
    }

    if (m_newMesh)
    {
        m_currentMeshId = model.addMesh();
        m_newMesh = false;
    }

    GLfloat x = atof(tokens[1].c_str());
    GLfloat y = atof(tokens[2].c_str());
    GLfloat z = atof(tokens[3].c_str());

    if (tokens.size() <= 4)
    {
        model.addVertex(m_currentMeshId, x, y, z);
    }
    else
    {
        model.addVertex(m_currentMeshId, x, y, z, atof(tokens[4].c_str()));
    }
}

void ObjParser::parseFaceElements(const std::vector<std::string>& tokens, PModel& model)
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

    // TODO: add texture coordinates and normal indices data to the model
#if 1
    std::vector<GLuint> indices;
    std::vector<GLuint> texCoords;
    std::vector<GLuint> normalIndices;
#endif

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
                //model.addIndex(m_currentMeshId, atoi(item.c_str()));
                indices.push_back(atoi(item.c_str()));
                break;
            case 2:
                if (!item.empty())
                {
                    texCoords.push_back(atoi(item.c_str()));
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
            model.addIndex(m_currentMeshId, ind - 1);
        }
        break;
    case 4:    // quadrilateral: the order is 0, 1, 2 for the first triangle and 0, 2, 3 for the second one
#if 0
        for (const auto& ind : indices)
        {
            model.addIndex(m_currentMeshId, ind);
        }
#else
        for (size_t m = {}; m < 3; ++m)
        {
            model.addIndex(m_currentMeshId, indices[m] - 1);
        }
        model.addIndex(m_currentMeshId, indices[0] - 1);
        model.addIndex(m_currentMeshId, indices[2] - 1);
        model.addIndex(m_currentMeshId, indices[3] - 1);
#endif
        break;
    default:
        // TODO: how to handle this?
        ATLASSERT(FALSE); break;
    }
}
