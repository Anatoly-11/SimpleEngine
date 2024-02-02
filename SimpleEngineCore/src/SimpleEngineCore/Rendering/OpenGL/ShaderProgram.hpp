#pragma once
#include "glm//mat4x4.hpp"

namespace SimpleEngine {

  class ShaderProgram {
    ShaderProgram() = delete;
    ShaderProgram(const ShaderProgram &) = delete;
    ShaderProgram &operator=(const ShaderProgram &) = delete;
  public:
    ShaderProgram(const char *vertex_shader_src, const char *fragment_shader_src) noexcept;
    ShaderProgram(ShaderProgram &&shaderProgram) noexcept;
    ShaderProgram &operator=(ShaderProgram &&shaderProgram) noexcept;
    ~ShaderProgram() noexcept;

    void bind() const noexcept;
    static void unbind() noexcept;
    bool is_compiled() const noexcept;
		void set_matrix4(const char *name, const glm::mat4 &matrix) const noexcept;
		void set_int(const char *name, const int value) const noexcept;
  private:
    bool m_isCompiled;
    unsigned int m_id;
  };
}