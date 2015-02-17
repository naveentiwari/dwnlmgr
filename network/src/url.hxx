// Shree Ganeshaya Namah

#ifndef NETWORK_URL_HXX
#define NETWORK_URL_HXX

/**
* @brief - This function returns the port specified in the URL
*
* @return uint16_t  - port number
*/
uint16_t URL::GetPort ()
{
    return vPort;
}

/**
* @brief - This function returns the communication protocol (enum)
*
* @return eCommProtocol - communication protocol
*/
eCommProtocol URL::GetCommProtocol ()
{
    return vCommProtocol;
}

/**
* @brief - This function returns the fully qualified URL
*
* @return CStrPtr - full URL
*/
CStrPtr URL::GetFullURL ()
{
    return vOriginalURL;
}

/**
* @brief - This function returns the communication protocol
*
* @return 
*/
CStrPtr URL::GetCommProtocolStr ()
{
    return vCommProtocolStr;
}

CStrPtr URL::GetBaseURL ()
{
    return vBaseURL;
}

CStrPtr URL::GetFilePath ()
{
    return vFilePath;
}

#endif // NETWORK_URL_HXX
