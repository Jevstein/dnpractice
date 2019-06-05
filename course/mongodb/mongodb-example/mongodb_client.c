


//Redis
//mongodb
//MySQL

#include <mongoc.h>


int main() {

	const char *uri_string = "mongodb://192.168.189.142:27017";
	bson_error_t error;

	mongoc_init();

	mongoc_uri_t *uri = mongoc_uri_new_with_error(uri_string, &error);
	if (!uri) {
		fprintf(stderr, "failed to parse URI: %s\n"
			"error message: %s\n",
			uri_string, error.message);
		return 0;
	}

	mongoc_client_t *client = mongoc_client_new_from_uri(uri);
	if (!client) {
		return EXIT_FAILURE;
	}

	mongoc_client_set_appname(client, "connect-example");
	mongoc_database_t *database = mongoc_client_get_database(client, "db_name");
	mongoc_collection_t *collection = mongoc_client_get_collection(client, "db_name", "col1_name");

	bson_t *command = BCON_NEW("ping", BCON_INT32(1));
	bson_t reply;

	bool retval = mongoc_client_command_simple(client, "admin", command, NULL, &reply, &error);
	if (!retval) {
		fprintf(stderr, "%s\n", error.message);
		return EXIT_FAILURE;
	}
	char *str = bson_as_json(&reply, NULL);
	printf("%s\n", str);

	bson_t *insert = BCON_NEW("hello", BCON_UTF8("world"));

	if (!mongoc_collection_insert_one(collection, insert, NULL, NULL, &error)) {
		fprintf(stderr, "%s\n", error.message);
	}

	bson_destroy(insert);
	bson_destroy(&reply);
	bson_destroy(command);
	bson_free(str);

	mongoc_collection_destroy(collection);
	mongoc_database_destroy(database);
	mongoc_uri_destroy(uri);

	mongoc_client_destroy(client);
	mongoc_cleanup();

	return EXIT_SUCCESS;

}





