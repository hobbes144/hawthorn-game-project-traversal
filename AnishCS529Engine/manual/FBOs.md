# Framebuffer Objects

An FBO is used to redirect rendering from the default framebuffer (screen) to 
offscreen textures or renderbuffers.

In our engine, we currently only support output to textures.

One common use of FBOs is to generate shadow maps in the ShadowPass.

## Initialization

When FBOs are initialized, the target textures must also be set up. Any number
of textures may be output to (as supported by the GPU). The resolution of all
the textures will be the same as the viewport size that is set when rendering
to the FBO.

## Usage

FBOs must be bound before being used. Once the render call is done, the FBOs
must be unbound.

Any textures that are populated by the FBO can be used after the render pass.

## Textures

Textures that are populated by the FBOs may be freely created or managed
outside the FBO. During FBO initialization, we must bind these textures to the
FBO using the glFramebufferTexture2D call.

After the FBO is written to in the render pass, the texture can be freely used.

Note that textures that are written to by the FBO are not owned by the FBO.