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
		if(isset($SESSION["REDIRECT"]))
		{
			$sua->redirect($SESSION["REDIRECT"]);
		}
		else
		{
			$sua->redirect(); //redirect to the default page (home page)
		}
	}
	else
	{
		//display invalid login (indescriptive)
		print "<div style='color:red'>ERROR: Invalid login, username and password do not match</div>";
		$sua->display_login_script();
	}
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
