#include "SimpleEngineCore/Camera.hpp"
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace SimpleEngine {

	Camera::Camera(const glm::vec3 &position, const glm::vec3 &rotation, const ProjectionMode projection_mode) noexcept :
		m_position(position), m_rotation(rotation), m_projection_mode(projection_mode), m_update_view_matrix(false) {
		update_view_matrix();
		update_projection_matrix();
	}

	const glm::vec3 &Camera::get_camera_position() const noexcept {
		return m_position;
	}

	const glm::vec3 &Camera::get_camera_rotation() const noexcept {
		return m_rotation;
	}

	void Camera::set_position(const glm::vec3 &position) noexcept {
		m_position = position;
		m_update_view_matrix = true;
	}

	void Camera::set_rotation(const glm::vec3 &rotation) noexcept {
		m_rotation = rotation;
		m_update_view_matrix = true;
	}

	void Camera::set_position_rotation(const glm::vec3 &position, const glm::vec3 &rotation) noexcept {
		m_position = position;
		m_rotation = rotation;
		m_update_view_matrix = true;
	}

	void Camera::set_projection_mode(const ProjectionMode projection_mode) noexcept {
		m_projection_mode = projection_mode;
		update_projection_matrix();
	}

	glm::mat4 Camera::get_view_matrix() noexcept {
		if(m_update_view_matrix) {
			update_view_matrix();
			m_update_view_matrix = false;
		}
		return m_view_matrix;
	}

	glm::mat4 Camera::get_projection_matrix() const  noexcept {
		return m_projection_matrix;
	}

	void Camera::move_forward(const float delta) noexcept {
		m_position += m_direction * delta;
		m_update_view_matrix = true;
	}
	
	void Camera::move_right(const float delta) noexcept {
		m_position += m_right * delta;
		m_update_view_matrix = true;
	}
	
	void Camera::move_up(const float delta) noexcept {
		m_position += s_word_up * delta;
		m_update_view_matrix = true;
	}

	void Camera::add_movement_and_rotation(const glm::vec3& movement_delta, const glm::vec3& rotation_delta) noexcept {
		m_position += m_direction * movement_delta.x;
		m_position += m_right     * movement_delta.y;
		m_position += m_up        * movement_delta.z;
		m_rotation += rotation_delta;
		m_update_view_matrix = true;
	}

	void Camera::update_view_matrix() noexcept {
		//float roll_in_radians  = glm::radians(m_rotation.x);
		//float pitch_in_radians = glm::radians(m_rotation.y);
		//float yaw_in_radians   = glm::radians(m_rotation.z);

		auto sincos = [](const float angle, float *s, float *c) {
			const float a = glm::radians(angle);
			*s = sin(a);
			*c = cos(a);
		};
	
		float s, c;
		sincos(m_rotation.x, &s, &c);
		const glm::mat3 rotate_matrix_x(
		 1,  0,  0,
		 0,  c,  s,
		 0, -s,  c
		);

		sincos(m_rotation.y, &s, &c);
		const glm::mat3 rotate_matrix_y(
		 c, 0, -s,
		 0, 1,  0,
		 s, 0,  c
		);

		sincos(m_rotation.z, &s, &c);
		const glm::mat3 rotate_matrix_z(
		 c, s, 0,
		-s, c, 0,
		 0, 0, 1
		);

		const glm::mat3 euler_rotate_matrix = rotate_matrix_z * rotate_matrix_y * rotate_matrix_x;

		m_direction = glm::normalize(euler_rotate_matrix * s_word_forward);
		m_right     = glm::normalize(euler_rotate_matrix * s_word_right);
		m_up        = glm::cross(m_right, m_direction);

		m_view_matrix = glm::lookAt(m_position, m_position + m_direction, m_up);
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