/*******************************************************************************
********************************************************************************
* Դ�ļ���: type_def.h
* ��    ��:
* ��    ��: v1.0
* ��д����: 
* ˵    ��:
* �޸���ʷ:
*******************************************************************************/
/******************************** ͷ�ļ�������ͷ ******************************/
#ifndef TYPE_DEF_H
#define TYPE_DEF_H

/******************************** �����ļ����� ********************************/

/******************************** ��ͳ������� ********************************/
#ifndef _STATIC
#define _STATIC          static
#endif

#ifndef _EXTERN
#define _EXTERN          extern
#endif

#define _VOID            void

#define _FAR
#define _NEAR

#ifndef _CONST
#define _CONST           const
#endif

#define NULLPTR            0       /* ָ�����ͱ�����ʼ�����ͷ�ʱӦ�Ըö��帳ֵ */

/*------------------ ���Ͷ��� -------------------------------*/
/* �������Ͷ��� */

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;

typedef signed   char      s8;     /* �з���8λ������������    */
typedef signed   short     s16;    /* �з���16λ������������   */
typedef signed   int       s32;    /* �з���32λ������������   */
typedef double             d64;    /* �з���64λ����?  ������?*/

typedef unsigned char      U8;
typedef unsigned short     U16;
typedef unsigned int       U32;

typedef signed   char      S8;     /* �з���8λ������������    */
typedef signed   short     S16;    /* �з���16λ������������   */
typedef signed   int       S32;    /* �з���32λ������������   */
typedef double             D64;    /* �з���64λ����?  ������?*/


typedef signed   int       SYS_STATUS;             /* ????????? */  

typedef char				_CHAR;
typedef unsigned char		_BYTE;
typedef short				_SHORT;
typedef unsigned short  	_WORD;
typedef unsigned short  	_BOOL;
typedef signed int			BOOL;
typedef unsigned int		_UINT;
typedef unsigned long		_DWORD;
typedef long				_LONG;
typedef float				_FLOAT;

typedef volatile _CHAR	_VCHAR;
typedef volatile _BOOL	_VBOOL;
typedef volatile _BYTE	_VBYTE;
typedef volatile _WORD	_VWORD;
typedef volatile _SHORT  _VSHORT;
typedef volatile _DWORD _VDWORD;
typedef volatile _LONG	_VLONG;
typedef volatile _FLOAT	_VFLOAT;  


typedef _CHAR *				_PCHAR;
typedef _BOOL*				_PBOOL;
typedef _BOOL _FAR*			_LPBOOL;    
typedef _CHAR *				_PSTR;
typedef _CHAR _FAR*			_LPSTR;     
typedef const _CHAR*		_PCSTR;     
typedef const _CHAR _FAR*	_LPCSTR;    
typedef _BYTE*				_PBYTE;
typedef _BYTE _FAR*			_LPBYTE;    
typedef _WORD*				_PWORD;
typedef _WORD _FAR*			_LPWORD;     
typedef _SHORT*				_PSHORT;
typedef _SHORT _FAR*		_LPSHORT;   
typedef _DWORD*				_PDWORD;
typedef _DWORD _FAR*		_LPDWORD;   
typedef long*				_PLONG;
typedef long _FAR*			_LPLONG;    
typedef float*				_PFLOAT;
typedef float _FAR*			_LPFLOAT;   
typedef _VOID*				_PVOID;

typedef u32					ProcessorId ;
typedef u16					PoolId ;
typedef  _DWORD				_HWND;

#define FALSE 0
#define TRUE  1
/******************************** ȫ�ֱ������� ********************************/

#endif
/******************************** ͷ�ļ����� **********************************/

