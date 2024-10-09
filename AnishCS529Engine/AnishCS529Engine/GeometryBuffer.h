//#pragma once
//#include <glad/glad.h>
//#include <vector>
//#include <unordererd_map>
//#include <memory>
//#include <string>
//
//
//class GeometryBuffer {
//public:
//	// We define in this class each attribute as vector.
//	enum class Attribute {
//		Position,
//		Normal,
//		TexCoord,
//		Color,
//		Tangent,
//		Bitangent
//	};
//
//	struct AttributeInfo {
//		GLint				size;
//		GLenum			type;
//		GLboolean		normalized;
//		GLsizei			stride;
//	};
//
//	static std::shared_ptr<GeometryBuffer> create(
//		const std::unordered_map<Attribute, std::pair<std::vector<float>, AttributeInfo>>& attrinbuteData,
//		const std::vector<unsigned int>& indices,
//		const 
//	)
//
//	~GeometryBuffer();
//
//	// Prevent copying
//	GeometryBuffer(const GeometryBuffer&) = delete;
//	GeometryBuffer& operator=(const GeometryBuffer&) = delete;
//
//private:
//	GeometryBuffer();
//
//	void initializeBuffers()
//};
//
//GeometryBuffer ::GeometryBuffer()
//{
//}
//
//GeometryBuffer ::~GeometryBuffer()
//{
//}
