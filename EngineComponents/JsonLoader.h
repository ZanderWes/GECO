#pragma once

#include <iostream>
#include <fstream>
#include "Dependancies/nlohmann/json.hpp"
#include "PhysicsManager.h"


class JsonLoader
{
public:
	JsonLoader() {};

	bool ParseJsonFile(const char* file_name);

	nlohmann::ordered_json& getJsonObjects();

private:

	nlohmann::ordered_json json_object_file;
};

static class LoadPhysicsObjects
{
public:
	LoadPhysicsObjects() {};

	void LoadPhysics(PhysicsManager& physics_factory, const char* file_name);

};