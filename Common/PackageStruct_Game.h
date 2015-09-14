#ifndef _PACKAGESTRUCT_GAME_H_INCLUDED_
#define _PACKAGESTRUCT_GAME_H_INCLUDED_

#include "PackageStruct.h"
#include "Protocol_Game.h"
#include "CommStruct.h"
#pragma pack(push, 1)


struct MSG_JOINTABLE_REQ : public MSG_BASE_FORWARD
{
	MSG_JOINTABLE_REQ() {
		memset( this, 0, sizeof(MSG_JOINTABLE_REQ) );
		m_byCategory = Games_Protocol;
		m_byProtocol = JoinTable_REQ;
	}
};


struct MSG_JOINTABLE_BRD : public MSG_BASE_FORWARD
{
	MSG_JOINTABLE_BRD() {
		memset( this, 0, sizeof(MSG_JOINTABLE_REQ) );
		m_byCategory = Games_Protocol;
		m_byProtocol = JoinTable_BRD;
	}
};


struct MSG_STARTGAME_REQ : public MSG_BASE_FORWARD
{
	MSG_STARTGAME_REQ() {
		memset( this, 0, sizeof(MSG_STARTGAME_REQ) );
		m_byCategory = Games_Protocol;
		m_byProtocol = StartGame_REQ;
	}
};

struct MSG_STARTGAME_ANC : public MSG_BASE_FORWARD
{
	DWORD 	m_dwErrorCode;
	MSG_STARTGAME_ANC() {
		memset( this, 0, sizeof(MSG_STARTGAME_ANC) );
		m_byCategory = Games_Protocol;
		m_byProtocol = StartGame_ANC;
	}
};

struct MSG_INITCARDS_BRD : public MSG_BASE_FORWARD
{
	BYTE m_byCards[CNPOKER_CARD_LEN_2];
	MSG_INITCARDS_BRD() {
		memset( this, 0, sizeof(MSG_INITCARDS_BRD) );
		m_byCategory = Games_Protocol;
		m_byProtocol = InitCards_BRD;
	}
};


// 叫地主 请求
struct MSG_CALLBANK_REQ : public MSG_BASE_FORWARD
{
	BYTE byCall; // 0 不叫， 1 叫地主
	MSG_CALLBANK_REQ() {
		memset( this, 0, sizeof(MSG_CALLBANK_REQ) );
		m_byCategory = Games_Protocol;
		m_byProtocol = CallBank_REQ;
	}
};

// 叫地主 应答
struct MSG_CALLBANK_BRD : public MSG_BASE_FORWARD
{
    DWORD dwUserID; // 0 不叫， 1 叫地主
	MSG_CALLBANK_BRD() {
		memset( this, 0, sizeof(MSG_CALLBANK_BRD) );
		m_byCategory = Games_Protocol;
		m_byProtocol = CallBank_BRD;
	}
};

// 明牌
struct MSG_SHOWCARDS_REQ : public MSG_BASE_FORWARD
{
	MSG_SHOWCARDS_REQ() {
		memset( this, 0, sizeof(MSG_SHOWCARDS_REQ) );
		m_byCategory = Games_Protocol;
		m_byProtocol = ShowCards_REQ;
	}
};

struct MSG_SHOWCARDS_BRD : public MSG_BASE_FORWARD
{
	MSG_SHOWCARDS_BRD() {
		memset( this, 0, sizeof(MSG_SHOWCARDS_BRD) );
		m_byCategory = Games_Protocol;
		m_byProtocol = ShowCards_BRD;
	}
};

// 出牌
struct MSG_DISCARDS_REQ : public MSG_BASE_FORWARD
{
	BYTE uiSize;
	BYTE byDiscards[CNPOKER_CARD_LEN_2]; // 最多20张

	MSG_DISCARDS_REQ() {
		memset( this, 0, sizeof(MSG_DISCARDS_REQ) );
		m_byCategory = Games_Protocol;
		m_byProtocol = Discards_REQ;
	}
};

struct MSG_DISCARDS_BRD : public MSG_BASE_FORWARD
{
    DWORD dwUserID; // 出牌有效，下一位
	DWORD uiSize;
	BYTE byDiscards[CNPOKER_CARD_LEN_2]; // 最多20张

	MSG_DISCARDS_BRD() {
		memset( this, 0, sizeof(MSG_DISCARDS_BRD) );
		m_byCategory = Games_Protocol;
		m_byProtocol = Discards_BRD;
	}
};


// 取得胜利
struct MSG_WINPLAYER_BRD : public MSG_BASE_FORWARD
{
    DWORD dwUserID;         // 0 不叫， 1 叫地主
	MSG_WINPLAYER_BRD() {
		memset( this, 0, sizeof(MSG_WINPLAYER_BRD) );
		m_byCategory = Games_Protocol;
		m_byProtocol = WinPlayer_BRD;
	}
};

// 取得胜利
struct MSG_END_BRD : public MSG_BASE_FORWARD
{
    DWORD dwUserID;         // 0 不叫， 1 叫地主
	MSG_END_BRD() {
		memset( this, 0, sizeof(MSG_END_BRD) );
		m_byCategory = Games_Protocol;
		m_byProtocol = End_BRD;
	}
};

/*************************************/
#pragma pack(pop)

#endif // _PACKAGESTRUCT_GAME_H_INCLUDED_
