#include "Camera.h"

void Camera::Awake()
{
	window = objectContext.window;
	auto gameObject = EntityManager::GetEntityById<GameObject>(ownerId);
	transform = gameObject->GetComponent<TransformComponent>();
}

void Camera::LateUpdate()
{
	sf::View view = window->GetView();
	const sf::Vector2f& tragetPosition = transform->GetPosition();
	view.setCenter(tragetPosition.x, tragetPosition.y);
	window->SetView(view);
}
