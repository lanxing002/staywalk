#include "Serialize.h"
#include "Logger.h"

using namespace staywalk;
using namespace staywalk::reflect;

static const std::string kObjectTypeKey = "__object_type_";

Dumper::Dumper(fs::path dir)
    : target_path_(dir){
    tmp_path_ = Utility::create_temp_dir();
    if (!fs::exists(target_path_)) {
        log(LogLevel::Warining, fmt::format("dumper target folder not exists: {}", target_path_.u8string()));
        log(LogLevel::Warining, fmt::format("create new folder: {}", target_path_.u8string()));
        fs::create_directory(target_path_);
    }
}

void Dumper::dump(Ref<Object> obj) {
    dump_obj_impl(obj);
}

void Dumper::dump_obj_impl(const shared_ptr<Object> obj) {
    const idtype dump_id = obj->get_guid();
    auto it = status_table_.find(dump_id);
    if (it != status_table_.end()){
        assert(it->second != Status::Dumping);
        if (it->second == Status::Done)
            return;
    }
    status_table_[dump_id] = Status::Dumping;
    Writer writer(sb_);
    writer.StartObject();
    writer.String(kObjectTypeKey.c_str());
    writer.String(obj->get_meta_info().tname.c_str());
    obj->dump(writer);
    writer.EndObject();
    status_table_[dump_id] = Status::Done;
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

template<>
void Loader::read_single<string>(string& str, ifstream& ifs) {
    str.clear();
    auto strlen = str.length();
    ifs.read(reinterpret_cast<char*>(&strlen), sizeof strlen);
    str.resize(strlen);
    ifs.read((str.data()), strlen);
}

template<>
void Loader::read_single(fs::path& path, ifstream& ifs) {
    string pstr; this->read_single(pstr, ifs);
    path = fs::path{ pstr };
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
        string tname;
        this->read(tname, ifs);
        result = create_empty(MetaInfo{tname});
        result->load(ifs, *this);
    }
    status_table_[id] = Status::Done;
    ref_cache_[id] = result;
    return result;
}




