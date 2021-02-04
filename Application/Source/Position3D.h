#pragma once
class Position3D
{
	int x, y, z;

public:
	Position3D(int, int, int);
	Position3D();
	~Position3D();

	void setX(int);
	void setY(int);
	void setZ(int);

	int getX();
	int getY();
	int getZ();
};

