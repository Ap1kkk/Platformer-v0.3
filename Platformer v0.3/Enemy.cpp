#include "Enemy.h"

Enemy::Enemy() : Damageble(entityId)
{
	Debug::LogInfo("Created with id: " + std::to_string(entityId), typeid(*this).name());
	
	Entity::SubscribeOnEvent(EventType::OnEnemyMovementRequest);
}

void Enemy::Awake()
{
	AddTextComponent(drawLayer);

	AddSpriteComponent(drawLayer);
	SetTextureRect(enemyTexture, sf::IntRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT));

	MakePhysical();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(spawnPosition.x, spawnPosition.y);
	bodyDef.fixedRotation = true;
	physicComponent->SetBodyDef(bodyDef);
	physicComponent->InitializeBody();


	b2PolygonShape boxShape;
	
	boxShape.SetAsBox(colliderSize.x, colliderSize.y);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	boxFixtureDef.friction = 1;
	boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::Enemy));


	bodyFixture = physicComponent->AddFixture(boxFixtureDef);

	userData = new FixtureUserData;
	userData->damageble = this;
	bodyFixture->SetUserData(userData);

	body = physicComponent->GetBody();

	health = AddComponent<Health>();
	health->SetDrawableComponent(drawableTextComponent);
	health->SetTextOffset(hpOffset);
	health->SetEnemyData(spawnChunkId, spawnOffset);
	if (healthPointsToSet != -1)
	{
		health->SetHealthPoints(healthPointsToSet);
	}

	attackSensor = AddComponent<EnemyAttackSensor>();
	attackSensor->SetPhysicComponent(physicComponent);
	attackSensor->SetOffset(attackSensorOffset);

	animator = AddComponent<Animator>();

	auto animIdle = new Animation(true, 0.2f, entityId);
	animIdle->SetDrawableSpriteComponent(drawableSpriteComponent);

	animIdle->AddFrame(sf::IntRect(FRAME_WIDTH * 0, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));

	animator->AddState<IdleEnemyAnimState>(AnimationType::Idle, animIdle);

	auto animRun = new Animation(true, 0.4f, entityId);
	animRun->SetDrawableSpriteComponent(drawableSpriteComponent);

	animRun->AddFrame(sf::IntRect(FRAME_WIDTH * 1, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));
	animRun->AddFrame(sf::IntRect(FRAME_WIDTH * 2, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));
	animRun->AddFrame(sf::IntRect(FRAME_WIDTH * 3, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));
	animRun->AddFrame(sf::IntRect(FRAME_WIDTH * 4, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));

	animator->AddState<RunEnemyAnimState>(AnimationType::Run, animRun);
	animator->SetInitialState(AnimationType::Run);


	auto animAttack = new Animation(false, 0.1f, entityId);
	animAttack->SetDrawableSpriteComponent(drawableSpriteComponent);

	animAttack->AddFrame(sf::IntRect(FRAME_WIDTH * 0, FRAME_HEIGHT * 0, FRAME_WIDTH, FRAME_HEIGHT));
	animAttack->AddFrame(sf::IntRect(FRAME_WIDTH * 1, FRAME_HEIGHT * 0, FRAME_WIDTH, FRAME_HEIGHT));
	animAttack->AddFrame(sf::IntRect(FRAME_WIDTH * 2, FRAME_HEIGHT * 0, FRAME_WIDTH, FRAME_HEIGHT));
	animAttack->AddFrame(sf::IntRect(FRAME_WIDTH * 3, FRAME_HEIGHT * 0, FRAME_WIDTH, FRAME_HEIGHT));
	animAttack->AddFrame(sf::IntRect(FRAME_WIDTH * 4, FRAME_HEIGHT * 0, FRAME_WIDTH, FRAME_HEIGHT));
	animAttack->AddFrame(sf::IntRect(FRAME_WIDTH * 5, FRAME_HEIGHT * 0, FRAME_WIDTH, FRAME_HEIGHT));

	animator->AddState<AttackEnemyAnimState>(AnimationType::Attack, animAttack);
}

void Enemy::Update()
{
	curentTime += Time::DeltaTime();
	if (isMoving)
	{
		if (curentTime >= movingTime)
		{
			curentTime = 0.f;
			if (faceDirection == FaceDirection::Right)
			{
				faceDirection = FaceDirection::Left;
			}
			else
			{
				faceDirection = FaceDirection::Right;
			}
			isMoving = false;
			{
				EventData data(EventType::OnEnemyTurnedFace);
				data.id = entityId;
				Event::Invoke(data);
			}

			{
				EventData data(EventType::OnEnemyStoppedRunning);
				data.id = entityId;
				Event::Invoke(data);
			}
		}
		else
		{
			auto vel = body->GetLinearVelocity();
			float deltaVel = enemyVelocity - abs(vel.x);
			vel = b2Vec2((short)faceDirection * Time::FixedDeltaTime() * deltaVel, vel.y);
			body->SetLinearVelocity(vel);
		}
	}
	else
	{
		if (curentTime >= idleTime)
		{
			curentTime = 0.f;
			isMoving = true;

			EventData data(EventType::OnEnemyStartedRunning);
			data.id = entityId;
			Event::Invoke(data);
		}
	}
	isRunningData = isMoving;
}
