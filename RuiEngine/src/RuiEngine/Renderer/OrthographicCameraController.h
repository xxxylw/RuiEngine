#pragma once

#include "RuiEngine/Renderer/OrthographicCamera.h"
#include "RuiEngine/Core/Timestep.h"

#include "RuiEngine/Events/ApplicationEvent.h"
#include "RuiEngine/Events/MouseEvent.h"

namespace RuiEngine {

	struct OrthographicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(uint32_t width, uint32_t height);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level);

		const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }

	private:
		void CalculateView();

		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCameraBounds m_Bounds;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0, 0, 0 };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 2.0f, m_CameraRotationSpeed = 180.0f;
	};

}