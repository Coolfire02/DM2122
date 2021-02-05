#include "HitBox.h"

HitBox::HitBox(Box* box) : size(1.0f), originalBox(box), thisTickBox(nullptr) {
	/*this->originalHitBoxes.push_back(box);
	hasMultipleBoxes = false;*/
}

HitBox::HitBox() : size(1.0f), originalBox(nullptr), thisTickBox(nullptr) {

}

void HitBox::setOriginalHitBox(Box* box) {
	originalBox = box;
}

bool HitBox::collidedWith(HitBox other) {
	if (this->thisTickBox != nullptr && other.getThisTickBox() != nullptr) {
		if (this->thisTickBox->locIsInBox(other.getThisTickBox()))
			return true;
	}
	return false;
}

Box* HitBox::getOriginalBox() {
	return this->originalBox;
}

Box* HitBox::getThisTickBox() {
	return this->thisTickBox;
}

//HitBox::HitBox(std::vector<Box*> boxes) : size(1.0f) {
//	this->originalHitBoxes = boxes;
//	hasMultipleBoxes = true;
//}

//void HitBox::setHitBox(std::vector<Box*> boxes) {
//	this->originalHitBoxes = boxes;
//}

void HitBox::update(Mtx44 matrix) {
	Mtx44 bot = Mtx44(originalBox->botLeftPos->getX(), originalBox->botLeftPos->getY(), originalBox->botLeftPos->getZ(), 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	Mtx44 top = Mtx44(originalBox->topRightPos->getX(), originalBox->topRightPos->getY(), originalBox->topRightPos->getZ(), 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	if (thisTickBox == nullptr) thisTickBox = new Box(this->originalBox->botLeftPos, this->originalBox->topRightPos);

	bot = matrix * bot;
	thisTickBox->botLeftPos->setX(bot.ValueAtPos(0, 0));
	thisTickBox->botLeftPos->setY(bot.ValueAtPos(1, 0));
	thisTickBox->botLeftPos->setZ(bot.ValueAtPos(2, 0));

	top = matrix * top;
	thisTickBox->topRightPos->setX(bot.ValueAtPos(0, 0));
	thisTickBox->topRightPos->setY(bot.ValueAtPos(1, 0));
	thisTickBox->topRightPos->setZ(bot.ValueAtPos(2, 0));
}

HitBox::~HitBox() {
	delete originalBox;
	delete thisTickBox;
}