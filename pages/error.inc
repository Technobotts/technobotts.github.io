<?php
$code = isset($_GET['code']) ? $_GET['code'] : '';
if($code == 403) {
?>
	<h2>Cool story, bro.</h2>
	<p>You don't have permission to view this page.</p>
<?php 
} else if($code == 404) {
?>
	<h2>Oh dear.</h2>
	<p>The page you requested cannot be found.</p>
<?php 
} else if($code == 500) {
?>
	<h2>Internal Server Error 500</h2>
	<p>We've screwed up bigtime</p>
<?php 
} else {
?>
	<h2>Dude. Duuuuuude.</h2>
	<p>I mean, seriously, why would you actually type 'error' at the end of the url?</p>
<?php 
}
?>