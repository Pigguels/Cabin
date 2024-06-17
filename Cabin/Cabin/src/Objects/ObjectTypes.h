#pragma once

enum ObjectTypes : unsigned int
{
	Empty = 0x00000000,
	Camera = 0x00000001,
	Transform = 0x00000002,
	RigidBody = 0x00000004,
	Sprite = 0x00000008,
};
