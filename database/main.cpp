/* Copyright © 2012 Fabian Schuiki, Sandro Sgier */
#include <gc_cpp.h>
#include <iostream>
#include <common/Error.h>
#include "Server.h"


int main(int argc, char *argv[])
{
	GC_INIT();
	database::Server s;
	try {
		s.run(argc, argv);
	} catch (Error *e) {
		std::cerr << "*** " << e->what() << std::endl;
	} catch (std::exception &e) {
		std::cerr << "*** exception: " << e.what() << std::endl;
	} catch (std::exception *e) {
		std::cerr << "*** exception: " << e->what() << std::endl;
	}
	return 0;
}