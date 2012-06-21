<?php
function sanitizeClassPath($classPath)
{
	$matches = explode ('.',$classPath);
	foreach($matches as &$match)
	{
		$match = preg_replace('/[^a-zA-Z0-9_]/','',$match);
	}
	return implode($matches,'/').'.java';
}
$svn_root = 'http://technobotts.svn.beanstalkapp.com/all/Robocup/';
$urls = array(
	'robot' => 'Soccer/trunk/New%20Robot/src/',
	'sensors' => 'Utils/trunk/Sensors/src/',
	'omni pilots' => 'Utils/trunk/OmniPilots/',
	'data manipulation' => 'Utils/trunk/Data%20Manipulation/'
);

$project = isset($_GET['project']) ? $_GET['project'] : 'robot';
$classPath = isset($_GET['class']) ? $_GET['class'] : false;
$format = isset($_GET['pretty']) ? $_GET['pretty'] : false;
?><?php
if(isset($urls[$project]) && $classPath)
{
	$url = $svn_root.$urls[$project];
	$classPath = sanitizeClassPath($classPath);
	$code = @file_get_contents($url.$classPath);
	if($code)
	{
		if($format)
		{
			require('../geshi.php');
			$geshi = new GeSHi($code, 'java');
			$geshi->enable_classes();
			$geshi->set_header_type(GESHI_HEADER_DIV);
			$geshi->enable_line_numbers(GESHI_FANCY_LINE_NUMBERS);
			?>
		
<html>
	<head>
		<title><?php echo $classPath ?></title>
		<link rel="stylesheet" type="text/css" href="/geshi/java.css" />
	</head>
	<body>
			<?php
			echo $geshi->parse_code();
			?>
	</body>
</html>
			<?php
		}
		else
		{
			header('content-type: text/plain');
			echo $code;
		}
	}
	else
	{
		header('content-type: text/plain');
		echo "File Not Found";
	}
}
else
{
	echo "Not valid arguments";
}
?>