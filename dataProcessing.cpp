#include <string>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;


const string locationsFileName="locationsTestBrent.txt";
map<int,string> locationsMap;

class SoundEvent
{
	public:
		SoundEvent(string s);	//format:   "mm/dd/yy hh:mm:ss id level"
		void PrintEvent();
		void PrintEventOneLine();

		int month;
		int day;
		int year;
		int hour;
		int minute;
		int second;
		int id;
		string location;
		int level;

		int dayTotal;	//day 1 is January 1, 2000
		int dayOfYear;
		int secondOfDay;
		int dayOfWeek; //day 1 is Sunday, day 2 is Monday, ... , day 7 is Saturday
		string dayOfWeekString;
};

class SoundEvents
{
	public:
		vector<SoundEvent*> v;

		void AnalyzeAndPrint_dayOfWeek();
		void AnalyzeAndPrint_hour();
		void AnalyzeAndPrint_id();
		void AnalyzeAndPrint_level();
		void AnalyzeAndPrint_time();

		void PrintEvents();
		void PrintEventsOneLine();
		void PrintEventsFormattedTree();
		void PrintEventsFormattedTreeHTML();
};



void usage()
{
	printf("usage: dataProcessing <inputfilename>\n");
	exit(0);
}

int main(int argc,char** argv)
{
	ifstream ifs;
	ifstream ifs2;
	string line;
	SoundEvent* SE;
	SoundEvents SEs;
	int i;
	string s;

	if(argc != 2)
		usage();
	
	ifs2.open(locationsFileName.c_str());

	while(ifs2 >> i)
		ifs2 >> locationsMap[i];

	ifs2.close();

	ifs.open(argv[1]);

	if(ifs.fail())
	{
		printf("problem with command line argument -- could not open file\n");
		usage();
	}

	while(getline(ifs,line))
	{
		SE = new SoundEvent(line);
		SEs.v.push_back(SE);
	}

	ifs.close();

	SEs.PrintEventsFormattedTreeHTML();
	

	return 0;
}






SoundEvent::SoundEvent(string s)
{
	int i;
	
	sscanf(s.c_str(),"%d/%d/%d %d:%d:%d %d %d",&month,&day,&year,&hour,&minute,&second,&id,&level);

	if(locationsMap.find(id) != locationsMap.end())
		location=locationsMap[id];
	else
		location="Location Not Set";

	secondOfDay = hour*3600 + minute*60 + second;

	dayOfYear = day;
	if(month>1)
		dayOfYear+=31;
	if(month>2)
	{
		dayOfYear+=28;
		if(year%4==0)
			dayOfYear++;
	}
	if(month>3)
		dayOfYear+=31;
	if(month>4)
		dayOfYear+=30;
	if(month>5)
		dayOfYear+=31;
	if(month>6)
		dayOfYear+=30;
	if(month>7)
		dayOfYear+=31;
	if(month>8)
		dayOfYear+=31;
	if(month>9)
		dayOfYear+=30;
	if(month>10)
		dayOfYear+=31;
	if(month>11)
		dayOfYear+=30;

	dayTotal=dayOfYear;
	for(i=2000; i<year; i++)
	{
		dayTotal+=365;
		if(i%4==0)
			dayTotal++;
	}

	//January 1, 2000 was a Saturday
	switch(dayTotal%7)
	{
		case 0: dayOfWeek=6; break;
		case 1: dayOfWeek=7; break;
		case 2: dayOfWeek=1; break;
		case 3: dayOfWeek=2; break;
		case 4: dayOfWeek=3; break;
		case 5: dayOfWeek=4; break;
		case 6: dayOfWeek=5; break;
		default: dayOfWeek=-1; break;
	}

	switch(dayOfWeek)
	{
		case 1:  dayOfWeekString = "Sunday"; break;
		case 2:  dayOfWeekString = "Monday"; break;
		case 3:  dayOfWeekString = "Tuesday"; break;
		case 4:  dayOfWeekString = "Wednesday"; break;
		case 5:  dayOfWeekString = "Thursday"; break;
		case 6:  dayOfWeekString = "Friday"; break;
		case 7:  dayOfWeekString = "Saturday"; break;
		default: dayOfWeekString = "ERROR ERROR ERROR ERROR ERROR ERROR"; break;
	}
}

void SoundEvent::PrintEvent()
{
	printf("month:  %d\nday:    %d\nweekday: %d\nyear:   %d\n\nhour:   %d\nminute: %d\nsecond: %d\n\ndayOfYear:  %d\ndayTotal:    %d\nsecondOfDay: %d\n\nid:    %d\nlevel: %d\n\n\n",
			month,day,dayOfWeek,year,hour,minute,second,dayOfYear,dayTotal,secondOfDay,id,level);
}
void SoundEvent::PrintEventOneLine()
{
	printf("%02d/%02d/%d %02d:%02d:%02d   id: %d   location: %s    dB level: %d\n",
			month,day,year,hour,minute,second,id,location.c_str(),level);
}

void SoundEvents::PrintEvents()
{
	int i;

	for(i=0; i<v.size(); i++)
		v[i]->PrintEvent();
}

void SoundEvents::PrintEventsOneLine()
{
	int i;

	for(i=0; i<v.size(); i++)
		v[i]->PrintEventOneLine();
}

