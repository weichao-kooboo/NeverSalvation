#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "myHUD.generated.h"

UCLASS()
class AmyHUD : public AHUD
{
	GENERATED_BODY()

public:
	AmyHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};