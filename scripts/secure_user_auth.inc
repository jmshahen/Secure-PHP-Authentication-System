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
	private $tableUSERS = "users";
	private $tableIP = "ip";
	public $gACTIVE = array("table"=>tableUSERS, "column"=>"active");
	public $gADMIN = array("table"=>tableUSERS, "column"=>"admin");
	public $gPASS = array("table"=>tableUSERS, "column"=>"password"); //used to validate login
	public $gSALT = array("table"=>tableUSERS, "column"=>"user_salt"); //used to validate login
	public $gUSERNAME = array("table"=>tableUSERS, "column"=>"username");
	//retrieves variables needed to fill the session varaible
	public $gSESSION;

	/**
	* put your comment there...
	*
	* @var array
	*/
	public $data = array();
	private $config;

	function __construct($fetch=array())
	{
		$this->gSESSION = array(
			$this->gACTIVE,
			$this->gADMIN,
			$this->gUSERNAME
		);
		
		$this->config = $this->loadConfig();

		$this->security_session();
		$this->security_blocked_ip();

		if(is_array($fetch) && !empty($fetch))
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

	/**
	* 
	* 
	*/
	static function display_login_script()
	{
		
	}

	/**
	* Pre-Fetches all the information the site will need
	*
	* If you supply as much information as you know you will need, this method will fetch
	* all of it in as little queries as possible. This method should be altered to include
	* other tables and data that you might want to pre-fetch to reduce stress on the SQL server
	* @param array $fetch
	* @return array
	* @throws Requires $config["tables"]
	* @throws Requires {@link $fetch} to be an array
	* @todo figure out how to effectively use $where
	*/
	function fetch($fetch)
	{
		$select = array();
		//$where = array();
		$results = array();

		if(is_array($fetch))
		{
			foreach($fetch as $item)
			{
				//checks for valid item
				if(is_array($item) && isset($item["table"]) && isset($item["column"]))
				{
					if(!isset($select[$item["table"]]))
					{
						$select[$item["table"]] = array();
					}
					//appends the column to select->table_name
					$select[$item["table"]][] = $item["column"];
				}
			}

			//removes all duplicate columns within the tables
			foreach($select as $table)
			{
				$select[$table] = array_unique($select[$table]);
				//$where[$table] = array_unique($where[$table]);

				if(count($select[$table]) > 0)
				{
					$results[$table] = $this->query("SELECT `".implode($select[$table], "`, `")."` FROM `".$table."`");
				}
			}

			return $results;
		}
		else
		{
			throw new Exception('$fetch must be an array.');
		}
	}

	/**
	* checks if the data is already fetched and stored in the $this->data array
	* it will also check the $_SESSION variable for the information
	* If it cannot find the data it will fetch for it
	*
	* @param array $data
	* @param boolean $forceFetch
	*/
	function get($data, $forceFetch=false)
	{
		if(is_array($data))
		{
			if(!isset($data["table"]) || !isset($data["column"]))
			{
				throw new Exception('$data is an invalid array.');
			}

			if($forceFetch)
			{
				return $this->fetch($data);
			}

			
		}
		else
		{
			throw new Exception('$data must be an array.');
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

	function loadConfig()
	{
		$this->config["script"] = array(
			"ip_blocked_login" => "/scripts/blocked_ip.php"
		);
	}
	
	/**
	* outputs a message to the user describing that their IP address is blocked
	* 	Provides them with an alternative means of logging in
	* 	A one time token link to be sent to the email assigned to the account
	*
	*/
	static function login_blocked_ip_msg()
	{
		//TODO: Style this message
		$str = <<<STR
It has come to our attention that your IP Address ({$_SEERVER["REMOTE_ADDR"]}) has been associated or been involved in harmful
activities towards this website. In order to prevent harm from coming to this website, we have 
blocked access to this website from your IP Address ({$_SEERVER["REMOTE_ADDR"]}).
<br/>
<br/>
If you are a valid user and need to access our website through the IP Address {$SERVER["REMOTE_ADDR"]}, 
please enter your account name below and follow the instruction that are sent to your email.<br/>
<form action="{$this->config["scripts"]["ip_blocked_login"]}">
	Username: <input name="user" /><br/>
	<input type="submit" value="Send Email" />
</form>
<div style="color: red;">
* There is a 10 minute delay between emails will be sent and each email 
token has a limited time length (as described in the email)<br/>
** It is suggested that you do not use this IP Address to access the website as it has been known
to be harmful to our systems and might be listening to your communications to y\our website.
</div>
STR;
		return str;
	}
	
	/**
	* 
	* 
	*/
	static function security_blocked_ip()
	{
		
	}
	
	/**
	* 
	* 
	*/
	static function security_test_credentials()
	{
		
	}

	/**
	* Checks the security of the current php session, checks for the valid IP Address,
	*
	*
	*/
	function security_session()
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

				//only used if the developer wishes to display a custom message
				if(!isset($this->data["expired_count"]) && !is_int($this->data["expired_count"]))
					{ $this->data["expired_count"] = 1; }
				else
					{ $this->data["expired_count"]++; }
				$this->data["expired"] = 1;
			}
		}

		if(isset($_SESSION["UPDATE"]))
		{
			//their session has expired
			if($_SESSION["UPDATE"] <= time())
			{
				$data = $this->fetch($this->gSESSION);


			}
		}
	}

	/**
	* checks whether the the user is trying to login and test to see if the IP has over drawn thier account tries
	* 
	* Returns 1 for trying to login, 0 for not trying and -1 for user suspended
	* @return integer
	*/
	static function trying_to_login()
	{
		//check the POST variables to see if they are trying to login
		if(true)
		{
			//check the IP address if it has tried to many times
			if(false)
			{
				return -1
			}
			
			return 1
		}
		
		return 0;
	}
	
	
	/**
	* executes a query and returns the reults in array form
	*
	* @param string $query
	*/
	function query($query)
	{
		$results = array();

		return $results;
	}
}
?>