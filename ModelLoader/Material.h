#pragma once


namespace ModelLoaderApp
{
    class Material
    {
    public:
        explicit Material(const std::string& name);

        virtual ~Material();

#if 0
    private:
        Material(const Material&) = delete;
        Material& operator=(const Material&) = delete;
#endif

    private:
        // Name of the material.
        const CAtlString m_name;
    };
}
