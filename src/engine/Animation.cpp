#include "Animation.h"
#include "Utility.h"
#include "Engine.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
//#include "SkeletonStaticMeshComponent.h"

namespace staywalk {
	Animation::Animation(const string& name /*= "0-animation"*/)
	:RObject(name){
		curr_time_ = 0.0;
	}

	void Animation::animate(float delta){
		curr_time_ += ticks_pers_ * delta;
		curr_time_ = fmod(curr_time_, duration_);
		calculate_bone_transform(node_root_, glm::mat4(1.0f));
	}

	void Animation::gl_delete(){

	}

	GLuint Animation::get_updated_glid(){
		if (glid_ == kGlSickId) gl_update();
		glBindBuffer(GL_UNIFORM_BUFFER, glid_);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(mat4) * kMaxBoneNum, bone_influences_.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		return glid_;
	}

	glm::mat4 Animation::calculate_per_bone(const Bone& bone){
		mat4 position_mat, rotate_mat, scale_mat;
		auto pos_num = bone.positions_.size();
		auto rotation_num = bone.rotations_.size();
		auto scale_num = bone.scales_.size();
		assert(pos_num > 0 && rotation_num && scale_num > 0);
		if (pos_num == 1) position_mat = glm::translate(mat4(1.0), bone.positions_[0].first);
		else {
			int time_idx = -1;
			for (int idx = 0; idx < pos_num - 1; idx++) {
				if (curr_time_ < bone.positions_[idx + 1].second) {
					time_idx = idx;
					break;
				}
			}
			assert(time_idx >= 0);
			int next_idx = time_idx + 1;
			float factor = (curr_time_ - bone.positions_[time_idx].second) /
				(bone.positions_[next_idx].second - bone.positions_[time_idx].second);
			glm::vec3 pos = glm::mix(bone.positions_[time_idx].first, bone.positions_[next_idx].first, factor);
			position_mat = glm::translate(glm::mat4(1.0f), pos);
		}

		if (1 == rotation_num) {
			auto rotation = glm::normalize(bone.rotations_[0].first);
			rotate_mat = glm::toMat4(rotation);
		}
		else {
			int time_idx = -1;
			for (int idx = 0; idx < rotation_num - 1; idx++) {
				if (curr_time_ < bone.rotations_[idx + 1].second) {
					time_idx = idx; break;
				}
			}
			assert(time_idx >= 0);
			float factor = (curr_time_ - bone.rotations_[time_idx].second) /
				(bone.rotations_[time_idx + 1].second - bone.rotations_[time_idx].second);
			glm::quat rot = glm::slerp(bone.rotations_[time_idx].first, bone.rotations_[time_idx + 1].first, factor);
			rotate_mat = glm::toMat4(glm::normalize(rot));
		}

		if (1 == scale_num) {
			scale_mat = glm::scale(mat4(1.0), bone.scales_[0].first);
		}
		else {
			auto time_idx = -1;
			for (auto idx = 0; idx < scale_num - 1; idx++) {
				if (curr_time_ < bone.scales_[idx + 1].second) {
					time_idx = idx; break;
				}
			}
			assert(time_idx >= 0);

			float factor = (curr_time_ - bone.scales_[time_idx].second)
				/ (bone.scales_[time_idx + 1].second - bone.scales_[time_idx].second);
			scale_mat = glm::scale(mat4(1.0), glm::mix(bone.scales_[time_idx].first, bone.scales_[time_idx + 1].first, factor));
		}
		return position_mat * rotate_mat * scale_mat;
	}

	void Animation::calculate_bone_transform(const BoneTreeNode& node, mat4 parent_transform) {
		mat4 transform = parent_transform * node.transform_;
		if (node.bone_id_ != -1) {
			transform = 
				parent_transform *  calculate_per_bone(bones_[node.bone_id_]) ;
			bone_influences_[node.bone_id_] = transform * bones_[node.bone_id_].offset_;
			// parent <-- animation <-- bone space <-- model space
		}

		for (int i = 0; i < node.children_.size(); i++)
			calculate_bone_transform(node.children_[i], transform);
	}

	void Animation::gl_update() {
		if (glid_ == kGlSickId) glGenBuffers(1, &glid_);
	}

	void Animation::load_post() {
		auto path = Utility::get_objects_dir() / (name_ + Utility::kBoneExt);
		auto ifs = ifstream(path, std::ios::binary);
		bool status = false;
		if (ifs) {
			size_t bsize = 0;
			ifs.read(reinterpret_cast<char*>(&bsize), sizeof(bsize));
			bones_.resize(bsize);
			for (auto& b : bones_) {
				ifs.read(reinterpret_cast<char*>(&b.id_), sizeof(b.id_));
				ifs.read(reinterpret_cast<char*>(&b.offset_), sizeof(b.offset_));
				Utility::read_vector_from_ifs(ifs, b.positions_);
				Utility::read_vector_from_ifs(ifs, b.rotations_);
				Utility::read_vector_from_ifs(ifs, b.scales_);
			}

			status = true;
		}
		log(fmt::format("load_post to {}, status: {}", path.u8string(), status),
			status ? LogLevel::Info : LogLevel::Warn);
		mark_dirty();
	}
	
	void Animation::dump_post() const {
		size_t bsize = bones_.size();
		auto path = Utility::get_objects_dir() / (name_ + Utility::kBoneExt);
		auto ofs = ofstream(path, std::ios::binary | std::ios::trunc);
		bool status = false;
		if (ofs) {
			ofs.write(reinterpret_cast<char*>(&bsize), sizeof(bsize));
			for (auto& b : bones_) {
				ofs.write(reinterpret_cast<const char*>(&b.id_), sizeof(b.id_));
				ofs.write(reinterpret_cast<const char*>(&b.offset_), sizeof(b.offset_));
				Utility::write_vector_to_ofs(ofs, b.positions_);
				Utility::write_vector_to_ofs(ofs, b.rotations_);
				Utility::write_vector_to_ofs(ofs, b.scales_);
			}

			status = true;
		}

		log(fmt::format("dump_post to {}, status: {}", path.u8string(), status),
			status ? LogLevel::Info : LogLevel::Warn);
	}

}

