//���������������������������������������������������������������������������
//                               Jb
//                               $$$c
//             $$$$$$$$$$$$$$$$$$$$$$b       d$$$$$$$$$$$$$$$$$$$$$P
//            .$$$$$$$$$$$$$$$$$$$$$$$$.     $$$$$$$$$$$$$$$$$$$$$$
//            ^""""""$$$$$P""""3$$$$$$$$c   d$$$$$""""$$$$$$"""""""
//                  4$$$$$"    $$$$$$$$$$b  $$$$$F   .$$$$$F
//                  $$$$$P    4$$$$$$$$$$$$$$$$$$    d$$$$$
//                 4$$$$$"    $$$$$$$$$$$$$$$$$$P    $$$$$F
//                 $$$$$$    4$$$$$""$$$$$$$$$$$    d$$$$$
//                4$$$$$"    $$$$$$  ^$$$$$$$$$P    $$$$$F
//                $$$$$$    4$$$$$%    *$$$$$$$"   J$$$$$
//               4$$$$$%    $$$$$$      ^$$$$$P    $$$$$F
//               """"""     """"""        *$$$"    """"""
//                                         "$$
//                                          ^%
//
//                         Turner - Networking Library
//
//                    Microsoft Windows 95/98/NT Version
//
//  Copyright (c) 1995-1999 by Dan Higdon, Tim Little, and Chuck Walbourn
//
//���������������������������������������������������������������������������
//
// THE AUTHORS MAKE NO WARRANTIES, EXPRESS OR IMPLIED, AS TO THE CORRECTNESS
// OF THIS CODE OR ANY DERIVATIVE WORKS WHICH INCORPORATE IT.  THE AUTHORS
// PROVIDE THE CODE ON AN "AS-IS" BASIS AND EXPLICITLY DISCLAIMS ANY
// LIABILITY, INCLUDING CONSEQUENTIAL AND INCIDENTAL DAMAGES FOR ERRORS,
// OMISSIONS, AND OTHER PROBLEMS IN THE CODE.
//
//���������������������������������������������������������������������������
//
//                        http://www.mythos-engine.org/
//
//���������������������������������������������������������������������������
//
// Created by Dan Higdon and Chuck Walbourn
//
// Turner Network Interface
//
// turnex.cpp
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include <assert.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Turner.hpp"

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//�����������������������  Constructors/Destructors  ������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// TurnerNetwork - Constructor
//���������������������������������������������������������������������������
TurnerNetwork::TurnerNetwork (GUID _guid, const char *_name,
                              int _players, DWORD sflags) :
    TurnerClassic(_guid,_name,_players,sflags)
{
}

TurnerNetwork::TurnerNetwork (GUID _guid, const char *_name,
                              int _players, const char *_passwd, DWORD sflags) :
    TurnerClassic(_guid,_name,_players,_passwd,sflags)
{
}


//���������������������������������������������������������������������������
// TurnerNetwork - Destructor
//���������������������������������������������������������������������������
TurnerNetwork::~TurnerNetwork()
{
    close ();
}



//���������������������������������������������������������������������������
//�����������������������������  Operations  ��������������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// static _player_callback
//���������������������������������������������������������������������������
static BOOL CALLBACK _player_callback (DPID id,
                                       DWORD dwType,
                                       LPCDPNAME lpcName,
                                       DWORD flags,LPVOID context)
{
    TurnerNetwork  *net = (TurnerNetwork *)context;

    switch (dwType)
    {
        case DPPLAYERTYPE_GROUP:
            net->sys_newgroup (id,
                               lpcName->lpszShortNameA, lpcName->lpszLongNameA,
                               0, 0, 0, flags);
        case DPPLAYERTYPE_PLAYER:
            net->sys_newplayer (id,
                                lpcName->lpszShortNameA, lpcName->lpszLongNameA,
                                0, 0, 0, flags);
    }

    return TRUE;
}


//���������������������������������������������������������������������������
// TurnerNetwork - connect_game
//���������������������������������������������������������������������������
int TurnerNetwork::connect_game (GUID guidSession)
{
    if (!pIDP)
        return DPERR_UNAVAILABLE;

    session.guidInstance = guidSession;
    int res = pIDP->Open (&session, DPOPEN_JOIN);
    Sleep(100);

    flags &= ~(TURNER_FLAGS_OPEN | TURNER_FLAGS_HOST);

    if (res == DP_OK)
    {
        flags |= TURNER_FLAGS_OPEN;
        pIDP->EnumGroups  (&guidSession, _player_callback, this,
                           DPENUMPLAYERS_REMOTE);
        pIDP->EnumPlayers (&guidSession, _player_callback, this,
                           DPENUMPLAYERS_REMOTE);
        return DP_OK;
    }

    return res;
}


