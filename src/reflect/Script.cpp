#include "Script.h"
#include "RenderObject.h"
#include "Input.h"
#include "InputManager.h"
#include "SimpleType.h"

#include "fmt/format.h"
#include "fmt/ranges.h"

using namespace staywalk;

namespace glm {
	auto format_as(const vec2 v){
		return fmt::format("vec2(x:{}, y:{})", v.x, v.y);
	}

	auto format_as(const vec3& v){
		return fmt::format("vec3(x:{}, y:{}, z:{})", v.x, v.y, v.z);
	}

	auto format_as(const vec4& v){
		return fmt::format("vec4(x:{}, y:{}, z:{}, w:{})", v.x, v.y, v.z, v.w);
	}

	auto format_as(const quat& q){
		return fmt::format("quat(x:{}, y:{}, z:{}, w:{})", q.x, q.y, q.z, q.w);
	}

	auto format_as(const mat4& m){
		return fmt::format("mat4(x:[{}, {}, {}, {}], y:[{}, {}, {}, {}], z:[{}, {}, {}, {}], t:[{}, {}, {}, {}])",
			m[0][0], m[0][1], m[0][2], m[0][3],
			m[1][0], m[1][1], m[1][2], m[1][3],
			m[2][0], m[2][1], m[2][2], m[2][3],
			m[3][0], m[3][1], m[3][2], m[3][3]
		);
	}
}

namespace staywalk {
	auto format_as(const AABB& aabb) {
		return fmt::format("AABB(min:[{}], max[{}])", aabb.min, aabb.max);
	}
}


static 
void py_bind_glm(py::module& __module) {
	py::class_<staywalk::vec3>(__module, "vec3")
		.def(py::init<>())
		.def(py::init<vec3>())
		.def(py::init<float, float, float>())
		.def(py::init<float>())
		.def_readwrite("x", &staywalk::vec3::x)
		.def_readwrite("y", &staywalk::vec3::y)
		.def_readwrite("z", &staywalk::vec3::z)
		.def(py::self + py::self)
		.def(py::self - py::self)
		.def(py::self * float())
		.def(float() * py::self)
		.def(py::self += py::self)
		.def(py::self -= py::self)
		.def(py::self *= float())
		.def(py::self == py::self)
		.def("__repr__", [](const vec3& vec) {return fmt::format("{}", vec); })
		;

	py::class_<staywalk::vec2>(__module, "vec2")
		.def(py::init<>())
		.def(py::init<vec2>())
		.def(py::init<float, float>())
		.def(py::init<float>())
		.def_readwrite("x", &staywalk::vec2::x)
		.def_readwrite("y", &staywalk::vec2::y)
		.def(py::self + py::self)
		.def(py::self - py::self)
		.def(py::self * float())
		.def(float() * py::self)
		.def(py::self += py::self)
		.def(py::self -= py::self)
		.def(py::self *= float())
		.def(py::self == py::self)
		.def("__repr__", [](const vec2& vec) {return fmt::format("{}", vec); })
		;

	py::class_<staywalk::vec4>(__module, "vec4")
		.def(py::init<>())
		.def(py::init<vec4>())
		.def(py::init<float, float, float, float>())
		.def(py::init<float>())
		.def_readwrite("x", &staywalk::vec4::x)
		.def_readwrite("y", &staywalk::vec4::y)
		.def_readwrite("y", &staywalk::vec4::z)
		.def_readwrite("y", &staywalk::vec4::w)
		.def(py::self + py::self)
		.def(py::self - py::self)
		.def(py::self * float())
		.def(float() * py::self)
		.def(py::self += py::self)
		.def(py::self -= py::self)
		.def(py::self *= float())
		.def(py::self == py::self)
		.def("__repr__", [](const vec4& vec) {return fmt::format("{}", vec); })
		;

	py::class_<staywalk::mat4>(__module, "mat4")
		.def(py::init<>())
		.def(py::init<mat4>())
		.def("__getitem__", py::overload_cast<int>(&mat4::operator[], py::const_))
		.def("__setitem__", [](mat4& m, int i, const vec4& val) {m[i] = val; })
		.def(py::self + py::self)
		.def(py::self - py::self)
		.def(py::self * float()) 
		.def(float() * py::self)
		.def(py::self += py::self)
		.def(py::self -= py::self)
		.def(py::self *= float())
		.def(py::self == py::self)
		.def("__repr__", [](const mat4& vec) {return fmt::format("{}", vec); })
		;

	py::class_<staywalk::AABB>(__module, "AABB")
		.def(py::init<>())
		.def(py::init<const vec3&, const vec3&>())
		.def("expand", py::overload_cast<const AABB&>(&AABB::expand))
		.def("expand", py::overload_cast<const vec3&>(&AABB::expand))
		.def(py::self == py::self)
		.def("__repr__", [](const AABB& vec) {return fmt::format("{}", vec); })
		;

	py::class_<staywalk::Vertex>(__module, "Vertex")
		.def(py::init<>())
		.def_readwrite("position", &Vertex::position)
		.def_readwrite("normal", &Vertex::normal)
		.def_readwrite("texcoords", &Vertex::texcoords)
		.def_readwrite("tangent", &Vertex::tangent)
		.def_readwrite("bitangent", &Vertex::bitangent);
}

static
void py_bind_custom(py::module& __module) {
	py::class_<::staywalk::InputManager, std::unique_ptr<InputManager, py::nodelete>>(__module, "InputManager")
		.def("pressed", &InputManager::press)
		.def("released", &InputManager::release)
		.def("left_click", &InputManager::left_click)
		.def("right_click", &InputManager::right_click)
		.def("middle_click", &InputManager::middle_click)
		.def("left_relase", &InputManager::left_relase)
		.def("right_relase", &InputManager::right_relase)
		.def("middle_relase", &InputManager::middle_relase)
		.def("pos", &InputManager::pos)
		.def("mouse_offset", &InputManager::mouse_offset)
		.def("wheel", &InputManager::wheel)
		;
}


// define python module
PYBIND11_MODULE(staywalk, __module) {
	// custom define
	py::class_<::staywalk::Drawable, std::shared_ptr<::staywalk::Drawable>>(__module, "Drawable");

	py_bind_custom(__module);
	py_bind_glm(__module);
	staywalk::reflect::py_bind_auto(__module);
}

void staywalk::reflect::py_bind_startup() {
	PyImport_AppendInittab("staywalk", PyInit_staywalk);
}