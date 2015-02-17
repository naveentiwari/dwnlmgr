#include <network.h>

URL::URL (CStrPtr pURLStr)
{
        DERR_IF_NULL(pURLStr);

    vOriginalURL    = MakeString (pURLStr);
    vURLBuffer      = CallocString (MAX_TXT_BUF);
    vPort           = 80;

    vIPStr          = NULL;

    ParseURL ();
    ConvertStrToCommProtocol ();
    ResolveToIP ();
}

URL::~URL ()
{
    Free (vURLBuffer);
}

/**
* @brief - This function parses the URL
*/
void URL::ParseURL ()
{
        Tokenize    tok (vOriginalURL, COLON, vURLBuffer, true);

    if (tok.GetFirstPart ()) {

        vCommProtocolStr    = tok.GetFirstPart ();

        tok.Separate (FORWARD_SLASH);
        tok.Separate (FORWARD_SLASH);
    } else {

        vCommProtocolStr    = NULL;
        vCommProtocol       = CP_UNKNOWN;
    }

        Tokenize    porttok (tok.GetLastPart (), COLON, NULL, true);

    if (porttok.GetFirstPart ()) {
        tok.Separate (COLON);

        vBaseURL    = tok.GetFirstPart ();

        tok.Separate (FORWARD_SLASH);

        vPort       = atoi (tok.GetFirstPart ());
    } else {
        tok.Separate (FORWARD_SLASH);

        vBaseURL    = tok.GetFirstPart ();
    }

    vFilePath   = tok.GetLastPart ();
}

void URL::ConvertStrToCommProtocol ()
{
    if (!vCommProtocolStr) {
        vCommProtocol   = CP_UNKNOWN;

        return;
    }

    if (0 == StrCmp (vCommProtocolStr, _T("http")))
        vCommProtocol   = CP_HTTP;
    else if (0 == StrCmp (vCommProtocolStr, _T("https")))
        vCommProtocol   = CP_HTTPS;
    else {
        DEBUG_ERROR;
    }
}

void URL::ResolveToIP ()
{
        Long        errmsg;

    memset (&vHints, 0, sizeof (addrinfo));

    errmsg  = getaddrinfo (vBaseURL, NULL, &vHints, &vRes);

    if (errmsg) {
        fprintf (stderr, "Unable to resolve URL to IP\n\tError Message: %s\n\tError Code: %d\n", gai_strerror (errmsg), errmsg);

        vRes    = NULL;
        //vHints  = NULL;
    }

    vCurAddrInfo    = vRes;
}

CStrPtr URL::GetFirstIPStr ()
{
        struct      in_addr     addr;

    vCurAddrInfo    = vRes;

    if (vCurAddrInfo) {

        addr.s_addr = ((struct sockaddr_in *)(vRes->ai_addr))->sin_addr.s_addr;

        return inet_ntoa (addr);
    }

    return NULL;
}

CStrPtr URL::GetNextIPStr ()
{
        struct      in_addr     addr;

    if (!vCurAddrInfo)
        return NULL;

    vCurAddrInfo    = vCurAddrInfo->ai_next;

    if (vCurAddrInfo) {

        addr.s_addr = ((struct sockaddr_in *)(vRes->ai_addr))->sin_addr.s_addr;

        return inet_ntoa (addr);
    }

    return NULL;
}

int main ()
{
        URL     url("https://1.as.dl.wireshark.org/win32/Wireshark-win32-1.12.3.exe");
        CStrPtr str;
        Long    sockfd;
        Char    buffer[1024];
        CStrPtr  message = "GET https://1.as.dl.wireshark.org/win32/Wireshark-win32-1.12.3.exe HTTP/1.0\r\nAccept-Encoding: gzip, deflate\r\nAccept-Language: en-US\r\n\r\n";

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");

        return -1;
    }



    int n;

    struct sockaddr_in serv_addr;
    struct hostent *server;
    struct addrinfo hints, *res;
    struct in_addr addr;


    server = gethostbyname(url.GetFirstIPStr ());
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    memset ((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(80);

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        perror("ERROR connecting");

    n = write(sockfd,message ,strlen(message));

    if (n < 0) 
         perror("ERROR writing to socket");

    memset (buffer, 0, 256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
         perror("ERROR reading from socket");
    printf("%s",buffer);

    memset (buffer, 0, 256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
         perror("ERROR reading from socket");
    printf("%s",buffer);

    memset (buffer, 0, 256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
         perror("ERROR reading from socket");
    printf("%s\n",buffer);
    return 0;
    return 0;
}
