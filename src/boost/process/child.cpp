#include <boost/process.hpp>
#include <boost/process/async.hpp>
#include <iostream>
#include <functional> // std::bind & placeholders
#include <sstream>    // ostringstream

namespace bp = boost::process;
using namespace std::placeholders;
using sv = std::vector<std::string>;

static void exit_handler(bp::child& process, int e, std::error_code ec) {
    std::cout << "Process " << process.id() << " exited with " << e << " (" << ec.message() << ")\n";
}

int main() {
//    auto work = make_work_guard(io);


	// https://www.boost.org/doc/libs/master/doc/html/boost/process/child.html#idm46243917696944-bb
	// As you can see the above link, child receives variadic template Args, which means we dont have to care about the order of arguments. 
		auto p = bp::child(sv{"/root/infinite arg1" }, bp::env["DW"]=std::string("great"),
				bp::on_exit([](int e, std::error_code ec){std::cout<< "end of my life" <<std::endl;})
			);

		std::cout<< "pid of my child " <<p.id()<<std::endl;
		//.detach makes child alive even if  the object destructed 
		p.detach();
//    work.reset(); // allow io to be finished
//    io.run();     // wait for that

    std::cout << "Bye\n";
		return 0;
}
