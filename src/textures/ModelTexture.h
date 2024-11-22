#pragma once

class ModelTexture {
private:
	unsigned int textureID;
	float shineDamper;
	float reflectivity;
	bool hasTransparency;
	bool useFakeLighting;

public:
	ModelTexture(unsigned int id);
	unsigned int getID() const{ return textureID;  }
	float getShineDamper() const { return shineDamper; }
	void setShineDamper(float shineDamper);
	float getReflectivity() const { return reflectivity; }
	void setReflectivity(float reflectivity);
	bool isHasTransparency() const { return hasTransparency; }
	void setHasTransparency(bool hasTransparency);
	bool isUseFakeLighting() const { return useFakeLighting; }
	void setUseFakeLighting(bool useFakeLighting);
};