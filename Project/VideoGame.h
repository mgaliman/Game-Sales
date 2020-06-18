#pragma once
#include<string>
#include<sstream>
#include<vector>

using namespace std;

class VideoGame
{
private:
	int rank;
	string name;
	string platform;
	int year;
	string genre;
	string publisher;
	float naSales;
	float euSales;
	float jpSales;
	float otherSales;
	float globalSales;
public:
	VideoGame();
	VideoGame(int rank, string name, string platform, 
		int year, string genre, string publisher,
		float naSales, float euSales, float jpSales, 
		float otherSales, float globalSales);
	string to_string() const;
	int get_rank() const;
	string get_name() const;
	char get_first_letter() const;
	string get_platform() const;
	int get_year() const;
	string get_genre() const;
	float get_globalSales() const;
};

struct compareYear
{
	bool operator()(const VideoGame&  i1, const VideoGame&  i2) const
	{
		return i1.get_year() > i2.get_year();
	}
};

struct compareGlobalSales
{
	bool operator()(const VideoGame&  i1, const VideoGame&  i2) const
	{
		if (i1.get_globalSales() == i2.get_globalSales())
			return i1.get_first_letter() > i2.get_first_letter();
		
		else
			return i1.get_globalSales() < i2.get_globalSales();
	}
};