//���������������������������������������������������������������������������
// TurnerNetwork - create_group
//
// Creates a new group ID, given short and long names.
//���������������������������������������������������������������������������
DPID TurnerNetwork::create_group (const char *short_name,
                                  const char *long_name,
                                  LPVOID data, DWORD size,
                                  DWORD _flags)
{
    if (!pIDP)
        return 0;

    DPID id = 0;

    DPNAME dp_name;
    dp_name.dwSize = sizeof (dp_name);
    dp_name.dwFlags  = 0;
    dp_name.lpszShortNameA = (char *)short_name;
    dp_name.lpszLongNameA  = (char *)long_name;

    pIDP->CreateGroup (&id, &dp_name, data, size, _flags);
    Sleep(500);

    return id;
}


//���������������������������������������������������������������������������
// TurnerNetwork - destroy_group
//
// Destroys a group by ID
//���������������������������������������������������������������������������
void TurnerNetwork::destroy_group (DPID group)
{
    if (pIDP)
        pIDP->DestroyGroup (group);
}


//���������������������������������������������������������������������������
// TurnerNetwork - set_group_name
//
// Sets a given group's name
//���������������������������������������������������������������������������
int TurnerNetwork::set_group_name(DPID group,
                                  const char *short_name, const char *long_name,
                                  DWORD _flags)
{
    if (!pIDP)
        return DPERR_UNAVAILABLE;

    DPNAME dp_name;
    dp_name.dwSize = sizeof (dp_name);
    dp_name.dwFlags  = 0;
    dp_name.lpszShortNameA = (char *)short_name;
    dp_name.lpszLongNameA  = (char *)long_name;

    return pIDP->SetGroupName(group, &dp_name, _flags);
}


//���������������������������������������������������������������������������
// TurnerNetwork - set_group_data
//
// Sets a given group's data
//���������������������������������������������������������������������������
int TurnerNetwork::set_group_data(DPID group, LPVOID data,
                                  DWORD size, DWORD _flags)
{
    if (!pIDP)
        return DPERR_UNAVAILABLE;

    return pIDP->SetGroupData(group, data, size, _flags);
}


//���������������������������������������������������������������������������
// TurnerNetwork - set_group_owner
//
// Sets a given group's owner
//���������������������������������������������������������������������������
int TurnerNetwork::set_group_owner(DPID group, DPID owner)
{
    if (!pIDP)
        return DPERR_UNAVAILABLE;

    return pIDP->SetGroupOwner(group, owner);
}


//���������������������������������������������������������������������������
// TurnerNetwork - join_group
//���������������������������������������������������������������������������
int TurnerNetwork::join_group  (DPID group, DPID player)
{
    if (!pIDP)
        return DPERR_UNAVAILABLE;

    if (!player)
        player = playerid;

    return pIDP->AddPlayerToGroup (group, player);
}


//���������������������������������������������������������������������������
// TurnerNetwork - leave_group
//���������������������������������������������������������������������������
int TurnerNetwork::leave_group (DPID group, DPID player)
{
    if (!pIDP)
        return DPERR_UNAVAILABLE;

    if (!player)
        player = playerid;

    return pIDP->DeletePlayerFromGroup (group, player);
}


//���������������������������������������������������������������������������
// TurnerNetwork - add_group
//���������������������������������������������������������������������������
int TurnerNetwork::add_group (DPID pgroup, DPID group)
{
    if (!pIDP)
        return DPERR_UNAVAILABLE;

    return pIDP->AddGroupToGroup (pgroup, group);
}


//���������������������������������������������������������������������������
// TurnerNetwork - remove_group
//���������������������������������������������������������������������������
int TurnerNetwork::remove_group (DPID pgroup, DPID group)
{
    if (!pIDP)
        return DPERR_UNAVAILABLE;

    return pIDP->DeleteGroupFromGroup (pgroup, group);
}


//���������������������������������������������������������������������������
// TurnerNetwork - send_ex
//���������������������������������������������������������������������������
int TurnerNetwork::send_ex (DPID from, DPID to, LPVOID data, DWORD size,
                            DWORD priority, DWORD timeout,
                            LPVOID context, LPDWORD msgid)
{
    if (!pIDP)
        return DPERR_UNAVAILABLE;

    if (!from)
        from = playerid;

    int res = pIDP->SendEx (from, to, sendfl, data, size,
                            priority, timeout, context, msgid);
    Sleep(0);

    return res;
}

//���������������������������������������������������������������������������
// TurnerNetwork - send_guaranteed_ex
//���������������������������������������������������������������������������
int TurnerNetwork::send_guaranteed_ex (DPID from, DPID to,
                                       LPVOID data, DWORD size,
                                       DWORD priority, DWORD timeout,
                                       LPVOID context, LPDWORD msgid)
{
    if (!pIDP)
        return DPERR_UNAVAILABLE;

    if (!from)
        from = playerid;

    int res = pIDP->SendEx (from, to, sendfl | DPSEND_GUARANTEED, data, size,
                            priority, timeout, context, msgid);
    Sleep(0);

    return res;
}


