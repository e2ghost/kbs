#include "bbs.h"

#ifndef REGISTER_TSINGHUA_WAIT_TIME
#define REGISTER_TSINGHUA_WAIT_TIME (24*60*60)
#endif

const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

const char seccode[SECNUM][5] = {
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
};

const char * const permstrings[] = {
        "基本权力",             /* PERM_BASIC */
        "进入聊天室",           /* PERM_CHAT */
        "呼叫他人聊天",         /* PERM_PAGE */
        "发表文章",             /* PERM_POST */
        "使用者资料正确",       /* PERM_LOGINOK */
        //"禁止发表文章",         /* PERM_DENYPOST */
        "站务禁",         /* PERM_BMMANAGER */
        "可隐身",               /* PERM_CLOAK */
        "可见隐身",             /* PERM_SEECLOAK */
        "长期帐号",         /* PERM_XEMPT */
        "编辑系统档案",         /* PERM_WELCOME */
        "板主",                 /* PERM_BOARDS */
        "帐号管理员",           /* PERM_ACCOUNTS */
        NAME_BBS_CHINESE "智囊团",       /* PERM_CHATCLOAK */
        //"投票管理员",           /* PERM_OVOTE */
        "封禁娱乐权限",           /* PERM_DENYRELAX */
        "系统维护管理员",       /* PERM_SYSOP */
        "Read/Post 限制",       /* PERM_POSTMASK */
        "精华区总管",           /* PERM_ANNOUNCE*/
        "讨论区总管",           /* PERM_OBOARDS*/
        "活动看版总管",         /* PERM_ACBOARD*/
        "不能 ZAP(讨论区专用)", /* PERM_NOZAP*/
        "聊天室OP(元老院专用)", /* PERM_CHATOP */
        "系统总管理员",         /* PERM_ADMIN */
        "机73版",          	/* PERM_HORNOR*/
        "看秘密精华区",         /* PERM_SECANC*/
        "看AKA版",           /* PERM_JURY*/
        "看Sexy版",           /* PERM_SEXY*/
        "自杀进行中",           /* PERM_SUICIDE?*/
        "观音姐姐",           /* PERM_MM*/
        "看系统讨论版",           /* PERM_DISS*/
        "封禁Mail",           /* PERM_DENYMAIL*/
};

/* You might want to put more descriptive strings for SPECIAL1 and SPECIAL2
   depending on how/if you use them. */
const char * const user_definestr[] = {
    "活动看版",                 /* DEF_ACBOARD */
    "使用彩色",                 /* DEF_COLOR */
    "编辑时显示状态栏",         /* DEF_EDITMSG */
    "分类讨论区以 New 显示",    /* DEF_NEWPOST */
    "选单的讯息栏",             /* DEF_ENDLINE */
    "上站时显示好友名单",       /* DEF_LOGFRIEND */
    "让好友呼叫",               /* DEF_FRIENDCALL */
    "使用自己的离站画面",       /* DEF_LOGOUT */
    "进站时显示备忘录",         /* DEF_INNOTE */
    "离站时显示备忘录",         /* DEF_OUTNOTE */
    "讯息栏模式：呼叫器/人数",  /* DEF_NOTMSGFRIEND */
    "菜单模式选择：一般/精简",  /* DEF_NORMALSCR */
    "阅读文章是否使用绕卷选择", /* DEF_CIRCLE */
    "阅读文章游标停於第一篇未读",       /* DEF_FIRSTNEW */
    "屏幕标题色彩：一般/变换",  /* DEF_TITLECOLOR */
    "接受所有人的讯息",         /* DEF_ALLMSG */
    "接受好友的讯息",           /* DEF_FRIENDMSG */
    "收到讯息发出声音",         /* DEF_SOUNDMSG */
    "离站後寄回所有讯息",       /* DEF_MAILMSG */
    "发文章时实时显示讯息",     /*"所有好友上站均通知",    DEF_LOGININFORM */
    "菜单上显示帮助信息",       /* DEF_SHOWSCREEN */
    "进站时显示十大新闻",       /* DEF_SHOWHOT */
    "进站时观看留言版",         /* DEF_NOTEPAD */
    "忽略讯息功能键: Enter/Esc",        /* DEF_IGNOREMSG */
    "使用高亮界面",                   /* DEF_HIGHCOLOR */
    "进站时观看上站人数统计图", /* DEF_SHOWSTATISTIC Haohmaru 98.09.24 */
    "未读标记使用 *",           /* DEF_UNREADMARK Luzi 99.01.12 */
    "使用GB码阅读",             /* DEF_USEGB KCN 99.09.03 */
    "对汉字进行整字处理",  /* DEF_CHCHAR 2002.9.1 */
    "显示详细用户数据(wForum)",  /*DEF_SHOWDETAILUSERDATA 2003.7.31 */
	"显示真实用户数据(wForum)", /*DEF_SHOWREALUSERDATA 2003.7.31 */
	"",
    "隐藏ip"                    /* DEF_SHOWALLIP */
};

