#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <sys/stat.h>
#include <string>
using namespace std;
struct commodity
{
    string commodityـname;//1
    int commodity_inventory;//2
    int commodity_price;//3
    string customer_name;//نام مشتری4
    string customer_last_name;//نام خانوادگی مشتری5
    string customer_phone_number;//شماره تلفن مشتری6
    string date;//تاریخ ثبت سفارش7
    int number_of_types_of_goods;//تعداد انواع کالا8
    int customer_commodity_index[100];//ایندکس کالاهای سفارش داده شده9
    int number_of_commodity[100];//تعداد کالای سفارش داده شده10
    int the_final_price;//قیمت نهایی سفارش11
};
class store
{
private:
    commodity a[1000];
public:
    fstream file[14];
    void add_commodity();
    void commodities();
    void place_an_order();
    void view_orders();
    void Turnover();
    void create_folder_and_file();
    void write();
    void read();
    void close_file();
    string current_time1();
}c;
int i = 0, k = 0;//12,13
int main()
{
    c.create_folder_and_file();
    c.read();
    int x;
    while (true)
    {
        cout << "sabt mahsool:1 , mahsoolat:2 , sabt sefaresh:3 , sefareshat:4 , gardesh mali:5\n";
        cin >> x;
        if (x == 1)
            c.add_commodity();
        else if (x == 2)
            c.commodities();
        else if (x == 3)
            c.place_an_order();
        else if (x == 4)
            c.view_orders();
        else if (x == 5)
            c.Turnover();
        else break;
    }
    c.write();
    c.close_file();
}
void store::add_commodity()//ثبت محصول
{
    cout << "Enter the product name\n";
    cin >> a[i].commodityـname;//دریافت نام کالای جدید
    cout << "Enter the inventory\n";
    cin >> a[i].commodity_inventory;//دریافت موجودی کالای جدید
    cout << "Enter the price of the product\n";
    cin >> a[i].commodity_price;//دریافت قیمت کالای جدید
    i++;
    cout << "add commodity done.\n";
}
void store::commodities()//محصولات
{
    int x;
    for (int j = 0; j < i; j++)
    {
        cout << "commodity" << j << ": " << a[j].commodityـname << "\t" << a[j].commodity_inventory << "\n";
    }
    while (true)
    {
        cout << "If you want to change the inventory of a product, enter its code\nOtherwise, enter -1\n";
        cin >> x;
        if (x >= 0 && x < i)
        {
            cout << "Enter the new inventory\n";
            cin >> a[x].commodity_inventory;
            cout << "done\n";
        }
        else break;
    }
}
void store::place_an_order()//ثبت سفارش
{
    int d;
    a[k].the_final_price = 0;
    cout << "Enter the number of types of products you want to order\n";
    cin >> a[k].number_of_types_of_goods;//تعداد نوع کالاهایی که میخواد سفارش بده
    for (int j = 0; j < a[k].number_of_types_of_goods; j++)
    {
        cout << "Enter the desired product ID.\nAnd then enter the number you want.\n";
    lbl_for: cin >> a[k].customer_commodity_index[j] >> a[k].number_of_commodity[j];
        if (a[a[k].customer_commodity_index[j]].commodity_inventory < a[k].number_of_commodity[j])
        {
            cout << "Insufficient inventory\n" << "There are " << a[a[k].customer_commodity_index[j]].commodity_inventory << " items in stock\n";
            if (a[a[k].customer_commodity_index[j]].commodity_inventory == 0)
            {
                a[k].number_of_commodity[j] = 0;
                continue;
            }
            else goto lbl_for;
        }
        else
        {
            a[a[k].customer_commodity_index[j]].commodity_inventory -= a[k].number_of_commodity[j];
            a[k].the_final_price += a[k].number_of_commodity[j] * a[a[k].customer_commodity_index[j]].commodity_price;
        }
    }
    cout << "Enter your first name, then your last name, then your phone number\n";
    cin >> a[k].customer_name >> a[k].customer_last_name >> a[k].customer_phone_number;
    a[k].date = current_time1();
    cout << "Enter the discount percentage\n";
    cin >> d;
    d = 100 - d;
    a[k].the_final_price *= d;
    a[k].the_final_price /= 100;
    k++;
}
void store::view_orders()//سفارشات
{
    int x;
    for (int j = k-1; j >= 0; j--)
        cout << j << "\t" << a[j].customer_last_name << "\t" << a[j].the_final_price << "\t"<< a[j].date << "\n";
    while (true)
    {
        cout << "Enter the order code to view order details.\nOtherwise, enter -1\n";
        cin >> x;
        if (x >= 0 && x < k)
        {
            cout << a[x].customer_name << "\t" << a[x].customer_last_name << "\n" << a[x].customer_phone_number << "\n" << a[x].date << "\n";
            for (int j = 0; j < a[x].number_of_types_of_goods; j++)
                cout << a[a[x].customer_commodity_index[j]].commodityـname << "\t" << a[x].number_of_commodity[j] << "\n";
            cout << a[x].the_final_price << "\n";
        }
        else break;
    }
}
void store::Turnover()//گردش مالی
{
    int x, s = 0, number;
    string date1, date2, year1, month1, day1, hour1, year2, month2, day2, hour2, y;
    cout << "If you want the turnover of the last month to be displayed by default, enter the 1\nOtherwise, enter the 2\n";
    cin >> x;
    if (x == 1)
    {
        date2 = current_time1();
        date1 = date2;
        if (date1.substr(6, 2) != "01")
        {
            number = std::stoi(date1.substr(6, 2));
            number--;
            if (number < 10)
            {
                y = "0" + to_string(number);
            }
            else y = to_string(number);
            date1.replace(6, 2, y);
        }
        else
        {
            number = std::stoi(date1.substr(0, 4));
            number--;
            y = to_string(number);
            date1.replace(0, 4, y);
            date1.replace(6, 2, "12");
        }
    }
    else if (x == 2)
    {
        cout << "Enter the beginning of the time range:\nEnter the year:\n";
        cin >> year1;
        cout << "Enter the month:\n";
        cin >> month1;
        cout << "Enter the day:\n";
        cin >> day1;
        cout << "Enter the hour:\n";
        cin >> hour1;
        cout << "Enter the end of the time range:\nEnter the year:\n";
        cin >> year2;
        cout << "Enter the month:\n";
        cin >> month2;
        cout << "Enter the day:\n";
        cin >> day2;
        cout << "Enter the hour:\n";
        cin >> hour2;
        date1 = year1 + " " + month1 + " " + day1 + " " + hour1;
        date2 = year2 + " " + month2 + " " + day2 + " " + hour2;
    }
    for (int j = 0; j < k; j++)
    {
        if (a[j].date >= date1 && a[j].date <= date2)
        {
            cout << a[j].date << "\t" << a[j].the_final_price << "\n";
            s += a[j].the_final_price;
        }
    }
    cout << "total= " << s << "\n";
}
void store::create_folder_and_file()
{
    bool flag = false;
    string foldername = "appfolder";
    string command = "mkdir " + string(foldername);
    if (system(command.c_str()) != 0)
    {
        cerr << "There was an error creating the folder\n";
        flag = true;
    }
    for (int j = 1; j < 14; j++)
    {
        string path = "appfolder/file" + to_string(j) + ".txt";
        if (flag)
            file[j].open(path);
        else
        {
            file[j].open(path, std::fstream::out);
        }
        if (!(file[j].is_open()))
            cout << "Error opening the file" + to_string(j) + ".txt\n";
    }
    for (int j = 12; j < 14; j++)
    {
        file[j].seekp(0, std::ios::end);
        if (file[j].tellp() == 0)
            file[j] << "0\n";
    }
}
void store::read()
{
    for (int j = 12; j < 14; j++)
        file[j].seekg(0, std::ios::beg);
    file[12] >> i;
    file[13] >> k;
    for (int j=0;j<i; j++)
    {
        file[1] >> a[j].commodityـname;
        file[2] >> a[j].commodity_inventory;
        file[3] >> a[j].commodity_price;
    }
    for (int j=0;j<k; j++)
    {
        file[4] >> a[j].customer_name;
        getline(file[5], a[j].customer_last_name);
        getline(file[6], a[j].customer_phone_number);
        getline(file[7], a[j].date);
        file[8] >> a[j].number_of_types_of_goods;
        for (int l = 0; l < a[j].number_of_types_of_goods; l++)
        {
            file[9] >> a[j].customer_commodity_index[l];
            file[10] >> a[j].number_of_commodity[l];
        }
        file[11] >> a[j].the_final_price;
    }
}
void store::write()
{
    for (int j = 1; j < 14; j++)
        file[j].seekp(0, std::ios::beg);
    for (int j = 0; j < i; j++)
    {
        file[1] << a[j].commodityـname << "\n";
        file[2] << a[j].commodity_inventory << "\n";
        file[3] << a[j].commodity_price << "\n";
    }
    for (int j = 0; j < k; j++)
    {
        file[4] << a[j].customer_name << "\n";
        file[5] << a[j].customer_last_name << "\n";
        file[6] << a[j].customer_phone_number << "\n";
        file[7] << a[j].date << "\n";
        file[8] << a[j].number_of_types_of_goods << "\n";
        for (int l = 0; l < a[j].number_of_types_of_goods; l++)
        {
            file[9] << a[j].customer_commodity_index[l] << "\n";
            file[10] << a[j].number_of_commodity[l] << "\n";
        }
        file[11] << a[j].the_final_price << "\n";
    }
    for (int j = 12; j < 14; j++)
        file[j].seekp(0, std::ios::beg);
    file[12] << i << "\n";
    file[13] << k << "\n";
}
void store::close_file()
{
    for (int j = 1; j < 14; j++)
        file[j].close();
}
string store::current_time1()
{
    auto current_time = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(current_time);
    char time_str[26];
    ctime_s(time_str, sizeof(time_str), &time);
    string x = string(time_str);
    string y;
    string s = x.substr(4, 3);
    if (s== "Jan")
        y = x.substr(20, 4) + " 01 " + x.substr(8, 2) + " " + x.substr(11, 8);
    else if (s=="Feb")
        y = x.substr(20, 4) + " 02 " + x.substr(8, 2) + " " + x.substr(11, 8);
    else if (s == "Mar")
        y = x.substr(20, 4) + " 03 " + x.substr(8, 2) + " " + x.substr(11, 8);
    else if (s == "Apr")
        y = x.substr(20, 4) + " 04 " + x.substr(8, 2) + " " + x.substr(11, 8);
    else if (s == "May")
        y = x.substr(20, 4) + " 05 " + x.substr(8, 2) + " " + x.substr(11, 8);
    else if (s == "Jun")
        y = x.substr(20, 4) + " 06 " + x.substr(8, 2) + " " + x.substr(11, 8);
    else if (s == "Jul")
        y = x.substr(20, 4) + " 07 " + x.substr(8, 2) + " " + x.substr(11, 8);
    else if (s == "Aug")
        y = x.substr(20, 4) + " 08 " + x.substr(8, 2) + " " + x.substr(11, 8);
    else if (s == "Sep")
        y = x.substr(20, 4) + " 09 " + x.substr(8, 2) + " " + x.substr(11, 8);
    else if (s == "Oct")
        y = x.substr(20, 4) + " 10 " + x.substr(8, 2) + " " + x.substr(11, 8);
    else if (s == "Nov")
        y = x.substr(20, 4) + " 11 " + x.substr(8, 2) + " " + x.substr(11, 8);
    else if (s == "Dec")
        y = x.substr(20, 4) + " 12 " + x.substr(8, 2) + " " + x.substr(11, 8);
    return y;
}