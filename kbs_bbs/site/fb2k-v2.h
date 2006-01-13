#ifndef __SYSNAME_H_
#define __SYSNAME_H_

#define USE_TMPFS           1   /*使用内存文件系统加速*/
#define TMPFSROOT   "cache" /*tmpfs的根在bbshome/cache */
#define CONV_PASS		1
#define NINE_BUILD		0
#define NEW_COMERS		1	/* 注册后在 newcomers 版自动发文 */
#define HAPPY_BBS		0
#define HAVE_COLOR_DATE		1
#define HAVE_TEMPORARY_NICK	1
#define HAVE_FRIENDS_NUM	1
#define HAVE_REVERSE_DNS	0
#define CHINESE_CHARACTER	1
#define CNBBS_TOPIC		1	/* 是否在进站过程中显示 cn.bbs.* 十大热门话题 */
#define MAIL2BOARD		0	/* 是否允许直接 mail to any board */
#define MAILOUT			1	/* 是否允许向站外主动发信 */
#define MANUAL_DENY		0	/*是否允许手动解封*/
#define BBS_SERVICE_DICT	1
#define HAVE_TSINGHUA_INFO_REGISTER 0

#define BUILD_PHP_EXTENSION 1   /*将php lib编成php extension */
/*#define USE_SEM_LOCK 1*/

#ifdef HAVE_MYSQL_SMTH
#define PERSONAL_CORP
#else
#undef PERSONAL_CORP
#endif

#define HAVE_WFORUM	1
#define FB2000			1
#define SMTH			1
#define FILTER			1
/* 
 *    Define DOTIMEOUT to set a timer to bbslog out users who sit idle on the system.
 *       Then decide how long to let them stay: MONITOR_TIMEOUT is the time in
 *          seconds a user can sit idle in Monitor mode; IDLE_TIMEOUT applies to all
 *             other modes. 
 *             */
#define DOTIMEOUT 1

#define USE_DEFAULT_MODE

/* 
 *    These are moot if DOTIMEOUT is commented; leave them defined anyway. 
 *    */
#define IDLE_TIMEOUT    (60*20) 
#define MONITOR_TIMEOUT (60*20) 

#define BBSUID 			501
#define BBSGID 			501

/* for bbs2www, by flyriver, 2001.3.9 */
#define SECNUM 13
#define BBS_PAGE_SIZE 20

#define SQUID_ACCL

#define DEFAULTBOARD    	"sysop"
#define FILTER_BOARD        "Filter"
#define SYSMAIL_BOARD       "sysmail"
#define BLESS_BOARD "Blessing"

#define MAXUSERS  		20000
#define MAXCLUB			128
#define MAXBOARD  		400
#define MAXACTIVE 		3000
/* remeber: if MAXACTIVE>46656 need change get_telnet_sessionid,
    make the number of session char from 3 to 4
    */
#define MAX_GUEST_NUM		256

#define POP3PORT		110
#define POP3SPORT		995
/* ASCIIArt, by czz, 2002.7.5 */
#define       LENGTH_SCREEN_LINE      255
#define       LENGTH_FILE_BUFFER      255
#define       LENGTH_ACBOARD_BUFFER   300
#define       LENGTH_ACBOARD_LINE     300

#define LIFE_DAY_USER		120
#define LIFE_DAY_YEAR          365
#define LIFE_DAY_LONG		666
#define LIFE_DAY_SYSOP		120
#define LIFE_DAY_NODIE		999
#define LIFE_DAY_NEW		15
#define LIFE_DAY_SUICIDE	15

#define DAY_DELETED_CLEAN	30
#define SEC_DELETED_OLDHOME	2592000 /* 3600*24*30，注册新用户如果存在这个用户的目录，保留时间 */

#define	REGISTER_WAIT_TIME	(1)
#define	REGISTER_WAIT_TIME_NAME	"1 分钟"

#ifdef SMTH
#define REGISTER_TSINGHUA_WAIT_TIME (24*60*60)
#endif

#define MAIL_MAILSERVER     "127.0.0.1:25"

