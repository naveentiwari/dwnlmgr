// Shree Ganeshaya Namah

#include <base.h>

/**
* @brief - Constructor to initialize the class members and do the first separation.
*
* @param [in] pSrcStr       - Source string
* @param [in] pSepChar      - Separator character
* @param [in] pUseExtBuf    - Pointer to external buffer, [Optional]
*/
Tokenize::Tokenize (CStrPtr pSrcStr, Char pSepChar, StrPtr pUseExtBuf, bool pIgnoreIfUnMatched)
{
    // get the length of the source string
    vStrLen             = StrLen (pSrcStr);

    // set the separation position to zero
    vSepTill            = 0;
    vIgnoreIfUnMatched  = pIgnoreIfUnMatched;

    // if the external buffer has not been provided, allocate 1
    if (!pUseExtBuf) {

        vIsExternalBuf      = true;
        vExternalBuf        = (StrPtr) Malloc (MAX_TXT_BUF);

    // external buffer provided
    } else {

        vIsExternalBuf      = false;
        vExternalBuf        = pUseExtBuf;
    }

    // copy the string in the buffer
    memcpy (vExternalBuf, pSrcStr, (vStrLen + 1) * sizeof(Char));

    // do the separation first time
    Separate (pSepChar);
}

/**
* @brief - Destructor to release the memory
*/
Tokenize::~Tokenize ()
{
    // release the buffer if it was allocated
    if (vIsExternalBuf)
        Free (vExternalBuf);
}

/**
* @brief - This function separates the string into two parts by the first separator character
*
* @param [in] pSepChar - Separator character
*/
void Tokenize::Separate (Char pSepChar)
{
        // initialize the index to start from the position already traversed
        ULong       ndx = vSepTill;

    // walk the string and check the character
    while (ndx < vStrLen && vExternalBuf[ndx] != pSepChar) {
        ++ndx;
    }

    // check if we have found the separator character
    if (ndx == vStrLen) {

        // check if it has to be ignored
        if (vIgnoreIfUnMatched)
            vFirstPart          = NULL;

        // finish the search, make the last as first and last as NULL
        else {
            vFirstPart      = vExternalBuf + vSepTill;
            vLastPart       = NULL;
            vSepTill        = vStrLen;
        }

    // separator character
    } else {

        // replace the separator character by EOS
        vExternalBuf[ndx]   = EOS;
        // set the first part
        vFirstPart          = vExternalBuf + vSepTill;
        // set the last part
        vLastPart           = vExternalBuf + ndx + 1;
        // set the traversed position
        vSepTill            = ndx + 1;
    }
}
