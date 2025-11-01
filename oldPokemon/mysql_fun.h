#pragma once

#include "util.h"


extern MYSQL* my;

extern bool is_mysql_connect;
extern bool is_first_game;
extern bool is_open_music;
extern bool is_open_sound_effect;
extern int background_music_id;
extern int game_music_id;




// 做初始化，仅连接数据库
void connect_mysql(const string host, const string user, const string password, const string db, const unsigned int port) {
	my = mysql_init(nullptr);
	if (my == nullptr)
	{
		std::cerr << "init MySQL error" << std::endl;
		is_mysql_connect = false;
		return;
	}

	if (mysql_real_connect(my, host.c_str(), user.c_str(), password.c_str(), db.c_str(), port, nullptr, 0) == nullptr)
	{
		std::cerr << "connect MySQL error" << std::endl;
		is_mysql_connect = false;
		return;
	}
	is_mysql_connect = true;

	std::cout << "mysql connect sucess" << std::endl;

	mysql_set_character_set(my, "utf8");
}



// 检查并更新is_first_game的值
void check_and_update_is_first_game() {
	std::string sql = "select * from game_status";
	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;

	MYSQL_RES* res = mysql_store_result(my);
	if (res == nullptr) {
		std::cerr << "mysql_store_result error" << std::endl;
		return;
	}

	const int rows = mysql_num_rows(res);			// 获取行数
	const int fields = mysql_num_fields(res);		// 获取列数

	for (int i = 0; i < rows; i++) {
		MYSQL_ROW row = mysql_fetch_row(res);
		for (int j = 0; j < fields; j++) {
			if (strcmp(row[j], "is_first_game") != 0) break;
			if (strcmp(row[++j], "1") == 0) is_first_game = true;
			else is_first_game = false;
			std::cout << "is_first_game: " << is_first_game << std::endl;			// 方便测试
			return;
		}
	}
}

// 设置is_first_game的值
void set_is_first_game(bool flag) {
	std::string sql;
	if (flag) sql = "update game_status set status = 1 where status_name = 'is_first_game'";
	else sql = "update game_status set status = 0 where status_name = 'is_first_game'";

	is_first_game = flag;

	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;
}



// 检查并更新is_open_music的值
void check_and_update_is_open_music() {
	std::string sql = "select * from game_status";
	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;

	MYSQL_RES* res = mysql_store_result(my);
	if (res == nullptr) {
		std::cerr << "mysql_store_result error" << std::endl;
		return;
	}

	const int rows = mysql_num_rows(res);			// 获取行数
	const int fields = mysql_num_fields(res);		// 获取列数

	for (int i = 0; i < rows; i++) {
		MYSQL_ROW row = mysql_fetch_row(res);
		for (int j = 0; j < fields; j++) {
			if (strcmp(row[j], "is_open_music") != 0) break;
			if (strcmp(row[++j], "1") == 0) is_open_music = true;
			else is_open_music = false;
			std::cout << "is_open_music: " << is_open_music << std::endl;			// 方便测试
			return;
		}
	}
}

// 设置is_open_music的值
void set_is_open_music(bool flag) {
	std::string sql;
	if (flag) sql = "update game_status set status = 1 where status_name = 'is_open_music'";
	else sql = "update game_status set status = 0 where status_name = 'is_open_music'";

	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;
}



// 检查并更新is_open_sound_effect的值
void check_and_update_is_open_sound_effect() {
	std::string sql = "select * from game_status";
	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;

	MYSQL_RES* res = mysql_store_result(my);
	if (res == nullptr) {
		std::cerr << "mysql_store_result error" << std::endl;
		return;
	}

	const int rows = mysql_num_rows(res);			// 获取行数
	const int fields = mysql_num_fields(res);		// 获取列数

	for (int i = 0; i < rows; i++) {
		MYSQL_ROW row = mysql_fetch_row(res);
		for (int j = 0; j < fields; j++) {
			if (strcmp(row[j], "is_open_sound_effect") != 0) break;
			if (strcmp(row[++j], "1") == 0) is_open_sound_effect = true;
			else is_open_sound_effect = false;
			std::cout << "is_open_sound_effect: " << is_open_sound_effect << std::endl;			// 方便测试
			return;
		}
	}
}

// 设置is_open_sound_effect的值
void set_is_open_sound_effect(bool flag) {
	std::string sql;
	if (flag) sql = "update game_status set status = 1 where status_name = 'is_open_sound_effect'";
	else sql = "update game_status set status = 0 where status_name = 'is_open_sound_effect'";

	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;
}



