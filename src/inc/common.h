#pragma once
#ifndef __SMB2_COMMON_H__
#define __SMB2_COMMON_H__

#include <stdint.h>
typedef struct header_ {
    uint8_t ProtocolId[4];
    uint16_t StructureSize;
    uint16_t CreditCharge;
    uint16_t ChannelSequence;
    uint16_t Reserved;
    uint32_t Status;
    uint16_t Command;
    uint16_t Credit;
    uint32_t Flags;
    uint32_t NextCommand;
    uint64_t MessageId;
    uint32_t Reserved2;
    uint32_t TreeId;
    uint64_t SessionId;
    uint8_t Signature[16];
};

typedef struct error_response_context_ {
    uint32_t ErrorDataLength;
    uint32_t ErrorId;
    
};

typedef struct error_response_ {
    uint16_t StructureSize;
    uint8_t ErorContextCount;
    uint8_t Reserved;
    uint32_t ByteCount;
    error_response_context_ ErrorContext;
};

typedef struct smb2_negotiate_request_ {
    uint16_t StructureSize;
    uint16_t DialectCount;
    uint16_t SecurityMode;
    uint16_t Reserved;
    uint32_t Capabilities;
    char ClientGuid[16]; //uint64_6
    uint32_t NegotiateContextOffset;
    uint16_t NegotiateContextCount;
    uint16_t Reserved2;
    uint16_t *Dialects;
    union {
        void *Padding;
    };
    
};

#endif //_SMB2_COMMON_H__