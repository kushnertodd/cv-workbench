/**
 Example showing usage of sqlite3 API to insert blobs by inserting a
    placeholder then writing to the blob handle

  Note that you could also read the whole thing into memory and do the insert with a bind.
  Doing it by opening the blob handle allows you to do blockwise reading/insertion,
    thereby inserting huge files without much memory consumption
 
 Gary "ChunkyKs" Briggs <chunky@icculus.org>

 gcc -o sqlite3_example_blob sqlite3_example_blob.c -lsqlite3 
 ./sqlite3_example_blob ./test.db ./sqlite3_example_blob

*/
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

int main(int argc, char **argv) {
	if(argc < 2) {
		fprintf(stderr, "Usage: %s <dbname> <filename>\n", argv[0]);
		exit(1);
	}

	// file to insert
	FILE *f = fopen(argv[2], "rb");
	if(NULL == f) {
		fprintf(stderr, "Couldn't open file %s\n", argv[2]);
		exit(1);
	}
	// Calculate size of file
	fseek(f, 0, SEEK_END);
	long filesize = ftell(f);
	fseek(f, 0, SEEK_SET);

	// Table name we're going to use
	char tablename[] = "testblob";
	char columnname[] = "blobby";

	// Actual database handle
	sqlite3 *db = NULL;

	// Database commands
	char create_sql[1024];
	snprintf(create_sql, sizeof(create_sql), "CREATE TABLE IF NOT EXISTS %s ("
			"id INTEGER PRIMARY KEY, %s BLOB)", tablename, columnname);

	// Going to insert a zeroblob of the size of the file
	char insert_sql[1024];
	snprintf(insert_sql, sizeof(insert_sql), "INSERT INTO %s (%s) VALUES (?)", tablename, columnname);

	// SQLite return value
	int rc;

	// Open the database
	rc = sqlite3_open(argv[1], &db);
	if(SQLITE_OK != rc) {
		fprintf(stderr, "Can't open database %s (%i): %s\n", argv[1], rc, sqlite3_errmsg(db));
		exit(1);
	}

	char *exec_errmsg;
	rc = sqlite3_exec(db, create_sql, NULL, NULL, &exec_errmsg);
	if(SQLITE_OK != rc) {
		fprintf(stderr, "Can't create table (%i): %s\n", rc, sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	sqlite3_stmt *insert_stmt;
	rc = sqlite3_prepare_v2(db, insert_sql, -1, &insert_stmt, NULL);
	if(SQLITE_OK != rc) {
		fprintf(stderr, "Can't prepare insert statment %s (%i): %s\n", insert_sql, rc, sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	// Bind a block of zeros the size of the file we're going to insert later
	sqlite3_bind_zeroblob(insert_stmt, 1, filesize);
	if(SQLITE_DONE != (rc = sqlite3_step(insert_stmt))) {
		fprintf(stderr, "Insert statement didn't work (%i): %s\n", rc, sqlite3_errmsg(db));
		exit(1);
	}

	sqlite3_int64 rowid = sqlite3_last_insert_rowid(db);
	printf("Created a row, id %i, with a blank blob size %i\n", (int)rowid, (int)filesize);

	// Getting here means we have a valid file handle, f, and a valid db handle, db
	//   Also, a blank row has been inserted with key rowid
	sqlite3_blob *blob;
	rc = sqlite3_blob_open(db, "main", tablename, columnname, rowid, 1, &blob);
	if(SQLITE_OK != rc) {
		fprintf(stderr, "Couldn't get blob handle (%i): %s\n", rc, sqlite3_errmsg(db));
		exit(1);
	}

	const int BLOCKSIZE = 1024;
	int len;
	void *block = malloc(BLOCKSIZE);
	
	int offset = 0;
	while(0 < (len = fread(block, 1, BLOCKSIZE, f))) {
		if(SQLITE_OK != (rc = sqlite3_blob_write(blob, block, len, offset))) {
			fprintf(stderr, "Error writing to blob handle. Offset %i, len %i\n", offset, len);
			exit(1);
		}
		offset+=len;
	}

	sqlite3_blob_close(blob);

	printf("Successfully wrote to blob\n");

	free(block);

	fclose(f);
	sqlite3_finalize(insert_stmt);
	sqlite3_close(db);
	return 0;
}

