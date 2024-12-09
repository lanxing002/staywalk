#include "Serialize.h"
#include "Logger.h"
#include "World.h"
#include "Actor.h"
#include "SimpleType.h"

#include <rapidjson/prettywriter.h>
#include <sstream>
using namespace staywalk;
using namespace staywalk::reflect;

static const std::string kObjectTypeKey = "__object_type_";

Dumper::Dumper(fs::path file_name)
    : target_file_(file_name){
    doc_ = json::Document();
}

void staywalk::reflect::Dumper::dump_world(const World& world){
    doc_.SetObject();
    real_objs_.SetObject();
    json::Value actors;
    json::Value cameras;
    json::Value lights;
    json::Value assets;

    write(world.actors_, actors);
    write(world.cameras_, cameras);
    write(world.lights_, lights);
    write(world.assets_, assets);

    doc_.AddMember("actors", actors, doc_.GetAllocator());
    doc_.AddMember("cameras", cameras, doc_.GetAllocator());
    doc_.AddMember("lights", lights, doc_.GetAllocator());
    doc_.AddMember("assets", assets, doc_.GetAllocator());
    doc_.AddMember("__real_objects", real_objs_, doc_.GetAllocator());
    
    clear();
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
    json::Value value(json::kObjectType);
    value.AddMember(json::StringRef(kObjectTypeKey.c_str()),
        json::StringRef(obj->get_meta_info().tname.data()), doc_.GetAllocator()); //TODO:
    obj->dump(value, *this);
    json::Value key(std::to_string(dump_id).c_str(), doc_.GetAllocator());
    real_objs_.AddMember(key, value, doc_.GetAllocator());
    status_table_[dump_id] = Status::Done;
    return;
}

bool Dumper::clear()
{
    for (auto it = status_table_.begin(); it != status_table_.end(); it++) {
        if (it->second != Status::Done) {
            log(fmt::format("dump not finished yet : {}", it->first), LogLevel::Error);
            assert(false);
        }
    }
    json::StringBuffer sb;
    json::PrettyWriter<json::StringBuffer> writer(sb);
    doc_.Accept(writer);

    if (target_file_.has_parent_path() && target_file_.has_filename()) {
        if (!fs::exists(target_file_.parent_path()))
            fs::create_directory(target_file_.parent_path());
        ofstream ofs = ofstream(target_file_, std::ios::out | std::ios::trunc);
        ofs << sb.GetString();
    }
    else {
        log(fmt::format("dump target file is incorrect : {}", target_file_.u8string()), LogLevel::Error);
        return false;
    }

    return true;
}

Loader::Loader(fs::path file_name)
    : load_file_(file_name) {
    if (!fs::exists(file_name)) {
        log(fmt::format("Loader cannot open target file: [{}]", fs::absolute(file_name).u8string()), LogLevel::Error);
        return;
    }
    
    log(fmt::format("start load world from: [{}]", fs::absolute(file_name).u8string()));
    std::ifstream ifs(file_name, std::ios::in);
    json_str_ = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());

    doc_ = json::Document();
    if (doc_.Parse(json_str_.data()).HasParseError()) {
        log(fmt::format("parse json data error: [{}]", file_name.u8string()), LogLevel::Error);
    }
}

void Loader::load(World& world) {
    if (!doc_.IsObject()) {
        log(fmt::format("load world failed"), LogLevel::Warn);
        return;
    }
    auto actors_it = doc_.FindMember("actors");
    auto cameras_it = doc_.FindMember("cameras");
    auto lights_it = doc_.FindMember("lights");
    auto assets_it = doc_.FindMember("assets");
    auto real_objs_it = doc_.FindMember("__real_objects");
    const auto end_it = doc_.MemberEnd();
    if (actors_it == end_it || cameras_it == end_it || 
        lights_it == end_it || real_objs_it== end_it ||
        assets_it == end_it) {
        log("wrong world json data", LogLevel::Error);
    }

    real_objs_ = real_objs_it->value;
    read(world.actors_, actors_it->value);
    read(world.cameras_, cameras_it->value);
    read(world.lights_, lights_it->value);
    read(world.assets_, assets_it->value);

    clear();
}

void staywalk::reflect::Loader::clear(){
}

