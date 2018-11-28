#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <locale.h>

int m_len[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const char* m_name[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
const char* d_name[7] = { "Monday","Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};


struct Smonth
{
	int	number; //Количество дней в месяце
	int *date; //Массив названий дней
	char *name; //Название месяца
	int t; // Номер месяца
};



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



/*Вывод календаря в консоль*/
void p_month(Smonth *m, int j)
{
	printf("            %s\n", m_name[j]);
	printf("___________________________\n");
	printf(" Пн  Вт  Ср  Чт  Пт  Сб  Вс\n\n");



	for (int i = 1; i <= m->number; i++)
	{
		printf("%3d ", i);
		if (m->date[i] % 7 == 0)
			printf("\n");
	}
	printf("\n\n\n");
}

/*Запись календаря в файл*/
void fp_month(FILE* f, Smonth *m, int j)
{
	fprintf(f, "            %s\n", m_name[j]);
	/*fputs(m_name[j], f);*/
	fprintf(f, "___________________________\n");
	fprintf(f, " Пн  Вт  Ср  Чт  Пт  Сб  Вс\n\n");

	for (int i = 1; i <= m->number; i++)
	{
		fprintf(f, "%4d", i);
		if (m->date[i] % 7 == 0)
			fprintf(f, "\n");
	}
	fprintf(f, "\n\n\n");
}


void p_year(FILE* f, Smonth m[], int size, int name, int date)
{
	int selection;
	for (int i = 0; i < size; i++)
	{
		p_month(&m[i], name);
		name++;
	}

	printf("Save calendar?\n1. Yes\n2. No\n");
	scanf_s("%d", &selection);
	switch (selection)
	{
	case 1:
		for (int i = 0; i < size; i++)
		{
			fp_month(f, &m[i], name);
			name++;
		}
		break;

	case 2:
		exit(2);
	}
}


//
//void counting_days()
//{
//
//	int month;
//	int day;
//	int year, Feb, count = 0;
//	int i = 0, j = 0, k = 0;
//
//	time_t current_time;
//	struct tm  local_time;
//
//	time(&current_time);
//	localtime_s(&local_time, &current_time);
//
//	int Year = local_time.tm_year + 1900;
//	int Month = local_time.tm_mon + 1;
//	int Day = local_time.tm_mday;
//
//	printf("%d, %d, %d\n", Day, Month, Year);
//
//	printf("Enter date: ");
//	scanf_s("%d", &day);
//	printf("\nEnter month: ");
//	scanf_s("%d", &month);
//	printf("\nEnter the year: ");
//	scanf_s("%d", &year);
//	printf("\n");
//
//	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
//		Feb = 29;
//	else
//		Feb = 28;
//	m_len[1] = Feb;
//
//	for (i = Year; i <= year; i++)
//	{
//		for (k = Month; k <= 12; k++)
//		{
//			for (j = Day; j <= m_len[k - 1]; j++)
//			{
//				if ((i == year) && (k == month) && (j == day))
//				{
//					printf("count = %d\n", count);
//					break;
//				}
//				else
//					count++;
//			}
//			Day = 1;
//		}
//		Month = 1;
//	}
//}

//
//void day_of_week(int Month, int Data, int Day)
//{
//	int data, month;
//	printf("input month and data: ");
//	scanf_s("%d", &month);
//	scanf_s("%d", &data);
//	for (int k = Month; k <= 12; k++)
//	{
//		for (int j = data; j <= m_len[k - 1]; j++)
//		{
//			if ((k == month) && (j == data))
//			{
//				printf("day of week = %s\n", d_name[7 - Day%7]);
//				break;
//			}
//			else
//				Day++;
//		}
//		Data = 1;
//	}
//}

void Input(int month, int day, int date, int year)
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

void Calendar_output()
{
	FILE *f;
	fopen_s(&f, "calendar.txt", "w");

	int month=0;
	int day=0;
	int date=0;
	int year=0, Feb=0;

	Input(month, day, date, year);
	
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		Feb = 29;
	else
		Feb = 28;
	m_len[1] = Feb;

	Smonth* m = (Smonth*) malloc ((12 - month + 1) * sizeof(Smonth));
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

	p_year(f, m, (12 - month + 1), month-1, date);
	
	fclose(f);
}


void main()
{
	setlocale(LC_ALL, "Russian");


	//int month=0;
	//int day=0;
	//int date=0;
	//int year=0, Feb=0;

	//Input(month, day, date, year);
	//day_of_week(month, date, day);







	Calendar_output();
	//counting_days();
	system("pause");
}