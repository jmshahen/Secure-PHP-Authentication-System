<?php
/**
* The global authentication class and module for getting user information.
*
*
* @author Pongs <pongs1@live.com>
* @tutorial http://www.rohitab.com/discuss/topic/37608-secure-php-authentication-system
* @version 1.0
* @package auth
*/
session_start();

class secure_user_auth {
	/**
	* Constants used in __construct(), fetch(), get()
	*/
	const USERNAME = "username";
	const PASSWORD = "password";
	const USER_SALT = "user_salt";
	const ALL_SESSION = "all_session";


	public $data = array();
	private $table_names = array(
		"ip"=>"",
		"user"=>""
	);

	function __construct($fetch = array())
	{
		$this->session_security();

		if(is_array($fetch))
		{
			$this->fetch($fetch);
		}
	}

	/**
	* checks if the ip address is on the blacklist
	*
	* @param string $ip must be in the format for {@link http://ca3.php.net/manual/en/function.ip2long.php ip2long()} (e.g. "127.0.0.1")
	*/
	function blacklist($ip)
	{
		$ip = ip2long($ip);

		if($ip !== FALSE)
		{
			return $this->query("SELECT `uid` FROM ".$this->table_names["ip"]." WHERE `ip`='$ip'");
		}

		return false;
	}

	function fetch($fetch)
	{
		$select = array();
		$where = array();

		if(is_array($fetch))
		{
			//
			if(isset($fetch["USERNAME"]))
			{
				$select[] = USERNAME;
				if(!empty($fetch["USERNAME"]))
				{ $where[] = $fetch["USERNAME"]; }
			}

			$select = array_unique($select);
			$where = array_unique($where);
		}
	}

	/**
	* checks if the current user is logged in
	*
	* @param mixed $active an extra check to make sure that the user is active
	*/
	function isUSer($active=true)
	{
		if(isset($_SESSION["user"]))
		{
			return ($active)? $_SESSION["active"] : true;
		}
		return false;
	}


	function session_security()
	{
		if(isset($_SESSION["IP_ADDR"]))
		{
			//someone stole the session (bad person)
			//TODO: record ip address and block that person
			if($_SESSION["IP_ADDR"] != $_SERVER{"REMOTE_ADDR"})
			{
				session_unset();
				die("DON'T STEAL SESSIONS");
			}
		}

		if(isset($_SESSION["EXPIRES"]))
		{
			//their session has expired
			if($_SESSION["EXPIRES"] <= time())
			{
				session_unset();
			}
		}

		if(isset($_SESSION["UPDATE"]))
		{
			//their session has expired
			if($_SESSION["UPDATE"] <= time())
			{
				$this->
			}
		}
	}

	/**
	* executes a query and returns the reults in array form
	*
	* @param mixed $query
	*/
	function query($query)
	{
		$results = array();

		return $results;
	}
}
?>