#pragma once


namespace ModelLoaderApp
{
    class PMaterial
    {
    public:
        explicit PMaterial(const std::string& name);

        virtual ~PMaterial();

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
