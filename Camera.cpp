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
	} else if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) {
		m_speed -= m_speed_change;
		m_speed = glm::max(m_speed, 0.f);
	} else if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) {
		m_speed += m_speed_change;
	}
}

glm::mat4 Camera::getMatrix() {

	auto view = glm::lookAt(m_position, m_position + m_orientation, m_up);
	auto proj = glm::perspective(glm::radians(m_fov), (float)m_width / m_height, m_near, m_far);
	return proj * view;
}