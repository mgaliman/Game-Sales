#include "VideoGame.h"

VideoGame::VideoGame()
{
}

VideoGame::VideoGame(int rank, string name, string platform,
	int year, string genre, string publisher,
	float naSales, float euSales, float jpSales,
	float otherSales, float globalSales)
{
	this->rank = rank;
	this->name = name;
	this->platform = platform;
	this->year = year;
	this->genre = genre;
	this->publisher = publisher;
	this->naSales = naSales;
	this->euSales = euSales;
	this->jpSales = jpSales;
	this->otherSales = otherSales;
	this->globalSales = globalSales;
}

string VideoGame::to_string() const
{
	stringstream ss;
	ss
		<< " Rank-> " << rank
		<< " Name-> " << name
	//	<< " Platform-> " << platform
		<< " Year-> " << year
	//	<< " Genre-> " << genre
		<< " Publisher-> " << publisher
	//	<< " Na_Sales-> " << naSales
	//	<< " Eu_Sales-> " << euSales
	//	<< " Jp_Sales-> " << jpSales
	//	<< " Other Sales -> " << otherSales
		<< " Global Sales-> " << globalSales;
	return ss.str();
}

int VideoGame::get_rank() const
{
	return rank;
}

string VideoGame::get_name() const
{
	return name;
}

char VideoGame::get_first_letter() const
{
	return name[0];
}

string VideoGame::get_platform() const
{
	return platform;
}

int VideoGame::get_year() const
{
	return year;
}

string VideoGame::get_genre() const
{
	return genre;
}

float VideoGame::get_globalSales() const
{
	return globalSales;
}

