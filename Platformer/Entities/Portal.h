#pragma once
#include "Entity.h"

class Portal :
	public Entity
{
public:
	using Entity::Entity;

	void setPartner(Portal* partner);
	Portal* getPartner();

private:
	Portal* partner;
	
	void transportEntity(Entity* ent);
};