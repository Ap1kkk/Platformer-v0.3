#include "Enemy.h"

Enemy::Enemy() : Damageble(entityId)
{
	Debug::LogInfo("Created with id: " + std::to_string(entityId), typeid(*this).name());
}

void Enemy::Awake()
{
	AddSpriteComponent(drawLayer);
	SetTexture(enemyTexture);

	MakePhysical();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(spawnPosition.x, spawnPosition.y);
	bodyDef.fixedRotation = true;
	physicComponent->SetBodyDef(bodyDef);
	physicComponent->InitializeBody();

	//b2CircleShape circleShape;  
	//circleShape.m_p.Set(0, 0);
	//circleShape.m_radius = 15.f;
	b2PolygonShape boxShape;
	//b2Vec2 size = GetSpriteBoxHalfSize();
	
	boxShape.SetAsBox(colliderSize.x, colliderSize.y);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::Enemy));


	auto fixture = physicComponent->AddFixture(boxFixtureDef);

	userData = new FixtureUserData;
	userData->damageble = this;
	fixture->SetUserData(userData);

	body = physicComponent->GetBody();

	health = AddComponent<Health>();

	attackSensor = AddComponent<EnemyAttackSensor>();
	attackSensor->SetPhysicComponent(physicComponent);
	attackSensor->SetOffset(attackSensorOffset);
}