const char * const explain[] = {
	"斧 头 帮",
	"大话西游",
	"大小分舵",
        "吃喝玩乐",
	"唧唧歪歪",
	"吟风弄月",
        "西游之路",
        "豆腐西施",
	"东成西就",
        "大圣取经",
         NULL
};
 
const char * const groups[] = {
	"AxFaction",
	"zixia",
	"Factions",
	"Entertain",
	"Watering",
	"Poem",
	"GoWest",
	"DouFuGirl",
  	"PandoraBox",
  	"Reserve",
         NULL
};

const char secname[SECNUM][2][20]={
	{"斧 头 帮", "[黑帮/系统]"},
	{"大话西游", "[大话/技术]"},
	{"大小分舵", "[地盘/校班]"},
	{"吃喝玩乐", "[娱乐/体育]"},
	{"唧唧歪歪", "[感性/聊天]"},
	{"吟风弄月", "[心情/文化]"},
	{"西游之路", "[出国/聚会]"},
	{"豆腐西施", "[店面/当铺]"},
	{"东成西就", "[省份/城市]"},
	{"大圣取经", "[专业/申请]"},
};

const char * const mailbox_prop_str[] =
{
	    "发信时保存信件到发件箱",
	    "删除信件时不保存到垃圾箱",
	    "版面按 'v' 时进入: 收件箱(OFF) / 信箱主界面(ON)",
};

struct _shmkey
{
	char key[20];
	int value;
};

static const struct _shmkey shmkeys[]= {
{ "BCACHE_SHMKEY",  3693 },
{ "UCACHE_SHMKEY",  3696 },
{ "UTMP_SHMKEY",    3699 },
{ "ACBOARD_SHMKEY", 9013 },
{ "ISSUE_SHMKEY",   5010 },
{ "GOODBYE_SHMKEY", 5020 },
{ "PASSWDCACHE_SHMKEY", 3697 },
{ "STAT_SHMKEY",    5100 },
{ "CONVTABLE_SHMKEY",    5101 },
{ "MSG_SHMKEY",    5200 },
{    "",   0 }
};

int get_shmkey(char *s)
{
	int n=0;
	while(shmkeys[n].key!=0)
	{
		if(!strcasecmp(shmkeys[n].key, s))
			return shmkeys[n].value;
		n++;
	}
	return 0;
}

