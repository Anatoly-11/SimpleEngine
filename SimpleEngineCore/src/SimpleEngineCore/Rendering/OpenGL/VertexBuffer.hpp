#pragma once

namespace SimpleEngine {

  class VertexBuffer {
  public:
    VertexBuffer(const VertexBuffer &) = delete;
    VertexBuffer &operator=(const VertexBuffer &) = delete;
    enum class EUsage {
      Static,
      Dynamic,
      Stream
    };

    VertexBuffer(const void *data, const size_t size, const EUsage usage = VertexBuffer::EUsage::Static) noexcept;
   ~VertexBuffer() noexcept;
    VertexBuffer &operator=(VertexBuffer &&vertexBuffer) noexcept;
    VertexBuffer(VertexBuffer &&vertexBuffer) noexcept;

    void bind() const noexcept;
    static void unbind() noexcept;

  private:
    unsigned int m_id;
  };

}