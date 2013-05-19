-- # -*- coding: utf-8 -*-
-- # © 2012, Lara Sorokina, KubSAU
-- __author__ = 'wid0ki <laricasorokina@gmail.com>'

ALTER TABLE IF EXISTS entity2project DROP CONSTRAINT IF EXISTS _e2p_id_project;
ALTER TABLE IF EXISTS usr2grp DROP CONSTRAINT IF EXISTS _u2g_id_person;
ALTER TABLE IF EXISTS usr2grp DROP CONSTRAINT IF EXISTS _u2g_id_group;
ALTER TABLE IF EXISTS suggestion DROP CONSTRAINT IF EXISTS _s_id_creator;
ALTER TABLE IF EXISTS suggestion DROP CONSTRAINT IF EXISTS _s_id_assigned;
ALTER TABLE IF EXISTS suggestion DROP CONSTRAINT IF EXISTS _s_id_group;

DROP TABLE IF EXISTS person;
DROP TABLE IF EXISTS usr;
DROP TABLE IF EXISTS grp;
DROP TABLE IF EXISTS project;
DROP TABLE IF EXISTS usr2grp;
DROP TABLE IF EXISTS entity2project;
DROP TABLE IF EXISTS person2grp;
DROP TABLE IF EXISTS grp2project;
DROP TABLE IF EXISTS archive;
DROP TABLE IF EXISTS suggestion;
DROP TYPE IF EXISTS suggestion_type;
DROP TYPE IF EXISTS suggestion_status;
DROP TYPE IF EXISTS person_role;
DROP TYPE IF EXISTS archive_type;
DROP TYPE IF EXISTS usr_role;
DROP TYPE IF EXISTS entity_type;

CREATE TYPE suggestion_type AS ENUM ('suggestion','issue','bug','response');
CREATE TYPE suggestion_status AS ENUM ('submitted','in process','solved','wait verifying','close');
CREATE TYPE usr_role AS ENUM ('product owner','scrum master', 'teamlead', 'project manager', 'tester', 'programmer');
CREATE TYPE archive_type AS ENUM ('person','group','suggestion','project');
CREATE TYPE entity_type AS ENUM ('user','group','system');

CREATE TABLE usr (
	id SERIAL PRIMARY KEY,
	name VARCHAR (50),
	surname VARCHAR (50),
	birth DATE,
	email VARCHAR (256),
	secret VARCHAR (32)
) WITH (
	oids=false
);

CREATE TABLE grp (
	id SERIAL PRIMARY KEY,
	name VARCHAR (50),
	id_parent SERIAL
) WITH (
	oids=false
);

CREATE TABLE project (
	id SERIAL PRIMARY KEY,
	name VARCHAR (50),
	backlog TEXT,
	id_parent INT
) WITH (
	oids=false
);

CREATE TABLE usr2grp (
	id_person SERIAL,
	id_grp SERIAL,
	role usr_role
) WITH (
	oids=false
);

CREATE TABLE entity2project (
	id_project SERIAL,
	type_e entity_type,
	id_entity SERIAL
) WITH (
	oids=false
);

CREATE TABLE suggestion (
	id SERIAL PRIMARY KEY,
	id_creator SERIAL,
	type_s suggestion_type,
	title VARCHAR (300),
	content TEXT,
	rating INT,
	status suggestion_status,
	id_parent SERIAL,
	id_assigned SERIAL,
	id_group SERIAL
) WITH (
	oids=false
);

CREATE TABLE archive (
	id SERIAL PRIMARY KEY,
	type_a archive_type,
	info JSON,
	time_archived TIMESTAMPTZ
) WITH (
	oids=false
);

ALTER TABLE entity2project ADD CONSTRAINT _e2p_id_project FOREIGN KEY (id_project) REFERENCES project(id) MATCH FULL;
ALTER TABLE usr2grp ADD CONSTRAINT _u2g_id_person FOREIGN KEY (id_person) REFERENCES usr(id) MATCH FULL;
ALTER TABLE usr2grp ADD CONSTRAINT _u2g_id_group FOREIGN KEY (id_grp) REFERENCES grp(id) MATCH FULL;
ALTER TABLE suggestion ADD CONSTRAINT _s_id_creator FOREIGN KEY (id_creator) REFERENCES usr(id) MATCH FULL;
ALTER TABLE suggestion ADD CONSTRAINT _s_id_assigned FOREIGN KEY (id_assigned) REFERENCES usr(id) MATCH FULL;
ALTER TABLE suggestion ADD CONSTRAINT _s_id_group FOREIGN KEY (id_group) REFERENCES grp(id) MATCH FULL;