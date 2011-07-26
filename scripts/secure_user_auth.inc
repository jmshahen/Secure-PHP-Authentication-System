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
	const tableUSERS = "users";
	const tableIP = "ip";
	const getACTIVE_item = array("table"=>tableUSERS, "column"=>"active");
	const getADMIN_item = array("table"=>tableUSERS, "column"=>"admin");
	const getPASS_item = array("table"=>tableUSERS, "column"=>"password"); //used to validate login
	const getSALT_item = array("table"=>tableUSERS, "column"=>"user_salt"); //used to validate login
	const getUSER_item = array("table"=>tableUSERS, "column"=>"username");
	//retrieves variables needed to fill the session varaible
	const getSESSION_item_array = array(
		getACTIVE,
		getADMIN,
		getUSER
	);


	public $data = array();
	private $config;

	function __construct($fetch = array())
	{
		$this->config = $this->loadConfig();

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
	* @param string $query
	*/
	function query($query)
	{
		$results = array();

		return $results;
	}
}
?>