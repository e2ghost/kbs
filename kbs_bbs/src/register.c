/*
    Pirate Bulletin Board System
    Copyright (C) 1990, Edward Luke, lush@Athena.EE.MsState.EDU
    Eagles Bulletin Board System
    Copyright (C) 1992, Raymond Rocker, rocker@rock.b11.ingr.com
                        Guy Vega, gtvega@seabass.st.usm.edu
                        Dominic Tynes, dbtynes@seabass.st.usm.edu

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 1, or (at your option)
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

/*
    checked Global variable
*/
#include "bbs.h"

#define  EMAIL          0x0001
#define  NICK           0x0002
#define  REALNAME       0x0004
#define  ADDR           0x0008
#define  REALEMAIL      0x0010
#define  BADEMAIL       0x0020
#define  NEWREG         0x0040

char *sysconf_str();
char *Ctime();

extern struct user_info uinfo;
extern time_t login_start_time;
extern int convcode;            /* KCN,99.09.05 */
extern int switch_code();       /* KCN,99.09.05 */

void new_register()
{
    struct userec newuser;
    int allocid, do_try, flag;
    FILE* fn;
    char buf[STRLEN], fname[PATHLEN], title[STRLEN];

/* temp !!!!!*/
/*    prints("Sorry, we don't accept newusers due to system problem, we'll fixit ASAP\n");
    oflush();
    sleep(2);
    exit(-1);
*/
    memset(&newuser, 0, sizeof(newuser));
    getdata(0, 0, "使用GB编码阅读?(\xa8\xcf\xa5\xce BIG5\xbd\x58\xbe\x5c\xc5\xaa\xbd\xd0\xbf\xefN)(Y/N)? [Y]: ", buf, 4, DOECHO, NULL, true);
    if (*buf == 'n' || *buf == 'N')
        if (!convcode)
            switch_code();

    ansimore("etc/register", false);
    do_try = 0;
    while (1) {
        if (++do_try >= 10) {
            prints("\n掰掰，按太多下  <Enter> 了...\n");
            refresh();
            longjmp(byebye, -1);
        }
        getdata(0, 0, "请输入代号: ", newuser.userid, IDLEN + 1, DOECHO, NULL, true);
        flag = 1;
        if (id_invalid(newuser.userid) == 1) {
            prints("帐号必须由英文字母或数字组成，并且第一个字符必须是英文字母!\n");
            /*                prints("帐号必须由英文字母或数字，而且帐号第一个字是英文字母!\n"); */
            flag = 0;
        }
        if (flag) {
            if (strlen(newuser.userid) < 2) {
                prints("代号至少需有两个英文字母!\n");
            } else if ((*newuser.userid == '\0') || bad_user_id(newuser.userid)) {
                prints("系统用字或是不雅的代号。\n");
            } else if ((usernum = searchuser(newuser.userid)) != 0) {   /*( dosearchuser( newuser.userid ) ) midified by dong , 1998.12.2, change getuser -> searchuser , 1999.10.26 */
                prints("此帐号已经有人使用\n");
            } else {
                /*---	---*/
                struct stat lst;
                time_t lnow;

                lnow = time(NULL);
                sethomepath(genbuf, newuser.userid);
                if (!stat(genbuf, &lst) && S_ISDIR(lst.st_mode)
                    && (lnow - lst.st_ctime < SEC_DELETED_OLDHOME /* 3600*24*30 */ )) {
                    prints("目前无法注册帐号%s，请与系统管理人员联系。\n", newuser.userid);
                    sprintf(genbuf, "IP %s new id %s failed[home changed in past 30 days]", fromhost, newuser.userid);
                    bbslog("user","%s",genbuf);
                } else
                /*---	---*/
                    break;
            }
        }
    }

    newuser.firstlogin = newuser.lastlogin = time(NULL) - 13 * 60 * 24;
    do_try = 0;
    while (1) {
        char passbuf[STRLEN], passbuf2[STRLEN];

        if (++do_try >= 10) {
            prints("\n掰掰，按太多下  <Enter> 了...\n");
            refresh();
            longjmp(byebye, -1);
        }
        getdata(0, 0, "请设定您的密码: ", passbuf, 39, NOECHO, NULL, true);
        if (strlen(passbuf) < 4 || !strcmp(passbuf, newuser.userid)) {
            prints("密码太短或与使用者代号相同, 请重新输入\n");
            continue;
        }
        getdata(0, 0, "请再输入一次你的密码: ", passbuf2, 39, NOECHO, NULL, true);
        if (strcmp(passbuf, passbuf2) != 0) {
            prints("密码输入错误, 请重新输入密码.\n");
            continue;
        }

        setpasswd(passbuf, &newuser);
        break;
    }
    newuser.userlevel = PERM_BASIC;
    newuser.userdefine = -1;
/*   newuser.userdefine&=~DEF_MAILMSG;
    newuser.userdefine&=~DEF_EDITMSG; */
    newuser.userdefine &= ~DEF_NOTMSGFRIEND;
    if (convcode)
        newuser.userdefine &= ~DEF_USEGB;

    newuser.notemode = -1;
    newuser.exittime = time(NULL) - 100;
    /*newuser.unuse2 = -1;*/
    newuser.flags[0] = CURSOR_FLAG;
    newuser.flags[0] |= PAGER_FLAG;
    newuser.flags[1] = 0;
    newuser.firstlogin = newuser.lastlogin = time(NULL);

    allocid = getnewuserid2(newuser.userid);
    if (allocid > MAXUSERS || allocid <= 0) {
        prints("抱歉, 由于某些系统原因, 无法注册新的帐号.\n\r");
        oflush();
        sleep(2);
        exit(1);
    }
    newbbslog(BBSLOG_USIES, "APPLY: uid %d from %s", allocid, fromhost);

    update_user(&newuser, allocid, 1);

    if (!dosearchuser(newuser.userid)) {
        /* change by KCN 1999.09.08
           fprintf(stderr,"User failed to create\n") ;
         */
        prints("User failed to create %d-%s\n", allocid, newuser.userid);
        oflush();
        exit(1);
    }
    bbslog("user","%s","new account");
}

