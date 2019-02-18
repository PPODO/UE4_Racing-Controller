// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class HANSEI_CONTROLLEREditorTarget : TargetRules
{
	public HANSEI_CONTROLLEREditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "HANSEI_CONTROLLER" } );
	}
}
