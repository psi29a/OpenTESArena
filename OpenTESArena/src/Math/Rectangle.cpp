#include <cassert>

#include "SDL2\SDL.h"

#include "Rectangle.h"
#include "Point.h"

Rectangle::Rectangle(int x, int y, int width, int height)
{
	assert(width >= 0);
	assert(height >= 0);

	this->rect = std::unique_ptr<SDL_Rect>(new SDL_Rect());
	this->rect->x = x;
	this->rect->y = y;
	this->rect->w = width;
	this->rect->h = height;
}

Rectangle::Rectangle(int width, int height)
	: Rectangle(0, 0, width, height) { }

Rectangle::Rectangle()
	: Rectangle(0, 0, 0, 0) { }

Rectangle::Rectangle(const Rectangle &rectangle)
	: Rectangle(rectangle.rect->x, rectangle.rect->y, rectangle.rect->w, rectangle.rect->h) { }

Rectangle::~Rectangle()
{

}

int Rectangle::getWidth() const
{
	return this->rect->w;
}

int Rectangle::getHeight() const
{
	return this->rect->h;
}

int Rectangle::getLeft() const
{
	return this->rect->x;
}

int Rectangle::getRight() const
{
	return this->getLeft() + this->getWidth();
}

int Rectangle::getTop() const
{
	return this->rect->y;
}

int Rectangle::getBottom() const
{
	return this->getTop() + this->getHeight();
}

Point Rectangle::getTopLeft() const
{
	return Point(this->getLeft(), this->getTop());
}

Point Rectangle::getTopRight() const
{
	return Point(this->getRight(), this->getTop());
}

Point Rectangle::getBottomLeft() const
{
	return Point(this->getLeft(), this->getBottom());
}

Point Rectangle::getBottomRight() const
{
	return Point(this->getRight(), this->getBottom());
}

Point Rectangle::getCenter() const
{
	return Point(this->getLeft() + (this->getWidth() / 2),
		(this->getTop() + (this->getHeight() / 2)));
}

bool Rectangle::isEmpty() const
{
	return (this->getLeft() == 0) && (this->getRight() == 0) &&
		(this->getWidth() == 0) && (this->getHeight() == 0);
}

const SDL_Rect *Rectangle::getRect() const
{
	return this->isEmpty() ? nullptr : this->rect.get();
}

void Rectangle::setX(int x)
{
	this->rect->x = x;
}

void Rectangle::setY(int y)
{
	this->rect->y = y;
}

void Rectangle::setWidth(int width)
{
	this->rect->w = width;
}

void Rectangle::setHeight(int height)
{
	this->rect->h = height;
}

bool Rectangle::contains(const Point &point)
{
	return (point.getX() >= this->getLeft()) &&
		(point.getY() >= this->getTop()) &&
		(point.getX() <= this->getRight()) &&
		(point.getY() <= this->getBottom());
}

bool Rectangle::contains(const Rectangle &rectangle)
{
	return (rectangle.getLeft() >= this->getLeft()) &&
		(rectangle.getTop() >= this->getTop()) &&
		(rectangle.getRight() <= this->getRight()) &&
		(rectangle.getBottom() <= this->getBottom());
}

bool Rectangle::intersects(const Rectangle &rectangle)
{
	return !((rectangle.getLeft() <= this->getRight()) &&
		(rectangle.getRight() >= this->getLeft()) &&
		(rectangle.getTop() >= this->getBottom()) &&
		(rectangle.getBottom() <= this->getTop()));
}