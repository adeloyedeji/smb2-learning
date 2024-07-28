#ifndef _SMBL_H_
#define _SMBL_H_

#include "client.h"
#include "common.h"
#include "hash.h"
#include "list.h"
#include "logger.h"
#include "negotiate.h"
#include "queue.h"
#include "util.h"


struct smb2_header* generate_smb2_header(int credit_charge);

#endif //_SMBL_H_