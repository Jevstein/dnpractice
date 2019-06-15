
#include <stdio.h>
#include <string.h>

#include <mysql.h>


#define KING_MYSQL_SERVER 		"192.168.189.134"
#define KING_MYSQL_USERNAME		"replication"
#define KING_MYSQL_PASSWORD		"123456"
#define KING_MYSQL_DBNAME		"vip_order"

#define KING_BINARY_LENGTH		256*1024

#define KING_MYSQL_SELECT_TBL_USER	"SELECT U_IMG FROM TBL_USER"
#define KING_MYSQL_INSERT_TBL_USER	"INSERT TBL_USER(U_NAME, U_GENDER, U_IMG) VALUES('BoJing', 'man', ?)"

int read_binary(char *filename, char *buffer) {

	FILE *fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("fopen failed\n");
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	int length = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	int size = fread(buffer, 1, length, fp);
	if (size != length) {
		printf("fread faile\n");
		return size;
	}

	fclose(fp);

	return size;
}

int write_binary(char *filename, char *buffer, int length) {

	FILE *fp = fopen(filename, "wb+");
	if (fp == NULL) {
		printf("fopen failed\n");
		return -1;
	}
	
	int size = fwrite(buffer, 1, length, fp);
	if (size != length) {
		printf("fread faile\n");
		return size;
	}

	fclose(fp);

	return size;
}

//
int mysql_write(MYSQL *client, char *buffer, long length) {

	if (client == NULL) return -1;
	if (buffer == NULL) return -2;
	if (length <= 0) return -3;

	MYSQL_STMT *stmt = mysql_stmt_init(client);
	int ret = mysql_stmt_prepare(stmt, KING_MYSQL_INSERT_TBL_USER, strlen(KING_MYSQL_INSERT_TBL_USER));

	MYSQL_BIND param = {0};
	param.buffer_type = MYSQL_TYPE_LONG_BLOB;
	param.buffer = NULL;
	param.is_null = 0;
	param.length = NULL;

	ret = mysql_stmt_bind_param(stmt, &param);

	if (mysql_stmt_send_long_data(stmt, 0, buffer, length)) {
		printf(" err : %s\n", mysql_error(client));
	}

	ret = mysql_stmt_execute(stmt);
	mysql_stmt_close(stmt);
	
}


//
int mysql_read(MYSQL *client, char *buffer, int length) {
	if (client == NULL) return -1;
	if (buffer == NULL) return -2;
	if (length <= 0) return -3;

	
	MYSQL_STMT *stmt = mysql_stmt_init(client);
	int ret = mysql_stmt_prepare(stmt, KING_MYSQL_SELECT_TBL_USER, strlen(KING_MYSQL_SELECT_TBL_USER));
	
	MYSQL_BIND result = {0};
	unsigned long total_length = 0;
	
	result.buffer_type = MYSQL_TYPE_LONG_BLOB;
	result.length = &total_length;

	ret = mysql_stmt_bind_result(stmt, &result);
	ret = mysql_stmt_execute(stmt);
	ret = mysql_stmt_store_result(stmt);

	for (;;) {

		ret = mysql_stmt_fetch(stmt);
		if (ret != 0 && ret != MYSQL_DATA_TRUNCATED) break;

		int start = 0;
		while (start < (int)total_length) {

			result.buffer = buffer+start;
			result.buffer_length = 1;

			ret = mysql_stmt_fetch_column(stmt, &result, 0, start);
            if (ret!=0)
            {
                printf("msg=%s", mysql_error(client));
                return;
            }
            start += result.buffer_length;
		}

	}

	mysql_stmt_close(stmt);

	return total_length;
	
}


int main() {

	MYSQL mysql;
	if (NULL == mysql_init(&mysql)) {
		printf("mysql_init : %s\n", mysql_error(&mysql));
		return -1;
	}

	//mysql_connect
	if (!mysql_real_connect(&mysql, KING_MYSQL_SERVER, KING_MYSQL_USERNAME, KING_MYSQL_PASSWORD, 
		KING_MYSQL_DBNAME, 0, NULL, 0)) {
		printf("mysql_real_connect : %s\n", mysql_error(&mysql));
		return -1;
	}

	printf("Connected MySQL succcessful!");

	char buffer[KING_BINARY_LENGTH] = {0};
	int length = read_binary("111.png", buffer);

	mysql_write(&mysql, buffer, length);
	printf("length : %d\n", length);

	memset(buffer, 0, KING_BINARY_LENGTH);
	
	length = mysql_read(&mysql, buffer, KING_BINARY_LENGTH);
	write_binary("a.jpg", buffer, length);


	mysql_close(&mysql);

	return 0;

}



