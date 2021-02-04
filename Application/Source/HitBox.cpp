#include "HitBox.h"

HitBox::HitBox(Box* box) : size(1.0f), originalBox(box) {
	/*this->originalHitBoxes.push_back(box);
	hasMultipleBoxes = false;*/
}

HitBox::HitBox(Box* box) : size(1.0f), originalBox(nullptr) {

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
	
	bot = matrix * bot;
	originalBox->botLeftPos->setX(bot.ValueAtPos(0, 0));
	originalBox->botLeftPos->setY(bot.ValueAtPos(1, 0));
	originalBox->botLeftPos->setZ(bot.ValueAtPos(2, 0));

	top = matrix * top;
	originalBox->topRightPos->setX(bot.ValueAtPos(0, 0));
	originalBox->topRightPos->setY(bot.ValueAtPos(1, 0));
	originalBox->topRightPos->setZ(bot.ValueAtPos(2, 0));
}

HitBox::~HitBox() {
	delete originalBox;
}