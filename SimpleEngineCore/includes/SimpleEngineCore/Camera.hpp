#pragma once

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
		glm::mat4 get_view_matrix() noexcept;
		glm::mat4 get_projection_matrix() const noexcept;

		void move_forward(const float delta) noexcept;
		void move_right(const float delta) noexcept;
		void move_up(const float delta) noexcept;

		const glm::vec3 &get_camera_position() const noexcept;
		const glm::vec3 &get_camera_rotation() const noexcept;

		// movement_delta.x - forward, movement_delta.y - right, movement_delta.z - up
		// rotation_delta.x - roll, rotation_delta.y - pitch, rotation_delta.z - yaw
		void add_movement_and_rotation(const glm::vec3 &movement_delta, const glm::vec3 &rotation_delta) noexcept;

	private:
		void update_view_matrix() noexcept;
		void update_projection_matrix() noexcept;

		glm::vec3 m_position;
		glm::vec3 m_rotation; // X - Roll, Y -Pitch, Z - Yaw
		ProjectionMode m_projection_mode;

		glm::vec3 m_direction;
		glm::vec3 m_right;
		glm::vec3 m_up;

		static constexpr glm::vec3 s_word_up{0.f, 0.f, 1.f};
		static constexpr glm::vec3 s_word_right{0.f, -1.f, 0.f};
		static constexpr glm::vec3 s_word_forward{1.f, 0.f, 0.f};

		glm::mat4 m_view_matrix;
		glm::mat4 m_projection_matrix;
		bool m_update_view_matrix;
	};
}