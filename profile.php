<?php
/**
* A sample profile page. This page validates a users session credentials and if valid shows one page
* and if not valid then redirects to the login page.
*
* This simple profile page will be used to provide a template for use on all other webpages
* This page also gives examples of where an XSS attack can take place
* (kinda, seeing as this site is secure nothing will be able to make it an XSS)
* The page also provides access to scripts to change the user password and name
* @author Pongs <pongs1@live.com>
* @tutorial http://www.rohitab.com/discuss/topic/37608-secure-php-authentication-system
* @version 1.0
* @package profile
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

<?php
//checks if the user is logged in and active
if($sua.isUser(true)):
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
	<head>
		<title>Your Profile Page</title>
	</head>
	<body>
		<h1>Welcome <?php echo $sua.get($sua.USERNAME); ?></h1>
	</body>
</html>
<?php
else:
	$sua.redirectToLoginPage($_SERVER["REQUEST_URI"]);
endif;
?>