#define BBSDOMAIN_DEFAULT "bbs.mysite.net"   /* 站点域名 */
#define	SHORTNAME_DEFAULT "KBS"              /* 站名简称 */
#define BBSNAME_DEFAULT   "KBS 试验站"       /* 站名全称 */
#define MAILDOMAIN_DEFAULT "mysite.net"      /* 发对外邮件的地址 */

#ifdef ENABLE_CUSTOMIZING
#define NAME_BBS_ENGLISH sysconf_str_default("BBSDOMAIN", BBSDOMAIN_DEFAULT)
#define	NAME_BBS_CHINESE sysconf_str_default("SHORTNAME", SHORTNAME_DEFAULT)
#define BBS_FULL_NAME    sysconf_str_default("BBSNAME", BBSNAME_DEFAULT)
#define MAIL_BBSDOMAIN   sysconf_str_default("MAILDOMAIN", MAILDOMAIN_DEFAULT)
#else
#define NAME_BBS_ENGLISH BBSDOMAIN_DEFAULT
#define	NAME_BBS_CHINESE SHORTNAME_DEFAULT
#define BBS_FULL_NAME    BBSNAME_DEFAULT
#define MAIL_BBSDOMAIN   MAILDOMAIN_DEFAULT
#endif

#define FOOTER_MOVIE		"欢  迎  投  稿"
/*#define ISSUE_LOGIN		"本站使用曙光公司曙光天演服务器"*/
#define ISSUE_LOGIN		"kbsbbs 系统试验站"
#define ISSUE_LOGOUT		"还是走了罗"

#define NAME_USER_SHORT		"用户"
#define NAME_USER_LONG		"水木用户"
#define NAME_SYSOP		"System Operator"
#define NAME_BM			"版主"
#define NAME_POLICE		"警察"
#define	NAME_SYSOP_GROUP	"站务组"
#define NAME_ANONYMOUS		"我爱水木!"
#define NAME_ANONYMOUS_FROM	"匿名天使的家"
#define ANONYMOUS_DEFAULT 0

#define NAME_MATTER		"站务"
#define NAME_SYS_MANAGE		"系统维护"
#define NAME_SEND_MSG		"送讯息"
#define NAME_VIEW_MSG		"送讯息"

#define CHAT_MAIN_ROOM		"main"
#define	CHAT_TOPIC		"大家先随便聊聊吧"
#define CHAT_MSG_NOT_OP		"*** 您不是本聊天室的op ***"
#define	CHAT_ROOM_NAME		"聊天室"
#define	CHAT_SERVER		"聊天广场"
#define CHAT_MSG_QUIT		"切离系统"
#define CHAT_OP			"聊天室 op"
#define CHAT_SYSTEM		"系统"
#define	CHAT_PARTY		"大家"

#define DEFAULT_NICK		"每天爱你多一些"

#define MSG_ERR_USERID		"错误的使用者代号..."
#define LOGIN_PROMPT		"请输入代号"
#define PASSWD_PROMPT		"请输入密码"

/* 权限位定义 */
/*
   These are the 16 basic permission bits. 
   All but the last one are used in comm_lists.c and help.c to control user 
   access to priviliged functions. The symbolic names are given to roughly
   correspond to their actual usage; feel free to use them for different
   purposes though. The PERM_SPECIAL1 and PERM_SPECIAL2 are not used by 
   default and you can use them to set up restricted boards or chat rooms.
*/

#define NUMPERMS (30)

#define PERM_BASIC      000001
#define PERM_CHAT       000002
#define PERM_PAGE       000004
#define PERM_POST       000010
#define PERM_LOGINOK    000020
#define PERM_BMAMANGER	000040
#define PERM_CLOAK      000100
#define PERM_SEECLOAK   000200
#define PERM_XEMPT      000400
#define PERM_WELCOME    001000
#define PERM_BOARDS     002000
#define PERM_ACCOUNTS   004000
#define PERM_CHATCLOAK  010000
#define PERM_DENYRELAX      020000
#define PERM_SYSOP      040000
#define PERM_POSTMASK  0100000
#define PERM_ANNOUNCE  0200000
#define PERM_OBOARDS   0400000
#define PERM_ACBOARD   01000000
#define PERM_NOZAP     02000000
#define PERM_CHATOP    04000000
#define PERM_ADMIN     010000000
#define PERM_HORNOR   	020000000
#define PERM_SECANC    040000000
#define PERM_JURY      0100000000
#define PERM_CHECKCD      0200000000
#define PERM_SUICIDE   0400000000
#define PERM_COLLECTIVE 	01000000000
#define PERM_DISS        02000000000
#define PERM_DENYMAIL   	04000000000


