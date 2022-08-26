/*
    * @Author: Victor Ghost Checkpoints (g_checkpoints)
    * @Version: 0.2 26/08/22 (EU)

    * @Github: https://github.com/VictorMacielGhost/g_checkpoints
    * @Wiki: https://github.com/VictorMacielGhost/g_checkpoints/wiki 

    * @Warning: Don't Remove the credits!
*/

#if defined _g_checkpoints
    #endinput
#else
    #define _g_checkpoints_included
    #define _g_checkpoints_version "0.2"
#endif

#if !defined _samp_included
    #include <a_samp>
    #warning include `a_samp` before include g_checkpoints.
#endif

// defines

#define     MAX_CHECKPOINTS             (G_CP_ID:0x400)
#define     INVALID_CHECKPOINT_ID       (G_CP_ID:0xFFFF)

#define     CHECKPOINT_TYPE_NORMAL      (G_CP_TYPE:0b0000)
#define     CHECKPOINT_TYPE_RACE        (G_CP_TYPE:0b0001)

// enums

enum E_CHECKPOINTS_INFO
{
    G_CP_ID:E_CHECKPOINTS_ID,
    G_CP_TYPE:E_CHECKPOINTS_TYPE,
    E_CHECKPOINTS_FORPLAYERID,
    Float:E_CHECKPOINTS_X,
    Float:E_CHECKPOINTS_Y,
    Float:E_CHECKPOINTS_Z,
    Float:E_CHECKPOINTS_R,
    bool:E_CHECKPOINTS_ACTIVE
};

// Global Variables
static CheckpointsInfo[G_CP_ID:MAX_CHECKPOINTS][E_CHECKPOINTS_INFO];

// forwards

forward OnCheckpointCreated(G_CP_ID:checkpointid, G_CP_TYPE:type, forplayerid);
forward OnPlayerEnterGCheckpoint(playerid, G_CP_ID:checkpointid);

// internal functions

static stock G_CP_ID:GetNextCheckpointID()
{
    for(new G_CP_ID:i; i < MAX_CHECKPOINTS; i++)
    {
        if(!CheckpointsInfo[i][E_CHECKPOINTS_ACTIVE]) return i;
    }
    printf("[Checkpoints]: [ERROR]: Limits of checkpoints reached. Can not return one real id");
    return INVALID_CHECKPOINT_ID;
}

static stock SetCheckpointType(G_CP_ID:checkpointid, G_CP_TYPE:type)
{
    CheckpointsInfo[checkpointid][E_CHECKPOINTS_TYPE] = type;
}

static stock G_CP_TYPE:GetCheckpointType(G_CP_ID:checkpointid)
{
    return CheckpointsInfo[checkpointid][E_CHECKPOINT_TYPE];
}

// functions

stock G_CP_ID:SetPlayerCheckpointEx(playerid, G_CP_TYPE:type, Float:x, Float:y, Float:z, Float:range)
{
    new G_CP_ID:checkpointid = GetNextCheckpointID();
    CheckpointsInfo[checkpointid][E_CHECKPOINTS_ID] = checkpointid;
    CheckpointsInfo[checkpointid][E_CHECKPOINTS_X] = x;
    CheckpointsInfo[checkpointid][E_CHECKPOINTS_Y] = y;
    CheckpointsInfo[checkpointid][E_CHECKPOINTS_Z] = z;
    CheckpointsInfo[checkpointid][E_CHECKPOINTS_R] = range;
    SetCheckpointType(checkpointid, type);
    ToggleCheckpointActive(checkpointid, true);

    if(type == CHECKPOINT_TYPE_NORMAL)
    {
        SetPlayerCheckpoint(playerid, x, y, z, range);
    }

    // CallLocalFunction("OnCheckpointCreate", "iii", checkpointid, type, playerid);
    return CheckpointsInfo[checkpointid][E_CHECKPOINTS_ID];
}

stock CountCurrentCheckpoints()
{
    return GetNextCheckpointID() - 1;
}

stock SetMaxCheckpoints(value)
{
    #undef MAX_CHECKPOINTS
    #define MAX_CHECKPOINTS (value);
}

stock ToggleCheckpointActive(G_CP_ID:checkpointid, bool:toggle)
{
    CheckpointsInfo[checkpointid][E_CHECKPOINTS_ACTIVE] = toggle;
}

stock bool:IsCheckpointActive(G_CP_ID:checkpointid)
{
    return CheckpointsInfo[checkpointid][E_CHECKPOINTS_ACTIVE];
}

// deprecated