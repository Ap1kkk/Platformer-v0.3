#include "ExitedGameState.h"

ExitedGameState::ExitedGameState(SharedContext context) : sharedContext(context)
{
	SetStateType(GameStateType::Exited);
}

void ExitedGameState::EnterState()
{
	Debug::Log("Entered Paused state");
	//TODO ������ ���������� ��������� ���� � ������� ������
}

void ExitedGameState::Update()
{

}

void ExitedGameState::LeaveState()
{
	Debug::Log("Leaving Paused state");
}
