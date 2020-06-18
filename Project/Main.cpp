#include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<list>
#include<queue>
#include<ctime>
#include<chrono>
#include "VideoGame.h"
#include "bubble_sort.h"
#include "insertion_sort.h"
#include "quick_sort.h"

using namespace std;
using namespace chrono;

template <typename T>
T convert(string& s)
{
	stringstream c(s);
	T t;
	c >> t;
	return t;
}

void load(ifstream& in, vector<VideoGame>& v)
{
	string line, temp, name, platform, genre, publisher;
	getline(in, line);
	while (getline(in,line))
	{
		//cout << line << endl;
		stringstream ss(line);
		getline(ss, temp, ',');
		int rank = convert<int>(temp);
		getline(ss, name, ',');
		getline(ss, platform, ',');
		getline(ss, temp, ',');
		int year = convert<int>(temp);
		getline(ss, genre, ',');
		getline(ss, publisher, ',');
		getline(ss, temp, ',');
		float naSales = convert<float>(temp);
		getline(ss, temp, ',');
		float euSales = convert<float>(temp);
		getline(ss, temp, ',');
		float jpSales = convert<float>(temp);
		getline(ss, temp, ',');
		float otherSales = convert<float>(temp);
		getline(ss, temp);
		float globalSales = convert<float>(temp);
		v.emplace_back(rank, name, platform, year, genre, publisher, naSales, euSales, jpSales, otherSales, globalSales);
	}
}

multimap<string, VideoGame> fill_multimap(vector<VideoGame>& v)
{
	multimap<string, VideoGame> mm;
	for (int i = 0; i < v.size(); i++)
	{
		VideoGame vg = v[i];
		mm.emplace(vg.get_genre(), vg);
	}
	return mm;
}

list<VideoGame> fill_list(vector<VideoGame>& v)
{
	list<VideoGame> l;
	for (int i = 0; i < v.size(); i++)
	{
		l.push_back(v[i]);
	}
	return l;
}

void search_by_year(priority_queue<VideoGame, vector<VideoGame>, compareYear>& pq)
{
	while (!pq.empty())
	{
		cout << pq.top().to_string()<<endl;
		pq.pop();
	}
}

void search_by_genre(multimap<string, VideoGame>& mm, vector<VideoGame>& v, list<VideoGame>& l)
{
	bool next;
	do
	{
		system("cls");
		string genre;
		cout << "Genre: ";
		cin >> genre;

		pair<multimap<string, VideoGame>::iterator, multimap<string, VideoGame>::iterator> found = mm.equal_range(genre);

		cout << "\nMULTIMAP\n";
		auto mbegin = high_resolution_clock::now();
		if (found.first != found.second)
		{
			for (auto it = found.first; it != found.second; ++it)
				cout << it->second.to_string() << endl;
		}
		else
		{
			cout << "No Results" << endl;
		}
		auto mend = high_resolution_clock::now();
		double multimapSpeed = duration_cast<milliseconds>(mend - mbegin).count();

		cout << "\nVEKTOR\n";
		auto vbegin = high_resolution_clock::now();
		for (int i = 0; i < v.size(); i++)
		{
			if (genre == v[i].get_genre())
			{
				cout << v[i].to_string() << endl;
			}
		}
		auto vend = high_resolution_clock::now();
		double vectorSpeed = duration_cast<milliseconds>(vend - vbegin).count();

		cout << "\nLIST\n";
		auto lbegin = high_resolution_clock::now();
		for (auto it = l.begin(); it != l.end(); it++)
		{
			if (genre == (*it).get_genre())
			{
				cout << (*it).to_string() << endl;
			}
		}
		auto lend = high_resolution_clock::now();
		double listSpeed = duration_cast<milliseconds>(lend - lbegin).count();

		cout
			<< "\nMultimap speed: " << multimapSpeed << " ms"
			<< "\nVector speed: " << vectorSpeed << " ms"
			<< "\nList speed: " << listSpeed << " ms\n";
		
		vector<double> topSpeed{ multimapSpeed,vectorSpeed,listSpeed };
		double fastest = topSpeed[0];
		double slowest = topSpeed[0];
		double average = topSpeed[0];
		for (int i = 0; i < topSpeed.size(); i++)
		{
			if (fastest > topSpeed[i])
			{
				fastest = topSpeed[i];
			}	
			if (slowest < topSpeed[i])
			{
				slowest = topSpeed[i];
			}
		}
		for (int i = 0; i < topSpeed.size(); i++)
		{
			if (topSpeed[i] > fastest && topSpeed[i] < slowest)
			{
				average = topSpeed[i];
			}
		}
		
		if (topSpeed[0] == fastest)
			cout << endl << 1 << ". Multimap: " << multimapSpeed << " ms";
		
		if (topSpeed[1] == fastest)
			cout << endl << 1 << ". Vector: " << vectorSpeed << " ms";
		
		if (topSpeed[2] == fastest)
			cout << endl << 1 << ". List: " << listSpeed << " ms";
		
		if (topSpeed[0] == average)
			cout << endl << 2 << ". Multimap: " << multimapSpeed << " ms";

		if (topSpeed[1] == average)
			cout << endl << 2 << ". Vector: " << vectorSpeed << " ms";

		if (topSpeed[2] == average)
			cout << endl << 2 << ". List: " << listSpeed << " ms";

		if (topSpeed[0] == slowest)
			cout << endl << 3 << ". Multimap: " << multimapSpeed << " ms";

		if (topSpeed[1] == slowest)
			cout << endl << 3 << ". Vector: " << vectorSpeed << " ms";

		if (topSpeed[2] == slowest)
			cout << endl << 3 << ". List: " << listSpeed << " ms";

		cout << "\nNext(0,1)? ";
		cin >> next;
	} while (next);
}