// 检查并更新background_music_id的值
void check_update_background_music_id() {
	std::string sql = "select * from game_status";
	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;

	MYSQL_RES* res = mysql_store_result(my);
	if (res == nullptr) {
		std::cerr << "mysql_store_result error" << std::endl;
		return;
	}

	const int rows = mysql_num_rows(res);			// 获取行数
	const int fields = mysql_num_fields(res);		// 获取列数

	for (int i = 0; i < rows; i++) {
		MYSQL_ROW row = mysql_fetch_row(res);
		for (int j = 0; j < fields; j++) {
			if (strcmp(row[j], "background_music_id") != 0) break;
			if (strcmp(row[++j], "0") == 0) background_music_id = 0;
			else if (strcmp(row[j], "1") == 0) background_music_id = 1;
			else if (strcmp(row[j], "2") == 0) background_music_id = 2;
			else if (strcmp(row[j], "3") == 0) background_music_id = 3;
			else std::cout << "background_music_id error!" << std::endl;
			std::cout << "background_music_id: " << background_music_id << std::endl;			// 方便测试
			return;
		}
	}
}

// 设置background_music_id的值
void set_background_music_id(int val) {
	std::string sql;
	if (val == 0) sql = "update game_status set status = 0 where status_name = 'background_music_id'";
	if (val == 1) sql = "update game_status set status = 1 where status_name = 'background_music_id'";
	else if (val == 2) sql = "update game_status set status = 2 where status_name = 'background_music_id'";
	else if (val == 3) sql = "update game_status set status = 3 where status_name = 'background_music_id'";
	else sql = "update game_status set status = 0 where status_name = 'background_music_id'";

	background_music_id = val;

	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;
}



// 检查并更新game_music_id的值
void check_update_game_music_id() {
	std::string sql = "select * from game_status";
	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;

	MYSQL_RES* res = mysql_store_result(my);
	if (res == nullptr) {
		std::cerr << "mysql_store_result error" << std::endl;
		return;
	}

	const int rows = mysql_num_rows(res);			// 获取行数
	const int fields = mysql_num_fields(res);		// 获取列数

	for (int i = 0; i < rows; i++) {
		MYSQL_ROW row = mysql_fetch_row(res);
		for (int j = 0; j < fields; j++) {
			if (strcmp(row[j], "game_music_id") != 0) break;
			if (strcmp(row[++j], "0") == 0) game_music_id = 0;
			else if (strcmp(row[j], "1") == 0) game_music_id = 1;
			else if (strcmp(row[j], "2") == 0) game_music_id = 2;
			else if (strcmp(row[j], "3") == 0) game_music_id = 3;
			else if (strcmp(row[j], "4") == 0) game_music_id = 4;
			else if (strcmp(row[j], "5") == 0) game_music_id = 5;
			else std::cout << "game_music_id error!" << std::endl;
			std::cout << "game_music_id: " << game_music_id << std::endl;			// 方便测试
			return;
		}
	}
}

// 设置game_music_id的值
void set_game_music_id(int val) {
	std::string sql;
	if (val == 0) sql = "update game_status set status = 0 where status_name = 'game_music_id'";
	else if (val == 1) sql = "update game_status set status = 1 where status_name = 'game_music_id'";
	else if (val == 2) sql = "update game_status set status = 2 where status_name = 'game_music_id'";
	else if (val == 3) sql = "update game_status set status = 3 where status_name = 'game_music_id'";
	else if (val == 4) sql = "update game_status set status = 4 where status_name = 'game_music_id'";
	else if (val == 5) sql = "update game_status set status = 5 where status_name = 'game_music_id'";
	else sql = "update game_status set status = 0 where status_name = 'game_music_id'";

	game_music_id = val;

	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;
}



// 检查并更新是否记住密码
bool check_update_is_remember_password() {
	std::string sql = "select * from game_status";
	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;

	MYSQL_RES* res = mysql_store_result(my);
	if (res == nullptr) {
		std::cerr << "mysql_store_result error" << std::endl;
		return false;
	}

	const int rows = mysql_num_rows(res);			// 获取行数
	const int fields = mysql_num_fields(res);		// 获取列数

	for (int i = 0; i < rows; i++) {
		MYSQL_ROW row = mysql_fetch_row(res);
		for (int j = 0; j < fields; j++) {
			if (strcmp(row[j], "is_remember_password") != 0) break;
			if (strcmp(row[++j], "1") == 0) return true;
			else return false;
		}
	}

	return false;
}

