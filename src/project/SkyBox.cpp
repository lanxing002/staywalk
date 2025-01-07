#include "SkyBox.h"
#include "Utility.h"
#include "Engine.h"
#include "StaticMeshComponent.h"
#include "Material.h"

namespace staywalk {
	static MeshRef make_cube() {
		auto result = std::make_shared<Mesh>("skybox");
        float skybox_vertices[] = {
            // positions          
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
        };
        constexpr int vertices_num = sizeof(skybox_vertices) / (sizeof(float) * 3);
        result->vertices_.resize(vertices_num);
        result->indices_.resize(vertices_num);
        for (int i = 0; i < vertices_num; i++) {
            result->vertices_[i].position_.x = skybox_vertices[i * 3];
            result->vertices_[i].position_.y = skybox_vertices[i * 3 + 1];
            result->vertices_[i].position_.z = skybox_vertices[i * 3 + 2];

            result->indices_[i] = i;
        }
		return result;
	}

	static MaterialRef make_cube_material(){
		auto result = std::make_shared<Material>("skybox");
		result->program_ = std::make_shared<Program>("skybox"); // shader 
		CubeMapRef cubemap = std::make_shared<CubeMap>("skybox");  // material texture
		result->add_tex("skybox", cubemap);
		return result;
	}

	Ref<Skybox> Skybox::create(const string& name) {
		auto result = std::make_shared<Skybox>(name);
		result->sm_comp_ = std::make_shared<StaticMeshComponent>(name);
		auto cube = make_cube();
		auto mat = make_cube_material();
		result->sm_comp_->meshs.emplace_back(cube, mat);
		return result;
	}


	Skybox::Skybox(const string& name)
		: Actor(name){
	}

	void Skybox::tick(float delta) {
		if (sm_comp_) sm_comp_->tick(delta);
	}
}

