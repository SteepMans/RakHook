#ifndef RHEXAMPLE_EVENTS_HPP
#define RHEXAMPLE_EVENTS_HPP

#include <string>

#include "RakNet/BitStream.h"
#include "RakNet/StringCompressor.h"
#include "RakNet/PacketEnumerations.h"

#include "detail.hpp"

inline bool on_player_sync_skin(unsigned char& id, RakNet::BitStream* bs)
{
    if (id != 32)
        return true;

    uint16_t PlayerID;
    uint8_t Team;
    uint32_t Skin;
    float Pos_x;
    float Pos_y;
    float Pos_z;
    float Angle;
    uint32_t Col;
    uint8_t FightingStyle;
    std::vector<uint16_t> SkillLevel;

    bs->Read(PlayerID);
    bs->Read(Team);
    bs->Read(Skin);
    
    bs->Read(Pos_x);
    bs->Read(Pos_y);
    bs->Read(Pos_z);

    bs->Read(Angle);
    bs->Read(Col);
    bs->Read(FightingStyle);

    for (int idx = 0; idx < 11; idx++)
    {
        uint16_t skill;
        bs->Read(skill);

        SkillLevel.push_back(skill);
    }

    bs->Reset();

    bs->Write(PlayerID);
    bs->Write(Team);
    bs->Write(Skin);

    bs->Write(Pos_x);
    bs->Write(Pos_y);
    bs->Write(Pos_z);

    bs->Write(Angle);
    bs->Write(Col);
    bs->Write(FightingStyle);

    for (uint16_t skill : SkillLevel)
    {
        bs->Write(skill);
    }

    return true;
}

inline bool on_scm_event_tuning(unsigned char& id, RakNet::BitStream* bs)
{
    if (id != 96) // RPC_SetPlayerAttachedObject
        return true;

    int PlayerID;
    int VehicleID;
    uint32_t Arg1;
    uint32_t Arg2;
    uint32_t EventType;

    bs->Read(PlayerID);
    bs->Read(VehicleID);
    bs->Read(Arg1);
    bs->Read(Arg2);
    bs->Read(EventType);

    // евент тюнинг
    if (EventType == 2)
    {
        if (Arg1 >= 6384 && Arg1 <= 6444)
            return false;
    }

    bs->Reset();

    bs->Write(PlayerID);
    bs->Write(VehicleID);
    bs->Write(Arg1);
    bs->Write(Arg2);
    bs->Write(EventType);

    return true;
}

inline bool on_stream_in_vehicle(unsigned char& id, RakNet::BitStream* bs)
{
    if (id != 164) // RPC_SetPlayerAttachedObject
        return true;

    uint16_t VehicleID;
    uint32_t ModelID;
    float Position_x;
    float Position_y;
    float Position_z;
    float Angle;
    uint8_t Colour1;
    uint8_t Colour2;
    float Health;
    uint8_t Interior;
    uint32_t DoorDamage;
    uint32_t PanelDamage;
    uint8_t LightDamage;
    uint8_t TyreDamage;
    uint8_t Siren;
    std::vector<int> Mods;
    uint8_t Paintjob;
    int32_t BodyColour1;
    int32_t BodyColour2;

    bs->Read(VehicleID);
    bs->Read(ModelID);
    
    if (ModelID >= 15660)
        ModelID = 400;

    bs->Read(Position_x);
    bs->Read(Position_y);
    bs->Read(Position_z);

    bs->Read(Angle);
    bs->Read(Colour1);
    bs->Read(Colour2);
    bs->Read(Health);
    bs->Read(Interior);
    bs->Read(DoorDamage);
    bs->Read(PanelDamage);
    bs->Read(LightDamage);
    bs->Read(TyreDamage);
    bs->Read(Siren);

    for (int i = 0; i < 14; i++)
    {
        uint8_t mod;
        bs->Read(mod);

        Mods.push_back(mod);
    }
    bs->Read(Paintjob);
    bs->Read(BodyColour1);
    bs->Read(BodyColour2);

    bs->Reset();

    bs->Write(VehicleID);
    bs->Write(ModelID);
    bs->Write(Position_x);
    bs->Write(Position_y);
    bs->Write(Position_z);
    bs->Write(Angle);
    bs->Write(Colour1);
    bs->Write(Colour2);
    bs->Write(Health);
    bs->Write(Interior);
    bs->Write(DoorDamage);
    bs->Write(PanelDamage);
    bs->Write(LightDamage);
    bs->Write(TyreDamage);
    bs->Write(Siren);

    for (uint8_t mod : Mods)
    {
        bs->Write(mod);
    }
    bs->Write(Paintjob);
    bs->Write(BodyColour1);
    bs->Write(BodyColour2);
    return true;
}

