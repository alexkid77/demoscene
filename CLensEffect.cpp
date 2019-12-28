#include "CLensEffect.h"



CLensEffect::CLensEffect()
{
}
CLensEffect::CLensEffect(float radius,float focalDistance,float objectDistance)
{
	this->radius = radius;
	this->focal_distance = focalDistance;
	this->object_distance = objectDistance;
}

void CLensEffect::Init(SDL_Surface *bufferIn)
{
	this->bufferIn = bufferIn;
	this->LensPrecal();
}
void CLensEffect::Update(long deltaTime, SDL_Surface *bufferOut)
{
	this->drawLensPrecal(bufferOut);
}


void  CLensEffect::LensPrecal()
{
	unsigned int px;
	unsigned int py;
	this->pxPrecal = new int[this->radius * 2];
	this->pyPrecal = new int[this->radius * 2];
	int *pxPrecal = this->pxPrecal;
	int *pyPrecal = this->pyPrecal;


	memset(pxPrecal, 0, sizeof(int) *this->radius * 2);
	memset(pyPrecal, 0, sizeof(int) *this->radius * 2);

	unsigned int diameter = this->radius * 2;
	unsigned int radiusPow2 = this->radius*this->radius;


	for (int y = 0; y < diameter; y++)
		for (int x = 0; x < diameter; x++)
		{
			int y_temp = (y - this->radius);
			int x_temp = (x - this->radius);
			if ((x_temp*x_temp + y_temp * y_temp) < (radiusPow2))
			{

				int py = tan(asin(y_temp / this->focal_distance))*this->object_distance;
				int px = tan(asin(x_temp / this->focal_distance))*this->object_distance;
				pyPrecal[y] = py;
				pxPrecal[x] = px;
			}
		}
}


void CLensEffect::drawLensPrecal( SDL_Surface *bufferOut)
{
	int px;
	int py;
	int *pxPrecal =this->pxPrecal;
	int *pyPrecal =this->pyPrecal;

	if (bufferIn == NULL || bufferOut == NULL)
		return;
	unsigned int *ptrOrig = (unsigned int*)this->bufferIn->pixels;
	unsigned int *ptrDest = (unsigned int*)bufferOut->pixels;

	unsigned int H = this->bufferIn->h;
	unsigned int W = this->bufferIn->w;
	unsigned int maxSize = this->bufferIn->h*this->bufferIn->w;

	unsigned int diameter = this->radius * 2;
	unsigned int radiusPow2 = this->radius*this->radius;


	for (int y = 0; y < diameter; y++)
		for (int x = 0; x < diameter; x++)
		{
			int y_temp = (y - this->radius);
			int x_temp = (x - this->radius);

			if ((x_temp*x_temp + y_temp * y_temp) < (radiusPow2))
			{
				//get px and py pixel generate of the refraction of the glass
				py = pyPrecal[y];//tan(asin(y_temp / lens->focal_distance))*lens->object_distance;
				px = pxPrecal[x];//tan(asin(x_temp / lens->focal_distance))*lens->object_distance;
				int origPixel = px + this->radius + this->x + W * (-py + this->radius + this->y);
				int destPixel = x_temp + this->radius + this->x + W * (-y_temp + this->radius + this->y);


				//this is a validation for prevent memory range out

				if (origPixel > maxSize || destPixel > maxSize)
					continue;


				//the refracted pixel copy into the dest buffer
				ptrDest[destPixel] = ptrOrig[origPixel];


			}

		}
}

void CLensEffect::drawLens(SDL_Surface *bufferOut)
{
	int px;
	int py;
	int *pxPrecal = this->pxPrecal;
	int *pyPrecal = this->pyPrecal;

	if (bufferIn == NULL || bufferOut == NULL)
		return;

	unsigned int *ptrOrig = (unsigned int*)this->bufferIn->pixels;
	unsigned int *ptrDest = (unsigned int*)bufferOut->pixels;

	unsigned int H = this->bufferIn->h;
	unsigned int W = this->bufferIn->w;
	unsigned int maxSize = this->bufferIn->h*this->bufferIn->w;

	unsigned int diameter = this->radius * 2;
	unsigned int radiusPow2 = this->radius*this->radius;


	for (int y = 0; y < diameter; y++)
		for (int x = 0; x < diameter; x++)
		{
			int y_temp = (y - this->radius);
			int x_temp = (x - this->radius);

			if ((x_temp*x_temp + y_temp * y_temp) < (radiusPow2))
			{
				//get px and py pixel generate of the refraction of the glass
				py = tan(asin(y_temp / this->focal_distance))*this->object_distance;
				px = tan(asin(x_temp / this->focal_distance))*this->object_distance;
				int origPixel = px + this->radius + this->x + W * (-py + this->radius + this->y);
				int destPixel = x_temp + this->radius + this->x + W * (-y_temp + this->radius + this->y);


				//this is a validation for prevent memory range out

				if (origPixel > maxSize || destPixel > maxSize)
					continue;


				//the refracted pixel copy into the dest buffer
				ptrDest[destPixel] = ptrOrig[origPixel];


			}

		}

}

CLensEffect::~CLensEffect()
{
	delete []this->pxPrecal;
	delete []this->pyPrecal;
}
