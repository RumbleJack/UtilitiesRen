#ifndef PUBLIC_STATUS_DEFINITION
#define PUBLIC_STATUS_DEFINITION

#define RET_STATUS long
#define RET_OK			0
#define RET_ERR		-1
#define RET_EMPTY -2
#define RET_FULL	-3
#define RET_DATA_UNREADY -4
#define RET_PARAM_BEYOND -5
#define RET_DATA_ERR -6
#define RET_FAIL_OPEN  -7
#define RET_UNINITIALIZED -8
#define RET_BUSY	-9
#define RET_UNREALIZED -10
#define RET_MISMATCHED -11

typedef struct
{
	int PROCED : 1 ;
	int SAVED : 1 ;
} STATUS_LINE ;

typedef union
{
	STATUS_LINE Status ;
	long					  Val ;
} UNION_STATUS_LINE ;

#endif