int
uleveltochar( char* buf, struct userec *lookupuser )
{
	unsigned lvl;
	char userid[IDLEN+2];
	
	lvl = lookupuser->userlevel;
	strncpy( userid, lookupuser->userid, IDLEN+2 );

	// buf[10], buf 最多 4 个汉字 + 1 byte （\0结尾）
	//根据 level
	//
	if( !( lvl & PERM_POST ) ) strcpy( buf, "哑巴" ); 
      	else if ( ! (lvl & PERM_BASIC) ) strcpy( buf, "瞎子" ); 
	else if( lvl < PERM_DEFAULT ) strcpy( buf, "书生" );
    	//else if( lvl & PERM_SYSOP ) strcpy(buf,"帮主");
      	else if( lvl & PERM_MM && lvl & PERM_CHATCLOAK ) strcpy(buf,"晶晶姑娘");
      	else if( lvl & PERM_MM ) strcpy(buf,"观音美眉");
      	else  if( lvl & PERM_CHATCLOAK ) strcpy(buf,"无敌牛虱");
      	else if  ( lvl & PERM_BOARDS ) strcpy(buf,"二当家的");
      	else strcpy(buf, NAME_USER_SHORT);

	//中文说明，根据 level
    	if( !strcmp(lookupuser->userid,"SYSOP")
		    || !strcmp(lookupuser->userid,"Rama") )
	    strcpy( buf, "强盗头" );
    	else if( !strcmp(lookupuser->userid,"netterm") )
	    strcpy( buf, "老帮主" );
    	else if( !strcmp(lookupuser->userid,"zixia") )
	    strcpy( buf, "旺财" );
    	else if( !strcmp(lookupuser->userid,"windtear") )
	    	strcpy( buf, "清华总代" );
    	else if( !strcmp(lookupuser->userid,"click") )
	    	strcpy( buf, "小白龙马" );
    	else if( !strcmp(lookupuser->userid,"wuhu") )
	    	strcpy( buf, "八戒" );
    	else if( !strcmp(lookupuser->userid,"halen") )
	    strcpy( buf, "小皮卡秋" );
    	else if (!strcmp(lookupuser->userid,"cclu") ||
		!strcmp(lookupuser->userid,"SuperMM") ||
		!strcmp(lookupuser->userid,"SilverSnow") ||
		!strcmp(lookupuser->userid, "busygirl") )
	    strcpy( buf, "观音姐姐" );
    	else if( !strcmp(lookupuser->userid,"Bison") )
	    strcpy( buf, "淫贼" );
    	else if( !strcmp(lookupuser->userid,"CIE") )
	    strcpy( buf, "福布斯" );
    	else if( !strcmp(lookupuser->userid,"Roy") )
	    strcpy( buf, "大饼" );
    	else if( !strcmp(lookupuser->userid,"dwd") )
	    strcpy( buf, "多文天王" );
    	else if( !strcmp(lookupuser->userid,"birby") )
	    strcpy( buf, "持国天王" );
    	else if( !strcmp(lookupuser->userid,"KCN") )
	    strcpy( buf, "上帝" );
        else if( !strcmp(lookupuser->userid,"bad") )
        strcpy( buf, "唐僧" );
    	else if( !strcmp(lookupuser->userid,"cityhunter") 
		    || !strcmp(lookupuser->userid,"soso")
		    || !strcmp(lookupuser->userid,"Czz")
		    || !strcmp(lookupuser->userid,"flyriver") )
	    strcpy( buf, "牛魔王" );
    	else if( !strcmp(lookupuser->userid,"guest") )
	    strcpy( buf, "葡萄" );

    	return 1;
}

#include "modes.h"

char *
ModeType(mode)
int     mode;
{
    switch(mode) {
    case IDLE:      return "^@^zz..ZZ" ;
    case NEW:       return "新" NAME_USER_SHORT "注册" ;
    case LOGIN:     return "进入" NAME_BBS_NICK;
    case CSIE_ANNOUNCE:     return "汲取精华";
    case CSIE_TIN:          return "使用TIN";
    case CSIE_GOPHER:       return "使用Gopher";
    case MMENU:     return "主菜单";
    case ADMIN:     return NAME_SYS_MANAGE;
    case SELECT:    return "选择讨论区";
    case READBRD:   return "浏览讨论区";
    case READNEW:   return "察看新文章";
    case  READING:  return "审查文章";
    case  POSTING:  return "批阅文章" ;
    case MAIL:      return "信件选单" ;
    case  SMAIL:    return "寄信中";
    case  RMAIL:    return "读信中";
    case TMENU:     return "谈天说地区";
    case  LUSERS:   return "看谁在线上";
    case  FRIEND:   return "找线上好友";
    case  MONITOR:  return "监看中";
    case  QUERY:    return "查询" NAME_USER_SHORT;
    case  TALK:     return "聊天" ;
    case  PAGE:     return "呼叫" NAME_USER_SHORT;
    case  CHAT2:    return "梦幻国度";
    case  CHAT1:    return CHAT_SERVER "中";
    case  CHAT3:    return "快哉亭";
    case  CHAT4:    return "老大聊天室";
    case  IRCCHAT:  return "会谈IRC";
    case LAUSERS:   return "探视" NAME_USER_SHORT;
    case XMENU:     return "系统资讯";
    case  VOTING:   return "投票";
    case  BBSNET:   return "波若波罗蜜";
    case  EDITWELC: return "编辑 Welc";
    case EDITUFILE: return "编辑档案";
    case EDITSFILE: return NAME_SYS_MANAGE;
    case  EDITSIG:  return "刻印";
    case  EDITPLAN: return "拟计画";
    case ZAP:       return "订阅讨论区";
    case EXCE_MJ:   return "围城争霸";
    case EXCE_BIG2: return "比大营";
    case EXCE_CHESS:return "楚河汉界";
    case NOTEPAD:   return "留言板";
    case GMENU:     return "工具箱";
    case FOURM:     return "4m Chat";
    case ULDL:      return "UL/DL" ;
    case MSG:       return NAME_SEND_MSG;
    case USERDEF:   return "自订参数";
    case EDIT:      return "修改文章";
    case OFFLINE:   return "自杀中..";
    case EDITANN:   return "编修精华";
    case CCUGOPHER: return "他站精华";
    case LOOKMSGS:  return NAME_VIEW_MSG;
    case WFRIEND:   return "寻人名册";
    case LOCKSCREEN:return "屏幕锁定";
    case GIVEUPNET:
        return "戒网中..";
    case WEBEXPLORE:return "Web浏览";
    case SERVICES:    return "休闲娱乐..";
	case FRIENDTEST:  return "心有灵犀";
    case CHICKEN:
	return "星空战斗鸡";
	case KILLER:        return "杀人游戏";
    default: return "去了那里!?" ;
    }
}

