#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <locale.h>

#define menuSize 5

int m_len[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const char* m_name[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
const char* d_name[7] = { "Monday","Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
const char* menu[menuSize] = { "Output and saving of the calendar", "Output day of week","Counting days","Generation of calendar", "Exit" };

int menuIndex = 0;

struct Smonth
{
	int	number; //Количество дней в месяце
	int *date; //Массив названий дней
	char *name; //Название месяца
	int t; // Номер месяца
};

/*Определение длинны февраля*/
void Febrary(int year)
{
	int Feb;
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		Feb = 29;
	else
		Feb = 28;
	m_len[1] = Feb;
}

/*Ввод данных для печати календаря, сохранения и вывода названия дня недели*/
void input(int &year, int &month, int &date, int &day)
{
	printf("Enter the day of the week: ");
	scanf_s("%d", &day);
	printf("\nEnter date: ");
	scanf_s("%d", &date);
	printf("\nEnter month: ");
	scanf_s("%d", &month);
	printf("\nEnter the year: ");
	scanf_s("%d", &year);
	printf("\n");
}


/*Сохранение информации о последнем дне месяца*/
int f_month(int startDay, Smonth *m)
{
	m->date = (int*)malloc(m->number * (sizeof(int)));

	for (int i = 0; i < m->number; i++)
	{
		m->date[i] = startDay;
		startDay++;
		if (startDay > 7)
			startDay = 1;
	}
	return startDay;
}


/*Вывод месяца в консоль*/
void p_month(Smonth *m, int j)
{
	printf("            %s\n", m_name[j]);
	printf("___________________________\n");
	printf(" Mn  Tu  We  Th  Fr  St  Sn\n\n");

	for (int k = 1; k <= m->date[0]; k++)
		printf( "    ");
	for (int i = 1; i <= m->number; i++)
	{
		printf("%3d ", i);
		if (m->date[i] % 7 == 0)
			printf("\n");
	}
	printf("\n\n\n");
}


/*Запись месяца в файл*/
void fp_month(FILE* f, Smonth *m, int j)
{
	fprintf(f, "            %s\n", m_name[j]);
	fprintf(f, "___________________________\n");
	fprintf(f, " Mn  Tu  We  Th  Fr  St  Sn\n\n");

	for (int i = 1; i <= m->number; i++)
	{
		fprintf(f, "%4d", i);
		if (m->date[i] % 7 == 0)
			fprintf(f, "\n");
	}
	fprintf(f, "\n\n\n");
}

/*Печать года состоящего из месяцев + выбор для сохранения*/
void p_year(FILE* f, Smonth m[], int size, int name, int date)
{
	int j = name;
	int selection;
	for (int i = 0; i < size; i++)
	{
		p_month(&m[i], j);
		j++;
	}

	printf("Save calendar?\n1. Yes\n2. No\n");
	scanf_s("%d", &selection);
	switch (selection)
	{
	case 1:
		j = name;
		for (int i = 0; i < size; i++)
		{
			fp_month(f, &m[i], j);
			j++;
		}
		break;

	case 2:
		exit(2);
		break;
	}
}

/*Печать календаря*/
void Calendar_output(int year, int month, int date, int day)
{
	FILE *f;
	fopen_s(&f, "calendar.txt", "w");

	input(year, month, date, day);

	Febrary(year);

	Smonth* m = (Smonth*)malloc((12 - month + 1) * sizeof(Smonth));
	for (int i = 0; i < (12 - month + 1); i++)
	{
		m[i].t = month + i - 1; // Порядковый номер месяца с 0
		m[i].number = m_len[m[i].t]; // Длина месяца
	}

	int start_date = (day - ((day / 7) * 7)) - date;
	start_date = start_date % 7;

	for (int i = 0; i < (12 - month + 1); i++)
	{
		start_date = f_month(start_date, &m[i]);
	}

	p_year(f, m, (12 - month + 1), month - 1, date);

	fclose(f);
}

/*Определения дня недели*/
void day_of_week(int Month, int Date, int Day)
{
	int searchData, searchMonth;
	printf("input month: ");
	scanf_s("%d", &searchMonth);
	printf("input data: ");
	scanf_s("%d", &searchData);
	for (int k = Month; k <= 12; k++)
	{
		for (int j = Date; j <= m_len[k - 1]; j++)
		{
			if ((k == searchMonth) && (j == searchData))
			{
				printf("day of week = %s\n", d_name[((Day - ((Day / 7) * 7)) - Date)%7]);
				break;
			}
			else
				Day++;
		}
		Date = 1;
	}
}

/*Подсчет дней от текущей даты до искомой*/
void counting_days(int year, int month, int date)
{

	time_t current_time;
	struct tm  local_time;

	time(&current_time);
	localtime_s(&local_time, &current_time);

	int currentYear = local_time.tm_year + 1900;
	int currentMonth = local_time.tm_mon + 1;
	int currentDay = local_time.tm_mday;

	printf("%d.%d.%d\n", currentDay, currentMonth, currentYear);

	int count = 0;
	
	printf("\nEnter date: ");
	scanf_s("%d", &date);
	printf("\nEnter month: ");
	scanf_s("%d", &month);
	printf("\nEnter the year: ");
	scanf_s("%d", &year);
	printf("\n");

	Febrary(year);

	for (int i = currentYear; i <= year; i++)
	{
		for (int k = currentMonth; k <= 12; k++)
		{
			for (int j = currentDay; j <= m_len[k - 1]; j++)
			{
				if ((i == year) && (k == month) && (j == date))
				{
					printf("count = %d\n", count);
					break;
				}
				else
					count++;
			}
			currentDay = 1;
		}
		currentMonth = 1;
	}
}

void punct1(int year, int month, int date, int day)
{

	system("cls");
	printf("Output and saving of the calendar\n");
	Calendar_output(year, month, date, day);
	printf(">:^3\n");
	system("pause");
	_getch();
}

void punct2(int month, int date, int day)
{
	system("cls");
	printf("Output day of week\n\n");

	printf("Enter calendar generation data\n\n");
	printf("Enter the day of the week: ");
	scanf_s("%d", &day);
	printf("\nEnter date: ");
	scanf_s("%d", &date);
	printf("\nEnter month: ");
	scanf_s("%d", &month);

	printf("\n\nEnter new data\n\n");
	day_of_week(month, date, day);
	printf("}:->\n");
	system("pause");
	_getch();
}
void punct3(int year, int month, int date, int day)
{
	system("cls");
	printf("Counting days\n");
	counting_days(year, month, date);
	printf("*->->\n");
	system("pause");
	_getch();
}
void punct4()
{
	system("cls");
	printf("Generation of calendar\n");
	printf("(:\/)\n");
	system("pause");
	_getch();
}

	
int main()
{
	int month = 0;
	int day = 0;
	int date = 0;
	int year = 0;
	while (1)
	{
		system("cls");
		for (int i = 0; i < menuSize; i++)
		{
			if (i == menuIndex) printf("=> ");
			else
				printf("%d ", i + 1);
			printf("%s\n", menu[i]);


		}
		unsigned char c = _getch();
		if (c == 80) menuIndex++;
		if (c == 72) menuIndex--;
		if (menuIndex > menuSize - 1) menuIndex = menuSize - 1;
		if (menuIndex < 0) menuIndex = 0;
		if (c == 13)
			switch (menuIndex)
			{
			case 0: punct1(year, month, date, day); break;
			case 1: punct2(month, date, day); break;
			case 2: punct3(year, month, date, day); break;
			case 3: punct4(); break;
			case 4: return 0;
			}
	}
	return 0;
}


