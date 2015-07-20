/* contrib/cpp_fdw/cpp_fdw--1.0.sql */

-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION cpp_fdw" to load this file. \quit

CREATE FUNCTION cpp_fdw_handler()
RETURNS fdw_handler
AS 'MODULE_PATHNAME'
LANGUAGE C STRICT;

CREATE FUNCTION cpp_fdw_validator(text[], oid)
RETURNS void
AS 'MODULE_PATHNAME'
LANGUAGE C STRICT;

CREATE FOREIGN DATA WRAPPER cpp_fdw
  HANDLER cpp_fdw_handler
  VALIDATOR cpp_fdw_validator;
