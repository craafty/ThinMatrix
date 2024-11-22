#include "ModelTexture.h"

ModelTexture::ModelTexture(unsigned int id) : textureID(id), shineDamper(1), reflectivity(0), hasTransparency(false), useFakeLighting(false) {}

void ModelTexture::setShineDamper(float shineDamper)
{
	this->shineDamper = shineDamper;
}

void ModelTexture::setReflectivity(float reflectivity)
{
	this->reflectivity = reflectivity;
}

void ModelTexture::setHasTransparency(bool hasTransparency)
{
	this->hasTransparency = hasTransparency;
}

void ModelTexture::setUseFakeLighting(bool useFakeLighting)
{
	this->useFakeLighting = useFakeLighting;
}
