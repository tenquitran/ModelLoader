#pragma once


namespace ModelLoaderApp
{
    class PMaterial
    {
    public:
        explicit PMaterial(const PMaterialInfo& info);

        virtual ~PMaterial();

#if 0
    private:
        Material(const Material&) = delete;
        Material& operator=(const Material&) = delete;
#endif

    private:
        // Parameters: texDiffusePath - path to the diffuse texture file.
        bool initialize(const std::string& texDiffusePath);

    private:
        // Name of the material.
        const std::string m_name;

        // Diffuse texture ID.
        GLuint m_texDiffuseId = {};

        // Diffuse texture sampler.
        GLint m_texDiffuseSampler = {};
    };
}
