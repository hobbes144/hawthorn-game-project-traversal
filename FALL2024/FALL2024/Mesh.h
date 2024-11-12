#pragma once
#include "Geometry.h"
#include <vector>
#include <unordered_map>
#include <string>

class Mesh : public Geometry {
public:
	Mesh(const std::string& name);
	~Mesh() = default;

	// Redeclared functions from Geometry
	std::shared_ptr<GeometryBuffer> getGeometryBuffer() const override;
	std::string getType() const override;
	std::unique_ptr<Geometry> clone() const override;

	// Mesh-specific functions
	void setVertexData(const std::shared_ptr<GeometryBuffer>& geometryBuffer);
	void setVertexData(
		const std::vector<VertexData>& vertexData,
		const GLsizei stride,
		const std::vector<unsigned int>& indices);
	void setAttributeData(
		GeometryBuffer::Attribute attr, 
		const std::vector<float>& data, 
		int componentsPerVertex,
		const GLsizei stride);
	void setIndices(const std::vector<unsigned int>& newIndices);
	size_t getVertexCount() const;
	size_t getIndexCount() const;
	bool hasAttribute(GeometryBuffer::Attribute attr) const;
	const std::string& getName() const;

private:
	std::string name;
	std::vector<unsigned int> indices;
};