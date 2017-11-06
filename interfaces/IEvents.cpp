//
// Created by roscale on 11/2/17.
//

#include "IEvents.hpp"

void IEvents::onStart() {}
void IEvents::onUpdate() {}
void IEvents::onKey(int key, int scancode, int action, int mods) {}
void IEvents::onMouseMotion(double xabs, double yabs, double xrel, double yrel) {}
void IEvents::onMouseEnter(bool entered) {}
void IEvents::onMouseButton(int button, int action, int mods) {}
void IEvents::onMouseScroll(double xoffset, double yoffset) {}

IEvents::~IEvents() = default;