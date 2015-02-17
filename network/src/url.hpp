// Shree Ganeshaya Namah

#ifndef NETWORK_URL_HPP
#define NETWORK_URL_HPP

enum    eCommProtocol  {
        CP_UNKNOWN  = 0,
        CP_HTTP,
        CP_HTTPS,
        CP_FTP,
        CP_UDF
};

class URL {
public:
                            URL                     (CStrPtr pURLStr);
                           ~URL                     ();

        CStrPtr             GetFirstIPStr           ();
        CStrPtr             GetNextIPStr            ();

inline  uint16_t            GetPort                 ();

inline  eCommProtocol       GetCommProtocol         ();
inline  CStrPtr             GetCommProtocolStr      ();

inline  CStrPtr             GetFullURL              ();
inline  CStrPtr             GetBaseURL              ();
inline  CStrPtr             GetFilePath             ();

private:

        void                ParseURL                ();
        void                ConvertStrToCommProtocol();
        void                ResolveToIP             ();

        StrPtr              vOriginalURL;           ///< Original copy of the URL
        StrPtr              vURLBuffer;             ///< Buffer for storing content

        StrPtr              vCommProtocolStr;       ///< pointer to protocol
        StrPtr              vBaseURL;               ///< base URL
        StrPtr              vFilePath;              ///< file path
        StrPtr              vIPStr;                 ///< ip

        struct addrinfo     vHints;
        struct addrinfo *   vRes;
        struct addrinfo *   vCurAddrInfo;

        uint16_t            vPort;                  ///< port number
        eCommProtocol       vCommProtocol;          ///< communication protocol
};

#include "url.hxx"

#endif // NETWORK_URL_HPP
