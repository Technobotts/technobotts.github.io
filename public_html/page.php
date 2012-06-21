<?php
require_once '/home/a9745601/libs/pagefuncs.php';
require_once '/home/a9745601/libs/lessc.inc.php';

try {
    lessc::ccompile('style.less', 'style.css');
} catch (exception $ex) {
    exit($ex->getMessage());
}

$pages['home'] = page('Home');
$pages['team'] = page('Team');
$pages['soccer'] = page('RCJ Soccer');
$pages['soccer-2011'] = page('RCJ Soccer 2011');
$pages['fll'] = page('FLL');
$pages['sponsors'] = page('Sponsors');
$pages['error'] = page('Error',false);
$pages['fll-2008-old'] = page('Old Designs', false);


$pageTitle = 'Technobotts';

$pageId = getPageId();
$pageInfo = @$pages[$pageId];
if($pageInfo)
{
	if($pageInfo['title'])
	{
		$pageTitle .= ' | ' . ucwords($pageInfo['title']);
		if($pageId == 'error')
		{
			$pageTitle .= ' '.@$_GET['code'];
		}
	}
}
else
{
	header('HTTP/1.0 404 Not Found');
	$_GET['name'] = 'error';
	$_GET['code'] = 404;
	include('page.php');
	exit();
}
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
	<head>
		<meta http-equiv="Content-Type" content="text/html;charset=utf-8" />
		<meta name="keywords" content="Technobotts, robotics, team, Technobotts robotics team, lego, robocup, FIRST Lego League" />
		
		<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.6.4/jquery.min.js"></script>
		<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.8.16/jquery-ui.min.js"></script>
		<script type="text/javascript" src="http://jquery.thewikies.com/swfobject/jquery.swfobject.1-1-1.min.js"></script>
		<script type="text/javascript" src="/script.js"></script>
		
		<title><?php echo($pageTitle) ?></title>
		<link rel="stylesheet" type="text/css" href="/style.css"/>
		<link rel="stylesheet" type="text/css" href="http://fonts.googleapis.com/css?family=Orbitron:500" />
		<!--[if lt IE 8]>
			<link rel="stylesheet" href="/styleie7.css" type="text/css" />
		<![endif]-->
		
		<link rel="shortcut icon" href="/favicon.ico" type="image/vnd.microsoft.icon" />
		<script type="text/javascript">
		var _gaq = _gaq || [];
		_gaq.push(['_setAccount', 'UA-16943136-1']);
		_gaq.push(['_trackPageview']);
		
		(function() {
			var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
			ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
			var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
		})();
		</script>
	</head>
	<body>
		<div id="main">
			<div id="header">
				<h1 id="logo">Technobotts</h1>
				<ul id="navbar"><!--<?php
					foreach($pages as $url=>$page)
					{
						if($page['is-tab'])
						{
							echo '
					',
								'--><li'.($url == $pageId ? ' class="current"' : '').'>',
										'<a'.($url == $pageId ? '' : ' href="/'.$url.'"').'>'.$page['title'].'</a>',
									'</li><!--';
						}
					}
				?>
				
				--><li><a href="/blog/">Blog</a></li></ul>
			</div>
			<div id="content">
<?php includePage($pageId)?>
				<br style="clear:both; height: 0" />
			</div>
		</div>
		<div id="footer">
			<div id="footer-main">
				<span id="footer-toggle" title="expand footer">&#9650;</span>
				&copy; TechnoBotts 2010
			</div>
			<div id="footer-extra">
				<div style="float: left">Need to contact us? Shoot us an email at
					<a href="mailto:team@technobotts.info">team@technobotts.info</a>
				</div>
			</div>
		</div>
	</body>
</html>
