DROP DATABASE IF EXISTS celcon_db;

CREATE DATABASE IF NOT EXISTS celcon_db;

USE celcon_db;

DROP SCHEMA IF EXISTS celcon;

CREATE SCHEMA IF NOT EXISTS celcon;

CREATE TABLE IF NOT EXISTS celcon.posts (
	post_id INTEGER PRIMARY KEY,
	post_name VARCHAR(512)
);

CREATE TABLE IF NOT EXISTS celcon.roles (
	role_id INTEGER PRIMARY KEY,
	role_name VARCHAR(128)
);

CREATE TABLE IF NOT EXISTS celcon.users (
	user_id INTEGER PRIMARY KEY,
	user_login VARCHAR(256),
	role_id INTEGER,
	name VARCHAR(128),
	surname VARCHAR(128),
	patronymic VARCHAR(128),
	post_id INTEGER,
	FOREIGN KEY (role_id) REFERENCES celcon.roles (role_id),
	FOREIGN KEY (post_id) REFERENCES celcon.posts (post_id)
);

CREATE TABLE IF NOT EXISTS celcon.hash_algorithms (
	algorithm_id INTEGER PRIMARY KEY,
	algorithm_name VARCHAR(64)
);

CREATE TABLE IF NOT EXISTS celcon.tracking_files (
	file_id INTEGER PRIMARY KEY,
	file_path VARCHAR(512) NOT NULL,
	user_id INTEGER,
	algorithm_id INTEGER,
	hash VARCHAR(512),
	FOREIGN KEY (user_id) REFERENCES celcon.users (user_id),
	FOREIGN KEY (algorithm_id) REFERENCES celcon.hash_algorithms (algorithm_id)
);

CREATE TABLE IF NOT EXISTS celcon.changes_history (
	change_id INTEGER PRIMARY KEY,
	file_id INTEGER,
	new_hash VARCHAR(512),
	time TIMESTAMP,
	FOREIGN KEY (file_id) REFERENCES celcon.tracking_files (file_id)
);

CREATE TABLE IF NOT EXISTS celcon.login_history (
	login_id INTEGER PRIMARY KEY,
	user_id INTEGER,
	time TIMESTAMP,
	FOREIGN KEY (user_id) REFERENCES celcon.users (user_id)
);

CREATE TABLE IF NOT EXISTS celcon.log_messages (
	log_id INTEGER PRIMARY KEY,
	log_message TEXT,
	time TIMESTAMP
);