struct count_arg {
    int www_count;
    int telnet_count;
};

int countuser(struct user_info* uinfo,struct count_arg* arg,int pos)
{
    if (uinfo->mode==WEBEXPLORE)
        arg->www_count++;
    else
        arg->telnet_count++;
    return COUNT;
}

int multilogin_user(struct userec *user, int usernum,int mode)
{
    int logincount;
    int curr_login_num;
    struct count_arg arg;

    bzero(&arg,sizeof(arg));
    logincount = apply_utmpuid((APPLY_UTMP_FUNC)countuser, usernum, &arg);

    if (logincount < 1)
        RemoveMsgCountFile(user->userid);

#ifdef FILTER
    if (!strcmp(user->userid,"menss")&&logincount<2)
        return 0;
#endif
    if (HAS_PERM(user, PERM_MULTILOG))
        return 0;               /* don't check sysops */
    curr_login_num = get_utmp_number();
    /* Leeward: 97.12.22 BMs may open 2 windows at any time */
    /* Bigman: 2000.8.17 智囊团能够开2个窗口 */
    /* stephen: 2001.10.30 仲裁可以开两个窗口 */
	/* roy: 版主&AKA版同学可以开两个窗口 */
    if ((HAS_PERM(user,PERM_BOARDS) || HAS_PERM(user,PERM_CHATOP)||
        HAS_PERM(user,PERM_JURY) || HAS_PERM(user,PERM_CHATCLOAK)
		|| HAS_PERM(user, PERM_BMAMANGER)  )
        && logincount< 2)
        return 0;

    /* allow multiple guest user */
    if (!strcmp("guest", user->userid)) {
        if (logincount > MAX_GUEST_NUM) {
            return 2;
        }
        return 0;
    } else if (((curr_login_num < 500) && (logincount >= 2)) /*小于500可以双登*/
               || ((curr_login_num >= 500) && (logincount >= 1)  /*500人以上*/
                     && !(((arg.telnet_count==0)&&(mode==0))  /* telnet个数为零可以再登一个telnet */
                            || (((arg.www_count==0)&&(mode==1)) ))))       /*user login limit */
        return 1;
    return 0;
}

