#ifndef USER_INFO_DEFINITION
#define USER_INFO_DEFINITION
typedef enum
{
	ADMIN,
	OPER,
	VISIT,
	PROHIBIT,
	ILLEGAL
} ENUM_ACCOUNT_LEVEL ;

typedef struct
{
	CString Name ;
	CString Password ;
	ENUM_ACCOUNT_LEVEL Level ;
	BOOL	Modified ;
} STRUCT_USER_INFO ;

#define MAX_CNT_USER 100

#endif