#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MagazineWidget.generated.h"



UCLASS()
class DCIH_MULTITPSGAME_API UMagazineWidget : public UUserWidget
{
	GENERATED_BODY()
           
public:
	void Update(int32 MagazineNum);
	
protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_MagazineNum;
	
};
