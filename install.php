<?php
/**
* The install script that sets up the mysql database
*
*
* @author Pongs <pongs1@live.com>
* @tutorial http://www.rohitab.com/discuss/topic/37608-secure-php-authentication-system
* @version 1.0
* @package install
*/

/**
* returns an html formatted error page, displaying both $error_msg and $error_num
* @param string $error_msg The specifc error message that will be displayed (WARNING: not filtered; security risk[XSS])
* @param string $error_num A reference number the user can use to search up more information (WARNING: not filtered; security risk[XSS])
* @param int $tabs tabs the block to fit into the style of the source code
* @param bool $tab_first_line tabs the first line, all non-bool is considered true
* @return string
*/
function error_page($error_msg="Unknown Error", $error_num="Unknown Error Number", $tabs=0, $tab_first_line=false)
{
	//fills $tabs with the number of tabs that is needed
	$tabs = is_int($tabs)? ($tabs >= 0)?str_repeat("\t", $tabs) : "" : "";
	//anything non-boolean is considered true and will do full tabs
	$first_line_tabs = is_bool($tab_first_line)? ($tab_first_line? $tabs : "") : $tabs;

	$str = <<<EOS
{$first_line_tabs}<h1>Error Occured</h1>
{$tabs}Please note that an error has occured which is preventing the current page from loading properly.<br/>
{$tabs}<br/>
{$tabs}<div style="color: red;">
{$tabs}	<b>Specific Error ({$error_num}):</b><br/>
{$tabs}	&nbsp;&nbsp;&quot;{$error_msg}&quot;
{$tabs}</div>
EOS;
	return $str;
}

function display_error_page($error_msg="Unknown Error", $error_num="Unknown Error Number")
{
	$error = error_page($error_msg, $error_num, 1);

	$html = <<<EOS
<html>
	<head>
		<title>Error Occured</title>
	</head>
	<body>
		{$error}
	</body>
</html>
EOS;
	die($html);
}

//perform the action that is needed
if(isset($_POST["action"]))
{
	//doesn't allow anything but strings (excluds arrays)
	if(!is_int($_POST["action"]))
	{
		display_error_page("Action must be a int", 1);
	}

	switch($_POST["action"])
	{
		//sets up the "./scripts/mysql.inc" script, creates the users/ip table, sets up the administrator account
		case 1:
		{

			break;
		}
		//deletes this script for security reasons
		case 2:
		{
			unlink(__FILE__);
			
			$html = <<<EOS
<html>
	<head>
		<title>Installation Done</title>
	</head>
	<body>
		<h1>Congradulations</h1>
		<p>You have completely installed the Secure PHP Authentication System!</p>
		<p>Please Note: The install script has just been deleted and configuration 
		file (randomly named) has been created in the "scripts" folder. This file
		stores the mysql username and password and the other configuration data,
		please do all you can to not let people access this file. A .htaccess file
		in located within the folder to protect all those files, but you should 
		make sure to limit the people who can access this folder.</p>
	</body>
</html>
EOS;
			die($html);
			break; //habbit (don't need it since the script will 'die' before reaching this command)
		}
		default:
		{
			display_error_page("Unknown Action", 2);
		}
	}
}
//display the starting page
?>
<html>
	<head>
		<title>Install Secure PHP Authentication System</title>
		<script>
		function strip(html)
		{
		   var tmp = document.createElement("DIV");
		   tmp.innerHTML = html;
		   return tmp.textContent||tmp.innerText;
		}
		function show_user_mysql()
		{
			var user = 	strip(document.getElementById("username").value);
			var pass = 	strip(document.getElementById("password").value);
			var data = 	strip(document.getElementById("database").value);
			var table_user = 	strip(document.getElementById("user_table").value);
			var table_ip = 		strip(document.getElementById("ip_table").value);
			var result = document.getElementById("show_user_mysql_result");

			result.innerHTML = "CREATE USER '"+user+"'@'localhost' \
				IDENTIFIED BY '"+pass+"';<br/> \
				GRANT ALL ON "+data+"."+table_user+" TO '"+user+"'@'localhost'; \
				/*Only run this line once the table has been generated for you by me!*/<br/>\
				GRANT ALL ON "+data+"."+table_ip+" TO '"+user+"'@'localhost'; \
				/*Only run this line once the table has been generated for you by me!*/";
		}
		</script>
	</head>
	<body>
		<h1>Welcome to PHP Secure Auth. System</h1>
		<p>Author: Pongs &lt;pongs1@live.com&gt;</p>
		<?php
		if($_SERVER["SERVER_ADDR"] != "127.0.0.1"):
		?>
		<p style="color: red;">Security Alert:<br/>
			It is advised that complete this section under localhost (install not over the internet)
		</p>
		<?php 
		endif;
		
		if(isset($error))
		{ print $error; }
		?>

		<form method="post" action="">
			<h2>User Credentials</h2>
			<p>
				<i>NOTE: Please create an account within your MySQl database with only access to the table
				you are about to create. Enter this code into the mysql terminal or using a gui equivalent:<br/>
				<code>
				CREATE USER '<u>username_here</u>'@'localhost' IDENTIFIED BY '<u>password_here</u>';<br/>
				GRANT ALL ON <u>database_here</u>.<u>table_name_here</u> TO '<u>username_here</u>'@'localhost';
				</code></i>
			</p>
			<p>
				<table>
					<tr>
						<td>
							Username:
						</td>
						<td>
							<input type="text" id="username" name="username" />
						</td>
					</tr>
					<tr>
						<td>
							Password:
						</td>
						<td>
							<input type="password" id="password" name="password" />
						</td>
					</tr>
				</table>
			</p>

			<h2>MySQL Information</h2>
			<p style="color: purple;">
				<b>NOTE: The datbase MUST be created before hand, but the table MUST NOT created
				(it will be created) by this script.</b>
			</p>
			<p>
				<table>
					<tr>
						<td>
							Database Server: (e.g. localhost)
						</td>
						<td>
							<input type="text" name="server" />
						</td>
					</tr>
					<tr>
						<td>
							Database Name:
						</td>
						<td>
							<input type="text" name="database" />
						</td>
					</tr>
					<tr>
						<td>
							User Table Name:
						</td>
						<td>
							<input type="text" name="user_table" />
						</td>
					</tr>
					<tr>
						<td>
							IP Blacklist Table Name:
						</td>
						<td>
							<input type="text" name="ip_table" />
						</td>
					</tr>
				</table>
				<button onclick="show_user_mysql()">Show MySQL to Create User</button>
				<div id="show_user_mysql_result" style="font-style:italic;"></div>
			</p>
		</form>
	</body>
</html>
