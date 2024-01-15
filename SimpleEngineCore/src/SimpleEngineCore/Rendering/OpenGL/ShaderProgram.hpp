#pragma once

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
    bool isCompiled() const noexcept;//{ return m_isCompiled; }

  private:
    bool m_isCompiled;
    unsigned int m_id;
  };
}