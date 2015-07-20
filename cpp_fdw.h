/*-------------------------------------------------------------------------
 *
 * cpp_fdw.h
 *
 * Type and function declarations for CPP foreign data wrapper.
 *
 * Copyright (c) 2013, Citus Data, Inc.
 *
 * $Id$
 *
 *-------------------------------------------------------------------------
 */

#ifndef CPP_FDW_H
#define CPP_FDW_H

#include "fmgr.h"
#include "catalog/pg_foreign_server.h"
#include "catalog/pg_foreign_table.h"
#include "utils/hsearch.h"
#include "nodes/pg_list.h"
#include "nodes/relation.h"


/* Defines for valid option names and default values */
#define OPTION_NAME_FILENAME "filename"
#define OPTION_NAME_MAX_ERROR_COUNT "max_error_count"
#define OPTION_NAME_HDFS_DIRECTORY_PATH "hdfs_directory_path"
#define DEFAULT_MAX_ERROR_COUNT 0

#define CPP_TUPLE_COST_MULTIPLIER 10
#define ERROR_BUFFER_SIZE 1024
#define READ_BUFFER_SIZE 4096
#define GZIP_FILE_EXTENSION ".gz"
#define HDFS_BLOCK_PREFIX "blk_"
#define HDFS_BLOCK_PREFIX_LENGTH 4


/*
 * CppValidOption keeps an option name and a context. When an option is passed
 * into cpp_fdw objects (server and foreign table), we compare this option's
 * name and context against those of valid options.
 */
typedef struct CppValidOption
{
	const char *optionName;
	Oid optionContextId;

} CppValidOption;


/* Array of options that are valid for cpp_fdw */
static const uint32 ValidOptionCount = 3;
static const CppValidOption ValidOptionArray[] =
{
	/* foreign table options */
	{ OPTION_NAME_FILENAME, ForeignTableRelationId },
	{ OPTION_NAME_MAX_ERROR_COUNT, ForeignTableRelationId },
	{ OPTION_NAME_HDFS_DIRECTORY_PATH, ForeignTableRelationId }
};


/*
 * CppFdwOptions holds the option values to be used when reading and parsing
 * the cpp file. To resolve these values, we first check foreign table's 
 * options, and if not present, we then fall back to the default values 
 * specified above.
 */
typedef struct CppFdwOptions
{
	char *filename;
	int32 maxErrorCount;

} CppFdwOptions;


/*
 * CppFdwExecState keeps foreign data wrapper specific execution state that we
 * create and hold onto when executing the query.
 */
typedef struct CppFdwExecState
{
	char *filename;
	FILE *filePointer;
	void *gzFilePointer;
	uint32 maxErrorCount;
	uint32 errorCount;
	uint32 currentLineNumber;
	HTAB *columnMappingHash;

} CppFdwExecState;


/*
 * ColumnMapping reprents a hash table entry that maps a column name to column
 * related information. We construct these hash table entries to speed up the
 * conversion from CPP documents to PostgreSQL tuples; and each hash entry maps
 * the column name to the column's tuple index and its type-related information.
 */
typedef struct ColumnMapping
{
	char columnName[NAMEDATALEN];
	uint32 columnIndex;
	Oid columnTypeId;
	int32 columnTypeMod;
	Oid columnArrayTypeId;

} ColumnMapping;


/* Function declarations for foreign data wrapper */
extern Datum cpp_fdw_handler(PG_FUNCTION_ARGS);
extern Datum cpp_fdw_validator(PG_FUNCTION_ARGS);


#endif   /* CPP_FDW_H */
