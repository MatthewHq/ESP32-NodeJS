class creds
{
    public:
        // int iTest;
        // char *testChar;
        // static const int iTest;
        // static const char* testChar;          // Access specifier
        char* SSID;
        char* PASS;
        char* HOST;
        int PORT;
        char* URL;
        char* ENDPOINT_CA_CERT;
        const char* CA;
        creds();
};