void SoundEvents::PrintEventsFormattedTreeHTML()
{
	printf("<pre>\n");
	PrintEventsFormattedTree();
	printf("<\\pre>\n");
}

void SoundEvents::PrintEventsFormattedTree()
{
	multimap<int,SoundEvent*> z;
	multimap<int,SoundEvent*>::iterator zit;
	map<int,vector<SoundEvent*> > m;
	map<int,vector<SoundEvent*> >::iterator mit;
	int i;
	int lastHr;

	lastHr=-1;

	for(i=0; i<v.size(); i++)
		z.insert(make_pair(v[i]->secondOfDay,v[i]));
	for(zit=z.begin(); zit != z.end(); zit++)
		m[zit->second->id].push_back(zit->second);

	for(mit=m.begin(); mit != m.end(); mit++)
	{
		printf("ID%d: %s\n",mit->first,mit->second.at(0)->location.c_str());

		for(i=0; i<mit->second.size(); i++)
		{
			if(mit->second.at(i)->hour != lastHr)
			{
				printf("    %02d:00:00 - %02d:59:59\n",mit->second.at(i)->hour,mit->second.at(i)->hour);
				lastHr=mit->second.at(i)->hour;
			}
			printf("        ");
			mit->second.at(i)->PrintEventOneLine();
		}
	}
}


void SoundEvents::AnalyzeAndPrint_dayOfWeek()
{
	map<int,vector<SoundEvent*> > m;
	multimap<int,int> mkeys; //first is size of m[second]
	map<int,vector<SoundEvent*> >::iterator mit1;
	multimap<int,int>::reverse_iterator mitint;
	int i;

	for(i=0; i<v.size(); i++)
		m[v[i]->dayOfWeek].push_back(v[i]);
	for(mit1=m.begin(); mit1 != m.end(); mit1++)
		mkeys.insert(make_pair(mit1->second.size(),mit1->first));
	
	for(mitint=mkeys.rbegin(); mitint != mkeys.rend(); mitint++)
	{
		printf("There's %d instance(s) on %ss:\n",mitint->first,m[mitint->second][0]->dayOfWeekString.c_str());
		for(i=0; i<mitint->first; i++)
		{
			printf("    ");
			m[mitint->second][i]->PrintEventOneLine();
		}
		printf("\n");
	}
	printf("\n\n\n");
}


void SoundEvents::AnalyzeAndPrint_hour()
{
	map<int,vector<SoundEvent*> > m;
	multimap<int,int> mkeys; //first is size of m[second]
	map<int,vector<SoundEvent*> >::iterator mit1;
	multimap<int,int>::reverse_iterator mitint;
	int i;

	for(i=0; i<v.size(); i++)
		m[v[i]->hour].push_back(v[i]);
	for(mit1=m.begin(); mit1 != m.end(); mit1++)
		mkeys.insert(make_pair(mit1->second.size(),mit1->first));
	

	for(mitint=mkeys.rbegin(); mitint != mkeys.rend(); mitint++)
	{
		printf("There's %d instance(s) between %02d:00:00 and %02d:59:59:\n",mitint->first,m[mitint->second][0]->hour,m[mitint->second][0]->hour);
		for(i=0; i<mitint->first; i++)
		{
			printf("    ");
			m[mitint->second][i]->PrintEventOneLine();
		}
		printf("\n");
	}
	printf("\n\n\n");
}



void SoundEvents::AnalyzeAndPrint_id()
{
	map<int,vector<SoundEvent*> > m;
	multimap<int,int> mkeys; //first is size of m[second]
	map<int,vector<SoundEvent*> >::iterator mit1;
	multimap<int,int>::reverse_iterator mitint;
	int i;

	for(i=0; i<v.size(); i++)
		m[v[i]->id].push_back(v[i]);
	for(mit1=m.begin(); mit1 != m.end(); mit1++)
		mkeys.insert(make_pair(mit1->second.size(),mit1->first));
	

	for(mitint=mkeys.rbegin(); mitint != mkeys.rend(); mitint++)
	{
		printf("There's %d instance(s) from device id#%d:\n",mitint->first,m[mitint->second][0]->id);
		for(i=0; i<mitint->first; i++)
		{
			printf("    ");
			m[mitint->second][i]->PrintEventOneLine();
		}
		printf("\n");
	}
	printf("\n\n\n");
}

	

void SoundEvents::AnalyzeAndPrint_level()
{
	map<int,vector<SoundEvent*> > m;
	multimap<int,int> mkeys; //first is size of m[second]
	map<int,vector<SoundEvent*> >::iterator mit1;
	multimap<int,int>::reverse_iterator mitint;
	int i;

	for(i=0; i<v.size(); i++)
		m[((v[i]->level)/10)*10].push_back(v[i]);
	for(mit1=m.begin(); mit1 != m.end(); mit1++)
		mkeys.insert(make_pair(mit1->second.size(),mit1->first));
	

	for(mitint=mkeys.rbegin(); mitint != mkeys.rend(); mitint++)
	{
		printf("There's %d instance(s) between %ddB and %ddB:\n",mitint->first,((m[mitint->second][0]->level)/10)*10,((m[mitint->second][0]->level)/10)*10+9);
		for(i=0; i<mitint->first; i++)
		{
			printf("    ");
			m[mitint->second][i]->PrintEventOneLine();
		}
		printf("\n");
	}
	printf("\n\n\n");
}
