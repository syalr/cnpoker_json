#include "GamePoker.h"


GamePoker::GamePoker() : m_bySize(0)
{
}

GamePoker::~GamePoker()
{
}

int GamePoker::SetPoker( BYTE * pokers, BYTE bySize )
{
    memset( m_byPK, 0x0, sizeof(m_byPK) );

    for(BYTE i=0; i<bySize; i++ ) {
        m_byPK[i] = pokers[i];
    }

    m_byThanType = Parser();
}

bool GamePoker::operator > (const GamePoker & other ) const
{
    if (this->m_byThanType == PH_End) {
        return false;
    }

    if (other.m_byThanType == PH_End) {
        return false;
    }

	if ( this->m_byThanType != other.m_byThanType )
    {
		if ( this->m_byThanType == PH_MAX ) {
			return true;
        }

		if ( this->m_byThanType == PH_4 )
        {
            if ( this->m_byThanType > other.m_byThanType ) {
                return true;
            }
        }

		return false;
	}

	if ( this->m_byThanValue > other.m_byThanValue ) {
		return true;
    }

    return false;
}

int GamePoker::Parser()
{
	if ( m_bySize <= 0 || m_byPK == NULL ) {
		return (PH_0);
	}

	m_byThanCount = 0;
	m_byThanValue = m_byPK[0]; // 取第一个牌为比较值

	// (高击中 + 低复杂度) 判断区
	if ( m_bySize == 1 ) {
		return (PH_1); // 单牌
	}
	else if ( m_bySize == 2) {
		if ( m_byPK[0] == m_byPK[1] ) {
			return (PH_2); // 对子
		}
		if ( (m_byPK[0] == 14) && (m_byPK[1] == 15) ) {
			return (PH_MAX); // 王炸
		}
		return -1;
	}

	short _Max_Value = 0; 	// PK最大面值
	short _Min_Value = 15; 	// PK最小面值
	short _Max_Count = 0; 	// PK计量最多
	short _Min_Count = 0; 	// PK计量最少
	short _Min_Index = 0; 	// PK计量需要一个下标位来判断

	const short CS_SLOT = 15; // PK的下标最大常量数
	short _PK_Slot[CS_SLOT] = {0}; // PK的SLOT容器

	short _idx = 0;
	short _val = 0;
	for ( short i=0; i<(short)m_bySize; ++i)
	{
		_idx = m_byPK[i];
		if ( _idx >= 15 ) {
			return (PH_0);
		}

		_PK_Slot[_idx]++;
		_val = _PK_Slot[_idx];

		_Max_Value = (_idx >  _Max_Value) ? _idx : _Max_Value; 	// 高位置获取
		_Min_Value = (_idx <= _Min_Value) ? _idx : _Min_Value; 	// 低位置获取
		_Max_Count = (_val >  _Max_Count) ? _val : _Max_Count; 	// 高计量获取
	}

	if ( (_Max_Value == _Min_Value) ) { // PK 大小面值都相等时
		if ( m_bySize == 3 ) {
			return (PH_3); // 3个
		}
		if ( m_bySize == 4 ) {
			return (PH_4); // 炸弹
		}
		return (PH_0);
	}

	if ( _Max_Count > 4) {
		return (PH_0);
	}

	// 得出最小面值的牌
	for (short i=0; i<(short)m_bySize; ++i)
	{
		_idx = m_byPK[i];
		_val = _PK_Slot[_idx];
		_Min_Count = (_val <= _Min_Count) ? _val : _Min_Count; // 低计量获取
	}

	m_byThanValue = _Max_Value; // 到这里取最大值为比较值
	if ( _Max_Count == _Min_Count ) { // PK 数量都相等时
		m_byThanCount = m_bySize / _Max_Count;
		short _Div_0 = m_bySize / (_Max_Value - _Min_Value + 1);
		short _Div_1 = m_bySize % (_Max_Value - _Min_Value + 1);
		short _Div_2 = m_bySize / _Max_Count;
		short _Div_3 = m_bySize % _Max_Count;
		if ( (_Max_Count == _Div_0) && (_Div_1 == 0) ) {
			if ( _Max_Count == 1 ) {
				if ( (_Div_2 >= 5) && (_Div_3 == 0) )
					return (PH_4); // 顺子
				else
					return (PH_0); // 顺不起来
			}
			if ( _Max_Count == 2 ) {
				if ( (_Div_2 >= 3) && (_Div_3 == 0) )
					return 0; // 连对
				else
					return (PH_0); // 连不起来
			}
			if ( _Max_Count == 3 ) {
				if ( (_Div_2 >= 2) && (_Div_3 == 0) )
					return 0; // 飞机
				else
					return (PH_0); // 飞不起来
			}
		}
		return (PH_0);
	}

	_idx = 0;
	for (short i=0; i<(short)m_bySize; ++i)
	{
		_idx = m_byPK[i];
		if ( _PK_Slot[_idx] == _Max_Count ) {
			break;
		}
	}

	m_byThanValue = _idx; // 到这里取最多牌面值为比较值:
	if ( _Max_Count == 3 ) {
		m_byThanCount = 1;
		if ( (_Min_Count == 1) && (m_bySize == 4) ) {
			return (PH_31); // 三带一
		}
		if ( (_Min_Count == 2) && (m_bySize == 5) ) {
			return (PH_32); // 三带二
		}

		// 是否三个连起来了
		short _Three_Max_Value 	= 0; 	// 3同位最大面值
		short _Three_Min_Value 	= 15; 	// 3同位最小面值
		short _Three_Count 		= 0; 	// 3同位个数
		short _Two_Count 		= 0; 	// 2同位个数
		short _One_Count 		= 0; 	// 1同位个数
		for (short i=0; i<(short)CS_SLOT; ++i)
		{
			_idx = _PK_Slot[i];
			if ( _idx == 3 ) {
				_Three_Max_Value = (i >  _Three_Max_Value) ? i : _Three_Max_Value; // 高位置获取
				_Three_Min_Value = (i <= _Three_Min_Value) ? i : _Three_Min_Value; // 低位置获取
				_Three_Count++;
			}
			else if ( _idx == 2 ) {
				_Two_Count++;
			}
			else if ( _idx == 1 ) {
				_One_Count++;
			}
		}

		short _Div_0 = (_Three_Max_Value - _Three_Min_Value + 1) / _Three_Count;
		short _Div_1 = (_Three_Max_Value - _Three_Min_Value + 1) % _Three_Count;
		if ( (_Div_0 == 1) && (_Div_1 == 0) ) {
			m_byThanCount = _Three_Count;
			if ( _Three_Count == (_Two_Count * 2 + _One_Count) ) {
				return (PH_31); // 三带一
			}
			return (PH_0);
		}
		return (PH_0);
	}

	if ( _Max_Count == 4 ) {
		if ( _Min_Count == 1 ) {
			if ( m_bySize == 5 )
				return (PH_41); // 四带一
			if ( m_bySize == 6 )
				return (PH_411); // 四带二
			return (PH_0);
		}
		if ( _Min_Count == 2 ) {
			if ( m_bySize == 6 )
				return (PH_42); // 四带一对
			if ( m_bySize == 8 )
				return (PH_422); // 四带两对
			return (PH_0);
		}
		return (PH_0);
	}

	return (PH_0);
}

/**********  end of 出牌算法 **********/
