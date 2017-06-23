#include<iostream>
using namespace std;
class Date
{
private:
	int year,month,day;
public:
	void SetDate(int y,int m,int n);
	void Print();
};
void Date::SetDate(int y,int m,int n)
{
	year=y;
	month=m;
	day=n;
}
void Date::Print()
{
	cout<<year<<".";
	if(month<10) cout<<"0";
	cout<<month<<".";
	if(day<10) cout<<"0";
	cout<<day<<endl;
}
int main()
{
	Date NationalDay,today;
	int year,month,day;
	NationalDay.SetDate(1949,10,1);
	cout<<"please input a date(yy--mm--dd)";
	cin>>year>>month>>day;
	today.SetDate(year,month,day);
	cout<<"National Day is";
	NationalDay.Print();
	cout<<"Today is";
	today.Print();
	return 0;
}
