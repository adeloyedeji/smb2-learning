#ifndef __SMB2_CONSTANTS_H__
#define __SMB2_CONSTANTS_H__

// Header command codes
#define COMMAND_NEGOTIATE          0x0000
#define COMMAND_SESSION_SETUP      0x0001
#define COMMAND_LOGOFF             0x0002
#define COMMAND_TREE_CONNECT       0x0003
#define COMMAND_TREE_DISCONNECT    0x0004
#define COMMAND_CREATE             0x0005
#define COMMAND_CLOSE              0x0006
#define COMMAND_FLUSH              0x0007
#define COMMAND_READ               0x0008
#define COMMAND_WRITE              0x0009
#define COMMAND_LOCK               0x000A
#define COMMAND_IOCTL              0x000B
#define COMMAND_CANCEL             0x000C
#define COMMAND_ECHO               0x000D
#define COMMAND_QUERY_DIRECTORY    0x000E
#define COMMAND_CHANGE_NOTIFY      0x000F
#define COMMAND_QUERY_INFO         0x0010
#define COMMAND_SET_INFO           0x0011
#define COMMAND_OPLOCK_BREAK       0x0012
#define COMMAND_SERVER_TO_CLIENT_NOTIFICATION   0x0013


// Header flags codes
#define FLAGS_SERVER_TO_REDIR               0x00000001
#define FLAGS_ASYNC_COMMAND                 0x00000002
#define FLAGS_RELATED_OPERATIONS            0x00000004
#define FLAGS_SIGNED                        0x00000008
#define FLAGS_PRIORITY_MASK                 0x00000070
#define FLAGS_DFS_OPERATIONS                0x10000000
#define FLAGS_REPLAY_OPERATION              0x20000000

// SMB2 Negotiate request security mode
#define NEGOTIATE_SIGNING_ENABLED           0x0001
#define NEGOTIATE_SIGNING_REQUIRED          0x0002

// SMB2 Dialect 3.x Global capabilities
#define GLOBAL_CAP_DFS                      0x00000001
#define GLOBAL_CAP_LEASING                  0x00000002
#define GLOBAL_CAP_LARGE_MTU                0x00000004
#define GLOBAL_CAP_MULTI_CHANNEL            0x00000008
#define GLOBAL_CAP_PERSISTENT_HANDLES       0x00000010
#define GLOBAL_CAP_DIRECTORY_LEASING        0x00000020
#define GLOBAL_CAP_ENCRYPTION               0x00000040
#define GLOBAL_CAP_NOTIFICATIONS            0x00000080

#define SMB202                              0x0202
#define SMB210                              0x0210
#define SMB300                              0x0300
#define SMB302                              0x0302
#define SMB311                              0x0311

#define ERROR_ID_DEFAULT                    0x00000000
#define ERROR_ID_SHARE_REDIRECT             0x72645253

#endif // __SMB2_CONSTANTS_H__