// Copyright 2001-2016 Crytek GmbH / Crytek Group. All rights reserved.

#include "StdAfx.h"
#include "IResourceSelectorHost.h"
#include "QParentWndWidget.h"
#include "ListSelectionDialog.h"
#include "SystemControlsEditorIcons.h"
#include "AudioControlsEditorPlugin.h"
#include "ResourceSelectorDialog.h"
#include <CryGame/IGameFramework.h>
#include <IEditor.h>

using namespace ACE;

namespace
{
dll_string ShowSelectDialog(const SResourceSelectorContext& context, const char* szPreviousValue, const EItemType controlType)
{
	CAudioAssetsManager* pAssetsManager = CAudioControlsEditorPlugin::GetAssetsManager();
	CRY_ASSERT(pAssetsManager);

	QParentWndWidget parent(context.parentWindow);
	parent.center();
	parent.setWindowModality(Qt::ApplicationModal);

	CResourceSelectorDialog dialog(&parent, controlType);

	char* szLevelName;
	gEnv->pGameFramework->GetEditorLevel(&szLevelName, nullptr);
	dialog.SetScope(pAssetsManager->GetScope(szLevelName));
	return dialog.ChooseItem(szPreviousValue);
}

dll_string AudioTriggerSelector(const SResourceSelectorContext& context, const char* szPreviousValue)
{
	return ShowSelectDialog(context, szPreviousValue, EItemType::Trigger);
}

dll_string AudioSwitchSelector(const SResourceSelectorContext& context, const char* szPreviousValue)
{
	return ShowSelectDialog(context, szPreviousValue, EItemType::Switch);
}

dll_string AudioSwitchStateSelector(const SResourceSelectorContext& context, const char* szPreviousValue)
{
	return ShowSelectDialog(context, szPreviousValue, EItemType::State);
}

dll_string AudioParameterSelector(const SResourceSelectorContext& context, const char* szPreviousValue)
{
	return ShowSelectDialog(context, szPreviousValue, EItemType::Parameter);
}

dll_string AudioEnvironmentSelector(const SResourceSelectorContext& context, const char* szPreviousValue)
{
	return ShowSelectDialog(context, szPreviousValue, EItemType::Environment);
}

dll_string AudioPreloadRequestSelector(const SResourceSelectorContext& context, const char* szPreviousValue)
{
	return ShowSelectDialog(context, szPreviousValue, EItemType::Preload);
}

REGISTER_RESOURCE_SELECTOR("AudioTrigger", AudioTriggerSelector, "")
REGISTER_RESOURCE_SELECTOR("AudioSwitch", AudioSwitchSelector, "")
REGISTER_RESOURCE_SELECTOR("AudioSwitchState", AudioSwitchStateSelector, "")
REGISTER_RESOURCE_SELECTOR("AudioRTPC", AudioParameterSelector, "")
REGISTER_RESOURCE_SELECTOR("AudioEnvironment", AudioEnvironmentSelector, "")
REGISTER_RESOURCE_SELECTOR("AudioPreloadRequest", AudioPreloadRequestSelector, "")
}