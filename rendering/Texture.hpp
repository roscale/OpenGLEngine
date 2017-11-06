//
// Created by roscale on 10/29/17.
//

#pragma once


class Texture {
private:
	unsigned int textureID;

public:
	float shineDamper = 1;
	float reflectivity = 0;
	bool hasTransparency = false;

	explicit Texture(unsigned int textureID);

	void bind();
	void unbind();
};

