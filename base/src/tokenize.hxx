// Shree Ganeshaya Namah

#ifndef BASE_TOKENIZE_HXX
#define BASE_TOKENIZE_HXX

/**
* @brief - This function returns the first part of the separation
*
* @return StrPtr - Pointer to string
*/
StrPtr Tokenize::GetFirstPart ()
{
    return vFirstPart;
}

/**
* @brief - This function returns the remaining part of the string
*
* @return 
*/
StrPtr Tokenize::GetLastPart ()
{
    return vLastPart;
}

#endif // BASE_TOKENIZE_HXX
