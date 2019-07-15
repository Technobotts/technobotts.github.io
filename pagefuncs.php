<?php
global $pages;
$pages = array();

function page($title = '', $isTab = true)
{
	$ret = array();
	$ret['title'] = $title;
	$ret['is-tab'] = $isTab;
	return $ret;
}

function getPageId()
{
	return isset($_GET['name']) ? $_GET['name'] : 'home';
}

function getPage($pageId)
{
	if(@$pages[$pageId])
	{
		return $pages[$pageId];
	}
	else
	{
		return false;
	}
}

function indenter($buffer)
{
	return str_replace("\n", "\n\t\t\t", $buffer);
}


function includePage($pageId)
{
	ob_start("indenter");
	include("pages/$pageId.inc");
	ob_end_flush();
}
?>