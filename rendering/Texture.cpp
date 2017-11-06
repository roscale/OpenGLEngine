//
// Created by roscale on 10/29/17.
//

#include <GL/glew.h>
#include "Texture.hpp"

Texture::Texture(unsigned int textureID) : textureID(textureID) {

}

void Texture::bind() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
