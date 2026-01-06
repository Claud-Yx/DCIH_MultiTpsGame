// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "YGC_LineVisualizer.generated.h"

/**
 * 2개 점으로 제한된 라인 시각화 컴포넌트
 * 블루프린트 에디터에서 StartPoint/EndPoint를 드래그로 조작 가능
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DCIH_MULTITPSGAME_API UYGC_LineVisualizer : public USplineComponent
{
	GENERATED_BODY()

public:
	UYGC_LineVisualizer();

	// 시작점 월드 좌표
	UFUNCTION( BlueprintCallable, Category="Line Visualizer" )
	FVector GetStartPointWorld() const;

	// 끝점 월드 좌표
	UFUNCTION( BlueprintCallable, Category="Line Visualizer" )
	FVector GetEndPointWorld() const;

	// 시작점 설정 (로컬 좌표)
	UFUNCTION( BlueprintCallable, Category="Line Visualizer" )
	void SetStartPoint(const FVector& NewLocation);

	// 끝점 설정 (로컬 좌표)
	UFUNCTION( BlueprintCallable, Category="Line Visualizer" )
	void SetEndPoint(const FVector& NewLocation);

	// TraceHit 결과 저장 (디버그용)
	UFUNCTION( BlueprintCallable, Category="Line Visualizer" )
	void SetTraceHit(const FHitResult& Hit);

protected:
	virtual void OnRegister() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	// 런타임 디버그 시각화 옵션
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category="Line Visualizer|Debug" )
	bool bEnableDebugDraw = false;

	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category="Line Visualizer|Debug" )
	float DebugPointSize = 10.f;

	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category="Line Visualizer|Debug" )
	float DebugLineThickness = 2.f;

private:
	// 점 개수를 2개로 고정
	void EnsureTwoPoints();

	FHitResult TraceHit{};
};
