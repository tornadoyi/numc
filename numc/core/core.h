#ifndef __NC_CORE_H__
#define __NC_CORE_H__


// first thing numc does: stop the compiler from committing suicide
#include "utils/disable_stupid_warnings.h"

// standard libaraies
#include <complex>

// utils
#include "utils/macros/macros.h"
#include "utils/constants.h"
#include "utils/meta.h"
#include "utils/forward_declarations.h"
#include "utils/xpr_helper.h"

#include "num_traits.h"

// core modules
#include "shape.h"
#include "functors/functors.h"
#include "array_op.h"
#include "ops/ops.h"
#include "array.h"




#endif