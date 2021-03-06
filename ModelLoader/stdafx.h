// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// Additional headers our program requires.

#include <fstream>
#include <string>
#include <sstream>

#include <atlstr.h>
using namespace ATL;

#include "../../CommonLibOgl/CommonLibOgl/CommonLibOgl.h"

#include "PMaterialInfo.h"
#include "PMeshPartInfo.h"
#include "PMeshData.h"

#include "PMaterial.h"

#include "PMeshPart.h"
#include "PMesh.h"
#include "PModel.h"

#include "ObjParser.h"
