#pragma once

#include "poNodeContainer.h"

class ___FILEBASENAME___;
typedef std::shared_ptr<___FILEBASENAME___> ___FILEBASENAME___Ref;

class ___FILEBASENAME___
: public po::scene::NodeContainer
{
public:
	static ___FILEBASENAME___Ref create();
	virtual ~___FILEBASENAME___();

	void setup() override;

protected:
	___FILEBASENAME___();

private:
 
};