void copy_vector(multimap<string, VideoGame>& mm)
{
	vector<string> v;
	bool next;
	do
	{
		system("cls");
		string genre;
		cout << "Genre: ";
		cin >> genre;
		int count = 0;
		pair<multimap<string, VideoGame>::iterator, multimap<string, VideoGame>::iterator> found = mm.equal_range(genre);

		if (found.first != found.second)
		{
			for (auto it = found.first; it != found.second; ++it)
			{
				v.push_back(it->second.to_string());
			}
		}
		else
		{
			cout << "No Results" << endl;
		}
		
		cout << "\nNext(0,1)? ";
		cin >> next;
	} while (next);

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}
}

void search_by_global_sales(priority_queue<VideoGame, vector<VideoGame>, compareGlobalSales>& pq)
{
	while (!pq.empty())
	{
		cout << pq.top().to_string() << endl;
		pq.pop();
	}
}

void sort_bubble(vector<VideoGame>& v1)
{
	auto begin = high_resolution_clock::now();
	bubble_sort(v1);
	auto end = high_resolution_clock::now();
	cout
		<< "\nBubble time:"
		<< duration_cast<milliseconds>(end - begin).count()
		<< " ms\n";
}

void sort_insertion(vector<VideoGame>& v2)
{
	auto begin = high_resolution_clock::now();
	insertion_sort(v2);
	auto end = high_resolution_clock::now();
	cout
		<< "\nInsertion time:"
		<< duration_cast<milliseconds>(end - begin).count()
		<< " ms\n";
}

void guess()
{
	int n = 100000000;
	vector<int> v;

	int num;
	cout << "Guess the duration time in ms: ";
	cin >> num;
	auto begin = high_resolution_clock::now();
	//Filling
	for (int i = 1; i <= n; i++)
	{
		v.push_back(i);
	}
	//Randomize
	random_shuffle(v.begin(), v.end());
	//Sort
	sort(v.begin(), v.end());
	//Search
	if (binary_search(v.begin(), v.end(), 7))
	{
		cout << "Number " << 7 << " found!" << endl;
	}
	else
	{
		cout << "Number " << 7 << " not found" << endl;
	}
	auto end = high_resolution_clock::now();
	double duration = duration_cast<milliseconds>(end - begin).count();

	cout
		<< "\nDuration time was "
		<< duration
		<< " ms\n"
		<< "You were wrong by " << num - duration << " ms\n";
}

void bogo(vector<VideoGame>& v3)
{
	vector<VideoGame> vFive;
	random_shuffle(v3.begin(), v3.end());
	for (int i = 0; i < 5; i++)
		vFive.push_back(v3[i]);
	
	bubble_sort(vFive);

	for (int i = 0; i < vFive.size(); i++)
		cout << vFive[i].to_string() << endl;
}

void quick(vector<VideoGame>& v)
{
	int n;
	cout << "Enter desired number: ";
	cin >> n;

	random_shuffle(v.begin(), v.end());
	
	vector<VideoGame> vn;
	for (int i = 0; i < n; i++)
		vn.push_back(v[i]);

	quick_sort(vn);
	
	for (int i = 0; i < vn.size(); i++)
	{
		cout << vn[i].to_string() << endl;
	}
}

unordered_multimap<string, VideoGame> fill_unordered_multimap(vector<VideoGame>& v)
{
	unordered_multimap<string, VideoGame> umm;
	for (int i = 0; i < v.size(); i++)
	{
		VideoGame vg = v[i];
		umm.emplace(vg.get_platform(), vg);
	}
	return umm;
}

