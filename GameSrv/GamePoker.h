#ifndef _GAMEPOKER_H_INCLUDED_
#define _GAMEPOKER_H_INCLUDED_

#include <Common.h>

#define PK_MAX_STRING 20

// Error Msg
#define DE_TABLE_EMPTY  0xF0   // ����Ϊ��
#define DE_SEAT_EMPTY   0xF1   // ��λ����
#define DE_SEAT_FULL    0xF1   // ��λ����
#define DE_PLAYING      0xF2   // ������Ϸ

enum ePK_TYPE   // ���Ƶ�����
{
    PH_0 	= 0    , 		// ��Ч
    PH_1 	= 100  , 		// ����
    PH_2 	       , 		// ����
    PH_3 	       ,		// ����
    PH_31 	       ,		// ����һ
    PH_32 	       ,		// ������

    PH_41 	       ,		// �Ĵ�һ
    PH_411 	       ,		// �Ĵ�����
    PH_42 	       ,		// �Ĵ�һ��
    PH_422 	       ,		// �Ĵ�����

    PH_C1 	= 200  , 		// ˳��
    PH_C2 	       ,		// ����
    PH_C3 	       ,		// �ɻ�

    PH_4 	= 500  ,		// ը��
    PH_MAX 	       ,		// ��ը

    PH_End 	= 1000 ,		// ��Ч
};

enum ePK_POWER
{
    PH_INVALID = 0 , 		// ��Ч�Ƽ�
    PH_PASS    = 10, 		// ת����Ȩ
    PH_AGAIN       , 		// �ٳ���Ȩ
    PH_THAN        , 		// �ȴ��Ƚ�
};

class GamePoker
{
public:
	GamePoker();
	virtual ~GamePoker(void);

    int SetPoker( BYTE * pokers, BYTE bySize );

    bool operator > (const GamePoker & other ) const;

protected:
	int Parser();

private:
    BYTE m_bySeat; // ˭�������

    BYTE m_bySize;
    BYTE m_byPK[PK_MAX_STRING];

    BYTE m_byThanType;      // �Ƚ�����
    BYTE m_byThanValue;     // �Ƚ���ֵ
    BYTE m_byThanCount;     // �Ƚ�����
};


#endif // _POKER_H_INCLUDED_
