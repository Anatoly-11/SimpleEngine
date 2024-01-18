
#include "VertexArray.hpp"

#include "SimpleEngineCore/Log.hpp"

#include <glad/glad.h>

namespace SimpleEngine {

  VertexArray::VertexArray() noexcept : m_id(0), m_elements_count(0) {
    glGenVertexArrays(1, &m_id);
  }

  VertexArray::~VertexArray() noexcept {
    glDeleteVertexArrays(1, &m_id);
  }

  VertexArray &VertexArray::operator=(VertexArray &&vertexArray) noexcept {
    m_id = vertexArray.m_id;
    m_elements_count = vertexArray.m_elements_count;
    vertexArray.m_elements_count = 0;
    vertexArray.m_id = 0;
    return *this;
  }

  VertexArray::VertexArray(VertexArray &&vertexArray) noexcept :
    m_id(vertexArray.m_id),
    m_elements_count(vertexArray.m_elements_count) {
    vertexArray.m_elements_count = 0;
    vertexArray.m_id = 0;
  }

  void VertexArray::add_buffer(const VertexBuffer &vertex_buffer) noexcept {
    bind();
    vertex_buffer.bind();

    glEnableVertexAttribArray(m_elements_count);
    glVertexAttribPointer(m_elements_count, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    ++m_elements_count;
  }
  
  void VertexArray::bind() const noexcept {
    glBindVertexArray(m_id);
  }

  void VertexArray::unbind() noexcept {
    glBindVertexArray(0);
  }
}