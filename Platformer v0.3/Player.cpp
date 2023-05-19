#include "Player.h"

Player::Player()
{
	Debug::LogInfo("Created with id: " + std::to_string(entityId), typeid(*this).name());

}

void Player::Awake()
{
	AddSpriteComponent(drawLayer);
	SetTextureRect(playerTexture, sf::IntRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT));

	MakePhysical();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(spawnPosition.x, spawnPosition.y);
	physicComponent->SetBodyDef(bodyDef);
	physicComponent->InitializeBody();

	b2PolygonShape boxShape;
	//b2Vec2 size = GetSpriteBoxHalfSize();
	boxShape.SetAsBox(12 , 42);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1.f;
	boxFixtureDef.friction = 1.f;
	boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::Player));

	physicComponent->AddFixture(boxFixtureDef);
	body = physicComponent->GetBody();
	//body->SetFixedRotation(true);
	camera = AddComponent<Camera>();
	 
	jumpSensor = AddComponent<JumpSensor>();
	jumpSensor->SetPhysicComponent(physicComponent);
	jumpSensor->SetOffset(sf::Vector2f(0, 42));

	playerMovement = AddComponent<PlayerMovement>();
	playerMovement->SetBody(body);
	playerMovement->SetJumpSensor(jumpSensor);

	attackSensor = AddComponent<AttackSensor>();
	attackSensor->SetPhysicComponent(physicComponent);
	attackSensor->SetOffset(sf::Vector2f(-21.f, 0.f));


	animator = AddComponent<Animator>();
	
	auto animIdle = new Animation(true, 0.2f);
	animIdle->SetDrawableSpriteComponent(drawableSpriteComponent);

	animIdle->AddFrame(sf::IntRect(FRAME_WIDTH * 0, FRAME_HEIGHT * 0, FRAME_WIDTH, FRAME_HEIGHT));
	animIdle->AddFrame(sf::IntRect(FRAME_WIDTH * 1, FRAME_HEIGHT * 0, FRAME_WIDTH, FRAME_HEIGHT));
	animIdle->AddFrame(sf::IntRect(FRAME_WIDTH * 2, FRAME_HEIGHT * 0, FRAME_WIDTH, FRAME_HEIGHT));
	animIdle->AddFrame(sf::IntRect(FRAME_WIDTH * 3, FRAME_HEIGHT * 0, FRAME_WIDTH, FRAME_HEIGHT));
	animIdle->AddFrame(sf::IntRect(FRAME_WIDTH * 4, FRAME_HEIGHT * 0, FRAME_WIDTH, FRAME_HEIGHT));
	animIdle->AddFrame(sf::IntRect(FRAME_WIDTH * 5, FRAME_HEIGHT * 0, FRAME_WIDTH, FRAME_HEIGHT));

	animator->AddState<IdlePlayerAnimState>(AnimationType::Idle, animIdle);
	animator->SetInitialState(AnimationType::Idle);


	auto animRun = new Animation(true, 0.2f);
	animRun->SetDrawableSpriteComponent(drawableSpriteComponent);

	animRun->AddFrame(sf::IntRect(FRAME_WIDTH * 0, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));
	animRun->AddFrame(sf::IntRect(FRAME_WIDTH * 1, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));
	animRun->AddFrame(sf::IntRect(FRAME_WIDTH * 2, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));
	animRun->AddFrame(sf::IntRect(FRAME_WIDTH * 3, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));
	animRun->AddFrame(sf::IntRect(FRAME_WIDTH * 4, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));
	animRun->AddFrame(sf::IntRect(FRAME_WIDTH * 5, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));
	animRun->AddFrame(sf::IntRect(FRAME_WIDTH * 6, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));
	animRun->AddFrame(sf::IntRect(FRAME_WIDTH * 7, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));

	animator->AddState<RunPlayerAnimState>(AnimationType::Run, animRun);

	auto animSprint = new Animation(true, 0.1f);
	animSprint->SetDrawableSpriteComponent(drawableSpriteComponent);

	animSprint->AddFrame(sf::IntRect(FRAME_WIDTH * 0, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));
	animSprint->AddFrame(sf::IntRect(FRAME_WIDTH * 1, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));
	animSprint->AddFrame(sf::IntRect(FRAME_WIDTH * 2, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));
	animSprint->AddFrame(sf::IntRect(FRAME_WIDTH * 3, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));
	animSprint->AddFrame(sf::IntRect(FRAME_WIDTH * 4, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));
	animSprint->AddFrame(sf::IntRect(FRAME_WIDTH * 5, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));
	animSprint->AddFrame(sf::IntRect(FRAME_WIDTH * 6, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));
	animSprint->AddFrame(sf::IntRect(FRAME_WIDTH * 7, FRAME_HEIGHT * 1, FRAME_WIDTH, FRAME_HEIGHT));

	animator->AddState<SprintedPlayerAnimState>(AnimationType::Sprint, animSprint);


	auto animJumpRaise = new Animation(false, 0.1f);
	animJumpRaise->SetDrawableSpriteComponent(drawableSpriteComponent);

	animJumpRaise->AddFrame(sf::IntRect(FRAME_WIDTH * 0, FRAME_HEIGHT * 2, FRAME_WIDTH, FRAME_HEIGHT));
	animJumpRaise->AddFrame(sf::IntRect(FRAME_WIDTH * 1, FRAME_HEIGHT * 2, FRAME_WIDTH, FRAME_HEIGHT));
	animJumpRaise->AddFrame(sf::IntRect(FRAME_WIDTH * 2, FRAME_HEIGHT * 2, FRAME_WIDTH, FRAME_HEIGHT));
	animJumpRaise->AddFrame(sf::IntRect(FRAME_WIDTH * 3, FRAME_HEIGHT * 2, FRAME_WIDTH, FRAME_HEIGHT));
	animJumpRaise->AddFrame(sf::IntRect(FRAME_WIDTH * 4, FRAME_HEIGHT * 2, FRAME_WIDTH, FRAME_HEIGHT));

	animator->AddState<JumpRaisedPlayerAnimState>(AnimationType::JumpRaise, animJumpRaise);


	auto animJumpFall = new Animation(false, 0.2f);
	animJumpFall->SetDrawableSpriteComponent(drawableSpriteComponent);

	animJumpFall->AddFrame(sf::IntRect(FRAME_WIDTH * 5, FRAME_HEIGHT * 2, FRAME_WIDTH, FRAME_HEIGHT));
	animJumpFall->AddFrame(sf::IntRect(FRAME_WIDTH * 6, FRAME_HEIGHT * 2, FRAME_WIDTH, FRAME_HEIGHT));
	animJumpFall->AddFrame(sf::IntRect(FRAME_WIDTH * 7, FRAME_HEIGHT * 2, FRAME_WIDTH, FRAME_HEIGHT));

	animator->AddState<JumpFallPlayerAnimState>(AnimationType::JumpFall, animJumpFall);

}
