#pragma once

#ifndef _IN_REFLECT
#include "reflect.h"

#include "pybind11/pybind11.h"
#include "pybind11/operators.h"
#include "pybind11/embed.h"
#include "pybind11/stl.h"
#include "pybind11/complex.h"
#include "pybind11/functional.h"
#include "pybind11/chrono.h"

#include "fmt/format.h"
#include "fmt/ranges.h"
namespace py = pybind11;
namespace staywalk {
	namespace reflect {
		void py_bind_startup();

		void py_bind_auto(py::module& __module);
	}
}

#include "generated/SerializeAll.gen.h"

#endif // !_IN_REFLECT
