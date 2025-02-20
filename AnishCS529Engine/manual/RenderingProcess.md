# Rendering Process

Below is the call stack for Rendering:
```
SceneGraph::update(deltaTime)
    ├── SceneGraph::updateNode(root, deltaTime)
        ├── GameObject::update(deltaTime)
            ├── Render2D::update(deltaTime)
                ├── Material::setProperty("ViewMatrix", camera->getViewMatrix())
                ├── Material::setProperty("ProjectionMatrix", camera->getProjectionMatrix())
                ├── Material::draw(mesh)
                    ├── RenderGraph::draw(mesh, properties)
                        ├── For each RenderPass:
                            ├── RenderPass::apply(properties, lightStack)
                                ├── Shader::use()
                                ├── RenderPass::applyProperties(properties, materialProperties)
                                ├── Light::applyToShader(shader, lightIndex)
                            ├── Mesh::draw()
                                ├── GeometryBuffer::bind()
                                ├── Renderer::draw()
```
