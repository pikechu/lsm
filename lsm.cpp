#include <lsm.h>
#include <algorithm>

void LSM::clear()
{
	this->sstables.clear();
}

void LSM::set(string key, string value)
{
	mem_table[key] = { value, false };

	_auto_compaction();
}

void LSM::del(string key, string value)
{
	mem_table[key] = { value, true };
	_auto_compaction();
	
}

std::string LSM::get(string key)
{
	if (mem_table.find(key) != mem_table.end() && !is_deleted(mem_table, key))
	{
		return mem_table[key].first;
	}
	// from lv0 to lv5
	for (int i = 0; i < levels.size(); i++)
	{
		for (auto tables : sstables[levels[i]])
		{

		}
	}
	
	return "";
}

// к╒ел mem to disk
void LSM::_auto_flush()
{
	if (mem_table.size() >= MEM_TABLE_MAX_SIZE)
	{
		vector<pair<string, string>> kv;
		for (const auto& i : mem_table)
		{
			// not deleted
			if (!i.second.second)
			{
				kv.push_back({ i.first, i.second.first });
			}
		}
		mem_table
	}
}

// disk compaction
void LSM::_auto_compaction()
{

	
}



void LSM::_split_to_sstable(const vector<pair<string, string>>* kv, Level to_level)
{

}

void LSM::_merge(vector<SortedStringTable*> input_tables, Level to_level)
{
	int elem_count = 0;
	for (auto table : input_tables)
	{
		elem_count += table->object_count();
	}
	for (auto table : this->sstables[to_level])
	{
		elem_count += table.object_count();
	}
	vector <pair<string, string>> sorted_datas(elem_count);
	

	map<int, int> current_idx;

}

bool is_deleted(MemoryTable &mem_table, string key)
{
	if (mem_table.find(key) != mem_table.end())
	{
		return mem_table[key].second;
	}
	return true;
}

LSM::LSM()
{
	for (auto lv : levels)
	{
		this->sstables[lv] = {};
	}
}

LSM::~LSM()
{

}

void SortedStringTable::set_max_size(int sz)
{
	this->max_size = sz;
}

bool SortedStringTable::insert(string key, string value)
{
	if (this->objects.size() == 0)
	{
		this->key_min = key;
	}
	if (this->objects.size() >= this->max_size) {
		return false;
	}
	this->objects.push_back(SortedStringTableObject(key, value));
	this->key_max = key;
	return true;
}

void SortedStringTable::del(string key)
{
	int idx = this->_binary_search(key);
	if (idx != -1)
	{
		this->objects[idx].is_deleted = true;
	}
}


std::string SortedStringTable::get(string key)
{
	int idx = this->_binary_search(key);
	if (idx == -1 || this->objects[idx].is_deleted)
	{
		return "";
	}
	return this->objects[idx].value;
}

int SortedStringTable::object_count()
{
	return this->objects.size();
}

const vector<SortedStringTableObject>& SortedStringTable::get_objects()
{
	return this->objects;
}

const SortedStringTableObject& SortedStringTable::get_object(int idx)
{
	return this->objects[idx];
}

int SortedStringTable::_binary_search(string key)
{
	int mid, left, right, idx = -1;
	left = 0;
	right = this->objects.size() - 1;
	while (left <= right)
	{
		mid = this->objects.size() / 2;
		if (this->objects[mid].key == key) {
			idx = mid;
			break;
		}
		if (this->objects[mid].key > key) {
			right = mid;
		}
		else
		{
			left = mid;
		}
	}
	return idx;
}

SortedStringTableObject::SortedStringTableObject(string key, string value) :
	key(key), value(value), is_deleted(false)
{

}

SortedStringTable::SortedStringTable(Level level) :
	max_size(cap[level].second)
{

}

void main()
{

}