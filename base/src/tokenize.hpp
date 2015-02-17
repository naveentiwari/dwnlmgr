// Shree Ganeshaya Namah

#ifndef BASE_TOKENIZE_HPP
#define BASE_TOKENIZE_HPP

/**
* @name - Tokenize 
* @brief - This class helps in braking string into parts using the separator character
*/
class Tokenize {
public:
                        Tokenize                (CStrPtr pSrcStr, Char pSepChar, StrPtr pUseExtBuf = NULL, bool pIgnoreIfUnMatched = true);
                       ~Tokenize                ();

        void            Separate                (Char pSepChar);

inline  StrPtr          GetFirstPart            ();
inline  StrPtr          GetLastPart             ();
private:

        bool            vIsExternalBuf;         ///< flag to check it we are using internal buffer or external buffer
        bool            vIgnoreIfUnMatched;     ///< flag to check if unmatched has to be ignored
        ULong           vSepTill;               ///< variable to store the location in string that we have traversed
        ULong           vStrLen;                ///< length of the string
        StrPtr          vExternalBuf;           ///< buffer used for operating

        StrPtr          vFirstPart;             ///< first part of the string
        StrPtr          vLastPart;              ///< remaining part of the string
};

#include "tokenize.hxx"

#endif // BASE_TOKENIZE_HPP
