#pragma once
#include <map>
#include <vector>
#include <limits.h>

using namespace std;

enum Level {
	LV_0 = 0,
	LV_1 = 1,
	LV_2 = 2,
	LV_3 = 3,
	LV_4 = 4,
	LV_5 = 5
};

vector<Level> levels = { LV_0, LV_1, LV_2, LV_3, LV_4, LV_5 };

// LV - auto_compaction阈值(区间重复文件数量/文件大小)
map<int, pair<int, int>> cap{
	{LV_0, {6, 10}},
	{LV_1, {5, 100}},
	{LV_2, {4, 1000}},
	{LV_3, {3, 10000}},
	{LV_4, {2, 100000}},
	{LV_5, {1, INT_MAX}}
};

const int MEM_TABLE_MAX_SIZE = 100;
//string LSM_STORAGE_PATH = "/data/lsm";

struct SortedStringTableObject
{
	string key;
	string value;
	bool is_deleted;

	SortedStringTableObject::SortedStringTableObject(string key, string value);
};

typedef map<string, pair<string, bool>> MemoryTable;


class SortedStringTable
{
private:
	vector<SortedStringTableObject> objects;
	int max_size;
	string key_max, key_min;

	int _binary_search(string key);
public:
	void set_max_size(int sz);
	bool insert(string key, string value);
	void del(string key);
	string get(string key);
	int object_count();
	const vector<SortedStringTableObject>& get_objects();
	const SortedStringTableObject& get_object(int idx);

	SortedStringTable::SortedStringTable(Level level);
};


class LSM
{
public:
	void clear();
	void set(string key, string value);
	void del(string key, string value);
	string get(string key);
	void manual_compaction();

	LSM::LSM();

private:
	MemoryTable mem_table;
	map<Level, vector<SortedStringTable>> sstables;
	void _auto_flush();
	void _auto_compaction();
	void _split_to_sstable(const vector < pair<string, string>>* kv, Level to_level);
	void _merge(vector<SortedStringTable*> input_tables, Level to_level);
};




