#ifndef USER_INFO_DEFINITION
#define USER_INFO_DEFINITION
typedef enum
{
	TOPMOST,
	ADMIN,
	OPER,
	VISIT,
	PROHIBIT,
	ILLEGAL
} ENUM_ACCOUNT_LEVEL ;

#define CHECK_THIS_HIGHER_LEVEL(ThisLevel, TargLevel) ((int)TargLevel - (int)ThisLevel)
typedef struct
{
	CString Name ;
	CString Password ;
	ENUM_ACCOUNT_LEVEL Level ;
	BOOL	Modified ;
} STRUCT_ACCOUNT_INFO ;

#define MAX_CNT_USER 100

#endif