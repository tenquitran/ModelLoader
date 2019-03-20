#pragma once


namespace ModelLoaderApp
{
    class PMaterial
    {
    public:
        // Parameters: info - data about the material;
        //             programId - GLSL program ID.
        PMaterial(const PMaterialInfo& info, GLuint programId);

        virtual ~PMaterial();

        GLuint getDiffuseTextureId() const;

#if 0
    private:
        Material(const Material&) = delete;
        Material& operator=(const Material&) = delete;
#endif

    private:
        // Parameters: texDiffusePath - path to the diffuse texture file;
        //             programId - GLSL program ID.
        bool initialize(const std::string& texDiffusePath, GLuint programId);

    private:
        // Name of the material.
        const std::string m_name;

        // Diffuse texture ID.
        GLuint m_texDiffuseId = {};

        // Diffuse texture sampler.
        GLint m_texDiffuseSampler = {};
    };
}
