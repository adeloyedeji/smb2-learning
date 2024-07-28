#include "smbl.h"

struct smb2_header* generate_smb2_header(int credit_charge)
{
    struct smb2_header* header = NULL;

    header = (struct smb2_header*)calloc(1, sizeof(struct smb2_header));
    if (!header)
        return header;
    
    header->ProtocolID[0] = 0xFE;
    header->ProtocolID[1] = 'S';
    header->ProtocolID[2] = 'M';
    header->ProtocolID[3] = 'B';
    header->StructureSize = SMB2_HEADER_STRUCTURE_SIZE;
    header->CreditCharge = credit_charge;
    header->Reserved = 0;
}