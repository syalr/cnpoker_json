#ifndef _PACKAGESTRUCT_GAME_H_INCLUDED_
#define _PACKAGESTRUCT_GAME_H_INCLUDED_

#include "PackageStruct.h"
#include "Protocol_Game.h"

#include "CommStruct.h"

#pragma pack(push, 1)


struct MSG_START_GAME_REQ : public MSG_BASE_FORWARD
{
	MSG_START_GAME_REQ() 
	{
		memset( this, 0, sizeof(MSG_START_GAME_REQ) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = StartGame_REQ;
	}
};

struct MSG_START_GAME_ANC : public MSG_BASE_FORWARD
{
	MSG_START_GAME_ANC() 
	{
		memset( this, 0, sizeof(MSG_START_GAME_ANC) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = StartGame_ANC;
	}
};

struct MSG_START_GAME_NAK : public MSG_BASE_FORWARD
{
	DWORD 	m_dwErrorCode;
	
	MSG_START_GAME_NAK() 
	{
		memset( this, 0, sizeof(MSG_START_GAME_NAK) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = StartGame_NAK;
	}
};


/*************************************/
#if 0
struct MSG_JOINROOM_REQ : public MSG_BASE_FORWARD
{
	unsigned int m_uiRoomNumber;
	
	MSG_JOINROOM_REQ() 
	{
		memset( this, 0, sizeof(MSG_JOINROOM_REQ) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = JoinRoom_REQ;
	}
};

struct MSG_JOINROOM_ANC : public MSG_BASE_FORWARD
{
	//PlayerInfo m_playerInfo;
	//unsigned int m_byRoomNumber;
	
	MSG_JOINROOM_ANC() 
	{
		memset( this, 0, sizeof(MSG_JOINROOM_ANC) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = JoinRoom_ANC;
	}
};

struct MSG_JOINTABLE_REQ : public MSG_BASE_FORWARD
{
	unsigned int m_uiTableNumber;
	//unsigned int m_uiSeat;
	
	MSG_JOINTABLE_REQ() 
	{
		memset( this, 0, sizeof(MSG_JOINTABLE_REQ) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = JoinTable_REQ;
	}
};

struct MSG_JOINTABLE_ANC : public MSG_BASE_FORWARD
{
	unsigned int m_uiTableNumber;
	
	MSG_JOINTABLE_ANC() 
	{
		memset( this, 0, sizeof(MSG_JOINTABLE_ANC) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = JoinTable_ANC;
	}
};

// 初始化牌
struct MSG_INITCARDS_BRD : public MSG_BASE_FORWARD
{
	BYTE m_byCards[20];
	
	MSG_INITCARDS_BRD() 
	{
		memset( this, 0, sizeof(MSG_INITCARDS_BRD) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = InitCards_BRD;
	}
};

struct MSG_INITCARDS_ANC : public MSG_BASE_FORWARD
{
	MSG_INITCARDS_ANC() 
	{
		memset( this, 0, sizeof(MSG_INITCARDS_ANC) );
		
		m_byCategory = Games_Protocol;
		//m_byProtocol = AG_InitCards_ANC;
	}
};

// 叫地主 请求
struct MSG_CALLLANDLOARD_REQ : public MSG_BASE_FORWARD
{
	BYTE m_byCall; // 0 不叫， 1 叫地主
	
	MSG_CALLLANDLOARD_REQ()
	{
		memset( this, 0, sizeof(MSG_CALLLANDLOARD_REQ) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = CallLandlord_REQ;
	}
};

// 叫地主 应答
struct MSG_CALLLANDLOARD_ANC : public MSG_BASE_FORWARD
{	
	MSG_CALLLANDLOARD_ANC()
	{
		memset( this, 0, sizeof(MSG_CALLLANDLOARD_ANC) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = CallLandlord_ANC;
	}
};

// 抢地主 请求
struct MSG_GRABLANDLOARD_REQ : public MSG_BASE_FORWARD
{
	MSG_GRABLANDLOARD_REQ() 
	{
		memset( this, 0, sizeof(MSG_GRABLANDLOARD_REQ) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = GrabLandlord_REQ;
	}
};

// 抢地主 应答
struct MSG_GRABLANDLOARD_ANC : public MSG_BASE_FORWARD
{
	//unsigned int m_uiSeat; // 成功抢到地主的玩家Key 还是说 Seat ?
	
