#include "Camera.h"

Camera::Camera() : m_width(100), m_height(100) {}

Camera::Camera(int w, int h) : m_width(w), m_height(h) {}

void Camera::control(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		m_position += m_speed * m_orientation;
	} else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		m_position -= m_speed * m_orientation;
	} else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		m_position += m_speed * glm::normalize(glm::cross(m_up, m_orientation));
	} else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		m_position -= m_speed * glm::normalize(glm::cross(m_up, m_orientation));
	} else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		m_position += m_speed * m_up;
	} else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)	{
		m_position -= m_speed * m_up;
	} else if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) {
		m_speed -= m_speed_change;
		m_speed = glm::max(m_speed, 1e-5f);
	} else if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) {
		m_speed += m_speed_change;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		auto pos = glm::vec2(mouseX, mouseY);
		if (m_mouse_released) {
			m_mouse_released = false;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		} else {
			
			auto rot = glm::radians(m_angle_change * (pos - m_click_pos) / glm::vec2(m_width, m_height));
			// auto rot_mat = glm::rotate(glm::mat4(1.f), glm::radians(rot.x), m_up);
			m_orientation = glm::normalize(glm::rotateY(m_orientation, rot.x));
			m_up = glm::normalize(glm::rotateY(m_up, rot.x));

			auto x = glm::cross(m_orientation, m_up);
			// rot_mat = glm::rotate(rot_mat, glm::radians(rot.y), x);
			m_orientation = glm::normalize(glm::rotate(m_orientation, rot.y, x));
			m_up = glm::normalize(glm::rotate(m_up, rot.y, x));
		}
		m_click_pos = pos;

	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_mouse_released = true;
	}
}

glm::mat4 Camera::getMatrix() {

	auto view = glm::lookAt(m_position, m_position + m_orientation, m_up);
	auto proj = glm::perspective(glm::radians(m_fov), (float)m_width / m_height, m_near, m_far);
	return proj * view;
}