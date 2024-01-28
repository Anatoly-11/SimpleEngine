#pragma once

//#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

namespace SimpleEngine {

	class Camera {
	public:
		enum class ProjectionMode {
			Perspective,
			Orthographic
		};

		Camera(const glm::vec3 &position = {0, 0, 0},
					 const glm::vec3 &rotation = {0, 0, 0},
					 const ProjectionMode projection_mode = ProjectionMode::Perspective) noexcept;

		void set_position(const glm::vec3 &position) noexcept;
		void set_rotation(const glm::vec3 &rotation) noexcept;
		void set_position_rotation(const glm::vec3 &position, const glm::vec3 &rotation) noexcept;
		void set_projection_mode(const ProjectionMode projection_mode) noexcept;
		glm::mat4 get_view_matrix() const noexcept;
		glm::mat4 get_projection_matrix() const  noexcept;

	private:
		void update_view_matrix() noexcept;
		void update_projection_matrix() noexcept;

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		ProjectionMode m_projection_mode;
		glm::mat4 m_view_matrix;
		glm::mat4 m_projection_matrix;
	};
}