int old_compute_user_value( struct userec *urec)
{
    int         value;

    /* if (urec) has CHATCLOAK permission, don't kick it */
	/* 元老和荣誉帐号 在不自杀的情况下， 生命力999 Bigman 2001.6.23 */
    /* 
    * zixia 2001-11-20 所有的生命力都使用宏替换，
    * 在 smth.h/zixia.h 中定义 
    * */

    if( urec->userlevel & PERM_MM )
	return LIFE_DAY_SYSOP;
    
    if( ((urec->userlevel & PERM_HORNOR)||(urec->userlevel & PERM_CHATCLOAK )) && (!(urec->userlevel & PERM_SUICIDE)))
        return LIFE_DAY_NODIE;

    if ( urec->userlevel & PERM_SYSOP) 
	return LIFE_DAY_SYSOP;
	/* 站务人员生命力不变 Bigman 2001.6.23 */
	

    value = (time(0) - urec->lastlogin) / 60;    /* min */
    if (0 == value) value = 1; /* Leeward 98.03.30 */

    /* 修改: 将永久帐号转为长期帐号, Bigman 2000.8.11 */
    if ((urec->userlevel & PERM_XEMPT) && (!(urec->userlevel & PERM_SUICIDE)) )
    {	if (urec->lastlogin < 988610030)
        return LIFE_DAY_LONG; /* 如果没有登录过的 */
        else
            return (LIFE_DAY_LONG * 24 * 60 - value)/(60*24);
    }
    /* new user should register in 30 mins */
    if( strcmp( urec->userid, "new" ) == 0 ) {
        return (LIFE_DAY_NEW - value) / 60; /* *->/ modified by dong, 1998.12.3 */
    }

    /* 自杀功能,Luzi 1998.10.10 */
    if (urec->userlevel & PERM_SUICIDE)
        return (LIFE_DAY_SUICIDE * 24 * 60 - value)/(60*24);
    /**********************/
    if(urec->numlogins <= 3)
        return (LIFE_DAY_SUICIDE * 24 * 60 - value)/(60*24);
    if( !(urec->userlevel & PERM_LOGINOK) )
        return (LIFE_DAY_NEW * 24 * 60 - value)/(60*24);
    /* if (urec->userlevel & PERM_LONGID)
         return (667 * 24 * 60 - value)/(60*24); */
    return (LIFE_DAY_USER * 24 * 60 - value)/(60*24);
}

int compute_user_value(struct userec *urec)
{
    int value;
    int registeryear;
    int basiclife;

    /* if (urec) has CHATCLOAK permission, don't kick it */
    /* 元老和荣誉帐号 在不自杀的情况下， 生命力999 Bigman 2001.6.23 */
    /* 
       * zixia 2001-11-20 所有的生命力都使用宏替换，
       * 在 smth.h/zixia.h 中定义 
       * */
    /* 特殊处理请移动出cvs 代码 */

    if (urec->lastlogin < 1022036050)
        return old_compute_user_value(urec);
    /* 这个是死人的id,sigh */
    if ((urec->userlevel & PERM_HORNOR) && !(urec->userlevel & PERM_LOGINOK))
        return LIFE_DAY_LONG;


    if (((urec->userlevel & PERM_HORNOR) || (urec->userlevel & PERM_CHATCLOAK)) && (!(urec->userlevel & PERM_SUICIDE)))
        return LIFE_DAY_NODIE;

    if ((urec->userlevel & PERM_ANNOUNCE) && (urec->userlevel & PERM_OBOARDS))
        return LIFE_DAY_SYSOP;
    /* 站务人员生命力不变 Bigman 2001.6.23 */


    value = (time(0) - urec->lastlogin) / 60;   /* min */
    if (0 == value)
        value = 1;              /* Leeward 98.03.30 */

    /* new user should register in 30 mins */
    if (strcmp(urec->userid, "new") == 0) {
        return (LIFE_DAY_NEW - value) / 60;     /* *->/ modified by dong, 1998.12.3 */
    }

    /* 自杀功能,Luzi 1998.10.10 */
    if (urec->userlevel & PERM_SUICIDE)
        return (LIFE_DAY_SUICIDE * 24 * 60 - value) / (60 * 24);
    /**********************/
    if (urec->numlogins <= 3)
        return (LIFE_DAY_SUICIDE * 24 * 60 - value) / (60 * 24);
    if (!(urec->userlevel & PERM_LOGINOK))
        return (LIFE_DAY_NEW * 24 * 60 - value) / (60 * 24);
    /* if (urec->userlevel & PERM_LONGID)
       return (667 * 24 * 60 - value)/(60*24); */
    registeryear = (time(0) - urec->firstlogin) / 31536000;

	/* roy: 两年以上用户生命力为LIFE_DAY_LONG */
    if (registeryear < 2)
        basiclife = LIFE_DAY_USER + 1;
    else 
        basiclife = LIFE_DAY_LONG + 1;
    return (basiclife * 24 * 60 - value) / (60 * 24);
}

/**
 * 精华区相关函数。
 */
