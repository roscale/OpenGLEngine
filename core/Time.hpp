//
// Created by roscale on 11/3/17.
//

#pragma once


class Time {
public:
	static double lastFrameTime;
	static float deltaTime;

	static double getCurrentTime();

	static void init();
	static void update();
};

