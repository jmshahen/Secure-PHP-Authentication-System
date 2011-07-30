<?php
/**
* The default page to present options for users and login/register information to non-users
*
*
* @author Pongs <pongs1@live.com>
* @tutorial http://www.rohitab.com/discuss/topic/37608-secure-php-authentication-system
* @version 1.0
* @package index
*/

/**
* import the secure_user_auth class
*/
include_once "scripts/secure_user_auth.inc";

/**
* create a new instance of the secure_user_auth class
*/
$sua = new secure_user_auth();
?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
<meta http-equiv="Pragma" content="cache">
<meta http-equiv="Cache-Control" content="no-cache">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<meta http-equiv="Lang" content="en">
<meta name="author" content="pongs">
<meta http-equiv="Reply-to" content="pongs1@live.com">
<meta name="description" content="the index page, see something different when logged on">
<meta name="keywords" content="index,content,blah">
<meta name="creation-date" content="11/11/2008">
<title>The Index Page</title>
</head>
<body>
	<?php
	if($sua.isUser(true)):
	?>
	<h1>Welcome <?php echo $sua.get($sua.getUSERNAME_item); ?></h1>
	<?php
	else:
	?>

	<?php
	endif;
	?>
</body>
</html>