// Shree Ganeshaya Namah

#ifndef BASE_DATATYPE_H
#define BASE_DATATYPE_H

#if defined(CHAR8)
typedef         char                    Char;
#elif defined(CHAR16)
typedef         char16_t                Char;
#elif defined(CHAR32)
typedef         char32_t                Char;
#endif

typedef         int64_t                 Long64;
typedef         int32_t                 Long;
typedef         int16_t                 Short;
typedef         int8_t                  Byte;

typedef         const int64_t           CLong64;
typedef         const int32_t           CLong;
typedef         const int16_t           CShort;
typedef         const int8_t            CByte;

typedef         uint64_t                ULong64;
typedef         uint32_t                ULong;
typedef         uint16_t                UShort;
typedef         uint8_t                 UByte;

typedef         const uint64_t          CULong64;
typedef         const uint32_t          CULong;
typedef         const uint16_t          CUShort;
typedef         const uint8_t           CUByte;

typedef         Char *                  StrPtr;
typedef         const Char *            CStrPtr;

#endif // BASE_DATATYPE_H
