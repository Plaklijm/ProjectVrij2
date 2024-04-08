// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace LocomotionModeTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Grounded)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InAir)
}

namespace StanceTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Standing)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crouching)
}

namespace GaitTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Walking)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sprinting)
}

namespace ActionTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(ChopTree)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EquipLamp)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EquipBook)
}