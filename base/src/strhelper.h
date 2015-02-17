// Shree Ganeshaya Namah

#ifndef BASE_STRHELPER_CPP
#define BASE_STRHELPER_CPP

#define     MAX_TXT_BUF         2048

#define     FORWARD_SLASH       Char('/')
#define     BACKSLASH           Char('\\')
#define     EOS                 Char('\0')
#define     COLON               Char(':')

#if defined(CHAR8)
#define     _T(x)               x
#else
#define     _T(x)               L##x
#endif

Long        StrCmp              (CStrPtr, CStrPtr);
Long        StrLen              (CStrPtr);

#endif // BASE_STRHELPER_CPP
