<?php
/**
* The login script to allow users to login and register
*
*
* @author Pongs <pongs1@live.com>
* @tutorial http://www.rohitab.com/discuss/topic/37608-secure-php-authentication-system
* @version 1.0
* @package login
*/

include_once "scripts/secure_user_auth.inc"

$sua = new secure_user_auth();

$trying_to_login = $sua->trying_to_login();

if($trying_to_login === 1)
{
	
	//check the user's credentials
	if($sua->security_test_credentials() === 1)
	{
		//redirect the user to the default page or to a redirect page if provided
		
	}
	else
	{
		//display invalid login (indescriptive)
	}
}
else if($trying_to_login === -1)
{
	//display message for blocked IP addresses
	$sua->login_blocked_ip_msg();
}
else if($trying_to_login === 0)
{
	//display login script
	$sua->display_login_script();
}
else
{
	//Should never run this else statement, but needed for programmer's mistakes
	print "Whoops, this shouldn't be appearing.<br/>".
	"Error Code: <b>$trying_to_login</b>";
	
	exit(0);
}
?>
