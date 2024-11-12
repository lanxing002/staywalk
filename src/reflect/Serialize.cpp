#include "Serialize.h"
namespace staywalk {
    namespace reflect {
        Dumper::Dumper(fs::path dir)
            : target_path_(dir)
        {
            tmp_path_ = Utility::create_temp_dir();
            if (!fs::exists(target_path_)) {
                log(LogLevel::Warining, fmt::format("dumper target folder not exists: {}", target_path_.u8string()));
                log(LogLevel::Warining, fmt::format("create new folder: {}", target_path_.u8string()));
                fs::create_directory(target_path_);
            }
        }

        void Dumper::dump(shared_ptr<Object> obj) {
            dump_obj_impl(obj);
        }

        void Dumper::write_nested_obj(const shared_ptr<Object> obj, ofstream& ofs) {
            //idtype dump_id = obj == nullptr ? kInvalidId : obj->get_guid();
            //write_basic(dump_id, ofs);
            //if (dump_id != kInvalidId) this->dump_obj_impl(obj);
        }

        void Dumper::dump_obj_impl(const shared_ptr<Object> obj) {
            //const idtype dump_id = obj->get_guid();
            //auto it = status_table_.find(dump_id);
            //if (it != status_table_.end()){
            //    assert(it->second != Status::Dumping);
            //    if (it->second == Status::Done)
            //        return;
            //}
            //status_table_[dump_id] = Status::Wait;
            //fs::path name = tmp_path_ /(std::to_string(dump_id) + Utility::kObjExt);
            //assert(!fs::exists(name));  // must be a new file 
            //ofstream ofs(name, std::ios::out | std::ios::binary | std::ios::trunc);
            //auto check_r = Utility::check_ofstream(ofs);
            //if (check_r) {
            //    status_table_[dump_id] = Status::Dumping;
            //    write_basic(obj->get_type_value(), ofs);
            //    obj->dump_impl(ofs, *this);
            //    status_table_[dump_id] = Status::Done;
            //}
            return;
        }

        bool Dumper::clear()
        {
            for (auto it = status_table_.begin(); it != status_table_.end(); it++) {
                if (it->second != Status::Done) {
                    log(LogLevel::Error, fmt::format("dump not finished yet : {}", it->first));
                    assert(false);
                }
            }
            const auto copyOptions = fs::copy_options::update_existing;
            fs::copy(tmp_path_, target_path_, copyOptions);  // no recursive
            fs::remove_all(tmp_path_);
            return true;
        }

        shared_ptr<Object> Loader::load(idtype id) {
            return load_obj_impl(id);
        }

        shared_ptr<Object> Loader::read_nested_obj(ifstream& ifs)
        {
            auto id = read_basic<idtype>(ifs);
            return  id == kInvalidId ? nullptr : load_obj_impl(id);
        }

        shared_ptr<Object> Loader::load_obj_impl(idtype id)
        {
            auto it = status_table_.find(id);
            if (it != status_table_.end()) {
                assert(it->second != Status::Loading);
                if (it->second == Status::Done)
                    return ref_cache_.find(id)->second;
            }

            status_table_[id] = Status::Wait;
            fs::path file_name = Utility::get_objects_dir() / (std::to_string(id) + Utility::kObjExt);
            ifstream ifs(file_name, std::ios::in | std::ios::binary);
            auto check_r = Utility::check_ifstream(ifs);
            shared_ptr<Object> result = nullptr;
            status_table_[id] = Status::Loading;
            if (check_r) {
                ObjectType ot = read_basic<ObjectType>(ifs);

                /*switch (ot)
                {
                case staywalk::ObjectType::Object:
                    result = std::make_shared<Object>();
                    break;
                case staywalk::ObjectType::GameObject:
                    result = std::make_shared<GameObject>();
                    break;
                case staywalk::ObjectType::Actor:
                    result = std::make_shared<Actor>();
                    break;
                case staywalk::ObjectType::GameComponent:
                    result = std::make_shared<GameComponent>();
                    break;
                case staywalk::ObjectType::StaticMeshComponent:
                    result = std::make_shared<StaticMeshComponent>();
                    break;
                case staywalk::ObjectType::Camera:
                    result = std::make_shared<Camera>();
                    break;
                case staywalk::ObjectType::Material:
                    result = std::make_shared<Material>();
                    break;
                case staywalk::ObjectType::RObject:
                    result = std::make_shared<RObject>();
                    break;
                case staywalk::ObjectType::RTex:
                    result = std::make_shared<RTex>();
                    break;
                case staywalk::ObjectType::RMesh:
                    result = std::make_shared<RMesh>();
                    break;
                case staywalk::ObjectType::RShader:
                    result = std::make_shared<RShader>();
                    break;
                case staywalk::ObjectType::RProgram:
                    result = std::make_shared<RProgram>();
                    break;
                case staywalk::ObjectType::RUniform:
                    result = std::make_shared<RUniform>();
                    break;
                default:
                    assert(false);
                    break;
                }*/

                //result->load_impl(ifs, *this);
            }
            status_table_[id] = Status::Done;
            ref_cache_[id] = result;
            return result;
        }

    }
}
