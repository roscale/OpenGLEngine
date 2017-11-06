//
// Created by roscale on 11/2/17.
//

#pragma once


class IEvents {
public:
//	IEvents() = delete;
	virtual void onStart();
	virtual void onUpdate();

	virtual void onKey(int key, int scancode, int action, int mods);
	virtual void onMouseMotion(double xabs, double yabs, double xrel, double yrel);
	virtual void onMouseEnter(bool entered);
	virtual void onMouseButton(int button, int action, int mods);
	virtual void onMouseScroll(double xoffset, double yoffset);

	virtual ~IEvents() = 0;
};

