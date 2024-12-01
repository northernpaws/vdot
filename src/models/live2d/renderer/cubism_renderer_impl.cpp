#include <CubismFramework.hpp>
#include <Rendering/CubismRenderer.hpp>

#include "cubism_renderer_2d.h"

Live2D::Cubism::Framework::Rendering::CubismRenderer* Live2D::Cubism::Framework::Rendering::CubismRenderer::Create() {
    return CSM_NEW CubismRenderer2D();
}

void Live2D::Cubism::Framework::Rendering::CubismRenderer::StaticRelease() {
}
