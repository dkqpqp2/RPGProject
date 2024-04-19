// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectAnimInstance.h"

USelectAnimInstance::USelectAnimInstance()
{
	IsSelect = false;
}

void USelectAnimInstance::AnimNotify_TransitionSelect()
{
	IsSelect = false;
}
