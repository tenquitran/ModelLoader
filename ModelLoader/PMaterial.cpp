#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace CommonLibOgl;
using namespace ModelLoaderApp;

//////////////////////////////////////////////////////////////////////////


PMaterial::PMaterial(const PMaterialInfo& info, GLuint programId)
    : m_name(info.m_materialName)
{
    if (m_name.empty())
    {
        ATLASSERT(FALSE); throw EXCEPTION(L"Empty material name");
    }
    
    if (!initialize(info.m_texDiffusePath, programId))
    {
        ATLASSERT(FALSE); throw EXCEPTION_FMT(L"Failed to initialize the \"%s\" material", m_name);
    }
}

PMaterial::~PMaterial()
{
    if (0 != m_texDiffuseId)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        glDeleteTextures(1, &m_texDiffuseId);
    }
}

GLuint PMaterial::getDiffuseTextureId() const
{
    return m_texDiffuseId;
}

bool PMaterial::initialize(const std::string& texDiffusePath, GLuint programId)
{
    if (texDiffusePath.empty())
    {
        std::wcerr << L"Empty path to diffuse texture";
        ATLASSERT(FALSE); return false;
    }

    // Load data from the texture file.

    int width = {}, height = {};

    auto del = [](unsigned char* pBuff) {
        SOIL_free_image_data(pBuff);
    };

    std::unique_ptr<unsigned char[], decltype(del)> spData(
        SOIL_load_image(texDiffusePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB));
    if (!spData)
    {
        CAtlString msg;
        msg.Format(L"Failed to load texture %S: %S", texDiffusePath.c_str(), SOIL_last_result());
        std::wcerr << msg.GetString() << '\n';
        ATLASSERT(FALSE); return false;
    }

    // Generate a texture ID and set texture parameters.

    glGenTextures(1, &m_texDiffuseId);
    glBindTexture(GL_TEXTURE_2D, m_texDiffuseId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Copy the texture file data to the texture object.
    glBindTexture(GL_TEXTURE_2D, m_texDiffuseId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, spData.get());

    // For each textures sampler uniform, tell OpenGL to which texture unit it belongs to using glUniform1i().
    // As we have only one texture, it's not necessary (at least with most OpenGL drivers) but useful for clarity.
    // With several textures, it's required.

    m_texDiffuseSampler = glGetUniformLocation(programId, "texDiffuse");
    if (-1 == m_texDiffuseSampler)
    {
        std::wcerr << L"Failed to find diffuse texture sampler\n";
        ATLASSERT(FALSE); return false;
    }

    glUseProgram(programId);

    glUniform1i(m_texDiffuseSampler, 0);

    glUseProgram(0);

    return true;
}