unordered_map<int, VideoGame> fill_unordered_map(vector<VideoGame>& v)
{
	unordered_map<int, VideoGame> um;
	for (int i = 0; i < v.size(); i++)
	{
		VideoGame vg = v[i];
		um.emplace(vg.get_rank(), vg);
	}
	return um;
}

void search_by_platform(unordered_multimap<string, VideoGame>& umm, vector<VideoGame>& v, list<VideoGame>& l)
{
	bool next;
	do
	{
		system("cls");
		string platform;
		cout << "Platform: ";
		cin >> platform;

		cout << "\nUNORDERED_MULTIMAP\n";
		pair<unordered_multimap<string, VideoGame>::iterator, unordered_multimap<string, VideoGame>::iterator> found = umm.equal_range(platform);
		auto umbegin = high_resolution_clock::now();
		if (found.first != found.second)
		{
			for (auto it = found.first; it != found.second; ++it)
				cout << it->second.to_string() << endl;
		}
		else
		{
			cout << "No Results" << endl;
		}
		auto umend = high_resolution_clock::now();
		double multimapSpeed = duration_cast<milliseconds>(umend - umbegin).count();

		cout << "\nVEKTOR\n";
		auto vbegin = high_resolution_clock::now();
		for (int i = 0; i < v.size(); i++)
		{
			if (platform == v[i].get_platform())
			{
				cout << v[i].to_string() << endl;
			}
		}
		auto vend = high_resolution_clock::now();
		double vectorSpeed = duration_cast<milliseconds>(vend - vbegin).count();

		cout << "\nLIST\n";
		auto lbegin = high_resolution_clock::now();
		for (auto it = l.begin(); it != l.end(); it++)
		{
			if (platform == (*it).get_platform())
			{
				cout << (*it).to_string() << endl;
			}
		}
		auto lend = high_resolution_clock::now();
		double listSpeed = duration_cast<milliseconds>(lend - lbegin).count();

		cout
			<< "\nUnordered_multimap speed: " << multimapSpeed << " ms"
			<< "\nVector speed: " << vectorSpeed << " ms"
			<< "\nList speed: " << listSpeed << " ms\n";

		vector<double> topSpeed{ multimapSpeed,vectorSpeed,listSpeed };
		double fastest = topSpeed[0];
		double slowest = topSpeed[0];
		double average = topSpeed[0];
		for (int i = 0; i < topSpeed.size(); i++)
		{
			if (fastest > topSpeed[i])
			{
				fastest = topSpeed[i];
			}
			if (slowest < topSpeed[i])
			{
				slowest = topSpeed[i];
			}
		}
		for (int i = 0; i < topSpeed.size(); i++)
		{
			if (topSpeed[i] > fastest && topSpeed[i] < slowest)
			{
				average = topSpeed[i];
			}
		}

		if (topSpeed[0] == fastest)
			cout << endl << 1 << ". Unordered_multimap: " << multimapSpeed << " ms";

		if (topSpeed[1] == fastest)
			cout << endl << 1 << ". Vector: " << vectorSpeed << " ms";

		if (topSpeed[2] == fastest)
			cout << endl << 1 << ". List: " << listSpeed << " ms";

		if (topSpeed[0] == average)
			cout << endl << 2 << ". Unordered_multimap: " << multimapSpeed << " ms";

		if (topSpeed[1] == average)
			cout << endl << 2 << ". Vector: " << vectorSpeed << " ms";

		if (topSpeed[2] == average)
			cout << endl << 2 << ". List: " << listSpeed << " ms";

		if (topSpeed[0] == slowest)
			cout << endl << 3 << ". Unordered_multimap: " << multimapSpeed << " ms";

		if (topSpeed[1] == slowest)
			cout << endl << 3 << ". Vector: " << vectorSpeed << " ms";

		if (topSpeed[2] == slowest)
			cout << endl << 3 << ". List: " << listSpeed << " ms";
		
		cout << "\nNext(0,1)? ";
		cin >> next;
	} while (next);
}

void visualize(unordered_map<int, VideoGame>& um)
{
	for (int i = 0; i < um.bucket_count(); i++)
	{
		unordered_map<int, VideoGame>::iterator found = um.find(um[i].get_rank());
		cout << "Bucket" << i << ": ";
		
		if (um.bucket_size(i) == 0)
		{

			if (found != um.end()) {
				cout << found->second.get_name() << endl;
			}
			else
			{
				cout << "[EMPTY]" << endl;
				return;
			}
		}
		else
		{
			cout << "[EMPTY]" << endl;
		}
	}
}

