/* Copyright © 2013 Fabian Schuiki */
#pragma once
#include "Track.hpp"
#include <boost/filesystem/path.hpp>

namespace auris {
namespace db {

class Database
{
public:
	typedef boost::filesystem::path Path;
	typedef list<Track> TrackList;

	const Path path;

	Database(const Path& p);
	~Database();

	void add();
	void remove();

	TrackList& getTrackList();

protected:
	TrackList trackList;
};

} // namespace db
} // namespace auris