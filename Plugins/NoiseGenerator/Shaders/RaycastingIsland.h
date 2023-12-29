#include "GlobalShader.h"

// This can go on a header or cpp file
class FRaycastingIsland : public FGlobalShader
{
    DECLARE_EXPORTED_SHADER_TYPE(FRaycastingIsland, Global);

    FRaycastingIsland() { }
    FRaycastingIsland(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
        : FGlobalShader(Initializer)
    {
    }

    static bool ShouldCache(EShaderPlatform Platform)
    {
        return true;
    }
};
