#include "Script.h"
#include "RenderObject.h"

// define python module
PYBIND11_MODULE(staywalk, __module) {
	// custom define
	py::class_<::staywalk::Drawable, std::shared_ptr<::staywalk::Drawable>>(__module, "Drawable");

	staywalk::reflect::py_bind_auto(__module);
}

void staywalk::reflect::py_bind_startup() {
	PyImport_AppendInittab("staywalk", PyInit_staywalk);
}