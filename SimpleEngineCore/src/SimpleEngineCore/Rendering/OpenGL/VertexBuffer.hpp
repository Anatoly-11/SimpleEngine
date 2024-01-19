#pragma once

#include <vector>

namespace SimpleEngine {

	enum class ShaderDataType {
		Float,
		Float2,
		Float3,
		Float4,
		Int,
		Int2,
		Int3,
		Int4,
	};

	struct BufferElement {
		ShaderDataType type;
		uint32_t component_type;
		size_t components_count;
		size_t size;
		size_t offset;

		BufferElement(const ShaderDataType type) noexcept;
	};

	class BufferLayout {
	public:
		BufferLayout(std::initializer_list<BufferElement> elements) noexcept;

		const std::vector<BufferElement> &get_elements() const noexcept;
		size_t get_stride() const noexcept;

	private:
		std::vector<BufferElement> m_elements;
		size_t m_stride;
	};



	class VertexBuffer {
	public:
		VertexBuffer(const VertexBuffer &) = delete;
		VertexBuffer &operator=(const VertexBuffer &) = delete;
		enum class EUsage {
			Static,
			Dynamic,
			Stream
		};

		VertexBuffer(const void *data, const size_t size, BufferLayout buffer_layout, const EUsage usage =
			VertexBuffer::EUsage::Static) noexcept;

		~VertexBuffer() noexcept;
		VertexBuffer &operator=(VertexBuffer &&vertexBuffer) noexcept;
		VertexBuffer(VertexBuffer &&vertexBuffer) noexcept;

		void bind() const noexcept;
		static void unbind() noexcept;

		const BufferLayout &get_layout() const noexcept;

	private:
		unsigned int m_id;
		BufferLayout m_buffer_layout;
	};

}