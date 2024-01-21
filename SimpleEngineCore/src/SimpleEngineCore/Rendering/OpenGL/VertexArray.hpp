#pragma once
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

namespace SimpleEngine {

	class VertexArray {
		VertexArray(const VertexArray &) = delete;
		VertexArray &operator=(const VertexArray &) = delete;
	public:
		VertexArray() noexcept;
		~VertexArray() noexcept;
		VertexArray &operator=(VertexArray &&vertexArray) noexcept;
		VertexArray(VertexArray &&vertexArray) noexcept;

		void add_vertex_buffer(const VertexBuffer &vertex_buffer) noexcept;
		void set_index_buffer(const IndexBuffer &index_buffer) noexcept;
		void bind() const noexcept;
		static void unbind() noexcept;
		size_t get_indices_count() const noexcept;
	private:
		unsigned int m_id;
		unsigned int m_elements_count;
		size_t m_indices_count;
	};
}