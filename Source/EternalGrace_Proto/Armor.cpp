// Fill out your copyright notice in the Description page of Project Settings.


#include "Armor.h"

FArmor::FArmor():ThumpNailImage(nullptr),ArmorName("No Armor"),BreastplateMesh(nullptr), bIsHeavyArmor(false), bIsHidingHair(false), bIsHidingFeet(false)
{
	ObjectType = EObjectType::BodyEquipment;
}
