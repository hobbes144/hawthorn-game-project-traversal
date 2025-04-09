#include "precompiled.h"
#include "RenderFlags.h"

static std::vector<uint32_t> RenderPassOrder = {
    RenderMask::SkydomePass,
    RenderMask::GBufferPrepass,
    RenderMask::ShadowPass,
    RenderMask::DebugPass,
    RenderMask::LightingPass,
    RenderMask::UIPass
};