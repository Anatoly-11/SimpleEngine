#pragma once
#include "VertexBuffer.hpp"

namespace SimpleEngine {

	class IndexBuffer {
		IndexBuffer(const IndexBuffer &) = delete;
		IndexBuffer &operator=(const IndexBuffer &) = delete;
	public:

		IndexBuffer(const void *data, const size_t count, const VertexBuffer::EUsage usage = VertexBuffer::EUsage::Static) noexcept;
		~IndexBuffer()  noexcept;

		IndexBuffer &operator=(IndexBuffer &&index_buffer) noexcept;
		IndexBuffer(IndexBuffer &&index_buffer) noexcept;

		void bind() const noexcept;
		static void unbind() noexcept;
		size_t get_count() const  noexcept;

	private:
		unsigned int m_id;
		size_t m_count;
	};

}