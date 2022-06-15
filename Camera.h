#pragma once
#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

class Camera
{
public:
	Camera();
	Camera(int w, int h);
	void control(GLFWwindow* window);
	glm::mat4 getMatrix();

public:
	int m_width;
	int m_height;
	float m_speed = 0.02;
	float m_speed_change = 1e-3;
	float m_angle_change = 100.;
	float m_fov = 45;
	float m_near = 0.1;
	float m_far = 100;
	glm::vec3 m_position = glm::vec3(0.0f, 1.0f, 5.0f);
	glm::vec3 m_orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	
	bool m_mouse_released = true;
	glm::vec2 m_click_pos = glm::vec2(0.f, 0.f);

};

