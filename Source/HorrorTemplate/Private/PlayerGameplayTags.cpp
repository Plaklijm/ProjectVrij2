// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameplayTags.h"

namespace LocomotionModeTags
{
	UE_DEFINE_GAMEPLAY_TAG(Grounded, FName{ TEXTVIEW("Player.LocomotionMode.Grounded") })
	UE_DEFINE_GAMEPLAY_TAG(InAir, FName{ TEXTVIEW("Player.LocomotionMode.InAir") })
}

namespace StanceTags
{
	UE_DEFINE_GAMEPLAY_TAG(Standing, FName{ TEXTVIEW("Player.Stance.Standing") })
	UE_DEFINE_GAMEPLAY_TAG(Crouching, FName{ TEXTVIEW("Player.Stance.Crouching") })
}

namespace GaitTags
{
	UE_DEFINE_GAMEPLAY_TAG(Walking, FName{ TEXTVIEW("Player.Gait.Walking") })
	UE_DEFINE_GAMEPLAY_TAG(Sprinting, FName{ TEXTVIEW("Player.Gait.Sprinting") })
}

namespace ActionTags
{
	UE_DEFINE_GAMEPLAY_TAG(ChopTree, FName{ TEXTVIEW("Player.Action.ChopTree") })
	UE_DEFINE_GAMEPLAY_TAG(EquipLamp, FName{ TEXTVIEW("Player.Action.EquipLamp") })
	UE_DEFINE_GAMEPLAY_TAG(EquipBook, FName{ TEXTVIEW("Player.Action.EquipBook") })
}
