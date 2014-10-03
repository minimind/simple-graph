#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "graphconstructiontest.h"
#include "graphvisitortest.h"
#include "graphcopytopologytest.h"
#include "graphaddtest.h"
#include "graphvisitorignorekeytest.h"

void ensureGraphTestLink()
{
  ensureGraphConstructionTestLink();
  ensureGraphVisitorTestLink();
  ensureGraphCopyTopologyTestLink();
  ensureGraphAddTestLink();
  ensureGraphVisitorIgnoreKeyTestLink();
}
