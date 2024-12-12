#include "Animation.h"
#include "Utility.h"
#include "Engine.h"
//#include "SkeletonStaticMeshComponent.h"

namespace staywalk {
	Animation::Animation(const string& name /*= "0-animation"*/)
	:RObject(name){

	}

	void Animation::load_post() {
		auto path = Utility::get_objects_dir() / (name_ + Utility::kBoneExt);
		auto ifs = ifstream(path, std::ios::binary);
		bool status = false;
		if (ifs) {
			size_t bsize = 0;
			ifs.read(reinterpret_cast<char*>(&bsize), sizeof(bsize));
			bones_.resize(bsize);

			ifs.read(reinterpret_cast<char*>(bones_.data()), bsize * sizeof(Bone));
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
			ofs.write(reinterpret_cast<const char*>(bones_.data()), bsize * sizeof(Bone));
			status = true;
		}

		log(fmt::format("dump_post to {}, status: {}", path.u8string(), status),
			status ? LogLevel::Info : LogLevel::Warn);
	}

}