//���������������������������������������������������������������������������
// TurnerNetwork - broadcast_ex
//���������������������������������������������������������������������������
int TurnerNetwork::broadcast_ex (DPID from, LPVOID data, DWORD size,
                                 DWORD priority, DWORD timeout,
                                 LPVOID context, LPDWORD msgid)
{
    if (!pIDP)
        return DPERR_UNAVAILABLE;

    if (!from)
        from = playerid;

    int res = pIDP->SendEx (from, DPID_ALLPLAYERS, sendfl, data, size,
                            priority, timeout, context, msgid);
    Sleep(0);

    return res;
}


//���������������������������������������������������������������������������
// TurnerNetwork - broadcast_guaranteed_ex
//���������������������������������������������������������������������������
int TurnerNetwork::broadcast_guaranteed_ex (DPID from, LPVOID data, DWORD size,
                                            DWORD priority, DWORD timeout,
                                            LPVOID context, LPDWORD msgid)
{
    if (!pIDP)
        return DPERR_UNAVAILABLE;

    if (!from)
        from = playerid;

    int res = pIDP->SendEx (from, DPID_ALLPLAYERS, sendfl | DPSEND_GUARANTEED,
                            data, size, priority, timeout, context, msgid);
    Sleep(0);

    return res;
}



//���������������������������������������������������������������������������
//��������������������  System Message Process Routines  ��������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// TurnerNetwork - handle_sysmsg
//���������������������������������������������������������������������������
void TurnerNetwork::handle_sysmsg (DPID to, DPMSG_GENERIC *pmsg, DWORD size)
{
    assertMyth("TurnerNetwork::handle_sysmsg needs valid input", pmsg != 0);

    switch (pmsg->dwType)
    {
        case DPSYS_CREATEPLAYERORGROUP:
            {
                DPMSG_CREATEPLAYERORGROUP *msg = (DPMSG_CREATEPLAYERORGROUP *)pmsg;
                switch (msg->dwPlayerType)
                {
                    case DPPLAYERTYPE_PLAYER:
                        sys_newplayer (msg->dpId,
                                       msg->dpnName.lpszShortNameA,
                                       msg->dpnName.lpszLongNameA,
                                       msg->lpData, msg->dwDataSize,
                                       msg->dpIdParent, msg->dwFlags);
                        break;
                    case DPPLAYERTYPE_GROUP:
                        sys_newgroup  (msg->dpId,
                                       msg->dpnName.lpszShortNameA,
                                       msg->dpnName.lpszLongNameA,
                                       msg->lpData, msg->dwDataSize,
                                       msg->dpIdParent, msg->dwFlags);
                        break;
                }
            }
            break;

        case DPSYS_DESTROYPLAYERORGROUP:
            {
                DPMSG_DESTROYPLAYERORGROUP *msg = (DPMSG_DESTROYPLAYERORGROUP *)pmsg;
                switch (msg->dwPlayerType)
                {
                    case DPPLAYERTYPE_PLAYER:
                        sys_delplayer (msg->dpId,msg->dwFlags);
                        break;
                    case DPPLAYERTYPE_GROUP:
                        sys_delgroup (msg->dpId,msg->dwFlags);
                        break;
                }
            }
            break;

        case DPSYS_SETPLAYERORGROUPNAME:
            {
                DPMSG_SETPLAYERORGROUPNAME *msg = (DPMSG_SETPLAYERORGROUPNAME *)pmsg;
                switch (msg->dwPlayerType)
                {
                    case DPPLAYERTYPE_PLAYER:
                        sys_set_player_name(msg->dpId,
                                            msg->dpnName.lpszShortNameA,
                                            msg->dpnName.lpszLongNameA);
                        break;
                    case DPPLAYERTYPE_GROUP:
                        sys_set_group_name(msg->dpId,
                                           msg->dpnName.lpszShortNameA,
                                           msg->dpnName.lpszLongNameA);
                        break;
                }
            }
            break;

        case DPSYS_SETPLAYERORGROUPDATA:
            {
                DPMSG_SETPLAYERORGROUPDATA *msg = (DPMSG_SETPLAYERORGROUPDATA *)pmsg;
                switch (msg->dwPlayerType)
                {
                    case DPPLAYERTYPE_PLAYER:
                        sys_set_player_data(msg->dpId,
                                            msg->lpData, msg->dwDataSize);
                        break;
                    case DPPLAYERTYPE_GROUP:
                        sys_set_group_data(msg->dpId,
                                           msg->lpData, msg->dwDataSize);
                        break;
                }
            }
            break;

        case DPSYS_SETGROUPOWNER:
            {
                DPMSG_SETGROUPOWNER *msg = (DPMSG_SETGROUPOWNER*)pmsg;
                sys_set_group_owner(msg->idGroup, msg->idNewOwner,
                                    msg->idOldOwner);
            }
            break;

        case DPSYS_ADDPLAYERTOGROUP:
            {
                DPMSG_ADDPLAYERTOGROUP *msg = (DPMSG_ADDPLAYERTOGROUP *)pmsg;
                sys_add_player_to_group (msg->dpIdGroup, msg->dpIdPlayer);
            }
            break;

        case DPSYS_DELETEPLAYERFROMGRP:
            {
                DPMSG_ADDPLAYERTOGROUP *msg = (DPMSG_ADDPLAYERTOGROUP *)pmsg;
                sys_remove_player_from_group (msg->dpIdGroup,
                                              msg->dpIdPlayer);
            }
            break;

        case DPSYS_ADDGROUPTOGROUP:
            {
                DPMSG_ADDGROUPTOGROUP *msg = (DPMSG_ADDGROUPTOGROUP *)pmsg;
                sys_add_group_to_group (msg->dpIdParentGroup,
                                        msg->dpIdGroup);
            }
            break;

        case DPSYS_DELETEGROUPFROMGROUP:
            {
                DPMSG_ADDGROUPTOGROUP *msg = (DPMSG_ADDGROUPTOGROUP *)pmsg;
                sys_remove_group_from_group (msg->dpIdParentGroup,
                                             msg->dpIdGroup);
            }
            break;

        case DPSYS_SENDCOMPLETE:
            {
                DPMSG_SENDCOMPLETE *msg = (DPMSG_SENDCOMPLETE*)pmsg;
                sys_send_complete(msg->idFrom, msg->idTo,
                                  msg->lpvContext, msg->dwMsgID,
                                  msg->dwSendTime);
            }
            break;

        default:
            TurnerClassic::handle_sysmsg(to,pmsg,size);
    }
}