/*加入对 #TH 结尾的realemail的帐号自动通过注册的功能  by binxun
*/
int invalid_realmail(userid, email, msize)
    char *userid, *email;
    int msize;
{
    FILE *fn;
    char *emailfile, ans[4], fname[STRLEN];
    char genbuf[STRLEN];
    struct userec* uc;
    time_t now;
    int len = strlen(email);

    if ((emailfile = sysconf_str("EMAILFILE")) == NULL)
        return 0;

    if (strchr(email, '@') && valid_ident(email))
        return 0;
    /*
       ansimore( emailfile, false );
       getdata(t_lines-1,0,"您要现在 email-post 吗? (Y/N) [Y]: ",
       ans,2,DOECHO,NULL,true);
       while( *ans != 'n' && *ans != 'N' ) {
     */
    sprintf(fname, "tmp/email/%s", userid);
    if ((fn = fopen(fname, "r")) != NULL) {
        fgets(genbuf, STRLEN, fn);
        fclose(fn);
        strtok(genbuf, "\n");
        if (!valid_ident(genbuf)) {
        } else if (strchr(genbuf, '@') != NULL) {
            unlink(fname);
            strncpy(email, genbuf, msize);
            move(10, 0);
            prints("恭贺您!! 您已通过身份验证, 成为本站公民. \n");
            prints("         本站为您所提供的额外服务, \n");
            prints("         包括Mail,Post,Message,Talk 等. \n");
            prints("  \n");
            prints("建议您,  先四处浏览一下, \n");
            prints("         不懂的地方, 请在 sysop 版留言, \n");
            prints("         本站会派专人为您解答. \n");
            getdata(18, 0, "请按 <Enter>  <<  ", ans, 2, DOECHO, NULL, true);
            return 0;
        }
    }

#ifdef HAVE_TSINGHUA_INFO_REGISTER

    if(len >= 3)
    {
    	strncpy(genbuf,email+strlen(email)-3,3);
	if(!strncasecmp(genbuf,"#TH",3))
	{
		getuser(userid,&uc);
		// > 3 days
		now = time(NULL);
		if(now - uc->firstlogin >= REGISTER_TSINGHUA_WAIT_TIME)
		{
	 		if(auto_register(userid,email,msize) < 0) // 完成自动注册
				return 1;
			else
				return 0;     //success
		}
	}
    }
#endif
    return 1;
}

