#include "JsonLoader.h"


/*  JSON Loader  */
bool JsonLoader::ParseJsonFile(const char* file_name)
{
    try {
        std::ifstream stream(file_name);
        this->json_object_file = nlohmann::json::parse(stream);
    }
    catch(nlohmann::json::parse_error& error_)
    {
        std::cout << error_.what() << std::endl;
        return false;
    }

    return true;
}

nlohmann::ordered_json& JsonLoader::getJsonObjects()
{
    return this->json_object_file;
}


/************************************************************************************************************/
/*  Phyics Loader  */

void LoadPhysicsObjects::LoadPhysics(PhysicsManager &physics_factory, const char* file_name)
{
    JsonLoader json_loader;
    json_loader.ParseJsonFile(file_name);

    for (auto physics_body : json_loader.getJsonObjects().items())
    {
        std::shared_ptr<RigidBody> p_body = std::make_shared<RigidBody>();

        auto position = physics_body.value()["Position"].get<std::vector<float>>();
        auto cube_size = physics_body.value()["Extents"].get<std::vector<float>>();
        auto linear_velocity = physics_body.value()["Linear Velocity"].get<std::vector<float>>();
        auto Aangular_velocity = physics_body.value()["Angular Velocity"].get<std::vector<float>>();


        physics_factory.AddRigidBody(p_body);
    }

}
