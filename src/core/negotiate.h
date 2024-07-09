#ifndef _NEGOTIATE_H_
#define _NEGOTIATE_H_

#include "common.h"

#define NEGOTIATE_SIGNING_ENABLED           0x0001
#define NEGOTIATE_SIGNING_REQUIRED          0x0002

#define CAPABILITIES_GLOBAL_CAP_DFS                 0x00000001
#define CAPABILITIES_GLOBAL_CAP_LEASING             0x00000002
#define CAPABILITIES_GLOBAL_CAP_LARGE_MTU           0x00000004
#define CAPABILITIES_GLOBAL_CAP_MULTI_CHANNEL       0x00000008
#define CAPABILITIES_GLOBAL_CAP_PERSISTENT_HANDLES  0x00000010
#define CAPABILITIES_GLOBAL_CAP_DIRECTORY_LEASING   0x00000020
#define CAPABILITIES_GLOBAL_CAP_ENCRYPTION          0x00000040
#define CAPABILITIES_GLOBAL_CAP_NOTIFICATIONS       0x00000080

#define NEGOTIATE_CONTEXT_TYPE_PREAUTH_INTEGRITY_CAPABILITIES           0x0001
#define NEGOTIATE_CONTEXT_TYPE_ENCRYPTION_CAPABILITIES                  0x0002
#define NEGOTIATE_CONTEXT_TYPE_COMPRESSION_CAPABILITIES                 0x0003
#define NEGOTIATE_CONTEXT_TYPE_NETNAME_NEGOTIATE_CONTEXT_ID             0x0005
#define NEGOTIATE_CONTEXT_TYPE_TRANSPORT_CAPABILITIES                   0x0007
#define NEGOTIATE_CONTEXT_TYPE_SIGNING_CAPABILITIES                     0x0008
#define NEGOTIATE_CONTEXT_TYPE_RESERVED                                 0x0100

#define PREAUTH_INTEGRITY_CAPABILITIES_ALG_SHA512                       0x0001

#define ENCRYPTION_CAPABILITIES_AES_128_CCM                             0x0001
#define ENCRYPTION_CAPABILITIES_AES_128_GCM                             0x0002
#define ENCRYPTION_CAPABILITIES_AES_256_CCM                             0x0003
#define ENCRYPTION_CAPABILITIES_AES_256_GCM                             0x0004

#define COMPRESSION_CAPABILITIES_FLAG_NONE              0x00000000
#define COMPRESSION_CAPABILITIES_FLAG_CHAINED           0x00000001

#define COMPRESSION_CAPABILITIES_ALG_NONE               0x0000
#define COMPRESSION_CAPABILITIES_ALG_LZNT1              0x0001
#define COMPRESSION_CAPABILITIES_ALG_LZ77               0x0002
#define COMPRESSION_CAPABILITIES_ALG_LZ77_HUFFMAN       0x0003
#define COMPRESSION_CAPABILITIES_PATTERN_V1             0x0004
#define COMPRESSION_CAPABILITIES_LZ4                    0x0005

#define TRANSPORT_CAPABILITIES_ACCEPT_TRANSPORT_LEVEL_SECURITY      0x00000001

#define RDMA_TRANSFORM_ID_NONE              0x0000
#define RDMA_TRANSFORM_ID_ENCRYPTION        0x0001
#define RDMA_TRANSFORM_ID_SIGNING           0x0002

#define SIGNING_ALGORITHM_HMAC_SHA256       0x0000
#define SIGNING_ALGORITHM_AES_CMAC          0x0001
#define SIGNING_ALGORITHM_AES_GMAC          0x0002

struct negotiate_request_context_preauth_integrity {
    short HashAlgorithmCount;
    short SaltLength;
    short *HashAlgorithms;
    void *Salt;
};

struct negotiate_request_context_encryption {
    short CipherCount;
    short *Ciphers;
};

struct negotiate_request_context_compression{
    short CompressionAlgorithmCount;
    short Padding;
    int Flags;
    short *CompressionAlgorithms;
};

struct negotiate_request_context_values{
    short ContextType;
    short DataLength;
    void *Data;
};

struct negotiate_request_context_netname_id {
    char NetName[255];
};

struct negotiate_request_context_transport {
    int Flags;
};

struct negotiate_request_context_rdma_transform {
    short TransformCount;
    short Reserved1;
    int Reserved2;
    short *RDMATransformIds;
};

struct negotiate_request_context_signing {
    short SigningAlgorithmCount;
    short *SigningAlgorithms;
};

struct negotiate_request {
    short StructureSize;
    short DialectCount;
    short SecurityMode;
    short Reserved;
    int Capabilities;
    short ClientGuid[8];
    int NegotiateContextOffset;
    short NegotiateContextCount;
    short Reserved2;
    int ClientStartTime[2];
    short *Dialects;
    void *Padding;
    void *NegotiateContextList;
};

struct negotiate_response {
    short StructureSize;
    short SecurityMode;
    short DialectRevision;
    short NegotiateContextCount;
    short ServerGuid[8];
    int Capabilities;
    int MaxTransactSize;
    int MaxReadSize;
    int MaxWriteSize;
    int SystemTime[2];
    int ServerStartTime[2];
    short SecurityBufferOffset;
    short SecurityBufferLength;
    int NegotiateContextOffset;
    void *SecurityBuffer;
    void *Padding;
    void *NegotiateContextList;
};

#endif //_NEGOTIATE_H_