int ann_get_postfilename(char *filename, struct fileheader *fileinfo,
						MENU *pm)
{
	char fname[PATHLEN];
	char *ip;

	strcpy(filename, fileinfo->filename);
	sprintf(fname, "%s/%s", pm->path, filename);
	ip = &filename[strlen(filename) - 1];
	while (dashf(fname)) {
		if (*ip == 'Z')
			ip++, *ip = 'A', *(ip + 1) = '\0';
		else
			(*ip)++;
		sprintf(fname, "%s/%s", pm->path, filename);
	}
    return 0;
}

/**
 * 文章相关函数。
 */
time_t get_posttime(const struct fileheader *fileinfo)
{
	return atoi(fileinfo->filename + 2);
}

void set_posttime(struct fileheader *fileinfo)
{
	return;
}

void set_posttime2(struct fileheader *dest, struct fileheader *src)
{
	return;
}

/**
 * 版面相关。
 */
void build_board_structure(const char *board)
{
	return;
}

void get_mail_limit(struct userec* user,int *sumlimit,int * numlimit)
{
    if ((!(user->userlevel & PERM_SYSOP)) && strcmp(user->userid, "Arbitrator")) {
        if (user->userlevel & PERM_CHATCLOAK) {
            *sumlimit = 4000;
            *numlimit = 4000;
        } else
            /*
             *              * if (lookupuser->userlevel & PERM_BOARDS)
             *                           * set BM, chatop, and jury have bigger mailbox, stephen 2001.10.31 
             *                                        */
        if (user->userlevel & PERM_MANAGER) {
            *sumlimit = 600;
            *numlimit = 600;
        } else if (user->userlevel & PERM_LOGINOK) {
            *sumlimit = 240;
            *numlimit = 300;
        } else {
            *sumlimit = 15;
            *numlimit = 15;
        }
    }
    else {
        *sumlimit = 9999;
        *numlimit = 9999;
        return;
    }
}

char *showuserip(struct userec *user, char *ip)
{
    static char sip[25];
    char *c;

    if ((getCurrentUser() != NULL) && (getCurrentUser()->title == 10))
        return ip;
    if (user != NULL && (!DEFINE(user, DEF_HIDEIP)))
        return ip;
    strncpy(sip, ip, 24);
    sip[24] = 0;
    if ((c = strrchr(sip, '.')) != NULL) {
        *(++c) = '*';
        *(++c) = '\0';
    }
    return sip;
}

/* board permissions control */
int check_read_perm(struct userec *user, const struct boardheader *board)
{
    if (board == NULL)
        return 0;
    if (board->level & PERM_POSTMASK || HAS_PERM(user, board->level) || (board->level & PERM_NOZAP)) {
        if (board->flag & BOARD_CLUB_READ) {    /*俱乐部*/
            if (HAS_PERM(user,PERM_OBOARDS)&&HAS_PERM(user, PERM_SYSOP))
                return 1;
            if (board->clubnum <= 0 || board->clubnum >= MAXCLUB)
                return 0;
            if (user->club_read_rights[(board->clubnum - 1) >> 5] & (1 << ((board->clubnum - 1) & 0x1f)))
                return 1;
            else
                return 0;
        }
        return 1;
    }
    return 0;
}

int check_see_perm(struct userec* user,const struct boardheader* board)
{
    if (board == NULL)
        return 0;
    if (board->level & PERM_POSTMASK
    	|| ((user==NULL)&&(board->level==0))
    	|| ((user!=NULL)&& HAS_PERM(user, board->level) )
    	|| (board->level & PERM_NOZAP))
	{
        if (board->flag & BOARD_CLUB_HIDE)     /*隐藏俱乐部*/
		{
			if (user==NULL) return 0;
			   if (HAS_PERM(user, PERM_OBOARDS))
					return 1;
			   return check_read_perm(user,board);
		}
        return 1;
    }
    return 0;
}

