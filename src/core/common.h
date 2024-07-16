#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdint.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DIALECT_2_0_2   0x0202
#define DIALECT_2_1_0   0x0210
#define DIALECT_3_0_0   0x0300
#define DIALECT_3_0_2   0x0302
#define DIALECT_3_1_1   0x0311
#define DIALECT_COUNT   5

#define COMMAND_NEGOTIATE                           0x0000
#define COMMAND_SESSION_SETUP                       0x0001
#define COMMAND_LOGOFF                              0x0002
#define COMMAND_TREE_CONNECT                        0x0003
#define COMMAND_TREE_DISCONNECT                     0x0004
#define COMMAND_CREATE                              0x0005
#define COMMAND_CLOSE                               0x0006
#define COMMAND_FLUSH                               0x0007
#define COMMAND_READ                                0x0008
#define COMMAND_WRITE                               0x0009
#define COMMAND_LOCK                                0x000A
#define COMMAND_IOCTL                               0x000B
#define COMMAND_CANCEL                              0x000C
#define COMMAND_ECHO                                0x000D
#define COMMAND_QUERY_DIRECTORY                     0x000E
#define COMMAND_CHANGE_NOTIFY                       0x000F
#define COMMAND_QUERY_INFO                          0x0010
#define COMMAND_SET_INFO                            0x0011
#define COMMAND_OPLOCK_BREAK                        0x0012
#define COMMAND_SERVER_TO_CLIENT_NOTIFICATION       0x0013

#define HEADER_FLAG_SERVER_TO_REDIR                 0x00000001
#define HEADER_FLAG_ASYNC_COMMAND                   0x00000002
#define HEADER_FLAG_RELATED_OPERATION               0x00000004
#define HEADER_FLAG_SIGNED                          0x00000008
#define HEADER_FLAG_PRIORITY_MASK                   0x00000070
#define HEADER_FLAG_DFS_OPERATION                   0x10000000
#define HEADER_FLAG_REPLAY_OPERATION                0x20000000

#define SMB2_ERROR_ID_DEFAULT                       0x00000000
#define SMB2_ERROR_ID_SHARE_REDIRECT                0x72645253

#define SYMBOLIC_LINK_ERROR_RESPONSE_FLAG_ABSOLUTE  0x00000000
#define SYNBOLIC_LINK_ERROR_RESPONSE_FLAG_RELATIVE  0x00000001

#define CAPABILITIES_GLOBAL_CAP_DFS                 0x00000001
#define CAPABILITIES_GLOBAL_CAP_LEASING             0x00000002
#define CAPABILITIES_GLOBAL_CAP_LARGE_MTU           0x00000004
#define CAPABILITIES_GLOBAL_CAP_MULTI_CHANNEL       0x00000008
#define CAPABILITIES_GLOBAL_CAP_PERSISTENT_HANDLES  0x00000010
#define CAPABILITIES_GLOBAL_CAP_DIRECTORY_LEASING   0x00000020
#define CAPABILITIES_GLOBAL_CAP_ENCRYPTION          0x00000040
#define CAPABILITIES_GLOBAL_CAP_NOTIFICATIONS       0x00000080

struct smbd_tcp_header{
    char Zero;
    char StreamProtocolLength[3];
    void *SMB2Message;
};

struct smb2_header {
    char ProtocolID[4];
    short StructureSize;
    short CreditCharge;
    short ChannelSequence;
    short Reserved;
    int Status;
    short Command;
    short CreditsRequestResponse;
    int Flags;
    int NextCommand;
    int64_t MessageId;
    int Reserved2;
    int TreeId;
    int64_t SessionId;
    int64_t Signature[2];
};

struct smb2_error_context_response{
    int ErrorDataLength;
    int ErrorId;
    void *ErrorContextData;
};

struct smb2_error_context_symbolic_link_error_response {
    int SymLinkLength;
    int SymLinkErrorTag;
    int ReparseTag;
    short ReparseDataLength;
    short UnparsedPathLength;
    short SubstituteNameOffset;
    short SubstituteNameLength;
    short PrintNameOffset;
    short PrintNameLength;
    int Flags;
    void *PathBuffer;
};

struct smb2_error_context_share_redirect_error_response {
    int StructureSize;
    int NotificationType;
    int ResourceNameOffset;
    int ResourceNameLength;
    short Reserved;
    short TargetType;
    int IpAddrCount;
    void *IpAddrMoveList;
    char *ResourceName;
};

struct smb2_error_response {
    short StructureSize;
    char ErrorContextCount;
    char Reserved;
    int ByteCount;
    struct smb2_error_context_response *ErrorData;
};

