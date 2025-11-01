#include "util.h"
#include "mysql_fun.h"
#include "picture.h"
#include "scene_manager.h"
#include "scene_progress_bar.h"
#include "scene_login_registration.h"
#include "scene_menu.h"
#include "scene_knapsack.h"
#include "scene_set.h"
#include "scene_exit.h"
#include "scene_pokemon.h"
#include "scene_game.h"
#include "pokeman_charmander.h"
#include "pokemon_squirtle.h"
#include "pokemon_bulbasaur.h"
#include "bullet.h"
#include "collision_line.h"
#include "time.h"


const std::string host = "127.0.0.1";											// 数据库连接的ip地址
const std::string user = "qin";													// 用户名
const std::string password = "123456";											// 用户名密码
const std::string db = "pokemon_db";											// 宝可梦数据
const unsigned int port = 3306;													// 端口号

bool is_debug = false;								                            // 是否开启调式模式
bool is_mysql_connect = false;						                            // 是否成功连接数据库

Scene* progress_bar_scene = nullptr;											// 进度条场景对象指针
Scene* login_registration_scene = nullptr;										// 登录注册场景对象指针
Scene* menu_scene = nullptr;						                            // 菜单场景对象指针
Scene* knapsack_scene = nullptr;					                            // 背包场景对象指针
Scene* set_scene = nullptr;							                            // 设置场景对象指针
Scene* exit_scene = nullptr;													// 退出场景对象指针
Scene* pokemon_scene = nullptr;						                            // 宝可梦场景对象指针
Scene* game_scene = nullptr;						                            // 游戏场景对象指针

SceneManager* scene_manager;						                            // 场景管理对象指针

Pokemon* pokemon_player_1 = nullptr;				                            // 宝可梦玩家1
Pokemon* pokemon_player_2 = nullptr;				                            // 宝可梦玩家2

std::vector<CollisionLine> collision_thwartwise_line_list;					    // 横向的碰撞线容器
std::vector<CollisionLine> collision_vertical_line_list;						// 竖向的碰撞线容器
std::vector<Bullet*> bullet_list;												// 子弹容器

HWND hwnd;																		// 窗口句柄
MYSQL* my;																		// mysql的连接句柄

// 设置内容
constexpr int background_music_num = 3;											// 背景音乐的数量
constexpr int game_music_num = 5;												// 战斗音乐的数量

bool is_first_game = false;							                            // 是否是第一次游戏
bool is_attribute_restrain = true;												// 是否有属性克制
bool is_open_music = true;														// 是否打开音乐
bool is_open_sound_effect = true;												// 是否打开音效
bool is_playing_background_music = false;										// 是否正在播放背景音乐
bool is_playing_game_music = false;												// 是否正在播放战斗音乐(游戏场景的音乐)

int background_music_id = 1;													// 主菜单播放的背景音乐 
int temp_background_music_id = background_music_id;								// 正在播放的音乐id
int game_music_id = 1;															// 游戏场景正在播放的战斗音乐
int temp_game_music_id = game_music_id;											// 正在播放的音乐id

// 背包道具内容
bool is_selected_healing_potion_1P = false;										// 1P是否选择了治疗药水
bool is_selected_healing_potion_2P = false;										// 2P是否选择了治疗药水
bool is_selected_power_potion_1P = false;										// 1P是否选择了能量药水
bool is_selected_power_potion_2P = false;										// 2P是否选择了能量药水
bool is_selected_invisibility_potion_1P = false;								// 1P是否选择了隐身药水
bool is_selected_invisibility_potion_2P = false;								// 2P是否选择了隐身药水


int main() {
	// 初始化数据库并给相关参数赋值
	connect_mysql(host, user, password, db, port);
	check_and_update_is_first_game();
	check_and_update_is_open_music();
	check_and_update_is_open_sound_effect();
	check_update_background_music_id();
	check_update_game_music_id();

	srand(time(NULL)); 

	// 帧率 （每一帧至少停留的时间，单位：ms)
	const int FPS = 60;

	// 定义一个ExMessage类型的变量msg，用于存储消息信息
	ExMessage msg;

	// 初始化句柄
    hwnd = initgraph(1280, 720, EX_SHOWCONSOLE);

	// 加载音乐图片资源
	load_res();

	// 给不同的场景对象指针初始化
	progress_bar_scene = new SceneProgressBar();
	login_registration_scene = new SceneLoginRegistration();
	menu_scene = new SceneMenu();
	knapsack_scene = new SceneKnapsack();
	set_scene = new SceneSet();
	exit_scene = new SceneExit();
	pokemon_scene = new ScenePokemon();
	game_scene = new SceneGame();

	scene_manager = new SceneManager();

	// 初始化场景位置
	scene_manager->scene_set(progress_bar_scene);

	// 批量绘图函数
	BeginBatchDraw();

	while (true) {
		// 记录现在的时间戳
		DWORD current_start_time = GetTickCount();

		// 处理消息，做到如场景切换，鼠标点击带动的其他功能等
		while (peekmessage(&msg)) {
			scene_manager->on_input(msg);
		}

		// 更新画面的信息及相关逻辑，时间增量为 本次时间戳 - 上次更新结束的时间戳
		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_time = current_tick_time - last_tick_time;
		scene_manager->on_update(delta_time);
		last_tick_time = current_start_time;

		// 根据更新的信息刷新画面
		cleardevice();
		scene_manager->on_draw();
		FlushBatchDraw();

		// 处理帧率
		DWORD current_end_time = GetTickCount();
		DWORD current_delta_time = current_end_time - current_start_time;
		if (current_delta_time < 1000 / FPS) Sleep(1000 / FPS - current_delta_time);
	}

	closegraph();
	return 0;
}


// 副主函数
int _main(int x, int y) {
	srand(time(NULL));

	// 帧率 （每一帧至少停留的时间，单位：ms)
	const int FPS = 60;

	// 定义一个ExMessage类型的变量msg，用于存储消息信息
	ExMessage msg;

	// 初始化句柄
	hwnd = initgraph(1280, 720, EX_SHOWCONSOLE);

	// 加载音乐图片资源
	//load_res();

	// 给不同的场景对象指针初始化
	menu_scene = new SceneMenu();
	knapsack_scene = new SceneKnapsack();
	set_scene = new SceneSet();
	pokemon_scene = new ScenePokemon();
	game_scene = new SceneGame();

	scene_manager = new SceneManager();

	// 初始化场景位置，这里默认为菜单场景，即程序运行后会直接进入菜单场景
	scene_manager->scene_set(pokemon_scene);

	// 批量绘图函数
	BeginBatchDraw();

	while (true) {
		// 记录现在的时间戳
		DWORD current_start_time = GetTickCount();

		// 处理消息，做到如场景切换，鼠标点击带动的其他功能等
		while (peekmessage(&msg)) {
			scene_manager->on_input(msg);
		}

		// 更新画面的信息及相关逻辑，时间增量为 本次时间戳 - 上次更新结束的时间戳
		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_time = current_tick_time - last_tick_time;
		scene_manager->on_update(delta_time);
		last_tick_time = current_start_time;

		// 根据更新的信息刷新画面
		cleardevice();
		scene_manager->on_draw();
		FlushBatchDraw();

		// 处理帧率
		DWORD current_end_time = GetTickCount();
		DWORD current_delta_time = current_end_time - current_start_time;
		if (current_delta_time < 1000 / FPS) Sleep(1000 / FPS - current_delta_time);
	}

	closegraph();
	return 0;
}