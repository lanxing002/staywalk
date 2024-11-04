#pragma once
#include "Common.h"
#include "RenderObject.h"

namespace staywalk{
	class Utility{
	public:
		static const string kFileExt;

		static int64_t GetRandomId();

		static bool check_ifstream(const std::ifstream& fstrm);
		
		static bool check_ofstream(const std::ofstream& fstrm);

		static void load_model(const string & path);
	};

	class Dumper {
	public:
		enum class Status {
			Wait,
			Dumping,
			Done
		};
		
		Dumper() {}
		Dumper(const Dumper&) = delete;
		Dumper(Dumper&&) = delete;
		Dumper& operator=(const Dumper&) = delete;
		Dumper& operator=(Dumper&&) = delete;

		void dump_in_file(shared_ptr<Object> obj);

	private:
		hashtable<long long, Status> status_table_;
	};

	class Loader {
	public:
		enum class Status {
			Wait,
			Loading,
			Done
		};

		Loader() {}
		Loader(const Loader&) = delete;
		Loader(Loader&&) = delete;
		Loader& operator=(const Loader&) = delete;
		Loader& operator=(Loader&&) = delete;

		shared_ptr<Object> laod_in_file(long long id);

	private:
		hashtable<long long, Status> status_table_;
	};
}


