#pragma once
#include "VertexBuffer.hpp"

namespace SimpleEngine {

  class VertexArray {
    VertexArray(const VertexArray &) = delete;
    VertexArray &operator=(const VertexArray &) = delete;
  public:
    VertexArray() noexcept;
    ~VertexArray() noexcept;
    VertexArray &operator=(VertexArray &&vertexArray) noexcept;
    VertexArray(VertexArray &&vertexArray) noexcept;

    void add_buffer(const VertexBuffer &vertex_buffer) noexcept;
    void bind() const noexcept;
    static void unbind() noexcept;

  private:
    unsigned int m_id;
    unsigned int m_elements_count;
  };
}