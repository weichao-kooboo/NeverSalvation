// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class NeverSalvationTarget : TargetRules
{
	public NeverSalvationTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
        ExtraModuleNames.AddRange(new string[] { "LibuvSupport", "SystemInfo" });
        ExtraModuleNames.Add("Logic");
        ExtraModuleNames.Add("NeverSalvation");
	}
}
