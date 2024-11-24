#include "PyEnv.h"
#include "Utility.h"
#include "Logger.h"
#include "Script.h"

#include <pybind11/embed.h>

namespace py = pybind11;
namespace staywalk {
static PyObject* pymsg(PyObject* self, PyObject* args){
	const char* what;
	if (PyArg_ParseTuple(args, "s", &what))
		staywalk::log(what);
	return Py_None;
}

static PyObject* pyerror(PyObject* self, PyObject* args){
	const char* what;
	if (PyArg_ParseTuple(args, "s", &what))
		staywalk::log(what);
	return Py_None;
}

static PyObject* pyflush(PyObject* self, PyObject* args){
	return Py_None;
}


PyMethodDef pystdout[] ={
	{"write", pymsg,	METH_VARARGS, "doc for stdout"},
	{"flush", pyflush,	METH_VARARGS, "doc for flush"},
	{0, 0, 0, 0} // sentinel
};


PyMethodDef pystderr[] ={
	{"write", pyerror, METH_VARARGS, "doc for stderr"},
	{"flush", pyflush, METH_VARARGS, "doc for flush"},
	{0, 0, 0, 0} // sentinel
};

PyModuleDef stdout_module = {
	PyModuleDef_HEAD_INIT,	// PyModuleDef_Base m_base;
	"statwalk_redirect",	// const char* m_name;
	"doc for redirect",		// const char* m_doc;
	-1,						// Py_ssize_t m_size;
	pystdout,    // PyMethodDef *m_methods
};

PyModuleDef stderr_module ={
	PyModuleDef_HEAD_INIT,	// PyModuleDef_Base m_base;
	"statwalk_redirect",    // const char* m_name;
	"doc for redirect",		// const char* m_doc;
	-1,						// Py_ssize_t m_size;
	pystderr,	// PyMethodDef *m_methods
};

PyMODINIT_FUNC create_stdout(void){
	PyObject* msg = PyModule_Create(&stdout_module);
	PySys_SetObject("stdout", msg);
	return msg;
}

PyMODINIT_FUNC create_stderr(void){
	PyObject* err = PyModule_Create(&stderr_module);
	PySys_SetObject("stderr", err);
	return err;
}

void Py::__init(){
	static bool init = false;
	if (!init) {
        auto py_home = Utility::get_py_home().wstring();
        Py_SetPythonHome(py_home.c_str());
		reflect::py_bind();
		PyImport_AppendInittab("__sw_stdout", create_stdout);
		PyImport_AppendInittab("__sw_stderr", create_stderr);
		py::initialize_interpreter();
		PyImport_ImportModule("__sw_stdout");
		PyImport_ImportModule("__sw_stderr");

        init = true;
	}
	return;
}

void Py::run(const string& code){
    Py::__init();
    //py::exec(R"(
    //    import sys
    //    with open('E:/ttdt.txt', 'w') as f:
    //        f.write(str(sys.path))
    //    kwargs = dict(name="World", number=42)
    //    message = "Hello, {name}! The answer is {number}".format(**kwargs)
    //    print(message)
    //)");

	try {
		py::exec(code);
	}
	catch (const py::error_already_set& e) {
		staywalk::log(e.what(), LogLevel::Error);
	}
}
}

