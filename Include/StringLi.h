//RC  4/29/2002  \HRandy95\Include\StringLi.h
#pragma once

#include "StrClass.h"
#include <afxtempl.h>

class StringList final : public CList<String, String &> {};
