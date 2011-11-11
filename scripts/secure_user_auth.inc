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

	function __construct($fetch = array())
	{
		$this->gSESSION = array(
			$this->gACTIVE,
			$this->gADMIN,
			$this->gUSERNAME
		);
		$this->config = $this->loadConfig();

		//tries to login the user by a "remember me" cookie
		$this->login_cookie();

		if(is_array($fetch))
		{
			$this->fetch($fetch);
		}
	}

	/**
	* 
	* 
	*/
	static function display_login_script()
	{
		
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

	/**
	* If a "Remember Me" cookie is found, try to log in the user
	*/
	function login_cookie()
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