// 设置is_remember_password
void set_is_remember_password(bool flag) {
	std::string sql;
	if (flag) sql = "update game_status set status = 1 where status_name = 'is_remember_password'";
	else sql = "update game_status set status = 0 where status_name = 'is_remember_password'";

	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;
}



// 检查并更新是否打开眼睛(是否显示密码)
bool check_update_is_open_eye() {
	std::string sql = "select * from game_status";
	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;

	MYSQL_RES* res = mysql_store_result(my);
	if (res == nullptr) {
		std::cerr << "mysql_store_result error" << std::endl;
		return false;
	}

	const int rows = mysql_num_rows(res);			// 获取行数
	const int fields = mysql_num_fields(res);		// 获取列数

	for (int i = 0; i < rows; i++) {
		MYSQL_ROW row = mysql_fetch_row(res);
		for (int j = 0; j < fields; j++) {
			if (strcmp(row[j], "is_open_eye") != 0) break;
			if (strcmp(row[++j], "1") == 0) return true;
			else return false;
		}
	}

	return false;
}

// 设置is_open_eye
void set_is_open_eye(bool flag) {
	std::string sql;
	if (flag) sql = "update game_status set status = 1 where status_name = 'is_open_eye'";
	else sql = "update game_status set status = 0 where status_name = 'is_open_eye'";

	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;
}



// 注册账号
bool registration_account(string account, string password) {
	std::string sql;
	sql = "insert into accounts values('" + account + "', '" + password + "')";

	const int n = mysql_query(my, sql.c_str());
	if (n == 0) {
		std::cout << sql << " sucess:" << n << std::endl;
		return true;
	}
	else {
		std::cout << sql << " failed:" << n << std::endl;
		return false;
	}
}

// 检查是否可以登录
bool check_is_can_login(string account, string password) {
	std::string sql = "select * from accounts";
	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;

	MYSQL_RES* res = mysql_store_result(my);
	if (res == nullptr) {
		std::cerr << "mysql_store_result error" << std::endl;
		return false;
	}

	const int rows = mysql_num_rows(res);			// 获取行数
	const int fields = mysql_num_fields(res);		// 获取列数

	for (int i = 0; i < rows; i++) {
		MYSQL_ROW row = mysql_fetch_row(res);
		for (int j = 0; j < fields; j++) {
			if (strcmp(row[j], account.c_str()) == 0 && strcmp(row[++j], password.c_str()) == 0) {
				std::cout << "login sucess!" << std::endl;
				return true;
			}
		}
	}

	std::cout << "login failed" << std::endl;
	return false;
}

// 清空被记住的账号
void clear_remembered_accounts() {
	std::string sql;
	sql = "delete from remembered_accounts";

	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;
}

// 设置更新被记住的账号
void set_update_remembered_accounts(string account, string password) {
	clear_remembered_accounts();

	std::string sql;
	sql = "insert into remembered_accounts values('" + account + "', '" + password + "')";

	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;
}

// 获取被记住的账号中的账号
string get_remembered_accounts_accounts() {
	std::string sql = "select * from remembered_accounts";
	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;

	MYSQL_RES* res = mysql_store_result(my);
	if (res == nullptr) {
		std::cerr << "mysql_store_result error" << std::endl;
		return "";
	}

	const int rows = mysql_num_rows(res);			// 获取行数
	const int fields = mysql_num_fields(res);		// 获取列数

	for (int i = 0; i < rows; ++i) {
		MYSQL_ROW row = mysql_fetch_row(res);
		return row[0];
	}

	return "";
}

// 获取被记住的账号中的密码
string get_remembered_accounts_password() {
	std::string sql = "select * from remembered_accounts";
	const int n = mysql_query(my, sql.c_str());
	if (n == 0) std::cout << sql << " sucess:" << n << std::endl;
	else std::cout << sql << " failed:" << n << std::endl;

	MYSQL_RES* res = mysql_store_result(my);
	if (res == nullptr) {
		std::cerr << "mysql_store_result error" << std::endl;
		return "";
	}

	const int rows = mysql_num_rows(res);			// 获取行数
	const int fields = mysql_num_fields(res);		// 获取列数

	for (int i = 0; i < rows; ++i) {
		MYSQL_ROW row = mysql_fetch_row(res);
		return row[1];
	}

	return "";
}