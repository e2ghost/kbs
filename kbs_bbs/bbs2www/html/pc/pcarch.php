<?php
	/*
	** @id:windinsn dec 22,2003
	*/
	$needlogin = 0;
	require("pcfuncs.php");
	
	function pc_check_archdate($yy,$mm)
	{
		$yy = (int)($yy);
		$mm = (int)($mm);
		if($yy > date("Y") || $yy < 2003 ) return FALSE;
		if($mm < 1 || $mm > 12) return FALSE;
		$nextMonth = get_next_month($yy,$mm);
		$nyy = $nextMonth[0];
		$nmm = $nextMonth[1];
		return array( number_format($yy * 10000000000 + $mm * 100000000 + 1000000 , 0 , "" , "") ,
		       		number_format($nyy*10000000000 + $nmm * 100000000 + 1000000 , 0 , "" , "")
		       		);
	}
	
	$userid = addslashes($_GET["userid"]);
	$archDate = pc_check_archdate($_GET["y"],$_GET["m"]);
	
	if(!$archDate)
	{
		pc_html_init("gb2312");
		html_error_quit("对不起，档案日期错误!");
		exit();	
	}
	
	$link = pc_db_connect();
	$pc = pc_load_infor($link,$userid);
	if(!$pc)
	{
		pc_html_init("gb2312");
		pc_db_close($link);
		html_error_quit("对不起，您要查看的Blog不存在");
		exit();
	}
?>
<?xml version="1.0" encoding="gb2312"?>
<!DOCTYPE html
     PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<!-- saved from url=<?php echo "http://".$pcconfig["SITE"]."/pc/pcarch.php?userid=".$pc["USER"]."&y=".substr($archDate[0],0,4)."&m=".substr($archDate[0],4,2); ?>-->
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312"/>
<TITLE><?php echo $pc["NAME"]."(".time_format($archDate[0])." ～ ".time_format($archDate[1])."档案)"; ?></TITLE>
<style>
.date{FONT-WEIGHT: bold;MARGIN-BOTTOM: 10px;FONT-SIZE: 18px;COLOR: #993366;FONT-FAMILY: palatino, georgia, times new roman, serif}
.content{font-size:14px;line-height:24px;}
</style>
<body>
<?php
	echo "<a name=\"top\"><p class=date>::Blog信息::<br />名称: ".$pc["NAME"]."<br />作者: <a href=\"".$pcconfig["SITE"]."/bbsqry.php?userid=".$pc["USER"]."\">".$pc["USER"]."</a><br />域名: <a href=\"".pc_personal_domainname($pc["USER"])."\">".pc_personal_domainname($pc["USER"])."</a><br />站点: <a href=\"http://".$pcconfig["SITE"]."\">".$pcconfig["BBSNAME"]."</a><br /></p>";
	echo "<p class=date>档案日期：".time_format($archDate[0])." ～ ".time_format($archDate[1])."</p><hr size=1>";
	
	$query = "SELECT * FROM nodes WHERE uid = '".$pc["UID"]."' AND type = 0 AND changed >= ".$archDate[0]." AND changed <= ".$archDate[1]." ";
	if(pc_is_admin($currentuser,$pc) && $loginok == 1)
		$query .= " AND ( access = 0 OR access = 1 OR access = 2 ) ";
	elseif(pc_is_friend($currentuser["userid"],$pc["USER"]) || bbs_is_bm($pcconfig["BRDNUM"], $currentuser["index"]))
		$query .= " AND ( access = 0 OR access = 1 ) ";
	else
		$query .=" AND access = 0 ";
	
	$query .=" ORDER BY nid DESC ;";
	$result = mysql_query($query);
	while($rows=mysql_fetch_array($result))
	{
		echo "<p class=date>".time_format($rows[created])."</p>";
		echo "<p class=content><strong>主题: </strong><a href=\"http://".$pcconfig["SITE"]."/pc/pccon.php?id=".$pc["UID"]."&nid=".$rows[nid]."&s=all\">".html_format($rows[subject])."</a><br />";
		echo "<font class=content>".html_format($rows[body],TRUE,$rows[htmltag])."</font><br /><br /><a href=\"#top\">[返回顶部]</a></p><hr size=1>";
	}
	mysql_free_result($result);
	
	echo "<p align=center><a href=\"http://".$pcconfig["SITE"]."\">".$pcconfig["BBSNAME"]."</a></p>";
	pc_db_close($link);
	html_normal_quit();
?>