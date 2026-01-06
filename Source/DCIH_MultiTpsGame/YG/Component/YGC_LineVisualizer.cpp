// Fill out your copyright notice in the Description page of Project Settings.

#include "YGC_LineVisualizer.h"

UYGC_LineVisualizer::UYGC_LineVisualizer()
{
	// Tick 활성화
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	// 스플라인 기본 설정
	SetClosedLoop(false);

	// 직선으로 설정 (곡선 아님)
	SetSplinePointType(0, ESplinePointType::Linear);
	SetSplinePointType(1, ESplinePointType::Linear);
}

void UYGC_LineVisualizer::OnRegister()
{
	Super::OnRegister();
	EnsureTwoPoints();
}

#if WITH_EDITOR
void UYGC_LineVisualizer::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	EnsureTwoPoints();
}
#endif

void UYGC_LineVisualizer::EnsureTwoPoints()
{
	const int32 NumPoints = GetNumberOfSplinePoints();

	if (NumPoints < 2)
	{
		// 점이 부족하면 추가
		ClearSplinePoints();
		AddSplinePoint(FVector::ZeroVector, ESplineCoordinateSpace::Local, false);
		AddSplinePoint(FVector(100.f, 0.f, 0.f), ESplineCoordinateSpace::Local, false);
		UpdateSpline();
	}
	else if (NumPoints > 2)
	{
		// 점이 많으면 2개만 남기고 삭제
		while (GetNumberOfSplinePoints() > 2)
		{
			RemoveSplinePoint(GetNumberOfSplinePoints() - 1, false);
		}
		UpdateSpline();
	}

	// 항상 직선 타입 유지
	SetSplinePointType(0, ESplinePointType::Linear);
	SetSplinePointType(1, ESplinePointType::Linear);
}

FVector UYGC_LineVisualizer::GetStartPointWorld() const
{
	return GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
}

FVector UYGC_LineVisualizer::GetEndPointWorld() const
{
	return GetLocationAtSplinePoint(1, ESplineCoordinateSpace::World);
}

void UYGC_LineVisualizer::SetStartPoint(const FVector& NewLocation)
{
	SetLocationAtSplinePoint(0, NewLocation, ESplineCoordinateSpace::Local, true);
}

void UYGC_LineVisualizer::SetEndPoint(const FVector& NewLocation)
{
	SetLocationAtSplinePoint(1, NewLocation, ESplineCoordinateSpace::Local, true);
}

void UYGC_LineVisualizer::SetTraceHit(const FHitResult& Hit)
{
	TraceHit = Hit;
}

void UYGC_LineVisualizer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bEnableDebugDraw)
	{
		if (UWorld* World = GetWorld())
		{
			const FVector StartWorld = GetStartPointWorld();
			const FVector EndWorld = GetEndPointWorld();

			// Hit 결과에 따라 색상 변경
			const FColor LineColor = TraceHit.bBlockingHit ? FColor::Green : FColor::Red;

			DrawDebugLine(World, StartWorld, EndWorld, LineColor, false, 0.f, 0, DebugLineThickness);
			DrawDebugPoint(World, StartWorld, DebugPointSize, FColor::Blue, false, 0.f);
			DrawDebugPoint(World, EndWorld, DebugPointSize, FColor::Cyan, false, 0.f);
		}
	}
}