inline bool on_set_player_skin(unsigned char& id, RakNet::BitStream* bs)
{
    if (id != 153) // RPC_SetPlayerAttachedObject
        return true;

    uint16_t playerId;
    uint32_t skin;

    bs->Read(playerId);
    bs->Read(skin);

    bs->Reset();

    bs->Write(playerId);

    if (skin > 17006)
        skin = 1;

    bs->Write(skin);
    return true;
}

inline bool on_attach_object_player(unsigned char& id, RakNet::BitStream* bs) 
{
    if (id != 113) // RPC_SetPlayerAttachedObject
        return true;

    uint16_t playerId;
    uint32_t indexSlot;
    bool isCreate;
    uint32_t model;
    uint32_t bone;
    uint32_t color1;
    uint32_t color2;
    float fOffsetX;
    float fOffsetY;
    float fOffsetZ;
    float fRotX;
    float fRotY;
    float fRotZ;
    float fScaleX;
    float fScaleY;
    float fScaleZ;

    bs->Read(playerId);
    bs->Read(indexSlot);
    bs->Read(isCreate);

    if (isCreate)
    {
        bs->Read(model);
        bs->Read(bone);
        
        bs->Read(fOffsetX);
        bs->Read(fOffsetY);
        bs->Read(fOffsetZ);

        bs->Read(fRotX);
        bs->Read(fRotY);
        bs->Read(fRotZ);

        bs->Read(fScaleX);
        bs->Read(fScaleY);
        bs->Read(fScaleZ);

        bs->Read(color1);
        bs->Read(color2);
    }


    bs->Reset();
    bs->Write(playerId);
    bs->Write(indexSlot);
    bs->Write(isCreate);

    if (isCreate)
    {
        bs->Write(16697);
        bs->Write(bone);

        bs->Write(fOffsetX);
        bs->Write(fOffsetY);
        bs->Write(fOffsetZ);

        bs->Write(fRotX);
        bs->Write(fRotY);
        bs->Write(fRotZ);

        bs->Write(fScaleX);
        bs->Write(fScaleY);
        bs->Write(fScaleZ);

        bs->Write(color1);
        bs->Write(color2);
    }

    return true;
}

inline bool on_show_dialog(unsigned char &id, RakNet::BitStream *bs) {
    if (id != 61) // RPC_ShowDialog
        return true;
    unsigned short did;
    unsigned char  style;
    std::string    title, but1, but2, text(4096, 0);

    // read
    bs->Read(did);
    bs->Read(style);
    title = read_with_size<unsigned char>(bs);
    but1  = read_with_size<unsigned char>(bs);
    but2  = read_with_size<unsigned char>(bs);
    StringCompressor::Instance()->DecodeString(text.data(), 4096, bs);

    title      = std::to_string(id) + " | " + title;
    text       = "[HOOKED] " + text;
    size_t pos = text.find('\0');
    if (pos != std::string::npos)
        text.insert(pos, " [HOOKED]");
    text.resize(4096);

    // write
    bs->Reset();
    bs->Write(did);
    bs->Write(style);
    write_with_size<unsigned char>(bs, title);
    write_with_size<unsigned char>(bs, but1);
    write_with_size<unsigned char>(bs, but2);
    StringCompressor::Instance()->EncodeString(text.data(), 4096, bs);
    return true;
}

inline bool on_client_msg(unsigned char &id, RakNet::BitStream *bs) {
    if (id != 93) // RPC_ClientMessage
        return true;
    unsigned long color;
    std::string   msg;

    // read
    bs->Read(color);
    msg = read_with_size<unsigned int>(bs);

    msg = "[HOOKED] " + msg;

    // write
    bs->Reset();
    bs->Write(color);
    write_with_size<unsigned int>(bs, msg);
    return true;
}

inline bool nop_player_sync(Packet *p) {
    return *p->data != ID_PLAYER_SYNC;
}

#endif // RHEXAMPLE_EVENTS_HPP