	MSG_GRABLANDLOARD_ANC() 
	{
		memset( this, 0, sizeof(MSG_GRABLANDLOARD_ANC) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = GrabLandlord_ANC;
	}
};

// 抢地主 广播 (最终地主确定)
struct MSG_GRABLANDLOARD_BRD : public MSG_BASE_FORWARD
{	
	MSG_GRABLANDLOARD_BRD() 
	{
		memset( this, 0, sizeof(MSG_GRABLANDLOARD_BRD) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = GrabLandlord_BRD;
	}
};

// 明牌
struct MSG_SHOWCARDS_REQ : public MSG_BASE_FORWARD
{
	MSG_SHOWCARDS_REQ() 
	{
		memset( this, 0, sizeof(MSG_SHOWCARDS_REQ) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = ShowCards_REQ;
	}
};

struct MSG_SHOWCARDS_ANC : public MSG_BASE_FORWARD
{
	DWORD m_dwUserID;
	BYTE  m_byCards[CNPOKER_CARD_LEN_2];
	
	MSG_SHOWCARDS_ANC() 
	{
		memset( this, 0, sizeof(MSG_SHOWCARDS_ANC) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = ShowCards_ANC;
	}
};

// 出牌
struct MSG_DISCARDS_REQ : public MSG_BASE_FORWARD
{
	unsigned int m_uiSize;
	BYTE m_byDiscards[CNPOKER_CARD_LEN_2]; // 最多20张
	
	MSG_DISCARDS_REQ() 
	{
		memset( this, 0, sizeof(MSG_DISCARDS_REQ) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = Discards_REQ;
	}
};

struct MSG_DISCARDS_ANC : public MSG_BASE_FORWARD
{
	DWORD m_dwUserID;
	DWORD m_uiSize;
	BYTE m_byDiscards[CNPOKER_CARD_LEN_2]; // 最多20张
	
	MSG_DISCARDS_ANC() 
	{
		memset( this, 0, sizeof(MSG_DISCARDS_ANC) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = Discards_ANC;
	}
};

// 出牌 无效 
struct MSG_DISCARDS_INVALID : public MSG_BASE_FORWARD
{
	DWORD m_dwErrorCode;
	
	MSG_DISCARDS_INVALID() 
	{
		memset( this, 0, sizeof(MSG_DISCARDS_INVALID) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = Discards_INVALID;
	}
};

// 要不起 请求
struct MSG_PASS_REQ : public MSG_BASE_FORWARD
{	
	MSG_PASS_REQ() 
	{
		memset( this, 0, sizeof(MSG_PASS_REQ) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = Pass_REQ;
	}
};

// 要不起 应答
struct MSG_PASS_ANC : public MSG_BASE_FORWARD
{
	//DWORD m_dwUserKey;
	//DWORD m_uiSize;
	
	MSG_PASS_ANC() 
	{
		memset( this, 0, sizeof(MSG_PASS_ANC) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = Pass_ANC;
	}
};

// 取得胜利
struct MSG_WINPLAYER_BRD : public MSG_BASE_FORWARD
{	
	MSG_WINPLAYER_BRD() 
	{
		memset( this, 0, sizeof(MSG_WINPLAYER_BRD) );
		
		m_byCategory = Games_Protocol;
		m_byProtocol = WinPlayer_BRD;
	}
};
#endif
/*************************************/


#pragma pack(pop)

#endif // _PACKAGESTRUCT_GAME_H_INCLUDED_
