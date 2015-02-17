#include <base.h>

Long StrCmp (CStrPtr pStr1, CStrPtr pStr2)
{
#ifdef CHAR8
    return strcmp (pStr1, pStr2);
#else
    return wcscmp (pStr1, pStr2);
#endif
}

Long StrLen (CStrPtr pStr)
{
#ifdef CHAR8
    return strlen (pStr);
#else
    return wcslen (pStr);
#endif
}
