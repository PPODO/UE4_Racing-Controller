// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class HANSEI_CONTROLLERTarget : TargetRules
{
	public HANSEI_CONTROLLERTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "HANSEI_CONTROLLER" } );
	}
}
