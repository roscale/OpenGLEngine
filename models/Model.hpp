//
// Created by roscale on 10/25/17.
//

#pragma once


class Model {
private:
	unsigned int vaoID;
	unsigned int vertexCount;

public:
	Model(unsigned int vaoID, unsigned int vertexCount);

	unsigned int getVaoID() const;
	unsigned int getVertexCount() const;

};