void nameCheck()
{
	cin.ignore();
	
	string name1, name2;

	cout << "First name: ";
	getline(cin, name1);
	cout << "Second name: ";
	getline(cin, name2);
	
	for (int i = 0; i < name1.size(); i++)
		name1[i] = toupper(name1[i]);

	for (int i = 0; i < name2.size(); i++)
		name2[i] = toupper(name2[i]);

	
	unordered_set<char> us1;
	for (int i = 0; i < name1.size(); i++)
	{
		us1.insert(name1[i]);
	}

	unordered_set<char> us2;
	for (int i = 0; i < name2.size(); i++)
	{
		us2.insert(name2[i]);
	}

	int check = us2.size();
	if (name1.size() < name2.size())
	{
		cout << "Second name can not be recreated from the first name!\n";
	}
	else
	{
		for (auto i = us1.begin(); i != us1.end(); i++)
		{
			for (auto j = us2.begin(); j != us2.end(); j++)
			{
				if (*i == *j)
				{
					check--;
				}
			}
		}
	}
	if (check <= 0)
	{
		cout<< "Second name can be recreated from the first name!\n";
	}
	else
	{
		cout << "Second name can not be recreated from the first name!\n";
	}
}

int main()
{
	srand(time(nullptr));

	cout << "LOADING ...";
	ifstream in("SPA_PROJ_006_GAME_SALES_data.csv");
	if (!in)
	{
		cout << "ERROR::SPA_PROJ_006_GAME_SALES_data.csv";
		return -404;
	}
	vector<VideoGame> v;
	load(in, v);
	in.close();

	system("cls");
	cout << "CHOOSE FUNCTION\n\n"
		<< "[1] Search by genre\n"
		<< "[2] Search by year\n"
		<< "[3] Copy in new vector\n"
		<< "[4] Search by global sales\n"
		<< "[5] Bubble vs Insertion\n"
		<< "[6] Guess the duration\n"
		<< "[7] Lets Bogo!\n"
		<< "[8] Quick quick!\n"
		<< "[9] Search by platform\n"
		<< "[10] Visualize!\n"
		<< "[11] Make name out of a name\n";

	int n;
	do
	{
		cin >> n;
		//Search by genre
		if (n == 1)
		{
			system("cls");
			multimap<string,VideoGame> mm(fill_multimap(v));
			list<VideoGame> l(fill_list(v));
			search_by_genre(mm, v, l);
		}
		//Search by year
		else if (n == 2)
		{
			system("cls");
			priority_queue<VideoGame, vector<VideoGame>, compareYear> pq(v.begin(),v.end());
			search_by_year(pq);
		}
		//Copy in new vector
		else if (n == 3)
		{
			system("cls");
			multimap<string, VideoGame> mm(fill_multimap(v));
			copy_vector(mm);
		}
		//Search by global sales
		else if (n == 4)
		{
			system("cls");
			priority_queue<VideoGame, vector<VideoGame>, compareGlobalSales> pq(v.begin(), v.end());
			search_by_global_sales(pq);
		}
		//Bubble vs Insertion
		else if (n == 5)
		{
			system("cls");
			vector<VideoGame> v1(v);
			vector<VideoGame> v2(v);
			sort_bubble(v1);
			sort_insertion(v2);
		}
		//Guess the duration
		else if (n == 6)
		{
			system("cls");
			guess();
		}
		//Lets Bogo!
		else if (n == 7)
		{
			system("cls");
			vector<VideoGame> v3(v);
			bogo(v3);
		}
		//Quick quick!
		else if (n == 8)
		{
			system("cls");
			quick(v);
		}
		//Search by platform
		else if (n == 9)
		{
			system("cls");
			unordered_multimap<string, VideoGame> umm(fill_unordered_multimap(v));
			list<VideoGame> l(fill_list(v));
			search_by_platform(umm, v, l);
		}
		//Visualize!
		else if (n == 10)
		{
			system("cls");
			unordered_map<int, VideoGame> um(fill_unordered_map(v));
			visualize(um);
		}
		//Make name out of a name
		else if (n == 11)
		{
			system("cls");
			nameCheck();
		}
		else
		{
			system("cls");
			cout << "CHOOSE FUNCTION\n\n"
				<< "[1] Search by genre\n"
				<< "[2] Search by year\n"
				<< "[3] Copy in new vector\n"
				<< "[4] Search by global sales\n"
				<< "[5] Bubble vs Insertion\n"
				<< "[6] Guess the duration\n"
				<< "[7] Lets Bogo!\n"
				<< "[8] Quick quick!\n"
				<< "[9] Search by platform\n"
				<< "[10] Visualize!\n"
				<< "[11] Make name out of a name\n";
		}
	} while (n < 1 || n > 11);

	return 0;
}