struct global_config {
    bool RequireMessageSigning;
    bool IsEncryptionSupported;
    bool IsCompressionSupported;
    bool IsChainedCompressionSupported;
    bool IsRDMATransformSupported;
    bool DisableEncryptionOverSecureTransport;
    bool IsSigningCapabilitiesSupported;
    bool IsTransportCapabilitiesSupported;
};

struct client_global_config {
    short ClientGuid[8];
    short MaxDialect;
    bool RequireSecureNegotiate;
    bool CompressAllRequests;
    bool IsMutualAuthOverQUICSupported;
    struct hash *ConnectionTable;
    struct hash *GlobalFileTable;
    struct hash *ServerName;
    struct hash *ShareList;
    struct hash *ClientCertificateMappingTable;
};

struct client_smb2_server;
struct user_credentials;
struct date_time;

struct file_id {
    int Persistent[2];
    int Volatile[2];
};

struct client_smb2_transport_connection {
    struct hash *SessionTable;
    struct hash *PreauthSessionTable;
    struct hash *OutstandingRequests;
    struct hash *SequenceWindow;
    void *GSSNegotiateToken;
    int MaxTransactSize;
    int MaxReadSize;
    int MaxWriteSize;
    short ServerGuid[8];
    bool RequireSigning;
    char ServerName[255];
    short Dialect;
    bool SupportsFileLeasing;
    bool SupportsMultiCredit;
    short ClientGuid[8];
    bool SupportsDirectoryLeasing;
    bool SupportsMultiChannel;
    bool SupportsPersistentHandles;
    bool SupportsEncryption;
    void *ClientCapabilities;
    void *ServerCapabilities;
    short ClientSecurityMode;
    short ServerSecurityMode;
    struct client_smb2_server *Server;
    void *Dialects;
    short PreauthIntegrityHashId;
    short PreauthIntegrityHashValue;
    short CipherId;
    short *CompressionIds;
    bool SupportsChainedCompression;
    short *RDMATransformIds;
    short SigningAlgorithmId;
    bool AcceptTransportSecurity;
};

struct client_smb2_channel {
    char SigningKey[1024];
    struct client_smb2_transport_connection *Connection;
};

struct client_smb2_session {
    int SessionId[2];
    struct hash *TreeConnectTable;
    char SessionKey[16];
    bool SigningRequired;
    struct client_smb2_transport_connection *Connection;
    struct user_credentials *UserCredentials;
    struct hash *OpenTable;
    bool IsAnonymous;
    bool ISGuest;
    struct client_smb2_channel *ChannelList;
    short ChannelSequence;
    bool EncryptData;
    short EncryptionKey;
    short DecryptionKey;
    short SigningKey[8];
    short ApplicationKey[8];
    short PreauthIntegrityHashValue;
    void *FullSessionKey;
};

struct client_smb2_tree_connect {
    char ShareName[255];
    int TreeConnectId;
    struct client_smb2_session *Session;
    bool IsDfsShare;
    bool IsCAShare;
    bool EncryptData;
    bool IsScaleoutShare;
    bool CompressData;
};

struct client_smb2_open_file {
    struct hash *OpenTable;
    short LeaseKey[8];
    short LeaseState;
    int LeaseEpoch;
};

struct client_smb2_lock_operations {
    int SequenceNumber;
    bool Free;
};

struct client_smb2_application_open_file {
    struct file_id *FileId;
    struct client_smb2_tree_connect *TreeConnect;
    struct client_smb2_transport_connection *Connection;
    struct client_smb2_session *Session;
    short OplockLevel;
    bool Durable;
    char FileName[255];
    bool ResilientHandle;
    struct date_time *LastDisconnectTime;
    int ResilientTimeout;
    struct client_smb2_lock_operations OperationBuckets[64];
    short DesiredAccess;
    short ShareMode;
    short CreateOptions;
    short FileAttributes;
    short CreateDisposition;
    int DurableTimeout;
    struct hash *OutstandingRequests;
    short CreateGuid[8];
    bool IsPersistent;
};

struct smb2_addresses {
    struct in_addr IPv4;
    struct in6_addr IPv6;
};

struct client_smb2_server {
    short ServerGuid[8];
    short DialectRevision;
    void *Capabilities;
    short SecurityMode;
    struct smb2_addresses *AddressList;
    char ServerName[255];
    short CipherId;
    short *RDMATransformIds;
    short SigningAlgorithmId;
};

struct client_smb2_share {
    char PathName[255];
    bool EncryptData;
};

#endif //_COMMON_H_