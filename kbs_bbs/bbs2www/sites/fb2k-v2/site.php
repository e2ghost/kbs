<?php
/*
define("ATTACHTMPPATH","boards/_attach");
function getattachtmppath($userid,$utmpnum)
{
  return ATTACHTMPPATH . "/" . $userid . "_" . $utmpnum;
}
*/

define("ATTACHMAXSIZE","1048576");
define("ATTACHMAXCOUNT","20");
define("MAINPAGE_FILE","mainpage.php");
define("QUOTED_LINES","3");
$section_nums = array("0", "1", "2", "3", "4", "5", "6", "7", "8", "9","A","B","C");
$section_names = array(
    array("BBS 系统", "[站内]"),
    array("清华大学", "[本校]"),
    array("学术科学", "[学科/语言]"),
    array("休闲娱乐", "[休闲/音乐]"),
    array("文化人文", "[文化/人文]"),
    array("社会信息", "[社会/信息]"),
    array("游戏天地", "[游戏/娱乐]"),
    array("体育健身", "[运动/健身]"),
    array("知性感性", "[谈天/感性]"),
    array("电脑信息", "[电脑/信息]"),
    array("软件开发", "[语言/工具]"),
    array("操作系统", "[系统/内核]"),
    array("电脑技术", "[专项技术]")
);
?>
