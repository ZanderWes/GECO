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
        auto angular_velocity = physics_body.value()["Angular Velocity"].get<std::vector<float>>();
        auto mass = physics_body.value()["Mass"].get<float>();

        p_body.get()->setBodyPosition(Point3D(position[0], position[1], position[2]));
        p_body.get()->getBoxCollider().get()->e = q3Vec3(cube_size[0], cube_size[1], cube_size[2]);
        p_body.get()->setLinearVelocity(VelocityVec3(linear_velocity[0], linear_velocity[1], linear_velocity[2]));
        p_body.get()->setMass(Mass(mass));
        p_body.get()->setAngularVelocity(AngularVelocityVec3(angular_velocity[0], angular_velocity[1], angular_velocity[2]));

        physics_factory.AddRigidBody(p_body);
    }

}