#define XPERMSTR "bTCPRp#@XWBA$VS!DEM1234567890%"
/* means the rest is a post mask */

/* This is the default permission granted to all new accounts. */
#define PERM_DEFAULT    (PERM_BASIC | PERM_CHAT | PERM_PAGE | PERM_POST | PERM_LOGINOK)

/* These permissions are bitwise ORs of the basic bits. They work that way
   too. For example, anyone with PERM_SYSOP or PERM_BOARDS or both has
   PERM_SEEBLEVELS. */

#define PERM_ADMINMENU  (PERM_ACCOUNTS | PERM_SYSOP|PERM_OBOARDS|PERM_WELCOME)
#define PERM_MULTILOG   (PERM_SYSOP | PERM_ANNOUNCE | PERM_OBOARDS)
#define PERM_LOGINCLOAK (PERM_SYSOP | PERM_ACCOUNTS | PERM_BOARDS | PERM_OBOARDS | PERM_WELCOME)
#define PERM_SEEULEVELS (PERM_SYSOP | PERM_BOARDS)
#define PERM_SEEBLEVELS (PERM_SYSOP | PERM_BOARDS)
#define PERM_MARKPOST   (PERM_SYSOP | PERM_BOARDS)
#define PERM_UCLEAN     (PERM_SYSOP | PERM_ACCOUNTS)
#define PERM_NOTIMEOUT  PERM_SYSOP
/* PERM_MANAGER will be used to allow 2 windows and 
bigger mailbox. --stephen 2001.10.31*/
#define PERM_MANAGER    (PERM_CHATOP | PERM_JURY | PERM_BOARDS)
#define PERM_SENDMAIL   0
#define PERM_READMAIL   PERM_BASIC
#define PERM_VOTE       PERM_BASIC

/* These are used only in Internet Mail Forwarding */
/* You may want to be more restrictive than the default, especially for an
   open access BBS. */

#define PERM_SETADDR    PERM_BASIC      /* to set address for forwarding */
#define PERM_FORWARD    PERM_BASIC      /* to do the forwarding */

/* Don't mess with this. */
#define HAS_PERM(user,x) ((x)?((user)->userlevel)&(x):1)
#define DEFINE(user,x)     ((x)?((user)->userdefine[def_list(x)])&(x):1)

#define USE_DEFAULT_DEFINESTR

/**
 * 看在线用户时的按键处理字符。
 */
#define UL_CHANGE_NICK_UPPER   'C'
#define UL_CHANGE_NICK_LOWER   'c'
#define UL_SWITCH_FRIEND_UPPER 'F'
#define UL_SWITCH_FRIEND_LOWER 'f'

/** 使用缺省的FILEHeader结构*/
#define HAVE_FILEHEADER_DEFINE

/**
 * Mailbox properties.
 * 
 * @author flyriver
 */

#define MBP_SAVESENTMAIL      0x00000001
#define MBP_FORCEDELETEMAIL   0x00000002
#define MBP_MAILBOXSHORTCUT   0x00000004

#define MBP_NUMS 3

#define HAS_MAILBOX_PROP(u, x) ((u)->mailbox_prop & x)

/**
 * Mailgroup macros.
 *
 * @author flyriver
 */
#define MAX_MAILGROUP_NUM 30
#define MAX_MAILGROUP_USERS 300

/**
attach define
*/
#define MAXATTACHMENTCOUNT	20                            //文章附件个数上限
#define MAXATTACHMENTSIZE 5*1024*1024                     //文章附件文件长度上限


#define CHECK_IP_LINK 1

#define BOARD_SHOW_ONLINE 1


#define COMMEND_ARTICLE "Recommend"

#define NOT_USE_DEFAULT_SMS_FUNCTIONS

#define HAVE_OWN_USERIP
#define SHOW_USERIP(user,x) showuserip(user,x)

#define QUOTED_LINES 3
#define QUOTELEV 0

#endif
