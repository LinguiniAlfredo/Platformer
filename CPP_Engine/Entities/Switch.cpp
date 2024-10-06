#include "Switch.h"
#include "Player.h"
#include "Surface.h"
#include "../Scene.h"
#include "../Components/Collision.h"
#include "../Components/Texture.h"

Switch::Switch(Scene* scene, std::vector<Surface*> switchBlocks, Vec2 currentPosition)
{
	//printf("creating switch\n");

	this->scene = scene;
	this->position = currentPosition;
	texture = on ? new Texture(scene->getRenderer(), onTexture) : new Texture(scene->getRenderer(), offTexture);
	collider = new Collision(scene->getRenderer(), currentPosition.x, currentPosition.y + 1, texture->getWidth(), texture->getHeight());

	this->switchBlocks = switchBlocks;
	for (Surface* block : switchBlocks) {
		scene->addEntity(block);
	}
}

Switch::Switch(Scene* scene, std::vector<Surface*> switchBlocks, std::string color, Vec2 currentPosition)
{
	//printf("creating switch\n");

	this->scene = scene;
	this->position = currentPosition;
	this->color = color;
	onTexture = "resources/textures/switch_" + color + ".png";
	texture = on ? new Texture(scene->getRenderer(), onTexture) : new Texture(scene->getRenderer(), offTexture);
	if (texture == nullptr)
	{
		printf("switch color not supported");
		texture = new Texture(scene->getRenderer(), offTexture);

	}
	collider = new Collision(scene->getRenderer(), currentPosition.x, currentPosition.y + 1, texture->getWidth(), texture->getHeight());

	this->switchBlocks = switchBlocks;
	for (Surface* block : switchBlocks) {
		scene->addEntity(block);
	}
}

Switch::Switch(Scene* scene, std::vector<Surface*> switchBlocks, std::string color, Vec2 currentPosition, bool on)
{
	//printf("creating switch\n");

	this->scene = scene;
	this->position = currentPosition;
	this->color = color;
	this->on = on;
	onTexture = "resources/textures/switch_" + color + ".png";
	texture = on ? new Texture(scene->getRenderer(), onTexture) : new Texture(scene->getRenderer(), offTexture);
	if (texture == nullptr)
	{
		printf("switch color not supported");
		texture = new Texture(scene->getRenderer(), offTexture);

	}
	collider = new Collision(scene->getRenderer(), currentPosition.x, currentPosition.y + 1, texture->getWidth(), texture->getHeight());

	this->switchBlocks = switchBlocks;
	for (Surface* block : switchBlocks) {
		scene->addEntity(block);
	}
}

Switch::~Switch()
{
	//printf("destroying switch\n");

	delete texture;
	texture = nullptr;
	delete collider;
	collider = nullptr;

	if (!switchBlocks.empty()) {
		for (Surface* block : switchBlocks) {
				block = nullptr;
		}
		switchBlocks.clear();
	}
}

void Switch::checkCollisions(float deltaTime)
{
	// Check player leaving collision box for switch so it doesn't happen each frame
	Player* player = dynamic_cast<Player*>(scene->getPlayer());
	if (player != nullptr) {
		if (colliding && !(SDL_HasIntersection(collider->getBox(), player->getCollider()->getBox()) && player->getPosition().y > position.y)) {
			onOff();
		}
		if (SDL_HasIntersection(collider->getBox(), player->getCollider()->getBox()) && player->getPosition().y > position.y) {
			colliding = true;
			setTexture("resources/textures/switch_" + color + "_lit.png");
		}
		else {
			colliding = false;
			setTexture("resources/textures/switch_" + color + ".png");
		}
	}
}

void Switch::onOff()
{
	on = !on;

	if (on) {
		setTexture(onTexture);
		for (Surface* block : switchBlocks) {
			block->setSolid(true);
			block->setTexture("resources/textures/block_" + color + ".png");
		}
	}
	else {
		for (Surface* block : switchBlocks) {
			block->setSolid(false);
			block->setTexture("resources/textures/trans_block_" + color + ".png");
		}
	}

}