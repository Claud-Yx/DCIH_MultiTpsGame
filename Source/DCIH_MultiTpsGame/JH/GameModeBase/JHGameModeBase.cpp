#include "JH/GameModeBase/JHGameModeBase.h"
#include "JH/Character/JHCharacter.h"
#include "JH/Controller/JHPlayerController.h"


AJHGameModeBase::AJHGameModeBase()
{
	DefaultPawnClass = AJHCharacter::StaticClass();

	PlayerControllerClass = AJHPlayerController::StaticClass();

	HUDClass = nullptr;

}