void check_register_info()
{
    char *newregfile;
    int perm;
    char buf[STRLEN];

    clear();
    sprintf(buf, "%s", email_domain());
    if (!(currentuser->userlevel & PERM_BASIC)) {
        currentuser->userlevel = PERM_DENYMAIL|PERM_DENYRELAX;
        return;
    }
    /*urec->userlevel |= PERM_DEFAULT; */
    perm = PERM_DEFAULT & sysconf_eval("AUTOSET_PERM",PERM_DEFAULT);

    invalid_realmail(currentuser->userid,curruserdata.realemail,STRLEN - 16);

    do_after_login(currentuser,utmpent,0);

    /*    if( sysconf_str( "IDENTFILE" ) != NULL ) {  commented out by netty to save time */
    while (strlen(currentuser->username) < 2) {
        getdata(2, 0, "请输入您的昵称:(例如," DEFAULT_NICK ") << ", buf, NAMELEN, DOECHO, NULL, true);
        strcpy(currentuser->username, buf);
        strcpy(uinfo.username, buf);
        UPDATE_UTMP_STR(username, uinfo);
    }
    if (strlen(curruserdata.realname) < 2) {
        move(3, 0);
        prints("请输入您的真实姓名: (站长会帮您保密的 !)\n");
        getdata(4, 0, "> ", buf, NAMELEN, DOECHO, NULL, true);
        strcpy(curruserdata.realname, buf);
    }
    if (strlen(curruserdata.address) < 6) {
        move(5, 0);
        prints("您目前填写的地址是‘%s’，长度小于 [1m[37m6[m，系统认为其过于简短。\n", curruserdata.address[0] ? curruserdata.address : "空地址");  /* Leeward 98.04.26 */
        getdata(6, 0, "请详细填写您的住址：", buf, NAMELEN, DOECHO, NULL, true);
        strcpy(curruserdata.address, buf);
    }
    if (strchr(curruserdata.email, '@') == NULL) {
        clear();
        move(3, 0);
        prints("只有本站的合法公民才能够完全享有各种功能， \n");
        /* alex           prints( "成为本站合法公民有两种办法：\n\n" );
           prints( "1. 如果你有合法的email信箱(非BBS), \n");
           prints( "       你可以用回认证信的方式来通过认证。 \n\n" );
           prints( "2. 如果你没有email信箱(非BBS)，你可以在进入本站以后，\n" );
           prints( "       在'个人工具箱'内 详细注册真实身份，( 主菜单  -->  I) 个人工具箱  -->  F) 填写注册单 )\n" );
           prints( "       SYSOPs 会尽快 检查并确认你的注册单。\n" );
           move( 17, 0 );
           prints( "电子信箱格式为: xxx@xxx.xxx.edu.cn \n" );
           getdata( 18, 0, "请输入电子信箱: (不能提供者按 <Enter>) << "
           , urec->email, STRLEN,DOECHO,NULL,true);
           if ((strchr( urec->email, '@' ) == NULL )) {
           sprintf( genbuf, "%s.bbs@%s", urec->userid,buf );
           strncpy( urec->email, genbuf, STRLEN);
           }
           alex, 因为取消了email功能 , 97.7 */
        prints("成为" NAME_BBS_NICK "合法" NAME_USER_SHORT "的方法如下：\n\n");
        prints("您的帐号在第一次登录后的 " REGISTER_WAIT_TIME_NAME "内（[1m[33m不是指上 BBS " REGISTER_WAIT_TIME_NAME "[m），\n");
        prints("    处于新手上路期间, 不能注册成为合法" NAME_USER_SHORT "，请四处参观学习，推荐阅读BBSHELP 版，学习本站使用方法和各种礼仪。\n");
        prints("\n " REGISTER_WAIT_TIME_NAME "后, 您就可以\033[33;1m填写注册单\033[m了，注册单通过站务认证以后，您就拥有本站合法用户的基本权限。注册单填写路径如下: \n\n");
        prints("I) 个人工具箱 --> F) 填写注册单\n\n");
        //prints("    " NAME_SYSOP_GROUP "会尽快检查并确认你的注册单。\n\n");
        /* Leeward adds below 98.04.26 */
        prints("[1m[33m如果您已经通过注册，成为合法" NAME_USER_SHORT "，却依然看到本信息，那可能是由于您没有在‘个人工具箱’内设定‘电子邮件信箱’。[m\n");
		prints("\nI) 个人工具箱 --> I) 设定个人资料\n");
		prints("\n如果你实在没有任何可用的'电子邮件信箱'可以设定，又不愿意看到本信息，可以使用%s.bbs@%s进行设定。\n
	 		\033[33;1m注意: 上面的子邮件信箱不能接收电子邮件，仅用来使系统不再显示本信息。\033[m", currentuser->userid, NAME_BBS_ENGLISH);
        pressreturn();
    }
#ifdef HAVE_BIRTHDAY
	if (!is_valid_date(curruserdata.birthyear+1900, curruserdata.birthmonth,
				curruserdata.birthday))
	{
		time_t now;
		struct tm *tmnow;

		now = time(0);
		tmnow = localtime(&now);
		clear();
		buf[0] = '\0';
		move(0, 0);
		prints("我们检查到你的部分注册资料不够完全，为了更好的为您提供个性化的服务，");
		move(1, 0);
		prints("希望您填写以下资料。");
		while (buf[0] < '1' || buf[0] > '2')
		{
			getdata(2, 0, "请输入你的性别: [1]男的 [2]女的 (1 or 2): ",
					buf, 2, DOECHO, NULL, true);
		}
		switch (buf[0])
		{
		case '1':
			curruserdata.gender = 'M';
			break;
		case '2':
			curruserdata.gender = 'F';
			break;
		}
		move(4, 0);
		prints("请输入您的出生日期");
		while (curruserdata.birthyear < tmnow->tm_year - 98
			   || curruserdata.birthyear > tmnow->tm_year - 3)
		{
			buf[0] = '\0';
			getdata(5, 0, "四位数公元年: ", buf, 5, DOECHO, NULL, true);
			if (atoi(buf) < 1900)
				continue;
			curruserdata.birthyear = atoi(buf) - 1900;
		}
		while (curruserdata.birthmonth < 1 || curruserdata.birthmonth > 12)
		{
			buf[0] = '\0';
			getdata(6, 0, "出生月: (1-12) ", buf, 3, DOECHO, NULL, true);
			curruserdata.birthmonth = atoi(buf);
		}
		do
		{
			buf[0] = '\0';
			getdata(7, 0, "出生日: (1-31) ", buf, 3, DOECHO, NULL, true);
			curruserdata.birthday = atoi(buf);
		} while (!is_valid_date(curruserdata.birthyear + 1900,
					curruserdata.birthmonth,
					curruserdata.birthday));
		write_userdata(currentuser->userid, &curruserdata);
	}
#endif
#ifdef NEW_COMERS
	if (currentuser->numlogins == 1)
	{
		FILE *fout;
		char buf2[STRLEN];

		sprintf(buf, "tmp/newcomer.%s", currentuser->userid);
		if ((fout = fopen(buf, "w")) != NULL)
		{
			fprintf(fout, "大家好,\n\n");
			fprintf(fout, "我是 %s (%s), 来自 %s\n", currentuser->userid,
					currentuser->username, fromhost);
			fprintf(fout, "今天%s初来此站报到, 请大家多多指教。\n",
#ifdef HAVE_BIRTHDAY
					(curruserdata.gender == 'M') ? "小弟" : "小女子");
#else
                                        "小弟");
#endif
			move(9, 0);
			prints("请作个简短的个人简介, 向本站其他使用者打个招呼\n");
			prints("(最多三行, 写完可直接按 <Enter> 跳离)....");
			getdata(11, 0, ":", buf2, 75, DOECHO, NULL, true);
			if (buf2[0] != '\0')
			{
				fprintf(fout, "\n\n自我介绍:\n\n");
				fprintf(fout, "%s\n", buf2);
				getdata(12, 0, ":", buf2, 75, DOECHO, NULL, true);
				if (buf2[0] != '\0')
				{
					fprintf(fout, "%s\n", buf2);
					getdata(13, 0, ":", buf2, 75, DOECHO, NULL, true);
					if (buf2[0] != '\0')
					{
						fprintf(fout, "%s\n", buf2);
					}
				}
			}
			fclose(fout);
			sprintf(buf2, "新手上路: %s", currentuser->username);
			post_file(currentuser, "", buf, "newcomers", buf2, 0, 2);
			unlink(buf);
		}
		pressanykey();
	}
#endif
    if (!strcmp(currentuser->userid, "SYSOP")) {
        currentuser->userlevel = ~0;
        currentuser->userlevel &= ~PERM_SUICIDE;        /* Leeward 98.10.13 */
        currentuser->userlevel &= ~(PERM_DENYMAIL|PERM_DENYRELAX);       /* Bigman 2000.9.22 */
        currentuser->userlevel &= ~PERM_JURY;       /* 不能是仲裁 */
    }
    if (!(currentuser->userlevel & PERM_LOGINOK)) {
        if (HAS_PERM(currentuser, PERM_SYSOP))
            return;
        if (!invalid_realmail(currentuser->userid, curruserdata.realemail, STRLEN - 16)) {
            currentuser->userlevel |= PERM_DEFAULT;
            /*
            if (HAS_PERM(currentuser, PERM_DENYPOST) && !HAS_PERM(currentuser, PERM_SYSOP))
                currentuser->userlevel &= ~PERM_POST;
            */
        } else {
            /* added by netty to automatically send a mail to new user. */
            /* begin of check if local email-addr  */
            /*       if (
               (!strstr( urec->email, "@bbs.") ) &&
               (!strstr( urec->email, ".bbs@") )&&
               (!invalidaddr(urec->email))&&
               sysconf_str( "EMAILFILE" )!=NULL) 
               {
               move( 15, 0 );
               prints( "您的电子信箱  尚须通过回信验证...  \n" );
               prints( "      SYSOP 将寄一封验证信给您,\n" );
               prints( "      您只要回信, 就可以成为本站合格公民.\n" );
               getdata( 19 ,0, "您要 SYSOP 寄这一封信吗?(Y/N) [Y] << ", ans,2,DOECHO,NULL,true);
               if ( *ans != 'n' && *ans != 'N' ) {
               code=(time(0)/2)+(rand()/10);
               sethomefile(genbuf,urec->userid,"mailcheck");
               if((dp=fopen(genbuf,"w"))==NULL)
               {
               fclose(dp);
               return;
               }
               fprintf(dp,"%9.9d\n",code);
               fclose(dp);
               sprintf( genbuf, "/usr/lib/sendmail -f SYSOP.bbs@%s %s ", 
               email_domain(), urec->email );
               fout = popen( genbuf, "w" );
               fin  = fopen( sysconf_str( "EMAILFILE" ), "r" );
               if ((fin != NULL) && (fout != NULL)) {
               fprintf( fout, "Reply-To: SYSOP.bbs@%s\n", email_domain());
               fprintf( fout, "From: SYSOP.bbs@%s\n",  email_domain() ); 
               fprintf( fout, "To: %s\n", urec->email);
               fprintf( fout, "Subject: @%s@[-%9.9d-]firebird mail check.\n", urec->userid ,code);
               fprintf( fout, "X-Forwarded-By: SYSOP \n" );
               fprintf( fout, "X-Disclaimer: None\n");
               fprintf( fout, "\n");
               fprintf(fout,"您的基本资料如下：\n",urec->userid);
               fprintf(fout,"使用者代号：%s (%s)\n",urec->userid,urec->username);
               fprintf(fout,"姓      名：%s\n",urec->realname);
               fprintf(fout,"上站位置  ：%s\n",urec->lasthost);
               fprintf(fout,"电子邮件  ：%s\n\n",urec->email);
               fprintf(fout,"亲爱的 %s(%s):\n",urec->userid,urec->username);
               while (fgets( genbuf, 255, fin ) != NULL ) {
               if (genbuf[0] == '.' && genbuf[ 1 ] == '\n')
               fputs( ". \n", fout );
               else fputs( genbuf, fout );
               }
               fprintf(fout, ".\n");                                    
               fclose( fin );
               fclose( fout );                                     
               }
               getdata( 20 ,0, "信已寄出, SYSOP 将等您回信哦!! 请按 <Enter> << ", ans,2,DOECHO,NULL ,true);
               }
               }else
               {
               showansi=1;
               if(sysconf_str( "EMAILFILE" )!=NULL)
               {
               prints("\n你的电子邮件地址 【[33m%s[m】\n",urec->email);
               prints("并非 Unix 帐号，系统不会投递身份确认信，请到[32m工具箱[m中修改..\n");
               pressanykey();
               }
               }
               deleted by alex, remove email certify */

            clear();            /* Leeward 98.05.14 */
            move(12, 0);
            prints("您现在还没有通过身份认证，没有talk,mail,message,post等权限。\n");
            prints("如果你要成为" NAME_BBS_NICK "的注册" NAME_USER_SHORT "，");
            prints("请到[33;1m个人工具箱[m_详细真实地填写[32m 注册单 [m");
            prints("经" NAME_SYSOP_GROUP "审核通过以后，就可以成为本站的注册" NAME_USER_SHORT ".\n");
            prints("\n主菜单  -->  I) 个人工具箱  -->  F) 填写注册单\n");
            pressreturn();
        }
        /* end of check if local email-addr */
        /*  above lines added by netty...  */
    }
    	curruserdata.realemail[STRLEN -16 - 1] = '\0';  //纠错代码
	write_userdata(currentuser->userid, &curruserdata);
    newregfile = sysconf_str("NEWREGFILE");
    /*if (currentuser->lastlogin - currentuser->firstlogin < REGISTER_WAIT_TIME && !HAS_PERM(currentuser, PERM_SYSOP) && newregfile != NULL) {
        currentuser->userlevel &= ~(perm);
        ansimore(newregfile, true);
    }先注释掉*/
}

/* 转让ID     by binxun  ... 2003.5 */
void ConveyID()
{
    FILE* fn = NULL;
	long now;
	char buf[STRLEN],filename[STRLEN];

    //检查权限
        if (HAS_PERM(currentuser, PERM_SYSOP) || HAS_PERM(currentuser, PERM_BOARDS) || HAS_PERM(currentuser, PERM_OBOARDS) || HAS_PERM(currentuser, PERM_ACCOUNTS)
        || HAS_PERM(currentuser, PERM_ANNOUNCE)
        || HAS_PERM(currentuser, PERM_JURY) || HAS_PERM(currentuser, PERM_SUICIDE) || HAS_PERM(currentuser, PERM_CHATOP) || (!HAS_PERM(currentuser, PERM_POST))
        || HAS_PERM(currentuser, PERM_DENYMAIL)
        || HAS_PERM(currentuser, PERM_DENYRELAX)) {
        clear();
        move(11, 28);
		prints("\033[1;33m你有重任在身,不能转让ID!\033[m");
        pressanykey();
        return;
    }

	//给出提示信息

    /*
    clear();
    move(1, 0);
    prints("选择转让ID后,将使该ID您的生命力减少到14天，14天后您的帐号自动消失。");
    move(3, 0);
    prints("在这14天内若改变主意的话，则可以通过登录本站一次恢复原生命力");
    move(5, 0);
    prints("自杀用户将丢失所有[33m特殊权限[m！！！");
    move(7, 0);
    */

    if (askyn("你确定要转让这个 ID 吗？", 0) == 1) {
        clear();
        getdata(0, 0, "请输入原密码(输入正确的话会立刻断线): ", buf, 39, NOECHO, NULL, true);   /*Haohmaru,98.10.12,check the passwds */
        if (*buf == '\0' || !checkpasswd2(buf, currentuser)) {
            prints("\n\n很抱歉, 您输入的密码不正确。\n");
            pressanykey();
            return;
        }

        currentuser->userlevel &= ~PERM_BASIC;

		//记录备份信息
        now = time(0);
        sprintf(filename, "etc/%s.tmp", currentuser->userid);
        fn = fopen(filename, "w");
		if(fn){
			fprintf(fn,"\033[1m %s \033[m 在 \033[1m%24.24s\033[m 转让ID了,以下是他的资料，请保留...",currentuser->userid,ctime(&now));
			getuinfo(fn, currentuser);
			fprintf(fn, "\n                     \033[1m 系统自动发信系统留\033[m\n");
			fclose(fn);
			sprintf(buf, "%s 转让ID", currentuser->userid);
			post_file(currentuser, "", filename, "Registry", buf, 0, 1);
			unlink(filename);
		}
		else{
		    //error info
		}

		//清空个人信息

		//断线
        abort_bbs(0);
    }

    return;
}
