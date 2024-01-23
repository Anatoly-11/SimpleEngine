#include "SimpleEngineCore/Camera.hpp"
#include "glm/trigonometric.hpp"

namespace SimpleEngine {

	Camera::Camera(const glm::vec3 &position, const glm::vec3 &rotation, const ProjectionMode projection_mode) noexcept :
		m_position(position), m_rotation(rotation), m_projection_mode(projection_mode) {
		update_view_matrix();
		update_projection_matrix();
	}

	void Camera::set_position(const glm::vec3 &position) noexcept {
		m_position = position;
		update_view_matrix();
	}

	void Camera::set_rotation(const glm::vec3 &rotation) noexcept {
		m_rotation = rotation;
	}

	void Camera::set_position_rotation(const glm::vec3 &position, const glm::vec3 &rotation) noexcept {
		m_position = position;
		m_rotation = rotation;
		update_view_matrix();
	}

	void Camera::set_projection_mode(const ProjectionMode projection_mode) noexcept {
		m_projection_mode = projection_mode;
		update_projection_matrix();
	}

	glm::mat4 Camera::get_view_matrix() const noexcept {
		return m_view_matrix;
	}

	glm::mat4 Camera::get_projection_matrix() const  noexcept {
		return m_projection_matrix;
	}

	void Camera::update_view_matrix() noexcept {
		auto sincos = [](const float angle, float *s, float *c) {
			*s = sin(glm::radians(-angle));
			*c = cos(glm::radians(-angle));
		};
	
		float s, c;
		sincos(m_rotation.x, &s, &c);
		glm::mat4 rotate_matrix_x(
		 1,  0, 0, 0,
		 0,  c, s, 0,
		 0, -s, c, 0,
		 0,  0, 0, 1
		);

		sincos(m_rotation.y, &s, &c);
		glm::mat4 rotate_matrix_y(
		 c, 0, s, 0,
		 0, 1, 0, 0,
		-s, 0, c, 0,
		 0, 0, 0, 1
		);

		sincos(m_rotation.z, &s, &c);
		glm::mat4 rotate_matrix_z(
		 c, s, 0, 0,
		-s, c, 0, 0,
		 0, 0, 1, 0,
		 0, 0, 0, 1
		);

		glm::mat4 translate_matrix(
		 1, 0, 0, 0,
		 0, 1, 0, 0,
		 0, 0, 1, 0,
		 -m_position[0], -m_position[1], -m_position[2], 1
		);

		m_view_matrix = rotate_matrix_z * rotate_matrix_y * rotate_matrix_x * translate_matrix;
	}

	void Camera::update_projection_matrix() noexcept {
		if(m_projection_mode == Camera::ProjectionMode::Perspective) {
			float r = 0.1f;
			float t = 0.1f;
			float f = 10;
			float n = 0.1f;
			m_projection_matrix = glm::mat4(
				n / r, 0, 0, 0,
				0, n / t, 0, 0,
				0, 0, (-f - n) / (f - n), -1,
				0, 0, -2 * f * n / (f - n), 0
			);
		} else if(m_projection_mode == Camera::ProjectionMode::Orthographic) {
			float r = 2;
			float t = 2;
			float f = 100;
			float n = 0.1f;
			m_projection_matrix = glm::mat4(
				1 / r, 0, 0, 0,
				0, 1 / t, 0, 0,
				0, 0, -2 / (f - n), 0,
				0, 0, (-f - n) / (f - n), 1
			);
		}
	}
}