shared_ptr<Object> Loader::load_obj_impl(const std::string& id)
{
    auto it = status_table_.find(id);
    if (it != status_table_.end()) {
        assert(it->second != Status::Loading);
        if (it->second == Status::Done)
            return ref_cache_.find(id)->second;
    }

    status_table_[id] = Status::Wait;
    shared_ptr<Object> result = nullptr;
    status_table_[id] = Status::Loading;
    auto itr = real_objs_.FindMember(id.c_str());
    if (itr != real_objs_.MemberEnd()) {
        std::string tname(itr->value[kObjectTypeKey.c_str()].GetString());
        result = create_empty(MetaInfo{ObjectType::Object/*useless parameter*/, std::string_view(tname)});
        result->load(itr->value, *this);
    }
    status_table_[id] = Status::Done;
    ref_cache_[id] = result;
    return result;
}

void staywalk::Transform::dump(rapidjson::Value& value, staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());
    {
        json::Value prop;
        dumper.write(location, prop);
        value.AddMember("location", prop, dumper.get_doc().GetAllocator()); 
    }

    {
        json::Value prop;
        dumper.write(scale, prop);
        value.AddMember("scale", prop, dumper.get_doc().GetAllocator());
    }

    {
        json::Value prop;
        dumper.write(rotation, prop);
        value.AddMember("rotation", prop, dumper.get_doc().GetAllocator());
    }
}

void staywalk::Transform::load(rapidjson::Value& value, staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;
    
    itr = value.FindMember("location");
    if(itr != value.MemberEnd()){
        loader.read(location, itr->value);
    }

    itr = value.FindMember("scale");
    if (itr != value.MemberEnd()) {
        loader.read(scale, itr->value);
    }

    itr = value.FindMember("rotation");
    if (itr != value.MemberEnd()) {
        loader.read(rotation, itr->value);
    }
}

void  AABB::dump(rapidjson::Value& value, staywalk::reflect::Dumper& dumper) const {
	assert(value.IsObject());
	{
		json::Value prop;
		dumper.write(min, prop);
		value.AddMember("min", prop, dumper.get_doc().GetAllocator());
	}

	{
		json::Value prop;
		dumper.write(max, prop);
		value.AddMember("max", prop, dumper.get_doc().GetAllocator());
	}
}

void AABB::load(rapidjson::Value& value, staywalk::reflect::Loader& loader) {
	assert(value.IsObject());
	json::Value::MemberIterator itr;

	itr = value.FindMember("min");
	if (itr != value.MemberEnd()) {
		loader.read(min, itr->value);
	}

	itr = value.FindMember("max");
	if (itr != value.MemberEnd()) {
		loader.read(max, itr->value);
	}
}

void Vertex::dump(rapidjson::Value& value, staywalk::reflect::Dumper& dumper) const {
    static_assert(std::is_trivial_v<Vertex> && "vertex must be trivial");
    //constexpr auto size = sizeof Vertex / sizeof(float);
    //dumper.write_array<const float*, size>(reinterpret_cast<const float*>(this), value);
}

void Vertex::load(rapidjson::Value& value, staywalk::reflect::Loader& loader) {

}

void SWCode::__SWCode::load(rapidjson::Value& value, staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    itr = value.FindMember("code");
    if (itr != value.MemberEnd()) {
        loader.read(text_, itr->value);
    }

    itr = value.FindMember("code_type");
    if (itr != value.MemberEnd()) {
        int codet = -1;
        loader.read(codet, itr->value);
        assert(codet > -1);
        code_type_ = static_cast<CodeType>(codet);
    }
}


void SWCode::__SWCode::dump(rapidjson::Value& value, staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());
    {
        json::Value prop;
        dumper.write(text_, prop);
        value.AddMember("code", prop, dumper.get_doc().GetAllocator());
    }

    {
        json::Value prop;
        int codet = (int)code_type_;
        dumper.write(codet, prop);
        value.AddMember("code_type", prop, dumper.get_doc().GetAllocator());
    }
}

//void staywalk::Object::dump(rapidjson::Value& value, staywalk::reflect::Dumper& dumper) const {
//    assert(value.IsObject());
//    {
//        json::Value prop;
//        dumper.write(name, prop);
//        value.AddMember("name", prop, dumper.get_doc().GetAllocator()); 
//    }
//
//    {
//        json::Value prop;
//        dumper.write(guid_, prop);
//        value.AddMember("guid_", prop, dumper.get_doc().GetAllocator());
//    }
//}