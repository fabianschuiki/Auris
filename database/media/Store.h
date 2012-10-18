/* Copyright © 2012 Fabian Schuiki, Sandro Sgier */
#pragma once
#include <common/Blob.h>
#include <common/Path.h>
#include <gc_cpp.h>

namespace database
{
	namespace media
	{
		class Store : public gc
		{
			Path path;
		public:
			Store(const Path &path);
			void persist(const Blob &data,
				std::string name, std::string format);
			Blob load(std::string name, std::string format);
			void setMainFormat(std::string name, std::string format);
			std::string getMainFormat(std::string name);
		};
	}
}