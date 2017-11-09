#include "Rectangle.h"



Rectangle::Rectangle(int l, int r, int t, int b) : left(l), right(r) , top(t), bottom(b)
{

}

void Rectangle::Translate(int dx, int dy)
{
	left += dx;
	right += dx;
	top += dy;
	bottom += dy;
}

void Rectangle::ClipTo(const Rectangle &other)
{
	if (left < other.left)
		left = other.left;

	if (right > other.right)
		right = other.right;

	if (top < other.top)
		top = other.top;

	if (bottom > other.bottom)
		bottom = other.bottom;
}

bool Rectangle::CompletelyOutside(const Rectangle &other)
{
	if (right > other.left)
		return true;

	if (left > other.right)
		return true;

	if (top > other.bottom)
		return true;

	if (bottom > other.top)
		return true;

	return false;
}

bool Rectangle::CompletelyInside(const Rectangle &other)
{
	if (right < other.left)
		return true;

	if (left < other.right)
		return true;

	if (top < other.bottom)
		return true;

	if (bottom < other.top)
		return true;

	return false;
}


