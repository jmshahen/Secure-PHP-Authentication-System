--Replace `DATABASE` and `TABLENAME`
CREATE TABLE `DATABASE`.`TABLENAME` (
	`uid` INT NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT 'The User ID, primary index, auto_increment',
	`active` BOOLEAN NOT NULL COMMENT 'Whether the user can or cannot use their account',
	`admin` INT NOT NULL COMMENT '0 for non-admins and can set different levels of admin after that',
	`username` VARCHAR(22) NOT NULL COMMENT 'Stores the username',
	`password` VARCHAR(64) NOT NULL COMMENT 'Stores the password hash',
	`date_created` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'Holds when the account was created, gets updated when they activate the email account (used to remove inactivated accounts)',
	`email` VARCHAR(256) NOT NULL COMMENT 'Holds the last valid email the user has stored',
	`email_confirmation` VARCHAR(64) NOT NULL COMMENT 'Holds the confirmation code that is sent the the persons email account',
	`salt` VARCHAR(20) NOT NULL COMMENT 'Stores a unique salt string that is used to verify the users password',
	`data` TEXT NOT NULL COMMENT 'Can hold what ever other information that isn''t needed to be well searchable'
) ENGINE = MyISAM;