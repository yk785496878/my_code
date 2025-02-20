
#include "./comm_listener.h"

#include "./common/uuid.h"
BEGIN_NS_AD
CommListener::CommListener()
{
    strID = UUID::generate_uuid();
}

CommListener::CommListener(const char *name)
{
    strID = name;
}

void CommListener::SetID(const char *id)
{
    memcpy(&strID[0], id, strlen(&id[0]));
}

char *CommListener::GetID()
{
    return &strID[0];
}
END_NS_AD