//���������������������������������������������������������������������������
// TurnerNetwork - sys_newgroup
//���������������������������������������������������������������������������
void TurnerNetwork::sys_newgroup (DPID group,
                                  LPCSTR short_name, LPCSTR long_name,
                                  LPVOID data, DWORD size, DPID pgroup,
                                 DWORD _flags)
{
}


//���������������������������������������������������������������������������
// TurnerNetwork - sys_delgroup
//���������������������������������������������������������������������������
void TurnerNetwork::sys_delgroup (DPID group, DWORD _flags)
{
}


//���������������������������������������������������������������������������
// TurnerNetwork - sys_set_group_name
//���������������������������������������������������������������������������
void TurnerNetwork::sys_set_group_name (DPID group, LPCSTR short_name, LPCSTR long_name)
{
}


//���������������������������������������������������������������������������
// TurnerNetwork - sys_set_group_data
//���������������������������������������������������������������������������
void TurnerNetwork::sys_set_group_data(DPID group, LPVOID data, DWORD size)
{
}


//���������������������������������������������������������������������������
// TurnerNetwork - sys_set_group_owner
//���������������������������������������������������������������������������
void TurnerNetwork::sys_set_group_owner(DPID group, DPID newowner, DPID oldowner)
{
}


//���������������������������������������������������������������������������
// TurnerNetwork - sys_add_player_to_group
//���������������������������������������������������������������������������
void TurnerNetwork::sys_add_player_to_group (DPID group, DPID player)
{
}


//���������������������������������������������������������������������������
// TurnerNetwork - sys_remove_player_from_group
//���������������������������������������������������������������������������
void TurnerNetwork::sys_remove_player_from_group (DPID group, DPID player)
{
}


//���������������������������������������������������������������������������
// TurnerNetwork - sys_add_group_to_group
//���������������������������������������������������������������������������
void TurnerNetwork::sys_add_group_to_group (DPID parent, DPID group)
{
}


//���������������������������������������������������������������������������
// TurnerNetwork - sys_remove_group_from_group
//���������������������������������������������������������������������������
void TurnerNetwork::sys_remove_group_from_group (DPID parent, DPID group)
{
}


//���������������������������������������������������������������������������
// TurnerNetwork - sys_send_complete
//���������������������������������������������������������������������������
void TurnerNetwork::sys_send_complete (DPID from, DPID to,
                                       LPVOID context, DWORD msgid,
                                       DWORD sendtime)
{
}



//���������������������������������������������������������������������������
//���������������������������  Utility Routines  ����������������������������
//���������������������������������������������������������������������������

//��� End of module - turnex.cpp ���
