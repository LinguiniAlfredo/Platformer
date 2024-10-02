#include "Portal.h"
#include "../Scene.h"
#include "../Components/Collision.h"
#include "../Components/Texture.h"


void Portal::transportEntity(Entity* ent)
{

}

void Portal::setPartner(Portal* partner)
{
	this->partner = partner;
}

Portal* Portal::getPartner()
{
	return partner;
}