//自动通过注册的函数  binxun
int auto_register(char* userid,char* email,int msize)
{
	struct userdata ud;
	struct userec* uc;
	char* item,*temp;
	char fdata[7][STRLEN];
	char genbuf[STRLEN];
	char buf[STRLEN];
	char fname[STRLEN];
	int unum;
	FILE* fout;
	int n;
	struct userec deliveruser;
	static const char *finfo[] = { "帐号位置", "申请代号", "真实姓名", "服务单位",
        "目前住址", "连络电话", "生    日", NULL
    };
  	static const char *field[] = { "usernum", "userid", "realname", "career",
    	"addr", "phone", "birth", NULL
	};

	bzero(&deliveruser,sizeof(struct userec));
	strcpy(deliveruser.userid,"deliver");
	deliveruser.userlevel = -1;
	strcpy(deliveruser.username,"自动发信系统");



	bzero(fdata,7*STRLEN);

	if((unum = getuser(userid,&uc)) == 0)return -1;//faild
	if(read_userdata(userid,&ud) < 0)return -1;

	strncpy(genbuf,email,STRLEN - 16);
	item =strtok(genbuf,"#");
	if(item)strncpy(ud.realname,item,NAMELEN);
	item = strtok(NULL,"#");  //学号
	item = strtok(NULL,"#");
	if(item)strncpy(ud.address,item,STRLEN);

	email[strlen(email) - 3] = '@';
	strncpy(ud.realemail,email,STRLEN-16); //email length must be less STRLEN-16


	sprintf(fdata[0],"%d",unum);
	strncpy(fdata[2],ud.realname,NAMELEN);
	strncpy(fdata[4],ud.address,STRLEN);
	strncpy(fdata[5],ud.email,STRLEN);
	strncpy(fdata[1],userid,IDLEN);

	sprintf(buf,"tmp/email/%s",userid);
	if ((fout = fopen(buf,"w")) != NULL)
	{
		fprintf(fout,"%s\n",email);
		fclose(fout);
	}

	if(write_userdata(userid,&ud) < 0)return -1;
	mail_file("deliver","etc/s_fill",userid,"恭喜你,你已经完成注册.",0,0);
	//sprintf(genbuf,"deliver 让 %s 自动通过身份确认.",uinfo.userid);

	sprintf(fname, "tmp/security.%d", getpid());
	if ((fout = fopen(fname, "w")) != NULL)
	{
		fprintf(fout, "系统安全记录系统\n\033[32m原因：%s自动通过注册\033[m\n", userid);
                fprintf(fout, "以下是通过者个人资料");
                fprintf(fout, "\n\n您的代号     : %s\n", ud.userid);
                fprintf(fout, "您的昵称     : %s\n", uc->username);
                fprintf(fout, "真实姓名     : %s\n", ud.realname);
                fprintf(fout, "电子邮件信箱 : %s\n", ud.email);
                fprintf(fout, "真实 E-mail  : %s\n", ud.realemail);
                fprintf(fout, "服务单位     : %s\n", "");
                fprintf(fout, "目前住址     : %s\n", ud.address);
                fprintf(fout, "连络电话     : %s\n", "");
                fprintf(fout, "注册日期     : %s", ctime(&uc->firstlogin));
                fprintf(fout, "最近光临日期 : %s", ctime(&uc->lastlogin));
                fprintf(fout, "最近光临机器 : %s\n", uc->lasthost);
                fprintf(fout, "上站次数     : %d 次\n", uc->numlogins);
                fprintf(fout, "文章数目     : %d(Board)\n", uc->numposts);
                fprintf(fout, "生    日     : %s\n", "");

                fclose(fout);
                //post_file(currentuser, "", fname, "Registry", str, 0, 2);

		sprintf(genbuf,"%s 自动通过注册",ud.userid);
		post_file(&deliveruser,"",fname,"Registry",genbuf,0,1,getSession());
	/*if (( fout = fopen(logfile,"a")) != NULL)
	{
		fclose(fout);
	}*/
	}

	sethomefile(buf, userid, "/register");
	if ((fout = fopen(buf, "w")) != NULL) {
		for (n = 0; field[n] != NULL; n++)
			fprintf(fout, "%s     : %s\n", finfo[n], fdata[n]);
		fprintf(fout, "您的昵称     : %s\n", uc->username);
		fprintf(fout, "电子邮件信箱 : %s\n", ud.email);
		fprintf(fout, "真实 E-mail  : %s\n", ud.realemail);
		fprintf(fout, "注册日期     : %s\n", ctime(&uc->firstlogin));
		fprintf(fout, "注册时的机器 : %s\n", uc->lasthost);
		fprintf(fout, "Approved: %s\n", userid);
		fclose(fout);
	}

	return 0;
}

