#include <hiredis/hiredis.h>
#include <hiredis/hiredis_ssl.h>
#include <string.h>
#include <stdlib.h>

/*
export LD_LIBRARY_PATH=/usr/local/lib
g++ -std=c++11  demo_ssl.cpp -o demo_ssl.out -I /usr/local/include/hiredis -lhiredis -lhiredis_ssl
*/
int main(int argn, char** argv)
{
    redisSSLContext *ssl;
    redisSSLContextError ssl_error = REDIS_SSL_CTX_NONE;
    redisContext *client;
    redisReply *reply;
    if (argn< 4) {
        printf("Usage: %s <host> <port> <cert> <key> [ca]\n", argv[0]);
        exit(1);
    }
    const char *hostname = (argn> 1) ? argv[1] : "127.0.0.1";
    int port = atoi(argv[2]);
    const char *cert = argv[3];
    const char *key = argv[4];
    const char *ca = argn> 4 ? argv[5] : NULL;

    redisInitOpenSSL();
    ssl = redisCreateSSLContext(ca, NULL, cert, key, NULL, &ssl_error);
    if (!ssl || ssl_error != REDIS_SSL_CTX_NONE) {
        printf("SSL Context error: %s\n", redisSSLContextGetError(ssl_error));
        exit(1);
    }

    struct timeval tv = { 1, 500000 }; // 1.5 seconds
    redisOptions options = {0};
    REDIS_OPTIONS_SET_TCP(&options, hostname, port);
    options.connect_timeout = &tv;
    client = redisConnectWithOptions(&options);

    if (client == NULL || client->err) {
        if (client) {
            printf("Connection error: %s\n", client->errstr);
            redisFree(client);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    if (redisInitiateSSLWithContext(client, ssl) != REDIS_OK) {
        printf("Couldn't initialize SSL!\n");
        printf("Error: %s\n", client->errstr);
        redisFree(client);
        exit(1);
    }

    /* Set */
    reply = (redisReply *)redisCommand(client,"SET %s %s", "welcome", "Hello, DCS for Redis!");
    if (reply == nullptr)
        printf("error in Set Data\n");
    else
    {
        printf("SET: %s\n", reply->str);
        freeReplyObject(reply);
    }

    /* Get */
    reply = (redisReply *)redisCommand(client,"GET welcome");
    if (reply == nullptr)
        printf("error in Set Data\n");
    else
    {
        printf("GET welcome: %s\n", reply->str);
        freeReplyObject(reply);
    }

    redisFree(client);
    return 0;
}
